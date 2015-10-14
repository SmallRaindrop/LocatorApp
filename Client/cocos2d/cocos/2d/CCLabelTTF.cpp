/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "CCLabelTTF.h"
#include "CCLabel.h"
#include "deprecated/CCString.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

LabelTTF::LabelTTF()
{

}

LabelTTF::~LabelTTF()
{
}

LabelTTF * LabelTTF::create()
{
    LabelTTF * ret = new LabelTTF();
    if (ret && ret->initWithString("", "assets/fonts/DroidSansFallback.ttf", 12, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::TOP))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

LabelTTF* LabelTTF::create(const std::string& string, const std::string& fontFile, float fontSize,
						   const Size &dimensions, TextHAlignment hAlignment, 
						   TextVAlignment vAlignment)
{
    LabelTTF *ret = new LabelTTF();
    if(ret && ret->initWithString(string, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LabelTTF::initWithString(const std::string& string, const std::string& fontFile, float fontSize,
                                const cocos2d::Size &dimensions, TextHAlignment hAlignment,
                                TextVAlignment vAlignment)
{
	if ( FileUtils::getInstance()->isFileExist(fontFile) )
	{
		TTFConfig ttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
		if (setTTFConfig(ttfConfig))
		{
			setDimensions(dimensions.width,dimensions.height);
			setString(string);
			setAlignment(hAlignment,vAlignment);
			enableOutline(Color4B::BLACK,2);
			return true;
		}
	}

	return false;
}

float LabelTTF::getFontSize() const
{
	TTFConfig ttfConfig = getTTFConfig();
	return ttfConfig.fontSize;
}

void LabelTTF::setFontSize(float fontSize)
{
	TTFConfig ttfConfig = getTTFConfig();

	if ( FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) )
	{
		TTFConfig newConfig(ttfConfig.fontFilePath.c_str(),fontSize,GlyphCollection::DYNAMIC);
		setTTFConfig(newConfig);
		enableOutline(Color4B::BLACK,2);
	}
}

const std::string& LabelTTF::getFontFile() const
{
	const TTFConfig& ttfConfig = getTTFConfig();
	return ttfConfig.fontFilePath;
}

void LabelTTF::setFontFile(const std::string& fontFile)
{
	TTFConfig ttfConfig = getTTFConfig();

	if ( FileUtils::getInstance()->isFileExist(fontFile) )
	{
		TTFConfig newConfig(fontFile.c_str(),ttfConfig.fontSize,GlyphCollection::DYNAMIC);
		setTTFConfig(newConfig);
		enableOutline(Color4B::BLACK,2);
	}
}

void LabelTTF::setSystemFontName(const std::string& systemFont)
{
	setFontFile(systemFont);
}

void LabelTTF::setSystemFontSize(float fontSize)
{
	setFontSize(fontSize);
}

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif

NS_CC_END
