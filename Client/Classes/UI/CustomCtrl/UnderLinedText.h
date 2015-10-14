#ifndef _UNDERLINE_TEXT_
#define _UNDERLINE_TEXT_

#include "UI/CocosUI.h"
#include "Net/pk_item.h"

class Line : public Node
{   
public:
    Line()
    {
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR));
    }
    
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
    {
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(Line::onDraw, this, transform, transformUpdated);
		renderer->addCommand(&_customCommand);
    }
    
    void setTouchPos(const Point& pt)
    {
        m_pTouchPoint = pt;
    }
    
    void setLineWidth(int nW)
    {
        m_nLineWidth = nW;
    }
    
    void enableShadow(bool bShadow)
    {
        _shadowEnabled = bShadow;
    }
    
    void onDraw(const kmMat4& transform, bool transformUpdated)
	{
		glLineWidth(m_nLineWidth);

		if (_shadowEnabled)
		{
			DrawPrimitives::setDrawColor4B(0,0,0, 200);
			DrawPrimitives::drawLine(convertToWorldSpace(Point(0, 0))+Point(2,-1), convertToWorldSpace(Point(getContentSize().width, 0))+Point(2,-1));
		}
		DrawPrimitives::setDrawColor4B(_realColor.r, _realColor.g, _realColor.b, 255);
		DrawPrimitives::drawLine(convertToWorldSpace(Point(0, 0)), convertToWorldSpace(Point(getContentSize().width, 0)));

		//Vertex2F vertices[2] = {Vertex2F(0, 0), Vertex2F(getContentSize().width, 0)};

  //      GLProgram *shader = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
  //      shader->retain();
		//shader->use();
		//shader->setUniformsForBuiltins(transform);
  //      GLint colorLocation = shader->getUniformLocation("u_color");
		//Color4F color((GLfloat)_realColor.r / 255, (GLfloat)_realColor.g / 255, (GLfloat)_realColor.b / 255, (float)getParent()->getOpacity() / 255);
		//shader->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);
		//GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
		//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		//glLineWidth(m_nLineWidth);
		//glDrawArrays(GL_LINES, 0, 2);
  //      shader->release();

		//CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,2);
	}

    static Line* LineWithParent(Node* pParent)
    {
        Line* pRet = new Line();
        pRet->setContentSize(pParent->getContentSize());
        pRet->setAnchorPoint(Point(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }
    
private:
    Point			m_pTouchPoint;
    CustomCommand	_customCommand;
	int				m_nLineWidth;
	bool			_shadowEnabled;
};



class UnderlinedText : public Text
{
public:
	enum Line_Style
	{
		LS_UNDER,
		LS_DELETE,
	};

	UnderlinedText()	{m_eLineStyle = LS_UNDER;};
	~UnderlinedText()	{};

    static UnderlinedText*	create(const char* strText)
	{
	    UnderlinedText* pRet = new UnderlinedText();
		pRet->init();
		pRet->setText(strText);
		pRet->setTouchEnabled(true);
        pRet->autorelease();
		pRet->m_pLine = Line::LineWithParent(pRet->getVirtualRenderer());
		pRet->m_pLine->setLineWidth(MAX(pRet->getFontSize()/15,1));
		pRet->m_pLine->enableShadow(((Label*)pRet->getVirtualRenderer())->isShadowEnabled());
		pRet->m_pLine->setPositionY(pRet->m_eLineStyle == LS_UNDER ? 0 : pRet->getFontSize() / 2);
		pRet->addProtectedChild(pRet->m_pLine);
		//pRet->setGlobalZOrder(1);
        return pRet;
	}
	virtual void setColor(const Color3B& color)
	{
		Text::setColor(color);
		m_pLine->setColor(color);
	}
	virtual void setFontSize(int nSize)
	{
		Text::setFontSize(nSize);
		m_pLine->setLineWidth(MAX(nSize/15,1));
        m_pLine->setContentSize(getContentSize());
	}
	void SetLineStyle(Line_Style ls)
	{
		m_eLineStyle = ls;
		m_pLine->setPositionY(m_eLineStyle == LS_UNDER ? 0 : getFontSize() / 2);
	}

private:
	Line*		m_pLine;
	Line_Style	m_eLineStyle;
};

#endif