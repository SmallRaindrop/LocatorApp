//此文件中的所有位置信息都是实现的逻辑坐标
struct PosInfo   
{
	int16 x;
	int16 y;
};

struct C2GS_PlayerMoveTo    ->
{	
	int32 curMapDataId; // player current map data id
	int16 posX;// player current position
	int16 posY;// player current position
	vector<PosInfo> posInfos;//move path
};



struct GS2C_PlayerStopMove <-
{
	int64 id;//player id
	int16 posX;// player current position
	int16 posY;// player current position
};

struct C2GS_PlayerStopMove ->
{
	int32 curMapDataId; // player current map data id
	int16 posX;// player current position
	int16 posY;// player current position
};

struct GS2C_PlayerMoveInfo    <-
{
	int64 	id;//player id
	int16    posX;// player current position
	int16    posY;// player current position
	vector<PosInfo> posInfos;//move path
};
// player look info
struct GS2C_LookInfoPlayer  <-
{
	int64	id;
	string	name;
	int64   guildId;
	int16	level;
	int8	career;
	int8	sex;
	int32 	weapon;
	int32	armor;
	int32	wing;

	int64	hp;
	int64	hpMax;
	int32	mp;
	int32	mpMax;

	int16	x;   // in logical, player current position
	int16	y;   // in logical, player current position
	int16	moveSpeed;
	int16   movedMs;
	int32	status;		// 状态标志位
	int8	vipLevel;	// vip等级
	vector<PosInfo> posInfos;//如果是摇杆移动，vector里只会包括一个pos, 记录dirx and diry
	int32   pkValue;
	int8    camp;
	int32   battleScore;
	int32   achievementId;
	int8   deadRestTime;//濒死状态剩余复活时间
	int16  restPoint;//剩余点数
	int8 helpNum;//拯救角色数目
	int16 restTime;//剩余毫秒
};

struct GS2C_LookInfoTreas  <-
{
	int64	id;
	int32   dataId;
	int16	x;   // in logical, player current position
	int16	y;   // in logical, player current position
	int8	status;		// 0开启中，1闲置中
	int32	disTime;	// 毁灭时间
};

//virtaul player look info
struct GS2C_LookInfoVirtualPlayer  <-
{
	int64	id;
	string	name;
	int64   guildId;
	int16	level;
	int8	career;
	int8	sex;
	int32 	weapon;
	int32	armor;
	int32	wing;

	int64	hp;
	int64	hpMax;
	int32	mp;
	int32	mpMax;

	int16	x;   // in logical, player current position
	int16	y;   // in logical, player current position
	int16	moveSpeed;
	int16   movedMs;
	int32	status;		// 状态标志位
	int8	vipLevel;	// vip等级
	vector<PosInfo> posInfos;//如果是摇杆移动，vector里只会包括一个pos, 记录dirx and diry
	int32   pkValue;
	int8    camp;
	int8    profession;//职业,
	int32   battleScore;
	int32   achievementId;
};
// monster look info
struct GS2C_LookInfoMonster   <-
{
	int64	id;
	int16	monster_data_id;//怪物在配置文件里的id

	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;

	int16	x;   // in logical,current position
	int16	y;   // in logical,current position
	int16	moveSpeed;
	int16   movedMs;
	int32	status;		// 状态标志位
	vector<PosInfo> posInfos;//路径节点，如果vector为空，不需要移动
	int8    camp;
};
// npc外观信息
struct GS2C_LookInfoNpc   <-
{
	int64		id;
	int32	npc_data_id;//npc 在配置文件里的id
	int16	x;   // in logical
	int16	y;   // in logical
	
};


struct GS2C_LookInfoItem <-
{
	int64		id;
	int32	item_data_id;
	int64   ownerId;
	int16	x; // in logical
	int16	y;  // in logical
};

// trap look info
struct GS2C_LookInfoTrap  <-
{
	int64 id;
	int32	trapDataId;

	int16	x;   // in logical, 左上角的x坐标
	int16	y;   // in logical, 左上角的y坐标
	int16	dx;  // x 方向的长度
	int16	dy;  // y 方向的长度
};

// pet look info
struct GS2C_LookInfoPet  <-
{
	int64 id;
	int64 masterId; //主人的id
	int16	dataId;//在配置文件里的id
	string name;
	int16	level;

	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;

	int16	x;   // in logical,current position
	int16	y;   // in logical,current position
	int16	moveSpeed;
	int16   movedMs;
	int32	status;		// 状态标志位
	vector<PosInfo> posInfos;//路径节点，如果vector为空，不需要移动
};

struct GS2C_LookInfoDynamicTransferDoor <-
{
	int64		id;
	int32	door_data_id;
	int16	x; // in logical
	int16	y;  // in logical
	int8    cx; //在x方向上的长度
	int8    cy; //在y方向上的长度
};

// 物件消失
struct GS2C_ActorDisapearList<-
{
	vector<int64>		info_list;
};

struct GS2C_MonsterStopMove <-
{
	int64 id;//monster id
	int16 posX;// monster current position
	int16 posY;// monster current position
};
struct GS2C_MonsterMoveInfo    <-
{
	int64 	id;//monster id
	int16    posX;// monster current position
	int16    posY;// monster current position
	vector<PosInfo> posInfos;//move path
};


struct C2GS_PetMoveTo    ->
{
	int32 curMapDataId; // pet current map data id
	int16 posX;// pet current position
	int16 posY;// pet current position
	vector<PosInfo> posInfos;//move path
};



struct C2GS_PetStopMove ->
{
	int32 curMapDataId; // pet current map data id
	int16 posX;// pet current position
	int16 posY;// pet current position
};

struct GS2C_PetStopMove <-
{
	int64 id;//pet id
	int16 posX;// pet current position
	int16 posY;// pet current position
};

struct GS2C_PetMoveInfo    <-
{
	int64 	id;//pet id
	int16    posX;// pet current position
	int16    posY;// pet current position
	vector<PosInfo> posInfos;//move path
};



//玩家，怪物，宠物 瞬移
struct GS2C_RoleTeleport <-
{
	int64 id;//player or monster or pet id
	int16 posX;// 瞬移到的位置
	int16 posY;// 瞬移到的位置
};


struct C2GS_PetTeleport_OutOfView ->
{
	int32 curMapDataId; // pet current map data id
	int64 id;//pet id
};



struct PushRoleInfo   
{
	int64 id
	int16 curX;
	int16 curY;
	int16 targetX;
	int16 targetY;
};
struct GS2C_SkillPushRoleList <-
{
	int64 castId;//施放者id
	int32	skillId; //技能ID
	vector<PushRoleInfo> affectRoles;
};



struct C2GS_PlayerEvade->
{
	int32 curMapDataId; //player current map data id
	int16 desPosX;
	int16 desPosY;
};
struct GS2C_PlayerEvade    <-
{
	int64 	id;//player id
	int16 desPosX;
	int16 desPosY;
};


