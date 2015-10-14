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

#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"

#include "cocostudio/CCSkin.h"
#include "cocostudio/CCTransformHelp.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmature.h"
#include "ccShaders.h"
#include "CCShaderCache.h"


using namespace cocos2d;

namespace cocostudio {

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

#define SET_VERTEX3F(_v_, _x_, _y_, _z_) (_v_).x = (_x_); (_v_).y = (_y_); (_v_).z = (_z_);

#define SkinEffectShader_Grey "	\n\
#ifdef GL_ES					\n\
	precision mediump float;		\n\
#endif							\n\
	varying vec4 v_fragmentColor;	\n\
	varying vec2 v_texCoord;		\n\
	uniform sampler2D CC_Texture0;	\n\
	void main()						\n\
	{								\n\
		vec4 c = texture2D(CC_Texture0, v_texCoord);                  \n\
		vec4 final = c;                                               \n\
		gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b);\n\
		gl_FragColor.w = c.w;                                         \n\
	}								\n\
"

#define SkinEffectShader_HighLight "	\n\
#ifdef GL_ES                                                    \n\
	precision mediump float;                                    \n\
#endif                                                          \n\
	varying vec4 v_fragmentColor;                               \n\
	varying vec2 v_texCoord;                                    \n\
	uniform sampler2D CC_Texture0;                              \n\
	void main()                                                 \n\
	{                                                           \n\
		vec4 c = texture2D(CC_Texture0, v_texCoord);                    \n\
		float greyNum = 4.8;											\n\
		vec4 final = c;                                                 \n\
		final.r = c.r * greyNum;                                        \n\
		final.g = c.g * greyNum;                                        \n\
		final.b = c.b * greyNum;                                        \n\
		gl_FragColor = final;                                           \n\
	}																	\n\
"

#define SkinEffectShader_Elite "\n\
#ifdef GL_ES					\n\
	precision mediump float;	\n\
#endif							\n\
	uniform sampler2D u_texture;\n\
	varying vec2 v_texCoord;	\n\
	varying vec4 v_fragmentColor;\n\
	void main(void)				\n\
	{							\n\
		vec4 normalColor = v_fragmentColor * texture2D(u_texture, v_texCoord);	\n\
		normalColor *= vec4(0.8, 0.8, 0.8, 1);									\n\
		normalColor.r += normalColor.a * 0.2;									\n\
		gl_FragColor = normalColor;												\n\
	}							\n\
"


Skin *Skin::create()
{
    Skin *skin = new Skin();
    if(skin && skin->init())
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::createWithSpriteFrameName(const std::string& pszSpriteFrameName)
{
    Skin *skin = new Skin();
    if(skin && skin->initWithSpriteFrameName(pszSpriteFrameName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin *Skin::create(const std::string& pszFileName)
{
    Skin *skin = new Skin();
    if(skin && skin->initWithFile(pszFileName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return nullptr;
}

Skin::Skin()
    : _bone(nullptr)
    , _armature(nullptr)
    , _displayName("")
	, _effectType(SkinEffect_None)
{
    kmMat4Identity(&_skinTransform);
}

bool Skin::initWithSpriteFrameName(const std::string& spriteFrameName)
{
    CCAssert(spriteFrameName != "", "");

    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    bool ret = true;

    if (pFrame != nullptr)
    {
        ret = initWithSpriteFrame(pFrame);
    }
    else
    {
        CCLOG("Cann't find CCSpriteFrame with %s. Please check your .plist file", spriteFrameName.c_str());
        ret = false;
    }
    _displayName = spriteFrameName;

    return ret;
}

bool Skin::initWithFile(const std::string& filename)
{
    bool ret = Sprite::initWithFile(filename);

    _displayName = filename;

    return ret;
}

void Skin::setSkinData(const BaseData &var)
{
    _skinData = var;

    setScaleX(_skinData.scaleX);
    setScaleY(_skinData.scaleY);
    setRotationSkewX(CC_RADIANS_TO_DEGREES(_skinData.skewX));
    setRotationSkewY(CC_RADIANS_TO_DEGREES(-_skinData.skewY));
    setPosition(Point(_skinData.x, _skinData.y));

    _skinTransform = getNodeToParentTransform();
    updateArmatureTransform();
}

const BaseData &Skin::getSkinData() const
{
    return _skinData;
}

void Skin::updateArmatureTransform()
{
    _transform = TransformConcat(_bone->getNodeToArmatureTransform(), _skinTransform);
//    if(_armature && _armature->getBatchNode())
//    {
//        _transform = TransformConcat(_transform, _armature->getNodeToParentTransform());
//    }
}

void Skin::updateTransform()
{
    // If it is not visible, or one of its ancestors is not visible, then do nothing:
    if( !_visible)
    {
        _quad.br.vertices = _quad.tl.vertices = _quad.tr.vertices = _quad.bl.vertices = Vertex3F(0, 0, 0);
    }
    else
    {
        //
        // calculate the Quad based on the Affine Matrix
        //

        Size &size = _rect.size;

        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;

        float x2 = x1 + size.width;
        float y2 = y1 + size.height;

        float x = _transform.mat[12];
        float y = _transform.mat[13];

        float cr = _transform.mat[0];
        float sr = _transform.mat[1];
        float cr2 = _transform.mat[5];
        float sr2 = -_transform.mat[4];
        float ax = x1 * cr - y1 * sr2 + x;
        float ay = x1 * sr + y1 * cr2 + y;

        float bx = x2 * cr - y1 * sr2 + x;
        float by = x2 * sr + y1 * cr2 + y;

        float cx = x2 * cr - y2 * sr2 + x;
        float cy = x2 * sr + y2 * cr2 + y;

        float dx = x1 * cr - y2 * sr2 + x;
        float dy = x1 * sr + y2 * cr2 + y;

        SET_VERTEX3F( _quad.bl.vertices, RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _positionZ );
        SET_VERTEX3F( _quad.br.vertices, RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _positionZ );
        SET_VERTEX3F( _quad.tl.vertices, RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _positionZ );
        SET_VERTEX3F( _quad.tr.vertices, RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _positionZ );
    }

    // MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
    if (_textureAtlas)
    {
        _textureAtlas->updateQuad(&_quad, _textureAtlas->getTotalQuads());
    }
}

kmMat4 Skin::getNodeToWorldTransform() const
{
    return TransformConcat( _bone->getArmature()->getNodeToWorldTransform(), _transform);
}

kmMat4 Skin::getNodeToWorldTransformAR() const
{
    kmMat4 displayTransform = _transform;
    Point anchorPoint =  _anchorPointInPoints;

    anchorPoint = PointApplyTransform(anchorPoint, displayTransform);

    displayTransform.mat[12] = anchorPoint.x;
    displayTransform.mat[13] = anchorPoint.y;

    return TransformConcat( _bone->getArmature()->getNodeToWorldTransform(),displayTransform);
}

void Skin::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	//TODO skin effect
	if ( _effectType == SkinEffect_None )
	{
		kmMat4 mv;
		kmGLGetMatrix(KM_GL_MODELVIEW, &mv);

		//TODO implement z order
		_quadCommand.init(_globalZOrder, _texture->getName(), _shaderProgram, _blendFunc, &_quad, 1, mv);
		renderer->addCommand(&_quadCommand);
	}
	else
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(Skin::draw_callback, this,renderer, transform, transformUpdated);
		renderer->addCommand(&_customCommand);
	}
}

void Skin::draw_callback(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	auto shader = getShaderProgram();
	shader->use();
	shader->setUniformsForBuiltins(transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
	GL::blendFunc(_blendFunc.src, _blendFunc.dst);

	GL::bindTexture2D( getTexture()->getName());

	//
	// Attributes
	//
#define kQuadSize sizeof(_quad.bl)
	size_t offset = (size_t)&_quad;

	// vertex
	int diff = offsetof( V3F_C4B_T2F, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( V3F_C4B_T2F, colors);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}

void Skin::setBone(Bone *bone)
{
    _bone = bone;
    if(Armature *armature = _bone->getArmature())
    {
        _armature = armature;
    }
}

Bone *Skin::getBone() const
{
    return _bone;
}

void Skin::setSkinEffectShaderProgram()
{
	switch (_effectType)
	{
	case cocostudio::SkinEffect_None: setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));break;
	case cocostudio::SkinEffect_Grey:
		{
			const GLchar* fragSource = SkinEffectShader_Grey;
			GLProgram* program = new GLProgram();
			program->initWithByteArrays(ccPositionTextureColor_vert, fragSource);
			setShaderProgram(program);
			program->release();

			CHECK_GL_ERROR_DEBUG();

			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

			CHECK_GL_ERROR_DEBUG();

			program->link();

			CHECK_GL_ERROR_DEBUG();

			program->updateUniforms();

			CHECK_GL_ERROR_DEBUG();
		}
		break;
	case cocostudio::SkinEffect_Elite:
		{
			const GLchar* fragSource = SkinEffectShader_Elite;
			GLProgram* program = new GLProgram();
			program->initWithByteArrays(ccPositionTextureColor_vert, fragSource);
			setShaderProgram(program);
			program->release();

			CHECK_GL_ERROR_DEBUG();

			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

			CHECK_GL_ERROR_DEBUG();

			program->link();

			CHECK_GL_ERROR_DEBUG();

			program->updateUniforms();

			CHECK_GL_ERROR_DEBUG();
		}
		break;
	case cocostudio::SkinEffect_HighLight:
		{
			const GLchar* fragSource = SkinEffectShader_HighLight;
			GLProgram* program = new GLProgram();
			program->initWithByteArrays(ccPositionTextureColor_vert, fragSource);
			setShaderProgram(program);
			program->release();

			CHECK_GL_ERROR_DEBUG();

			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
			program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

			CHECK_GL_ERROR_DEBUG();

			program->link();

			CHECK_GL_ERROR_DEBUG();

			program->updateUniforms();

			CHECK_GL_ERROR_DEBUG();
		}
		break;
	default:
		break;
	}
}

void Skin::setSkinEffect(SkinEffectType type)
{
	if ( type == _effectType )
	{
		return ;
	}
	
	_effectType = type;

	setSkinEffectShaderProgram();
}

}
