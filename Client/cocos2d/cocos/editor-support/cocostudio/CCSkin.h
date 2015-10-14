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

#ifndef __CCSKIN_H__
#define __CCSKIN_H__

#include "CCSprite.h"
#include "renderer/CCQuadCommand.h"

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCBone.h"

namespace cocostudio {

enum SkinEffectType
{
	SkinEffect_None,	//
	SkinEffect_Grey,	// ȥɫ
	SkinEffect_HighLight,	// 高亮
	SkinEffect_Elite,	// 精英 
};

class Skin : public cocos2d::Sprite
{
public:
    static Skin *create();
    static Skin *createWithSpriteFrameName(const std::string& pszSpriteFrameName);
    static Skin *create(const std::string& pszFileName);
public:
    /**
     *  @js ctor
     */
    Skin();

    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName) override;
    virtual bool initWithFile(const std::string& filename) override;

    void updateArmatureTransform();
    void updateTransform() override;

    kmMat4 getNodeToWorldTransform() const override;
    kmMat4 getNodeToWorldTransformAR() const;
    
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
	// add by yueliangyou
    virtual void draw_callback(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
	
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setSkinData(const BaseData &data);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual const BaseData &getSkinData() const;

    virtual void setBone(Bone *bone);
    virtual Bone *getBone() const;

    virtual const std::string &getDisplayName() const { return _displayName; }

	// skin effect [add by yueliangyou]
	virtual void setSkinEffectShaderProgram();

	virtual void setSkinEffect(SkinEffectType type);

protected:
    BaseData _skinData;
    Bone *_bone;
    Armature *_armature;
    kmMat4 _skinTransform;
    std::string _displayName;
    cocos2d::QuadCommand _quadCommand;     // quad command
	SkinEffectType _effectType;				// skin effect
	cocos2d::CustomCommand	_customCommand;	//
};

}

#endif /*__CCSKIN_H__*/
