/***
 * 模块：shader 精灵
 * 作者：sndy
 * 时间：2015-07-28
 * 说明：创建灰度精灵
 */

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ShaderSprite : public Sprite
{
public:
	ShaderSprite();
	~ShaderSprite();

	CREATE_FUNC(ShaderSprite);

	static ShaderSprite* createWithFile(const char * filename, float _rate = 1.5f);
	static ShaderSprite* createWithTexture(Texture2D* texture,float _rate = 1.5f);
	static ShaderSprite* createWithTexture(Texture2D *texture, const Rect& rect, float _rate = 1.5f);

	const GLchar* getShaderConfig();

	void initShader(float rate);
	void setTexture(const std::string &filename,float _rate = 1.5f );
	void setTexture(Texture2D* texture,float _rate = 1.5f );
	//改变灰度系数 默认是还原  大于1为高亮 小于1位灰色
	void setGrayRate(float _rate = 1.0f);
	void setBackgroundNotification();
	void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
	
protected:
	void onDraw(const kmMat4 &transform, bool transformUpdated);

	float			m_fGreyRate;               // 灰度系数 百分比值
	CustomCommand	_renderCommand;
};