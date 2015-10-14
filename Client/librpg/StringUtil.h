/* Name		：StringUtil
 * Author	：YueLiangYou
 * Date		: 2015-06-24
 * Desc		: 字符串通用处理
 * Param	: none
 * Return	: void
 */

#ifndef StringUtils_h__
#define StringUtils_h__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class StringUtil
{
public:

    /** 把字符串转化为颜色 */
    static Color3B StringToColor( const string& str,const string& delimd="," );

	/** 把字符串转化为矩形 */
	static Rect StringToRect( const string& str,const string& delimd="," );

	/** 分割字符串，str为源字符串，delimd为分隔符，des为输出的字符串容器 */
	static int StringSplit( const string& str,const string& delimd,vector<string>& des );
    static int StringSplit( const string& str,const string& delimd,list<string>& des );

    static void ReplaceStr(char* buf,std::string str,std::string pattern,std::string dstPattern,int count=-1);
    static void ReplaceStr(std::string& str,std::string pattern,std::string dstPattern,int count=-1);

	/*去空格*/
	static void StringTrim(string& str,char ch=' ');

    //转小写
    static void StringToLower(string& str);

    //转大写
    static void StringToUper(string& str);

	/* Name		：StringCut
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 字符串截断函数，按字截断，一个汉字为三个字，英文字母和数字一个字 
	 * Param	: str 源字符串，max 最大字数，tail 截断后增加加尾部
	 * Return	: 地图名称
	 */
	static string StringCut(const string& str,int max,const string& tail);

	/* Name		：StringCutFileName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 去掉文件名后缀
	 * Param	: none
	 * Return	: 文件名不带后缀
	 */
	static string StringCutFileName(const string& fileName);
};


#endif // StringUtils_h__
