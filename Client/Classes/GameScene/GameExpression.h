// 游戏表达式

#ifndef __GAME_EXPRESSION_H__
#define __GAME_EXPRESSION_H__

#include "GameDef.h"

// 脚步函数定义
typedef bool (*KeyFunc)(string param);

/* Name		：KeyFuncMapping
 * Author	：YueLiangYou
 * Date		: 2015-07-02
 * Desc		: 关键字和脚步函数映射结构
 * Param	: 
 * Return	: 
 */
struct KeyFuncMapping
{
	string	key;
	KeyFunc fn;
};

/* Name		：get_key_value
 * Author	：YueLiangYou
 * Date		: 2015-07-02
 * Desc		: 通过key和参数获取最后执行结果
 * Param	: key：关键字 param 脚本参数
 * Return	: 执行结果 true ，false
 */
bool get_key_value(const string& key,const string& param);

/* Name		：get_exp_value
 * Author	：YueLiangYou
 * Date		: 2015-07-02
 * Desc		: 获取一个脚本表达式的值
 * Param	: expression 脚本表达式
 * Return	: 执行结果 true ，false
 */
bool get_exp_value(const string& expression);

// 脚本函数列表 可扩展

// 等级达到多少级[10,20,30]，达到等级指定等级 true ，否则 false
bool game_exp_level(string param);
// 当前所在地图
bool game_exp_mapin(string param);
// 完成过那些引导
bool game_exp_guide(string param);
// 当前历程事件
bool game_exp_proc_event(string param);
#endif // __GAME_EXPRESSION_H__