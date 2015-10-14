#pragma once

//C头文件
#include <stdio.h>
#include <string.h>
#include <errno.h>
//C++头文件
#include <cctype>
#include <cmath>
//STL头文件
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

inline int StringSplit( const string& str,const string& delimd,vector<string>& des )
{
	size_t start = 0;
	size_t pos = 0;

	if (str.empty())
		return 0;

	int delimdCount=0;
	for( unsigned int i = 0; ; i++ )
	{
		if( pos == str.npos )	break;

		pos = str.find(delimd,start);
		if( pos != str.npos )
			delimdCount++;
		des.push_back(str.substr( start, pos - start ));
		start = pos+delimd.size();
	}

	return delimdCount;
}

inline int StringSplitToInt( const string& str,const string& delimd,vector<int>& des )
{
	size_t start = 0;
	size_t pos = 0;

	if (str.empty())
		return 0;

	int delimdCount=0;
	for( unsigned int i = 0; ; i++ )
	{
		if( pos == str.npos )	break;

		pos = str.find_first_of(delimd,start);
		if( pos != str.npos )
			delimdCount++;
		des.push_back(atoi(str.substr( start, pos - start ).c_str()));
		start = pos+delimd.size();
	}

	return delimdCount;
}