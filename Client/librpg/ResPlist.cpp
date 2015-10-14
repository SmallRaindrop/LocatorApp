#include "ResPlist.h"

ResPlist::ResPlist(const string& path) : ResBase(0,ResType_Pvr,path),
	m_pTexture(NULL),
	m_pDictFrames(NULL),m_pDict(NULL),m_nPVRFormat(0)
{
	string pathKey = getPathKey();
	m_pDict = __Dictionary::createWithContentsOfFileThreadSafe(pathKey.c_str());

	m_SpriteFrames.clear();
	m_SpriteFramesShadow.clear();
}

ResPlist::~ResPlist()
{
	for ( SpriteFrameTable::iterator itr = m_SpriteFrames.begin();itr != m_SpriteFrames.end();++itr )
	{
		CC_SAFE_RELEASE(itr->second);
	}

	for ( SpriteFrameTable::iterator itr = m_SpriteFramesShadow.begin();itr != m_SpriteFramesShadow.end();++itr )
	{
		CC_SAFE_RELEASE(itr->second);
	}

	CC_SAFE_RELEASE(m_pTexture);
	CC_SAFE_RELEASE(m_pDict);
}

bool ResPlist::load()
{
	string pathKey = getPathKey();
	/*m_pDict = __Dictionary::createWithContentsOfFileThreadSafe(pathKey.c_str());
	if ( !m_pDict )
	{
	return false;
	}*/

	__Dictionary* pMeta = (__Dictionary*)m_pDict->objectForKey("metadata");
	if ( !pMeta )
	{
		return false;
	}

	m_pDictFrames = (__Dictionary*)m_pDict->objectForKey("frames");
	if ( !m_pDictFrames )
	{
		return false;
	}

	m_nPVRFormat = pMeta->valueForKey("format")->intValue();
	// check the format
	CCAssert(m_nPVRFormat >=0 && m_nPVRFormat <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

	string texturePathKey = pMeta->valueForKey("textureFileName")->getCString();
	texturePathKey = gFileUtils->fullPathFromRelativeFile(texturePathKey.c_str(), pathKey.c_str());

	m_pImage = new Image;
	if ( m_pImage && m_pImage->initWithImageFile(texturePathKey))
	{
		return true;
	}
	CC_SAFE_RELEASE(m_pImage);
	m_pImage = NULL;

	return false;
}


void ResPlist::onLoadComplete(ResTask* pTask)
{
	m_pTexture = new Texture2D();
	if( m_pTexture && m_pTexture->initWithImage(m_pImage) )
	{
	}

	//// 修改图片数据位阴影
	//unsigned int* pixels = new unsigned int[m_pImage->getDataLen()/4];
	//memcpy(pixels,m_pImage->getData(),m_pImage->getDataLen());
	//for ( int i = 0;i<m_pImage->getHeight();++i )
	//{
	//	for ( int j = 0;j<m_pImage->getWidth();++j )
	//	{
	//		int idx = i*m_pImage->getWidth()+j;
	//		pixels[idx] = pixels[idx] & 0x4e000000;
	//	}
	//}
	//m_pTextureShadow = new Texture2D();
	//if( m_pTextureShadow && m_pTextureShadow->initWithData(pixels,m_pImage->getDataLen(),Texture2D::PixelFormat::RGBA8888,m_pImage->getWidth(),m_pImage->getHeight(),Size(m_pImage->getWidth(),m_pImage->getHeight())) )
	//{
	//}

	CC_SAFE_RELEASE(m_pImage);
	m_pImage = NULL;

	ResBase::onLoadComplete(pTask);
}

void ResPlist::pushAni(int key)
{
	for ( size_t i = 0;i<m_aniQueue.size();++i )
	{
		if ( key == m_aniQueue[i])
		{
			return;
		}
	}
	m_aniQueue.push_back(key);
}

void ResPlist::update(float dt)
{
	const static int MAX_LOAD_COUNT = 3;
	int i = 0;
	while ( !m_frameQueue.empty() && i++ < MAX_LOAD_COUNT )
	{
		string pathKey = m_frameQueue.front();
		m_frameQueue.pop();
		getSpriteFrame(pathKey);
	}

	if ( !m_frameQueue.empty() )
	{
		return ;
	}

	if ( m_aniQueue.empty() )
	{
		return;
	}
	m_aniQueue.erase(m_aniQueue.begin());
}

SpriteFrame* ResPlist::getSpriteFrame(const string& pathKey)
{
	if ( !isOk() )
	{
		return NULL;
	}

	SpriteFrameTable::iterator itr = m_SpriteFrames.find(pathKey);
	if ( itr != m_SpriteFrames.end() )
	{
		return itr->second;
	}

	return loadSpriteFrame(pathKey);
}

SpriteFrame* ResPlist::getSpriteFrameShadow(const string& pathKey)
{
	if ( !isOk() )
	{
		return NULL;
	}

	SpriteFrameTable::iterator itr = m_SpriteFramesShadow.find(pathKey);
	if ( itr != m_SpriteFramesShadow.end() )
	{
		return itr->second;
	}

	return loadSpriteFrameShadow(pathKey);
}

SpriteFrame* ResPlist::loadSpriteFrame(const string& pathKey)
{
	if ( !isOk() )
	{
		return NULL;
	}

	__Dictionary* frameDict = (__Dictionary*)m_pDictFrames->objectForKey(pathKey);
	if ( frameDict )
	{
		SpriteFrame* spriteFrame = NULL;
		switch (m_nPVRFormat)
		{
		case 0:
			{
				float x = frameDict->valueForKey("x")->floatValue();
				float y = frameDict->valueForKey("y")->floatValue();
				float w = frameDict->valueForKey("width")->floatValue();
				float h = frameDict->valueForKey("height")->floatValue();
				float ox = frameDict->valueForKey("offsetX")->floatValue();
				float oy = frameDict->valueForKey("offsetY")->floatValue();
				int ow = frameDict->valueForKey("originalWidth")->intValue();
				int oh = frameDict->valueForKey("originalHeight")->intValue();
				// check ow/oh
				if(!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
				}
				// abs ow/oh
				ow = abs(ow);
				oh = abs(oh);
				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTexture, 
					Rect(x, y, w, h), 
					false,
					Point(ox, oy),
					Size((float)ow, (float)oh)
					);
			}
			break;
		case 1:
		case 2:
			{
				Rect frame = RectFromString(frameDict->valueForKey("frame")->getCString());
				bool rotated = false;

				// rotation
				if (m_nPVRFormat == 2)
				{
					rotated = frameDict->valueForKey("rotated")->boolValue();
				}

				Point offset = PointFromString(frameDict->valueForKey("offset")->getCString());
				Size sourceSize = SizeFromString(frameDict->valueForKey("sourceSize")->getCString());

				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTexture, 
					frame,
					rotated,
					offset,
					sourceSize
					);
			}
			break;
		case 3:
			{
				// get values
				Size spriteSize = SizeFromString(frameDict->valueForKey("spriteSize")->getCString());
				Point spriteOffset = PointFromString(frameDict->valueForKey("spriteOffset")->getCString());
				Size spriteSourceSize = SizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
				Rect textureRect = RectFromString(frameDict->valueForKey("textureRect")->getCString());
				bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

				// get aliases
				//CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
				//CCString * frameKey = new CCString(spriteFrameName);

				//CCObject* pObj = NULL;
				//CCARRAY_FOREACH(aliases, pObj)
				//{
				//	std::string oneAlias = ((CCString*)pObj)->getCString();
				//	if (m_pSpriteFramesAliases->objectForKey(oneAlias.c_str()))
				//	{
				//		CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
				//	}

				//	m_pSpriteFramesAliases->setObject(frameKey, oneAlias.c_str());
				//}
				//frameKey->release();
				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTexture,
					Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
					textureRotated,
					spriteOffset,
					spriteSourceSize);
			}
			break;
		default:
			break;
		}
		// add sprite frame
		if ( spriteFrame )
		{
			spriteFrame->retain();
			m_SpriteFrames[pathKey] = spriteFrame;
			return spriteFrame;
		}
	}

	return NULL;
}

SpriteFrame* ResPlist::loadSpriteFrameShadow(const string& pathKey)
{
	if ( !isOk() )
	{
		return NULL;
	}

	__Dictionary* frameDict = (__Dictionary*)m_pDictFrames->objectForKey(pathKey);
	if ( frameDict )
	{
		SpriteFrame* spriteFrame = NULL;
		switch (m_nPVRFormat)
		{
		case 0:
			{
				float x = frameDict->valueForKey("x")->floatValue();
				float y = frameDict->valueForKey("y")->floatValue();
				float w = frameDict->valueForKey("width")->floatValue();
				float h = frameDict->valueForKey("height")->floatValue();
				float ox = frameDict->valueForKey("offsetX")->floatValue();
				float oy = frameDict->valueForKey("offsetY")->floatValue();
				int ow = frameDict->valueForKey("originalWidth")->intValue();
				int oh = frameDict->valueForKey("originalHeight")->intValue();
				// check ow/oh
				if(!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
				}
				// abs ow/oh
				ow = abs(ow);
				oh = abs(oh);
				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTextureShadow, 
					Rect(x, y, w, h), 
					false,
					Point(ox, oy),
					Size((float)ow, (float)oh)
					);
			}
			break;
		case 1:
		case 2:
			{
				Rect frame = RectFromString(frameDict->valueForKey("frame")->getCString());
				bool rotated = false;

				// rotation
				if (m_nPVRFormat == 2)
				{
					rotated = frameDict->valueForKey("rotated")->boolValue();
				}

				Point offset = PointFromString(frameDict->valueForKey("offset")->getCString());
				Size sourceSize = SizeFromString(frameDict->valueForKey("sourceSize")->getCString());

				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTextureShadow, 
					frame,
					rotated,
					offset,
					sourceSize
					);
			}
			break;
		case 3:
			{
				// get values
				Size spriteSize = SizeFromString(frameDict->valueForKey("spriteSize")->getCString());
				Point spriteOffset = PointFromString(frameDict->valueForKey("spriteOffset")->getCString());
				Size spriteSourceSize = SizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
				Rect textureRect = RectFromString(frameDict->valueForKey("textureRect")->getCString());
				bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

				// get aliases
				//CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
				//CCString * frameKey = new CCString(spriteFrameName);

				//CCObject* pObj = NULL;
				//CCARRAY_FOREACH(aliases, pObj)
				//{
				//	std::string oneAlias = ((CCString*)pObj)->getCString();
				//	if (m_pSpriteFramesAliases->objectForKey(oneAlias.c_str()))
				//	{
				//		CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
				//	}

				//	m_pSpriteFramesAliases->setObject(frameKey, oneAlias.c_str());
				//}
				//frameKey->release();
				// create frame
				spriteFrame = SpriteFrame::createWithTexture(m_pTextureShadow,
					Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
					textureRotated,
					spriteOffset,
					spriteSourceSize);
			}
			break;
		default:
			break;
		}
		// add sprite frame
		if ( spriteFrame )
		{
			spriteFrame->retain();
			m_SpriteFramesShadow[pathKey] = spriteFrame;
			return spriteFrame;
		}
	}

	return NULL;
}

void ResPlist::prepareSpriteFrames()
{
	DictElement* pElement = NULL;
	CCDICT_FOREACH(m_pDictFrames, pElement)
	{
		m_frameQueue.push(pElement->getStrKey());
	}
}

void ResPlist::loadSpriteFrames()
{
	DictElement* pElement = NULL;
	CCDICT_FOREACH(m_pDictFrames, pElement)
	{
		__Dictionary* frameDict = (__Dictionary*)pElement->getObject();
		string pathKey = pElement->getStrKey();
		if ( frameDict )
		{
			SpriteFrame* spriteFrame = NULL;
			switch (m_nPVRFormat)
			{
			case 0:
				{
					float x = frameDict->valueForKey("x")->floatValue();
					float y = frameDict->valueForKey("y")->floatValue();
					float w = frameDict->valueForKey("width")->floatValue();
					float h = frameDict->valueForKey("height")->floatValue();
					float ox = frameDict->valueForKey("offsetX")->floatValue();
					float oy = frameDict->valueForKey("offsetY")->floatValue();
					int ow = frameDict->valueForKey("originalWidth")->intValue();
					int oh = frameDict->valueForKey("originalHeight")->intValue();
					// check ow/oh
					if(!ow || !oh)
					{
						CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
					}
					// abs ow/oh
					ow = abs(ow);
					oh = abs(oh);
					// create frame
					spriteFrame = SpriteFrame::createWithTexture(m_pTexture, 
						Rect(x, y, w, h), 
						false,
						Point(ox, oy),
						Size((float)ow, (float)oh)
						);
				}
				break;
			case 1:
			case 2:
				{
					Rect frame = RectFromString(frameDict->valueForKey("frame")->getCString());
					bool rotated = false;

					// rotation
					if (m_nPVRFormat == 2)
					{
						rotated = frameDict->valueForKey("rotated")->boolValue();
					}

					Point offset = PointFromString(frameDict->valueForKey("offset")->getCString());
					Size sourceSize = SizeFromString(frameDict->valueForKey("sourceSize")->getCString());

					// create frame
					spriteFrame = SpriteFrame::createWithTexture(m_pTexture, 
						frame,
						rotated,
						offset,
						sourceSize
						);
				}
				break;
			case 3:
				{
					// get values
					Size spriteSize = SizeFromString(frameDict->valueForKey("spriteSize")->getCString());
					Point spriteOffset = PointFromString(frameDict->valueForKey("spriteOffset")->getCString());
					Size spriteSourceSize = SizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
					Rect textureRect = RectFromString(frameDict->valueForKey("textureRect")->getCString());
					bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

					// get aliases
					//CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
					//CCString * frameKey = new CCString(spriteFrameName);

					//CCObject* pObj = NULL;
					//CCARRAY_FOREACH(aliases, pObj)
					//{
					//	std::string oneAlias = ((CCString*)pObj)->getCString();
					//	if (m_pSpriteFramesAliases->objectForKey(oneAlias.c_str()))
					//	{
					//		CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
					//	}

					//	m_pSpriteFramesAliases->setObject(frameKey, oneAlias.c_str());
					//}
					//frameKey->release();
					// create frame
					spriteFrame = SpriteFrame::createWithTexture(m_pTexture,
						Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
						textureRotated,
						spriteOffset,
						spriteSourceSize);
				}
				break;
			default:
				break;
			}
			// add sprite frame
			if ( spriteFrame )
			{
				spriteFrame->retain();
				m_SpriteFrames[pathKey] = spriteFrame;
			}
		}
	}
}