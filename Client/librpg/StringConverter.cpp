#include "StringConverter.h"

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转整形
string StringConverter::toString( const int& vaule, unsigned short width, char fill,  std::ios::fmtflags flags )
{
	std::ostringstream outStream;

	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();
	
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 整形转字符
string StringConverter::toString( const unsigned int& vaule, unsigned short width, char fill, std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();

}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 短整形转字符
string StringConverter::toString( const short& vaule, unsigned short width, char fill,  std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 整形转字符
string StringConverter::toString( const unsigned short& vaule, unsigned short width, char fill, std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();

}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 长整形转字符
string StringConverter::toString( const long& vaule, unsigned short width, char fill,  std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();
}


// ---------------------------------------------------------------------------------------------------------------------------------------
// 无符号长整形转字符
string StringConverter::toString( const unsigned long& vaule, unsigned short width, char fill,  std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.width(width);
	outStream.fill(fill);
	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();
}
string StringConverter::toString( const long long& vaule, unsigned short width , char fill,  std::ios::fmtflags flags  )
{
    std::ostringstream outStream;
    outStream.width(width);
    outStream.fill(fill);
    if(flags)
    {
        outStream.setf(flags);
    }

    outStream<<vaule;
    return outStream.str();
}
// ---------------------------------------------------------------------------------------------------------------------------------------
// float转string
string StringConverter::toString( const float& vaule, unsigned short precision, unsigned short width, char fill,  std::ios::fmtflags flags )
{
	std::ostringstream outStream;
	outStream.precision(precision);
	outStream.width(width);
	outStream.fill(fill);

	if(flags)
	{
		outStream.setf(flags);
	}

	outStream<<vaule;
	return outStream.str();
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// bool转string
string StringConverter::toString( bool vaule, bool YesNo )
{
	if(YesNo)
	{
		if(vaule) return "yes";
		else return "no";
	}
	else
	{
		if(vaule) return "true";
		else  return "false";
	}

}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符容器转string
void StringConverter::toString( const vector<string>& vaule, string& outText )
{

	for( unsigned i =0; i < vaule.size(); i++ )
	{
		outText += vaule[i] + '\n';
	}
}

// 字符Map转string
void StringConverter::toString( const map<string,string>& vaule, string& outText )
{
	map<string,string>::const_iterator beginIt = vaule.begin();
	map<string,string>::const_iterator endIt = vaule.end();

	while( beginIt != endIt )
	{
		outText += beginIt->second + '\n';
		beginIt++;
	} 
	
}


// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转整形
int StringConverter::toInt( const string& vaule )
{
	std::istringstream inStream(vaule);
	int Ret = 0;
	inStream>>Ret;
	return Ret;
}


// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转无符号整形
unsigned int StringConverter::toUnsignedInt( const string& vaule)
{
	std::istringstream inStream(vaule);
	unsigned int Ret = 0;
	inStream>>Ret;
	return Ret;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转短整形
short StringConverter::toShort( const string& vaule )
{
	std::istringstream inStream(vaule);
	short Ret = 0;
	inStream>>Ret;
	return Ret;
}


// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转无符号短整形
unsigned short StringConverter::toUnsignedShort( const string& vaule)
{
	std::istringstream inStream(vaule);
	unsigned short Ret = 0;
	inStream>>Ret;
	return Ret;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转短整形
long StringConverter::toLong( const string& vaule )
{
	std::istringstream inStream(vaule);
	long Ret = 0;
	inStream>>Ret;
	return Ret;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转无符号短整形
unsigned long StringConverter::toUnsignedLong( const string& vaule)
{
	std::istringstream inStream(vaule);
	unsigned long Ret = 0;
	inStream>>Ret;
	return Ret;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// 字符转float
float StringConverter::toFloat( const string& vaule)
{
	std::istringstream inStream(vaule);
	float Ret = 0.0f;
	inStream>>Ret;
	return Ret;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// bool转string
bool StringConverter::toBool(const string& vaule )
{
	return (vaule == "yes" || vaule == "true" || vaule == "1" );
}

// bool转string
long long StringConverter::toLongLong( const string& vaule )
{
    std::istringstream inStream(vaule);
    long long Ret = 0;
    inStream>>Ret;
    return Ret;
}

unsigned char StringConverter::toUnsignedChar( const string& vaule )
{
	std::istringstream inStream(vaule);
	unsigned char Ret = 0;
	inStream>>Ret;
	return Ret;
}

