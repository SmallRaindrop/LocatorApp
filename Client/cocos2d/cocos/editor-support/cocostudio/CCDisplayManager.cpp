/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "cocostudio/CCDisplayManager.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCUtilMath.h"
#include "cocostudio/CCSkin.h"

#include "CCParticleSystemQuad.h"

using namespace cocos2d;

namespace cocostudio {

DisplayManager *DisplayManager::create(Bone *bone)
{
    DisplayManager *pDisplayManager = new DisplayManager();
    if (pDisplayManager && pDisplayManager->init(bone))
    {
        pDisplayManager->autorelease();
        return pDisplayManager;
    }
    CC_SAFE_DELETE(pDisplayManager);
    return nullptr;
}


DisplayManager::DisplayManager()
    : _displayRenderNode(nullptr)
    , _displayType(CS_DISPLAY_MAX)
    , _currentDecoDisplay(nullptr)
    , _displayIndex(-1)
    , _forceChangeDisplay(false)
    , _visible(true)
    , _bone(nullptr)
{
}

DisplayManager::~DisplayManager()
{
	clearDisplayList();

    if( _displayRenderNode )
    {
        _displayRenderNode->removeFromParentAndCleanup(true);
        if(_displayRenderNode->getReferenceCount() > 0)
            CC_SAFE_RELEASE_NULL(_displayRenderNode);
    }

}

bool DisplayManager::init(Bone *bone)
{
    bool ret = false;

    do
    {

        _bone = bone;

        initDisplayList(bone->getBoneData());

        ret = true;
    }
    while (0);

    return ret;
}


void DisplayManager::addDisplay(DisplayData *displayData, int index)
{
    DecorativeDisplay *decoDisplay = nullptr;

    if( (index >= 0) && (index < (int)_decoDisplayList.size()) )
    {
        decoDisplay = (DecorativeDisplay *)getDecorativeDisplayByIndex(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
		decoDisplay->retain();
        _decoDisplayList.push_back(decoDisplay);
    }

    DisplayFactory::addDisplay(_bone, decoDisplay, displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayWithIndex(index, false);
    }
}

void DisplayManager::addDisplay(Node *display, int index)
{
    DecorativeDisplay *decoDisplay = nullptr;

    if( (index >= 0) && (index < (int)_decoDisplayList.size()) )
    {
        decoDisplay = getDecorativeDisplayByIndex(index);
    }
    else
    {
        decoDisplay = DecorativeDisplay::create();
		decoDisplay->retain();
        _decoDisplayList.push_back(decoDisplay);
    }

    DisplayData *displayData = nullptr;
    if (Skin *skin = dynamic_cast<Skin *>(display))
    {
        skin->setBone(_bone);
        displayData = SpriteDisplayData::create();

        DisplayFactory::initSpriteDisplay(_bone, decoDisplay, skin->getDisplayName().c_str(), skin);

        if (SpriteDisplayData *spriteDisplayData = (SpriteDisplayData *)decoDisplay->getDisplayData())
        {
            skin->setSkinData(spriteDisplayData->skinData);
            ((SpriteDisplayData *)displayData)->skinData = spriteDisplayData->skinData;
        }
        else
        {
            bool find = false;

            for (long i = _decoDisplayList.size()-2; i>=0; i--)
            {
                DecorativeDisplay *dd = getDecorativeDisplayByIndex(i);
                SpriteDisplayData *sdd = static_cast<SpriteDisplayData*>(dd->getDisplayData());
                if (sdd)
                {
                    find = true;
                    skin->setSkinData(sdd->skinData);
                    static_cast<SpriteDisplayData*>(displayData)->skinData = sdd->skinData;
                    break;
                }
            }

            if (!find)
            {
                BaseData baseData;
                skin->setSkinData(baseData);
            }
        }
    }
    else if (dynamic_cast<ParticleSystemQuad *>(display))
    {
        displayData = ParticleDisplayData::create();

        display->removeFromParent();
        display->cleanup();
        
        Armature *armature = _bone->getArmature();
        if (armature)
        {
            display->setParent(armature);
        }
    }
    else if(Armature *armature = dynamic_cast<Armature *>(display))
    {
        displayData = ArmatureDisplayData::create();
        displayData->displayName = armature->getName();
        armature->setParentBone(_bone);
    }
    else
    {
        displayData = DisplayData::create();
    }

    decoDisplay->setDisplay(display);
    decoDisplay->setDisplayData(displayData);

    //! if changed display index is current display index, then change current display to the new display
    if(index == _displayIndex)
    {
        _displayIndex = -1;
        changeDisplayWithIndex(index, false);
    }
}

void DisplayManager::removeDisplay(int index)
{
    if(index == _displayIndex)
    {
        setCurrentDecorativeDisplay(nullptr);
        _displayIndex = -1;
    }

	DecorativeDisplay *dd = _decoDisplayList.at(index);
	CC_SAFE_RELEASE(dd);
    _decoDisplayList.erase(_decoDisplayList.begin()+index);
}

const std::vector<DecorativeDisplay*>& DisplayManager::getDecorativeDisplayList() const
{
    return _decoDisplayList;
}

void DisplayManager::changeDisplayWithIndex(int index, bool force)
{
    //CCASSERT( index < (int)_decoDisplayList.size(), "the _index value is out of range");

    _forceChangeDisplay = force;

    //! If index is equal to current display index,then do nothing
    if ( _displayIndex == index)
        return;


    _displayIndex = index;

    //! If displayIndex < 0, it means you want to hide you display
    if (_displayIndex < 0)
    {
        if(_displayRenderNode)
        {
            _displayRenderNode->removeFromParentAndCleanup(true);
            setCurrentDecorativeDisplay(nullptr);
        }
        return;
    }

    DecorativeDisplay *decoDisplay = getDecorativeDisplayByIndex(_displayIndex);
	if ( decoDisplay )
	{
		setCurrentDecorativeDisplay(decoDisplay);
	}
}

void CCDisplayManager::changeDisplayWithName(const std::string& name, bool force)
{
    for (size_t i = 0; i<_decoDisplayList.size(); i++)
    {
        if (getDecorativeDisplayByIndex(i)->getDisplayData()->displayName == name)
        {
            changeDisplayWithIndex(i, force);
            break;
        }
    }
}

void DisplayManager::setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay)
{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(false);
    }
#endif

    _currentDecoDisplay = decoDisplay;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (_currentDecoDisplay && _currentDecoDisplay->getColliderDetector())
    {
        _currentDecoDisplay->getColliderDetector()->setActive(true);
    }
#endif

    Node *displayRenderNode = _currentDecoDisplay == nullptr ? nullptr : _currentDecoDisplay->getDisplay();
    if (_displayRenderNode)
    {
        if (dynamic_cast<Armature *>(_displayRenderNode) != nullptr)
        {
            _bone->setChildArmature(nullptr);
        }
        _displayRenderNode->removeFromParentAndCleanup(true);
        _displayRenderNode->release();
    }

    _displayRenderNode = displayRenderNode;

    if(_displayRenderNode)
    {
        if (Armature *armature = dynamic_cast<Armature *>(_displayRenderNode))
        {
            _bone->setChildArmature(armature);
            armature->setParentBone(_bone);
        }
        else if (ParticleSystemQuad *particle = dynamic_cast<ParticleSystemQuad *>(_displayRenderNode))
        {
            particle->resetSystem();
        }

        _displayRenderNode->setColor(_bone->getDisplayedColor());
        _displayRenderNode->setOpacity(_bone->getDisplayedOpacity());

        _displayRenderNode->retain();
        _displayRenderNode->setVisible(_visible);

        _displayType = _currentDecoDisplay->getDisplayData()->displayType;
    }
    else
    {
        _displayType =  CS_DISPLAY_MAX;
    }
}

Node *DisplayManager::getDisplayRenderNode() const
{
    return _displayRenderNode;
}


DisplayType DisplayManager::getDisplayRenderNodeType() const
{
    return _displayType;
}

int DisplayManager::getCurrentDisplayIndex() const
{
    return _displayIndex;
}

DecorativeDisplay *DisplayManager::getCurrentDecorativeDisplay() const
{
    return _currentDecoDisplay;
}

DecorativeDisplay *DisplayManager::getDecorativeDisplayByIndex( int index)
{
	if ( index < 0 || index >= (int)_decoDisplayList.size() )
	{
		return nullptr;
	}
	
	DecorativeDisplay *decoDisplay = (DecorativeDisplay *)_decoDisplayList.at(index);
	if ( !decoDisplay )
	{
		DisplayData *displayData = _bone->getBoneData()->getDisplayData(_displayIndex);
		if ( displayData )
		{
			decoDisplay = DecorativeDisplay::create();
			decoDisplay->retain();
			decoDisplay->setDisplayData(displayData);
			DisplayFactory::createDisplay(_bone, decoDisplay);
			_decoDisplayList[index] = decoDisplay;
		}
	}

    return decoDisplay;
}

void DisplayManager::initDisplayList(BoneData *boneData)
{
    clearDisplayList();

    CS_RETURN_IF(!boneData);

	_decoDisplayList.resize(boneData->displayDataList.size());

	/*for(auto& object : boneData->displayDataList)
	{
	DisplayData *displayData = static_cast<DisplayData *>(object);

	DecorativeDisplay *decoDisplay = DecorativeDisplay::create();
	decoDisplay->setDisplayData(displayData);

	DisplayFactory::createDisplay(_bone, decoDisplay);

	_decoDisplayList.push_back(decoDisplay);
	}*/
}

void DisplayManager::clearDisplayList()
{
	for ( size_t i = 0;i<_decoDisplayList.size();++i )
	{
		CC_SAFE_RELEASE(_decoDisplayList[i]);
	}
	_decoDisplayList.clear();
}

bool DisplayManager::containPoint(Point &point)
{
    if(!_visible || _displayIndex < 0)
    {
        return false;
    }

    bool ret = false;

    switch (_currentDecoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        /*
         *  First we first check if the point is in the sprite content rect. If false, then we continue to check
         *  the contour point. If this step is also false, then we can say the bone not contain this point.
         *
         */

        Point outPoint = Point(0, 0);

        Sprite *sprite = (Sprite *)_currentDecoDisplay->getDisplay();
        sprite = (Sprite *)sprite->getChildByTag(0);

        ret = CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint);

    }
    break;

    default:
        break;
    }
    return ret;
}

bool DisplayManager::containPoint(float x, float y)
{
    Point p = Point(x, y);
    return containPoint(p);
}


void DisplayManager::setVisible(bool visible)
{
    if(!_displayRenderNode)
        return;

    _visible = visible;
    _displayRenderNode->setVisible(visible);
}

bool DisplayManager::isVisible() const
{
    return _visible;
}


Size DisplayManager::getContentSize() const
{
    CS_RETURN_IF(!_displayRenderNode) Size(0, 0);
    return _displayRenderNode->getContentSize();
}

Rect DisplayManager::getBoundingBox() const
{
    CS_RETURN_IF(!_displayRenderNode) Rect(0, 0, 0, 0);
    return _displayRenderNode->getBoundingBox();
}


Point DisplayManager::getAnchorPoint() const
{
    CS_RETURN_IF(!_displayRenderNode) Point(0, 0);
    return _displayRenderNode->getAnchorPoint();
}

Point DisplayManager::getAnchorPointInPoints() const
{
    CS_RETURN_IF(!_displayRenderNode) Point(0, 0);
    return _displayRenderNode->getAnchorPointInPoints();
}


}
