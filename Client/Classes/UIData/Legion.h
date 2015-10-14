/* 模块: 军团数据
   作者: Tangbo
   时间: 2015/9/24
 */


#include "Net/pk_guild.h"

//军团职称枚举
enum  LegionTitle_em
{
	LegionTitle_JiangJun = 1,             //将军
	LegionTitle_TaiWei,                   //太尉
	LegionTitle_DuWei,                    //督尉
	LegionTitle_XiaoWei,                  //校尉
	LegionTitle_ZhongWei,                 //中尉
	LegionTitle_ShiBing,                  //士兵
};

//职称权限 	%%公会成员权限
enum  LegionPermission_em
{
	LegionPermission_Approve      = 1<<1, 	               //审批权限
	LegionPermission_Kick         = 1<<2,    	           //踢人
	LegionPermission_Build        = 1<<3,   	           //建设
	LegionPermission_Armament     = 1<<4,                  //军械
	LegionPermission_Alter_Announcement = 1<<5,            //修改公告
	LegionPermission_Quiet        = 1<<6,                  //禁言
	LegionPermission_Appoint      = 1<<7,                  //职务任命
};



typedef vector<pk::memberList> Member_V;     //成员
typedef vector<pk::guildList>  Legion_V;       //公会

//公会成员类
class LegionMember_cl
{
public:
	LegionMember_cl();
	~LegionMember_cl();

	//获取公会成员列表
	const Member_V&  getMemberList(){return m_vMemberList;}

	//向公会中添加成员
	void addMember(pk::memberList* member);

	//删除公会成员
	void removeMemberByPlayerId(int playerid);
	
	void removeMember(pk::memberList* member);

	//获取当前公会的人数
	inline int getCount(){return (int)m_vMemberList.size();}

private:
	//公会成员
	Member_V  m_vMemberList;
};

class  Legion_cl
{
public:
	Legion_cl();
	~Legion_cl();

	//初始化公会
	void   initLegion(Legion_V _list);

	//初始化成员列表
	void   initMemberList(Member_V _list);

	//获取公会列表
	inline Legion_V& getGuildList(){return m_pGuild;}

	//获取公会成员
	inline LegionMember_cl* getLegionMemberList(){return m_pMember;}

private:

	//公会成员
	LegionMember_cl * m_pMember;

	//军团列表
	Legion_V           m_pGuild;
};