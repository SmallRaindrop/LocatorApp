#ifndef __StringConverter_H__
#define __StringConverter_H__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <sstream>

using namespace std;

class StringConverter
{
public:

	// 整形转字符
	static string toString( const int& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

	// 无符号整形转字符
	static string toString( const unsigned int& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

	// 短整形转字符
	static string toString( const short& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

	// 无符号短整形转字符
	static string toString( const unsigned short& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

	// 长整形转字符
	static string toString( const long& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

	// 无符号长整形转字符
	static string toString( const unsigned long& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );

    // 无符号长整形转字符
    static string toString( const long long& vaule, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0) );
	
	// float转string
	static string toString( const float& vaule, unsigned short precision, unsigned short width = 0, char fill = ' ',  std::ios::fmtflags flags = std::ios::fmtflags(0));

	// bool转string
	static string toString( bool vaule, bool YesNo );

	// 字符容器转string
	static void toString( const vector<string>& vaule, string& outText );

	// 字符Map转string
	static void toString( const map<string,string>& vaule, string& outText );

	// 字符转整形
	static int toInt( const string& vaule);

	// 字符转无符号整形
	static unsigned int toUnsignedInt( const string& vaule);

	// 字符转短整形
	static short toShort( const string& vaule);

	// 字符转无符号短整形
	static unsigned short toUnsignedShort( const string& vaule);

	// 字符转无符号短整形
	static unsigned char toUnsignedChar( const string& vaule);

	// 字符转长整形
	static long toLong( const string& vaule);

	// 字符转无符号长整形
	static unsigned long toUnsignedLong( const string& vaule);

	// 字符转float
	static float toFloat( const string& vaule);

	// bool转string
	static bool toBool( const string& vaule );

    // bool转string
    static long long toLongLong( const string& vaule );

};


#endif // __StringConverter_H__
