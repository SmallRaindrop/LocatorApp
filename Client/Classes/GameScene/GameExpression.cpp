#include "GameExpression.h"
#include "Hero.h"
#include "GameProcess.h"

KeyFuncMapping key_func_mapping[] = {
	{"level",game_exp_level},
	{"mapin",game_exp_mapin},
	{"guide",game_exp_guide},
	{"proc_event",game_exp_proc_event},
	{"",nullptr}
};

bool get_key_value(const string& key,const string& param)
{
	for (int i = 0; ; ++i )
	{
		if ( key_func_mapping[i].key.empty() || key_func_mapping[i].fn == nullptr )
		{
			break;
		}

		if( key_func_mapping[i].key == key )
		{
			return key_func_mapping[i].fn(param);
		}
	}

	return false;
}

bool get_exp_value(const string& expression)
{
	if ( expression.empty() )
	{
		return true;
	}

	char key[64] = "";
	char param[256] = "";
	sscanf(expression.c_str(),"%[^;:,{}()](%[^()])",key,param);

	return get_key_value(key,param);
}

// 脚本函数列表 可扩展
bool game_exp_level(string param)
{
	vector<string> lv_list;
	StringUtil::StringSplit(param,",",lv_list);
	for (size_t i = 0; i < lv_list.size(); i++)
	{
		int lv = atoi(lv_list[i].c_str());
		if ( lv == 0 )
		{
			LOGE("game expression level(%s) error!",param.c_str());
			return false;
		}
		if ( gHero->GetLevel() >= lv )
		{
			return true;
		}
	}
	
	return false;
}

bool game_exp_mapin(string param)
{
	if ( !gMap )
	{
		return false;
	}

	vector<string> map_list;
	StringUtil::StringSplit(param,",",map_list);
	for (size_t i = 0; i < map_list.size(); i++)
	{
		int mapid = atoi(map_list[i].c_str());
		if ( mapid == 0 )
		{
			LOGE("game expression mapin(%s) error!",param.c_str());
			return false;
		}
		if ( gMap->getMapDataID() == mapid )
		{
			return true;
		}
	}

	return false;
}

bool game_exp_guide(string param)
{
	vector<string> guide_list;
	StringUtil::StringSplit(param,",",guide_list);
	for (size_t i = 0; i < guide_list.size(); i++)
	{
		int guideid = atoi(guide_list[i].c_str());
		if ( guideid == 0 )
		{
			LOGE("game expression guide(%s) error!",param.c_str());
			return false;
		}
		//if ( gHero->GetGuidePtr()->compare() == guideid )
		{
			return true;
		}
	}

	return false;
}

bool game_exp_proc_event(string param)
{
	vector<string> event_list;
	StringUtil::StringSplit(param,",",event_list);
	for (size_t i = 0; i < event_list.size(); i++)
	{
		int eventid = atoi(event_list[i].c_str());
		if ( eventid == 0 )
		{
			LOGE("game expression proc_event(%s) error!",param.c_str());
			return false;
		}
		if ( gGameProcess->GetCurrEventID() == eventid )
		{
			return true;
		}
	}

	return false;
}