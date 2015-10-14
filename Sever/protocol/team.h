// -> client to server
// <- server to client
// <-> client & server

//	队伍由玩家通过“发起组队”按钮发起队伍，或者直接在地图或者聊天系统中对其它玩家发起邀请来创建。
//	创建队伍请求
//struct C2GS_CreateTeam -> 
//{
//	int64 playerId;
//};
struct C2GS_CreateTeam_Req ->
{
	int8 teamMemberMaxCount;
};
//	创建队伍的结果,将用提示信息通知


//	邀请组队请求
struct C2GS_InviteTeam_Req ->
{
	int64				inviteeId;//被邀请者id
};

//	邀请组队结果,将用提示信息通知
//struct GS2C_InviteTeam_Ret<-
//{
//	int64				inviteeId;//被邀请者id
//	int32				retCode;
//};

// 组队邀请, 如果inviterId和inviteeId都没有队伍，服务器新建立队队伍，并把组队邀请消息转给invitee
//           如果inviterId是队长，inviteeId没有队伍，把组队邀请消息转给invitee
struct GS2C_TeamInvite_Msg<-
{
	int64				inviterId;//邀请者id
	string				inviterName;//邀请者名字     
	int16				inviterLevel;//邀请者等级
	int8				inviterCareer;//邀请者职业
};
// 如果被邀请者invitee是队长，inviter没有队伍，服务器发送请求加入队伍的消息给invitee
struct GS2C_JoinTeam_Req<-
{
	int64				inviterId;//邀请者id
	string				inviterName;//邀请者名字    
	int16				inviterLevel;//邀请者等级
	int8				inviterCareer;//邀请者职业
};

//接受或拒绝组队邀请  是对GS2C_TeamInvite_Msg的回复
struct C2GS_AcceptOrRefuseTeamInvite->
{
	int64				inviterId;//邀请者id
	int8				isAccept;//1: 接受 0:拒绝
};
//批准或拒绝加入队伍请求
struct C2GS_ApproveOrRefuseJoinTeam->
{
	int64				inviterId;//邀请者id
	int8				isApprove;//1: 接受 0:拒绝      
};


struct TeamMemberInfo
{
	int64				id;//玩家的唯一id
	string				name;//玩家的名字
	int16				level;//玩家的等级
	int8				career;//玩家的职业
	int8				sex;//玩家的性别
	int32				hp;	//当前血量
	int32				maxhp;	//最大血量
};

// 队伍的完整信息
struct GS2C_TeamInfo<-
{
	int64					teamId;//队伍id
	int64					leadId;//队长id
	int8                    isPermitNum; //1:允许队员发起邀请  0：禁止队员发起邀请
	vector<TeamMemberInfo>	member_list;
};
// 增加队伍成员
struct GS2C_AddTeamMember<-
{
	TeamMemberInfo	member;
};
// 移除队伍成员
struct GS2C_RemoveTeamMember<-
{
	int64	memberId;
	int64	leadId;
	int8	reason; //0: 主动离开; 1:玩家下线; 2：被踢出队伍
};

// 退出队伍，如果是队长退出，就解散队伍
struct C2GS_ExitTeam_Req->
{
	int64					teamId;
};
//	退出队伍返回值, 如有必要
//struct GS2C_ExitTeam_Ret<-
//{
//	int64					teamId;
//	int32				    retCode;//0:成功， 非0：失败
//};
// 移除队伍
struct GS2C_RemoveTeam<-
{
	int64					teamId;
};

//队长可设置是否同意队员发起邀请，默认不勾选。
struct C2GS_ChangePermitAllMemberCanInvite_Req ->
{
	int8 isPermitNum; //1:允许队员发起邀请  0：禁止队员发起邀请
};
struct GS2C_ChangePermitAllMemberCanInvite <-
{
	int64	teamId;//队伍id
	int8    isPermitNum; //1:允许队员发起邀请  0：禁止队员发起邀请
};


struct GS2C_ChangeTeamSet_Ret <-
{
	int8					teamSet;//0:自由组队 1：选择允许所有组队   2：选择拒绝所有组队
};

//队长踢人请求
struct C2GS_TeamKickOutPlayer->
{
	int64	playerId;
};

struct OldTeamerInfo
{
	int64				id;//玩家的唯一id
	string				name;//玩家的名字
	int16				level;//玩家的等级
	int8				career;//玩家的职业
	int8				sex;//玩家的性别
};

//请求最近队友
struct C2GS_GetOldTeamer_Req ->
{
};

struct GS2C_GetOldTeamer_Ret <-
{
	vector<OldTeamerInfo>	teamerList;
};

struct GS2C_TeamMemberState <-
{
	int64	playerId;
	int8	online;//0上线，1下线
	int32	hp;
	int32	maxHp;
};

//以后可能要增加成员等级变化消息,及队友hp等属性的同步消息