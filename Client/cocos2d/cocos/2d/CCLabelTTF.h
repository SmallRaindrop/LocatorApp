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
#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "CCNode.h"
#include "CCLabel.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */



/** @brief LabelTTF is a subclass of TextureNode that knows how to render text labels
 *
 * All features from TextureNode are valid in LabelTTF
 *
 * LabelTTF objects are slow. Consider using LabelAtlas or LabelBMFont instead.
 *
 * Custom ttf file can be put in assets/ or external storage that the Application can access.
 * @code
 * LabelTTF *label1 = LabelTTF::create("alignment left", "A Damn Mess", fontSize, blockSize, 
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * LabelTTF *label2 = LabelTTF::create("alignment right", "/mnt/sdcard/Scissor Cuts.ttf", fontSize, blockSize,
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * @endcode
 *
 */
class CC_DLL LabelTTF : public Label
{
public:
    LabelTTF();
    ~LabelTTF();

	/** Creates an label.
     */
    static LabelTTF * create();

    static LabelTTF * create(const std::string& string, const std::string& fontFile, float fontSize,
                             const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER,
                             TextVAlignment vAlignment = TextVAlignment::TOP);
    
    /** initializes the LabelTTF with a font name, alignment, dimension and font size */
    bool initWithString(const std::string& string, const std::string& fontFile, float fontSize,
                        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, 
                        TextVAlignment vAlignment = TextVAlignment::TOP);
 
    float getFontSize() const;
    void setFontSize(float fontSize);
    
    const std::string& getFontFile() const;
    void setFontFile(const std::string& fontFile);

	/* Sets the system font[font name or font file] of label*/
	void setSystemFontName(const std::string& systemFont);

	/* Sets the system font size of label.*/
	void setSystemFontSize(float fontSize);
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

