/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图相关数据结构定义
 */

#ifndef __Map_Def_H_
#define __Map_Def_H_

#ifndef CC_SAFE_DELETE
#define CC_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#endif

#ifndef CC_SAFE_DELETE_ARRAY
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#endif

#ifndef CC_SAFE_FREE
#define CC_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#endif

#ifndef CC_SAFE_RELEASE
#define CC_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#endif

#ifndef CC_SAFE_RELEASE_NULL
#define CC_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#endif

#ifndef CC_SAFE_RETAIN
#define CC_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#endif

#ifndef CC_BREAK_IF
#define CC_BREAK_IF(cond)            if(cond) break
#endif

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

#include <string>
using namespace std;

#define tileInPixelsX	256	
#define tileInPixelsY	256

#define cellInPixelsX	110
#define cellInPixelsY	78


// 方向相关定义
enum __Dir{
	DIR_N=0,
	DIR_NE,
	DIR_E,
	DIR_SE,
	DIR_S,
	DIR_SW,
	DIR_W,
	DIR_NW,
	DIR_MAX
};

const int _DELTA_CX[DIR_MAX]={-1,0,1,1,1,0,-1,-1};
const int _DELTA_CY[DIR_MAX]={-1,-1,-1,0,1,1,1,0};

const float _DELTA_X[DIR_MAX]={0.0f,cellInPixelsX/2,cellInPixelsX,cellInPixelsX/2,0.0f,-cellInPixelsX/2,-cellInPixelsX,-cellInPixelsX/2};
const float _DELTA_Y[DIR_MAX]={cellInPixelsY,cellInPixelsY/2,0.0f,-cellInPixelsY/2,-cellInPixelsY,-cellInPixelsY/2,0.0f,cellInPixelsY/2};

#define Distance(X,Y,X0,Y0)	MAX(abs(X-X0),abs(Y-Y0))

#define XMAP_SIG 0x583def

// 地图块ID定义
enum map_block_id
{
	MAP_BLOCK_FAR = 1000,	// 地图远景层
	MAP_BLOCK_TERRAIN,		// 地图地表层
	MAP_BLOCK_MASK,			// 地图遮挡数据
	MAP_BLOCK_PART,
	MAP_BLOCK_REGION,
};

// 块ID，块大小，块数据
struct map_block
{
	int			id;
	int			size;
	char*		data;
};

// 1. 地图文件头
// 2. 地图块数据
// 3. 

struct map_header
{
	map_header()
	{
		memset(this,0,sizeof(map_header));
	}
	int signature;	// XMAP
	int version;	// 版本号
	int width;		// 地图宽
	int height;		// 地图高
	int mode;		// 预留
	int block_offset;	// 块数据偏移位置
	int block_size;	// 块数据大小
};

struct tile_image_data
{
	int offset;
	int size;
};

struct map_terrain
{
	map_terrain()
	{
		memset(this,0,sizeof(map_terrain));
	}
	int tile_count;		// 分块数
	int format;			// 图片数据格式
	int cell_size_x;	// 逻辑坐标X轴大小
	int cell_size_y;	// 逻辑坐标Y轴大小
	int cell_origin_x;	// 逻辑坐标系原点
	int cell_origin_y;
	int cell_data_size;
	int tile_data_size;
	int image_data_offset;	// 地形图片数据	
	int image_data_size;
	unsigned char* cell_data;
	struct tile_image_data *tile_data;	// 存放每个瓦片图片数据的偏移地址和长度
	unsigned char* image_data;
};

struct map_mask
{
	int x,y,w,h;
	int relate_data_size;		// 遮挡关系数据长度
	int mask_data_offset;		// 遮挡数据偏移地址
	int mask_data_size;			// 遮挡数据总长度，包括遮挡关系和遮挡数据
	unsigned char* mask_data;
};

struct map_part
{
	int x,y,h;
	int dataid;
	string name;
};

struct map_region_property
{
	string name;
	int val;
};

struct map_region
{
	int x,y,w,h;
	int property_count;
	map_region_property* properties;
};

enum map_status
{
	MAP_STATUS_OK,				// 成功
	MAP_STATUS_FILE_NOT_FOUND,	// 未找到文件
	MAP_STATUS_INVALID_FILE,	// 非法的.map文件
	MAP_STATUS_INVALID_PSD,		// 未按要求制作的PSD文件
	MAP_STATUS_INVALID_CONTEXT,		// 非法的context
	MAP_STATUS_TERRAIN_NOT_FOUND,	// 未找到地形文件
	MAP_STATUS_READ_ERROR,
	MAP_STATUS_UNKNOWN_ERROR,
	MAP_STATUS_MALLOC,			// 分配内存出错
	MAP_STATUS_UNSUPPORT,		// 未支持
};

enum map_context_type
{
	MAP_CONTEXT_NON,		// 未加载
	MAP_CONTEXT_PSD,		// 已加载PSD
	MAP_CONTEXT_MAP,		// 已加载MAP
};

struct map_context
{
	map_context() : type(MAP_CONTEXT_NON)
	{
		block_count = 0;
		mask_count = 0;
		mask_data_offset = 0;
		mask_data_size = 0;
		masks = NULL;
		part_count = 0;
		parts = 0;
		region_count = 0;
		regions = 0;
	}
	string name;
	map_header header;
	int	type;
	int block_count;
	map_terrain terrain;
	int mask_count;
	int mask_data_offset;
	int mask_data_size;
	map_mask* masks;
	int part_count;
	map_part* parts;
	int region_count;
	map_region* regions;
};

#endif