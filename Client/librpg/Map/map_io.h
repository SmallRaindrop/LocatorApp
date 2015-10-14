/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图文件读写相关
 * 地图文件格式 .map：
 * 1. 地图文件头
 * 2. 地图图片数据
 * 3. 地图遮挡物件图片数据
 */

#ifndef __map_io_h_
#define __map_io_h_

#include "commonRef.h"
#include "map_def.h"

namespace map_io
{
	/* Name		：load_from_map
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 从MAP文件中读入地图
	 * Param	: map_file .map格式文件名，context 地图上下文 包含部分数据
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t load_from_map(const char* map_file,map_context* context);

	/* Name		：map_free
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 释放地图上下文
	 * Param	: context 地图上下文
	 * Return	: void
	 */
	void map_free(map_context* context);

	/* Name		：read_image_data
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图图片信息
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	Data read_image_data(const char* map_file,int index,map_context* context);

	/* Name		：read_mask_image_data
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图遮挡图片信息
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	Data read_mask_image_data(const char* map_file,int index,map_context* context);

	/* Name		：read_map_header
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图文件头
	 * Param	: map_file 地图文件名称，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_header(const char* map_file,map_context* context);
	
	/* Name		：read_map_blocks
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图数据块
	 * Param	: map_file 地图文件名称，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_blocks(const char* map_file,map_context* context);

	/* Name		：read_map_block
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图数据块
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_block(ByteArray& array,map_context* context);

	/* Name		：read_map_terrain
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图地形
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_terrain(ByteArray& array,map_context* context);

	/* Name		：read_map_mask
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图遮挡信息
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_mask(ByteArray& array,map_context* context);

	/* Name		：read_map_part
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图部件信息
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_part(ByteArray& array,map_context* context);

	/* Name		：read_map_region
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 读入地图区域信息
	 * Param	: array 数据缓冲区，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t read_map_region(ByteArray& array,map_context* context);

	/* Name		：map_save
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图保存至.map格式文件
	 * Param	: map_file 地图文件名，context 地图上下文
	 * Return	: MAP_STATUS_OK成功，其他失败
	 */
	size_t map_save(const char* map_file,map_context* context);

	/* Name		：save_image_data
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图背景图片信息
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_image_data(FILE* fptr,map_context* context);

	/* Name		：save_mask_image_data
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图遮挡物件的图片信息
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_mask_image_data(FILE* fptr,map_context* context);

	/* Name		：save_map_header
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图文件头
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_header(FILE* fptr,map_context* context);

	/* Name		：save_map_blocks
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图数据块
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_blocks(FILE* fptr,map_context* context);

	/* Name		：save_map_terrain
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地形数据
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_terrain(FILE* fptr,map_context* context);

	/* Name		：save_map_mask
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入遮挡数据
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_mask(FILE* fptr,map_context* context);

	/* Name		：save_map_blocks
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图部件
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_part(FILE* fptr,map_context* context);

	/* Name		：save_map_blocks
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 写入地图区域数据
	 * Param	: fptr 地图文件指针，context 地图上下文
	 * Return	: 返回实际写入大小
	 */
	size_t save_map_region(FILE* fptr,map_context* context);

	//save tile map information to file
	size_t import_tmi(map_context* oldContext,map_context* context,const char *mapFileName);

};

#endif