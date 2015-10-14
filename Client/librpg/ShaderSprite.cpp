#include "ShaderSprite.h"

ShaderSprite::ShaderSprite() : m_fGreyRate(1.0f)
{

}

ShaderSprite::~ShaderSprite()
{
}

ShaderSprite* ShaderSprite::createWithFile(const char* fliename, float _rate)
{
	ShaderSprite* ret = ShaderSprite::create();
	if(ret)
	{
		ret->setTexture(fliename, _rate);
		return ret;
	}
	
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

ShaderSprite* ShaderSprite::createWithTexture(Texture2D *texture,float _rate/* = 1.5f*/)
{
	ShaderSprite* ret = ShaderSprite::create();
	if(ret)
	{
		ret->setTexture(texture, _rate);
		Rect rect = Rect::ZERO;
		rect.size = texture->getContentSize();
		ret->setTextureRect(rect);
		return ret;
	}

	CC_SAFE_RELEASE(ret);
	return nullptr;
}

ShaderSprite* ShaderSprite::createWithTexture(Texture2D *texture, const Rect& rect, float _rate /* = 1.5f */)
{
	ShaderSprite* ret = ShaderSprite::create();
	if(ret)
	{
		ret->setTexture(texture, _rate);
		ret->setTextureRect(rect,false,rect.size);
		return ret;
	}

	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void ShaderSprite::setBackgroundNotification()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
	auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
		this->setShaderProgram(nullptr);
		this->initShader(m_fGreyRate);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

const GLchar* ShaderSprite::getShaderConfig()
{
	static char shaderArray[10240] = {0};
	if(m_fGreyRate < 1.0f)
	{
		sprintf(shaderArray,  "                                                        \n\
					   #ifdef GL_ES                                                    \n\
					   precision mediump float;                                        \n\
					   #endif                                                          \n\
					   \n\
					   varying vec4 v_fragmentColor;                                   \n\
					   varying vec2 v_texCoord;                                        \n\
					   uniform sampler2D CC_Texture0;                                  \n\
					   \n\
					   void main()                                                     \n\
					   {                                                               \n\
					   vec4 c = texture2D(CC_Texture0, v_texCoord);                    \n\
					   vec4 final = c;                                                 \n\
					   gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b);  \n\
					   gl_FragColor.w = c.w;                                           \n\
					   }                                                               \n\
					   ");
	}
	else
	{
		sprintf(shaderArray,  "                                                        \n\
					   #ifdef GL_ES                                                    \n\
					   precision mediump float;                                        \n\
					   #endif                                                          \n\
					   \n\
					   varying vec4 v_fragmentColor;                                   \n\
					   varying vec2 v_texCoord;                                        \n\
					   uniform sampler2D CC_Texture0;                                  \n\
					   \n\
					   void main()                                                     \n\
					   {                                                               \n\
					   vec4 c = texture2D(CC_Texture0, v_texCoord);                    \n\
					   float greyNum = %0.2f;                                          \n\
					   vec4 final = c;                                                 \n\
					   final.r = c.r * greyNum;                                        \n\
					   final.g = c.g * greyNum;                                        \n\
					   final.b = c.b * greyNum;                                        \n\
					   gl_FragColor = final;                                           \n\
					   }                                                               \n\
					   ", m_fGreyRate);
	}

	return  shaderArray;
}

void ShaderSprite::initShader(float rate)
{
	if ( m_fGreyRate == rate )
	{
		return ;
	}

	m_fGreyRate = rate;

	if ( m_fGreyRate == 1.0f )
	{
		setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	}
	else
	{
		const GLchar* fragSource = getShaderConfig();
		auto program = new GLProgram();
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
}


void ShaderSprite::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	if ( m_fGreyRate == 1.0f )
	{
		Sprite::draw(renderer,transform,transformUpdated);
		return ;
	}
	else
	{
		_renderCommand.init(_globalZOrder);
		_renderCommand.func = CC_CALLBACK_0(ShaderSprite::onDraw, this, transform, transformUpdated);
		renderer->addCommand(&_renderCommand);
	}
}

void ShaderSprite::onDraw(const kmMat4 &transform, bool transformUpdated)
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

void ShaderSprite::setTexture(const std::string &filename, float _rate)
{
	Sprite::setTexture(filename);

	initShader(_rate);
	setBackgroundNotification();
}

void ShaderSprite::setTexture(Texture2D* texture,float _rate /* = 1.5f */ )
{
	Sprite::setTexture(texture);
	initShader(_rate);
	setBackgroundNotification();
}

void ShaderSprite::setGrayRate(float _rate /* = 1.0f */)
{
	initShader(_rate);
	setBackgroundNotification();
}