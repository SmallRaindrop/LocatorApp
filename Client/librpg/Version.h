#ifndef __Version_h_
#define __Version_h_

#include <string>
using namespace std;

// °æ±¾ºÅ¶¨Òå
struct VersionDef
{
	int v0;
	int v1;
	int v2;

	VersionDef() : v0(0),v1(0),v2(0){}
	VersionDef(int a,int b,int c) : v0(a),v1(b),v2(c){}
	VersionDef(string str){sscanf(str.c_str(),"%d.%d.%d",&v0,&v1,&v2);}
	VersionDef(const VersionDef& ver) : v0(ver.v0),v1(ver.v1),v2(ver.v2){}

	inline string to_str(){
		char buf[20] = {0}; 
		sprintf(buf,"%02d.%02d.%02d",v0,v1,v2);
		return buf; 
	}

	inline string to_str_(){
		char buf[20] = {0}; 
		sprintf(buf,"%02d_%02d_%02d",v0,v1,v2);
		return buf; 
	}

	inline bool is_high_to(const VersionDef& ver){
		if ( v0 != ver.v0 )
		{
			return true;
		}

		if (v0 >= ver.v0 && v1 > ver.v1 )
		{
			return true;
		}

		if (v0 >= ver.v0 && v1 >= ver.v1 && v2 > ver.v2)
		{
			return true;
		}

		if (v0 >= ver.v0 && v1 >= ver.v1 && v2 >= ver.v2 )
		{
			return true;
		}

		return false;
	}

	inline bool is_v2_high_to(const VersionDef& ver){
		if ( v0 > ver.v0 )
		{
			return true;
		}

		if (v0 >= ver.v0 && v1 > ver.v1 )
		{
			return true;
		}

		if (v0 >= ver.v0 && v1 >= ver.v1 && v2 > ver.v2)
		{
			return true;
		}

		return false;
	}

	inline bool is_invalid_to(const VersionDef& ver){
		return v0 != ver.v0;
	}

	inline bool is_equal_to(const VersionDef& ver){
		return v0 == ver.v0 && v1 == ver.v1 && v2 == ver.v2 ;
	}

	inline bool is_v0_equal_to(const VersionDef& ver){
		return v0 == ver.v0;
	}

	inline bool is_v1_equal_to(const VersionDef& ver){
		return v1 == ver.v1;
	}

	inline bool is_v2_equal_to(const VersionDef& ver){
		return v2 == ver.v2;
	}
};

#endif
