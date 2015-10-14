#ifndef __ResPlist_h_
#define __ResPlist_h_

#include "GameDef.h"
#include "ResBase.h"

class ResPlist : public ResBase
{
public:
	enum{
		ResPlist_None,
		ResPlist_Loading,
		ResPlist_Fail,
		ResPlist_Ok,
	};
public:
	ResPlist(const string& path);
	~ResPlist();

public:
	bool			load();
	void			onLoadComplete(ResTask* pTask);

public:
	SpriteFrame*	getSpriteFrame(const string& pathKey);
	SpriteFrame*	getSpriteFrameShadow(const string& pathKey);
	void update(float dt);

protected:
	SpriteFrame*	loadSpriteFrame(const string& pathKey);
	SpriteFrame*	loadSpriteFrameShadow(const string& pathKey);
	void			loadSpriteFrames();
	void			prepareSpriteFrames();

	void pushAni(int key);

protected:
	__Dictionary*	m_pDict;
	__Dictionary*	m_pDictFrames;
	int				m_nPVRFormat;

	Image*			m_pImage;
	Texture2D*		m_pTexture;
	Texture2D*		m_pTextureShadow;

	typedef map<string,SpriteFrame*> SpriteFrameTable;
	SpriteFrameTable	m_SpriteFrames;
	SpriteFrameTable	m_SpriteFramesShadow;
	vector<int>		m_aniQueue;
	queue<string>	m_frameQueue;
};
#endif