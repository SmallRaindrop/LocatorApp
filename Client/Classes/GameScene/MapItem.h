#ifndef __MapItem_h_
#define __MapItem_h_

#include "Role.h"
#include "db.h"
#include "ui/UIImageView.h"
#include "effect.h"

//#include "Net/pk_move.h"


class CMapItem : public MapObject
{
public:
	CMapItem(void);
	virtual ~CMapItem(void);

	CREATE_FUNC(CMapItem);
	//new
	virtual bool init();
	virtual void update(float dt);
	virtual bool isSelect(float x,float y);

	void		SetDataID(int dataid);
	void		SetOwnerID(MapObjectID owner){m_nOwner = owner;}
	MapObjectID	GetOwnerID(){return m_nOwner;}
	int			GetDataID(){ return m_pItemData?m_pItemData->id:0; }	
	inline ItemCfg* GetItemData(){ return m_pItemData; }

	void	beginBlink();
	void	stopBlink();

	void	onCover(bool covered);

	CC_SYNTHESIZE_READONLY(int,m_nDropArtID, DropArtID);
	CC_SYNTHESIZE_READONLY(int,m_nDispArtID, DispArtID);
	CC_SYNTHESIZE_READONLY(string,m_sDropArtName, DropArtName);
	CC_SYNTHESIZE_READONLY(string,m_sDispArtName, DispArtName);		;

protected:
	double			m_fBornTime;
	ItemCfg*		m_pItemData;
	Label*			m_pLabelName;			// 名字
	Node*	        m_pDropIcon;
	MapObjectID		m_nOwner;
};

class CPickupItemAction
{
public:
	void initWithMapItem(CMapItem* pMapItem);
	bool pickUp();
	inline MapObjectID			GetId(){ return m_id; }
private:
	MapObjectID		m_id;
	int             m_cellX;
	int             m_cellY;
	double          m_getTime;          //发送消息的最后时间
};

#endif
