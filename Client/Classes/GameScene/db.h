#ifndef __db_h_
#define __db_h_

#include "cfgFile.h"

struct ActiveCenterCfg{
	int		id;
	string	name;
	int		type;
	string	background;
	int		vipneed;
	int		level;
	int		frep_quantum;
	int		frep_quantum_vip;
	int		freq_day;
	int		freq_day_vip;
	int		playdate;
	string	playtime;
	string	playtypedesc;
	string	playtimedesc;
	string	rewardbasedesc;
	string	howjoin;
	int		buttonnum;
	string	buttontext0;
	string	buttontext1;
	string	buttonfun;
	string	howplay;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(type);
		pData->get(background);
		pData->get(vipneed);
		pData->get(level);
		pData->get(frep_quantum);
		pData->get(frep_quantum_vip);
		pData->get(freq_day);
		pData->get(freq_day_vip);
		pData->get(playdate);
		pData->get(playtime);
		pData->get(playtypedesc);
		pData->get(playtimedesc);
		pData->get(rewardbasedesc);
		pData->get(howjoin);
		pData->get(buttonnum);
		pData->get(buttontext0);
		pData->get(buttontext1);
		pData->get(buttonfun);
		pData->get(howplay);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s",id,name.c_str(),type,background.c_str(),vipneed,level,frep_quantum,frep_quantum_vip,freq_day,freq_day_vip,playdate,playtime.c_str(),playtypedesc.c_str(),playtimedesc.c_str(),rewardbasedesc.c_str(),howjoin.c_str(),buttonnum,buttontext0.c_str(),buttontext1.c_str(),buttonfun.c_str(),howplay.c_str());
	}
};

struct AchievementCfg{
	int		id;
	int		type;
	int		grade;
	int		finish_condition;
	int		is_progress;
	int		equipmentbaseid;
	int		validity;
	int		getnotice;
	int		firstnotice;
	int		award_honour;
	string	name;
	string	icon;
	string	nameicon;
	string	effects;
	string	desc;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(grade);
		pData->get(finish_condition);
		pData->get(is_progress);
		pData->get(equipmentbaseid);
		pData->get(validity);
		pData->get(getnotice);
		pData->get(firstnotice);
		pData->get(award_honour);
		pData->get(name);
		pData->get(icon);
		pData->get(nameicon);
		pData->get(effects);
		pData->get(desc);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s",id,type,grade,finish_condition,is_progress,equipmentbaseid,validity,getnotice,firstnotice,award_honour,name.c_str(),icon.c_str(),nameicon.c_str(),effects.c_str(),desc.c_str());
	}
};

struct Active_battle_monsterCfg{
	int		id;
	int		hp_origin;
	int		hp_rate;
	int		atk_origin;
	int		atk_rate;
	int		magic_atk_origin;
	int		magic_atk_rate;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(hp_origin);
		pData->get(hp_rate);
		pData->get(atk_origin);
		pData->get(atk_rate);
		pData->get(magic_atk_origin);
		pData->get(magic_atk_rate);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d",id,hp_origin,hp_rate,atk_origin,atk_rate,magic_atk_origin,magic_atk_rate);
	}
};

struct Active_battle_scoreCfg{
	int		id;
	string	killplayerscore;
	string	killbasescore;
	string	gatherscore;
	string	deadplayerscore;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(killplayerscore);
		pData->get(killbasescore);
		pData->get(gatherscore);
		pData->get(deadplayerscore);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%s",id,killplayerscore.c_str(),killbasescore.c_str(),gatherscore.c_str(),deadplayerscore.c_str());
	}
};

struct Active_battleCfg{
	int		id;
	int		level;
	int		cnt;
	string	playtime;
	int		teamexisttime;
	string	smallmonster;
	string	bigmonster;
	string	monstersoldiera;
	string	monstersoldierb;
	string	monsterdefensea;
	string	monsterdefenseb;
	string	monsterbarracksa;
	string	monsterbarracksb;
	string	monsterbasea;
	string	monsterbaseb;
	string	gatheritemid;
	string	gatheritempos;
	int		refreshmostertime;
	int		playermaxcnt;
	int		monstermaxcnt;
	int		recoveryareatimer;
	string	recoveryareaa;
	string	recoveryareab;
	int		addhp;
	int		addmp;
	int		reward_exp_win;
	int		reward_coin_win;
	int		reward_bindcoin_win;
	int		reward_honor_win;
	int		reward_exp_fail;
	int		reward_coin_fail;
	int		reward_bindcoin_fail;
	int		reward_honor_fail;
	int		reward_exp_draw;
	int		reward_coin_draw;
	int		reward_bindcoin_draw;
	int		reward_honor_draw;
	string	reward_item;
	string	buff;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(level);
		pData->get(cnt);
		pData->get(playtime);
		pData->get(teamexisttime);
		pData->get(smallmonster);
		pData->get(bigmonster);
		pData->get(monstersoldiera);
		pData->get(monstersoldierb);
		pData->get(monsterdefensea);
		pData->get(monsterdefenseb);
		pData->get(monsterbarracksa);
		pData->get(monsterbarracksb);
		pData->get(monsterbasea);
		pData->get(monsterbaseb);
		pData->get(gatheritemid);
		pData->get(gatheritempos);
		pData->get(refreshmostertime);
		pData->get(playermaxcnt);
		pData->get(monstermaxcnt);
		pData->get(recoveryareatimer);
		pData->get(recoveryareaa);
		pData->get(recoveryareab);
		pData->get(addhp);
		pData->get(addmp);
		pData->get(reward_exp_win);
		pData->get(reward_coin_win);
		pData->get(reward_bindcoin_win);
		pData->get(reward_honor_win);
		pData->get(reward_exp_fail);
		pData->get(reward_coin_fail);
		pData->get(reward_bindcoin_fail);
		pData->get(reward_honor_fail);
		pData->get(reward_exp_draw);
		pData->get(reward_coin_draw);
		pData->get(reward_bindcoin_draw);
		pData->get(reward_honor_draw);
		pData->get(reward_item);
		pData->get(buff);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s",id,level,cnt,playtime.c_str(),teamexisttime,smallmonster.c_str(),bigmonster.c_str(),monstersoldiera.c_str(),monstersoldierb.c_str(),monsterdefensea.c_str(),monsterdefenseb.c_str(),monsterbarracksa.c_str(),monsterbarracksb.c_str(),monsterbasea.c_str(),monsterbaseb.c_str(),gatheritemid.c_str(),gatheritempos.c_str(),refreshmostertime,playermaxcnt,monstermaxcnt,recoveryareatimer,recoveryareaa.c_str(),recoveryareab.c_str(),addhp,addmp,reward_exp_win,reward_coin_win,reward_bindcoin_win,reward_honor_win,reward_exp_fail,reward_coin_fail,reward_bindcoin_fail,reward_honor_fail,reward_exp_draw,reward_coin_draw,reward_bindcoin_draw,reward_honor_draw,reward_item.c_str(),buff.c_str());
	}
};

struct Active_wuziCfg{
	int		id;
	int		chess1;
	int		chess2;
	int		chess3;
	string	pos;
	int		score_die;
	int		score_pop1;
	int		score_pop2;
	int		score_pop3;
	int		score_pop4;
	int		score_pop5;
	int		hp_origin;
	int		hp_rate;
	int		reward_exp;
	int		reward_exp_rate;
	int		reward_coin;
	int		reward_coin_rate;
	string	reward_item;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(chess1);
		pData->get(chess2);
		pData->get(chess3);
		pData->get(pos);
		pData->get(score_die);
		pData->get(score_pop1);
		pData->get(score_pop2);
		pData->get(score_pop3);
		pData->get(score_pop4);
		pData->get(score_pop5);
		pData->get(hp_origin);
		pData->get(hp_rate);
		pData->get(reward_exp);
		pData->get(reward_exp_rate);
		pData->get(reward_coin);
		pData->get(reward_coin_rate);
		pData->get(reward_item);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",id,chess1,chess2,chess3,pos.c_str(),score_die,score_pop1,score_pop2,score_pop3,score_pop4,score_pop5,hp_origin,hp_rate,reward_exp,reward_exp_rate,reward_coin,reward_coin_rate,reward_item.c_str());
	}
};

struct AncientScrollCfg{
	int		id;
	int		base_level;
	int		max_level;
	int		capacity_comsume;
	string	attribute;
	string	skill_id;
	int		is_level_max_free_fight;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(base_level);
		pData->get(max_level);
		pData->get(capacity_comsume);
		pData->get(attribute);
		pData->get(skill_id);
		pData->get(is_level_max_free_fight);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%s,%s,%d",id,base_level,max_level,capacity_comsume,attribute.c_str(),skill_id.c_str(),is_level_max_free_fight);
	}
};

struct AttributeInfoCfg{
	int		id;
	string	name;
	int		index;
	int		base;
	int		min;
	int		max;
	int		detail_display;
	int		total_display;
	int		p1_display;
	int		p2_display;
	int		p3_display;
	int		p4_display;
	int		comment;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(index);
		pData->get(base);
		pData->get(min);
		pData->get(max);
		pData->get(detail_display);
		pData->get(total_display);
		pData->get(p1_display);
		pData->get(p2_display);
		pData->get(p3_display);
		pData->get(p4_display);
		pData->get(comment);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,name.c_str(),index,base,min,max,detail_display,total_display,p1_display,p2_display,p3_display,p4_display,comment);
	}
};

struct AudioCfg{
	int		id;
	string	file;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(file);
	}

	void format(char* str){
		sprintf(str,"%d,%s",id,file.c_str());
	}
};

struct AutofightCfg{
	int		id;
	string	skill10;
	string	skill11;
	string	skill12;
	string	skill20;
	string	skill21;
	string	skill22;
	string	skill30;
	string	skill31;
	string	skill32;
	string	hp;
	string	mp;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(skill10);
		pData->get(skill11);
		pData->get(skill12);
		pData->get(skill20);
		pData->get(skill21);
		pData->get(skill22);
		pData->get(skill30);
		pData->get(skill31);
		pData->get(skill32);
		pData->get(hp);
		pData->get(mp);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",id,skill10.c_str(),skill11.c_str(),skill12.c_str(),skill20.c_str(),skill21.c_str(),skill22.c_str(),skill30.c_str(),skill31.c_str(),skill32.c_str(),hp.c_str(),mp.c_str());
	}
};

struct BagGridCfg{
	int		id;
	int		a1;
	int		a2;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(a1);
		pData->get(a2);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,a1,a2);
	}
};

struct BluePrintCfg{
	int		id;
	int		use_number;
	int		item_id;
	int		occupy_flag;
	int		item_number;
	int		gold;
	int		time;
	int		treasure;
	string	material_1;
	string	material_2;
	string	material_3;
	string	material_4;
	string	material_5;
	string	material_6;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(use_number);
		pData->get(item_id);
		pData->get(occupy_flag);
		pData->get(item_number);
		pData->get(gold);
		pData->get(time);
		pData->get(treasure);
		pData->get(material_1);
		pData->get(material_2);
		pData->get(material_3);
		pData->get(material_4);
		pData->get(material_5);
		pData->get(material_6);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s",id,use_number,item_id,occupy_flag,item_number,gold,time,treasure,material_1.c_str(),material_2.c_str(),material_3.c_str(),material_4.c_str(),material_5.c_str(),material_6.c_str());
	}
};

struct BossRefreshCfg{
	int		id;
	string	notice;
	int		time;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(notice);
		pData->get(time);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d",id,notice.c_str(),time);
	}
};

struct BuffCfg{
	int		id;
	int		buff_level;
	int		resist_check;
	int		check_result;
	int		buff_type;
	int		layers;
	int		effect_type;
	int		p1;
	int		p2;
	int		p3;
	int		p4;
	int		p5;
	int		p6;
	string	dam_p1;
	string	dam_p2;
	int		dam_p3;
	int		heal_property;
	string	property;
	int		duration_to_player;
	int		duration_to_nonplayer;
	int		interval;
	int		multi_skill_duration;
	int		isremovedead;
	int		remove_by_other;
	int		isdebuff;
	string	name;
	int		detail_display;
	string	icon;
	string	art;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(buff_level);
		pData->get(resist_check);
		pData->get(check_result);
		pData->get(buff_type);
		pData->get(layers);
		pData->get(effect_type);
		pData->get(p1);
		pData->get(p2);
		pData->get(p3);
		pData->get(p4);
		pData->get(p5);
		pData->get(p6);
		pData->get(dam_p1);
		pData->get(dam_p2);
		pData->get(dam_p3);
		pData->get(heal_property);
		pData->get(property);
		pData->get(duration_to_player);
		pData->get(duration_to_nonplayer);
		pData->get(interval);
		pData->get(multi_skill_duration);
		pData->get(isremovedead);
		pData->get(remove_by_other);
		pData->get(isdebuff);
		pData->get(name);
		pData->get(detail_display);
		pData->get(icon);
		pData->get(art);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%d,%s,%s",id,buff_level,resist_check,check_result,buff_type,layers,effect_type,p1,p2,p3,p4,p5,p6,dam_p1.c_str(),dam_p2.c_str(),dam_p3,heal_property,property.c_str(),duration_to_player,duration_to_nonplayer,interval,multi_skill_duration,isremovedead,remove_by_other,isdebuff,name.c_str(),detail_display,icon.c_str(),art.c_str());
	}
};

struct BulletCfg{
	int		id;
	int		type;
	int		speed;
	int		radius;
	int		duration;
	int		multi_skill_duration;
	int		delay;
	int		castpoint;
	string	aim_art;
	string	flyart;
	string	hitart;
	string	blastart;
	int		hit_skill;
	string	blast_skill;
	int		penetrate;
	string	multi_track;
	int		multi_bullet;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(speed);
		pData->get(radius);
		pData->get(duration);
		pData->get(multi_skill_duration);
		pData->get(delay);
		pData->get(castpoint);
		pData->get(aim_art);
		pData->get(flyart);
		pData->get(hitart);
		pData->get(blastart);
		pData->get(hit_skill);
		pData->get(blast_skill);
		pData->get(penetrate);
		pData->get(multi_track);
		pData->get(multi_bullet);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%d,%s,%d,%s,%d",id,type,speed,radius,duration,multi_skill_duration,delay,castpoint,aim_art.c_str(),flyart.c_str(),hitart.c_str(),blastart.c_str(),hit_skill,blast_skill.c_str(),penetrate,multi_track.c_str(),multi_bullet);
	}
};

struct ChatCfg{
	int		id;
	int		displaytype;
	int		broadcasttype;
	string	content;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(displaytype);
		pData->get(broadcasttype);
		pData->get(content);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%s",id,displaytype,broadcasttype,content.c_str());
	}
};

struct ChestCfg{
	int		id;
	int		art_id;
	int		body_size;
	string	lock_type;
	int		destruction_time;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(art_id);
		pData->get(body_size);
		pData->get(lock_type);
		pData->get(destruction_time);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%s,%d",id,art_id,body_size,lock_type.c_str(),destruction_time);
	}
};

struct CommonCfg{
	int		id;
	int		param1;
	int		param2;
	int		param3;
	int		param4;
	int		param5;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(param1);
		pData->get(param2);
		pData->get(param3);
		pData->get(param4);
		pData->get(param5);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d",id,param1,param2,param3,param4,param5);
	}
};

struct Copy_stepCfg{
	int		id;
	string	desc;
	string	detail_desc;
	int		step_type;
	string	step_target;
	int		step_cnt;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(desc);
		pData->get(detail_desc);
		pData->get(step_type);
		pData->get(step_target);
		pData->get(step_cnt);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%d,%s,%d",id,desc.c_str(),detail_desc.c_str(),step_type,step_target.c_str(),step_cnt);
	}
};

struct DefTypeCfg{
	int		id;
	int		def_name;
	int		phy_res;
	int		fire_res;
	int		cold_res;
	int		elec_res;
	int		toxin_res;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(def_name);
		pData->get(phy_res);
		pData->get(fire_res);
		pData->get(cold_res);
		pData->get(elec_res);
		pData->get(toxin_res);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d",id,def_name,phy_res,fire_res,cold_res,elec_res,toxin_res);
	}
};

struct DigitAjustCfg{
	int		id;
	int		value;
	int		mod;
	int		name;
	int		description;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(value);
		pData->get(mod);
		pData->get(name);
		pData->get(description);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d",id,value,mod,name,description);
	}
};

struct DramaCfg{
	int		id;
	int		main;
	int		sub;
	int		mode;
	int		left_right;
	int		person_type;
	int		npc_id;
	string	chatstr;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(main);
		pData->get(sub);
		pData->get(mode);
		pData->get(left_right);
		pData->get(person_type);
		pData->get(npc_id);
		pData->get(chatstr);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%s",id,main,sub,mode,left_right,person_type,npc_id,chatstr.c_str());
	}
};

struct EquipBaseCfg{
	int		id;
	string	name;
	int		type;
	int		sub_type1;
	int		subtype;
	int		is_sole;
	int		weaponfix;
	string	skillid;
	int		base_capacity;
	int		base_enhance_level;
	int		enhance_item;
	string	enhance_item_number;
	string	enhance_money;
	int		art_id;
	string	descripe;
	string	attribute;
	string	attribute1;
	string	attribute2;
	string	attribute3;
	string	attribute4;
	string	attribute5;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(type);
		pData->get(sub_type1);
		pData->get(subtype);
		pData->get(is_sole);
		pData->get(weaponfix);
		pData->get(skillid);
		pData->get(base_capacity);
		pData->get(base_enhance_level);
		pData->get(enhance_item);
		pData->get(enhance_item_number);
		pData->get(enhance_money);
		pData->get(art_id);
		pData->get(descripe);
		pData->get(attribute);
		pData->get(attribute1);
		pData->get(attribute2);
		pData->get(attribute3);
		pData->get(attribute4);
		pData->get(attribute5);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%d,%d,%d,%s,%d,%d,%d,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s",id,name.c_str(),type,sub_type1,subtype,is_sole,weaponfix,skillid.c_str(),base_capacity,base_enhance_level,enhance_item,enhance_item_number.c_str(),enhance_money.c_str(),art_id,descripe.c_str(),attribute.c_str(),attribute1.c_str(),attribute2.c_str(),attribute3.c_str(),attribute4.c_str(),attribute5.c_str());
	}
};

struct EquipComposeCfg{
	int		id;
	int		rate1;
	int		rate2;
	int		rate3;
	int		rate4;
	int		rate5;
	int		rate6;
	int		rate7;
	int		rate8;
	int		rate9;
	int		rate10;
	int		rate11;
	int		rate12;
	int		itemdataid;
	int		itemcnt;
	int		moneycost;
	string	rabbet_rates;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(rate1);
		pData->get(rate2);
		pData->get(rate3);
		pData->get(rate4);
		pData->get(rate5);
		pData->get(rate6);
		pData->get(rate7);
		pData->get(rate8);
		pData->get(rate9);
		pData->get(rate10);
		pData->get(rate11);
		pData->get(rate12);
		pData->get(itemdataid);
		pData->get(itemcnt);
		pData->get(moneycost);
		pData->get(rabbet_rates);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",id,rate1,rate2,rate3,rate4,rate5,rate6,rate7,rate8,rate9,rate10,rate11,rate12,itemdataid,itemcnt,moneycost,rabbet_rates.c_str());
	}
};

struct EquipmenthiddenCfg{
	int		id;
	int		equipdataid;
	int		hp;
	int		mp;
	int		atk_l;
	int		atk_h;
	int		def;
	int		atk_magic_l;
	int		atk_magic_h;
	int		def_magic;
	int		hit;
	int		dodge;
	int		crit;
	int		speed;
	int		damage_add;
	int		damage_reduce;
	int		damage_magic_add;
	int		damage_magic_reduce;
	int		hit_rate;
	int		dodge_rate;
	int		crit_rate_add;
	int		crit_times_add;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(equipdataid);
		pData->get(hp);
		pData->get(mp);
		pData->get(atk_l);
		pData->get(atk_h);
		pData->get(def);
		pData->get(atk_magic_l);
		pData->get(atk_magic_h);
		pData->get(def_magic);
		pData->get(hit);
		pData->get(dodge);
		pData->get(crit);
		pData->get(speed);
		pData->get(damage_add);
		pData->get(damage_reduce);
		pData->get(damage_magic_add);
		pData->get(damage_magic_reduce);
		pData->get(hit_rate);
		pData->get(dodge_rate);
		pData->get(crit_rate_add);
		pData->get(crit_times_add);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,equipdataid,hp,mp,atk_l,atk_h,def,atk_magic_l,atk_magic_h,def_magic,hit,dodge,crit,speed,damage_add,damage_reduce,damage_magic_add,damage_magic_reduce,hit_rate,dodge_rate,crit_rate_add,crit_times_add);
	}
};

struct EquipmenthardCfg{
	int		id;
	int		sub_type;
	int		consolidatelevel;
	int		useitem;
	int		luckystone;
	int		luckystonerate;
	int		hp;
	int		mp;
	int		atk_l;
	int		atk_h;
	int		def;
	int		atk_magic_l;
	int		atk_magic_h;
	int		def_magic;
	int		hit;
	int		dodge;
	int		crit;
	int		speed;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(sub_type);
		pData->get(consolidatelevel);
		pData->get(useitem);
		pData->get(luckystone);
		pData->get(luckystonerate);
		pData->get(hp);
		pData->get(mp);
		pData->get(atk_l);
		pData->get(atk_h);
		pData->get(def);
		pData->get(atk_magic_l);
		pData->get(atk_magic_h);
		pData->get(def_magic);
		pData->get(hit);
		pData->get(dodge);
		pData->get(crit);
		pData->get(speed);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,sub_type,consolidatelevel,useitem,luckystone,luckystonerate,hp,mp,atk_l,atk_h,def,atk_magic_l,atk_magic_h,def_magic,hit,dodge,crit,speed);
	}
};

struct EquipRefineBonusCfg{
	int		id;
	int		index1;
	int		index2;
	int		index3;
	int		index4;
	int		index5;
	int		index6;
	int		index7;
	int		index8;
	int		index9;
	int		index10;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(index1);
		pData->get(index2);
		pData->get(index3);
		pData->get(index4);
		pData->get(index5);
		pData->get(index6);
		pData->get(index7);
		pData->get(index8);
		pData->get(index9);
		pData->get(index10);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,index1,index2,index3,index4,index5,index6,index7,index8,index9,index10);
	}
};

struct EquipRandomCfg{
	int		id;
	int		randtimes;
	int		randparam;
	int		hp_l;
	int		hp_h;
	int		hp_rate;
	int		hp_p_l;
	int		hp_p_h;
	int		hp_p_rate;
	int		mp_l;
	int		mp_h;
	int		mp_rate;
	int		mp_p_l;
	int		mp_p_h;
	int		mp_p_rate;
	int		atk_l;
	int		atk_h;
	int		atk_rate;
	int		atk_magic_l;
	int		atk_magic_h;
	int		atk_magic_rate;
	int		atk_p_l;
	int		atk_p_h;
	int		atk_p_rate;
	int		atk_magic_p_l;
	int		atk_magic_p_h;
	int		atk_magic_p_rate;
	int		def_l;
	int		def_h;
	int		def_rate;
	int		def_p_l;
	int		def_p_h;
	int		def_p_rate;
	int		def_magic_l;
	int		def_magic_h;
	int		def_magic_rate;
	int		def_magic_p_l;
	int		def_magic_p_h;
	int		def_magic_p_rate;
	int		damage_add_l;
	int		damage_add_h;
	int		damage_add_rate;
	int		damage_magic_add_l;
	int		damage_magic_add_h;
	int		damage_magic_add_rate;
	int		damage_reduce_l;
	int		damage_reduce_h;
	int		damage_reduce_rate;
	int		damage_magic_reduce_l;
	int		damage_magic_reduce_h;
	int		damage_magic_reduce_rate;
	int		damage_all_reduce_l;
	int		damage_all_reduce_h;
	int		damage_all_reduce_rate;
	int		hit_l;
	int		hit_h;
	int		hit_rate;
	int		dodge_l;
	int		dodge_h;
	int		dodge_rate;
	int		crit_l;
	int		crit_h;
	int		crit_rate;
	int		strength_l;
	int		strength_h;
	int		strength_rate;
	int		agility_l;
	int		agility_h;
	int		agility_rate;
	int		intelligence_l;
	int		intelligence_h;
	int		intelligence_rate;
	int		all_l;
	int		all_h;
	int		all_rate;
	int		speed_l;
	int		speed_h;
	int		speed_rate;
	int		poison_damage_l;
	int		poison_damage_h;
	int		poison_damage_rate;
	int		atk_max_l;
	int		atk_max_h;
	int		atk_max_rate;
	int		atk_magic_max_l;
	int		atk_magic_max_h;
	int		atk_magic_max_rate;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(randtimes);
		pData->get(randparam);
		pData->get(hp_l);
		pData->get(hp_h);
		pData->get(hp_rate);
		pData->get(hp_p_l);
		pData->get(hp_p_h);
		pData->get(hp_p_rate);
		pData->get(mp_l);
		pData->get(mp_h);
		pData->get(mp_rate);
		pData->get(mp_p_l);
		pData->get(mp_p_h);
		pData->get(mp_p_rate);
		pData->get(atk_l);
		pData->get(atk_h);
		pData->get(atk_rate);
		pData->get(atk_magic_l);
		pData->get(atk_magic_h);
		pData->get(atk_magic_rate);
		pData->get(atk_p_l);
		pData->get(atk_p_h);
		pData->get(atk_p_rate);
		pData->get(atk_magic_p_l);
		pData->get(atk_magic_p_h);
		pData->get(atk_magic_p_rate);
		pData->get(def_l);
		pData->get(def_h);
		pData->get(def_rate);
		pData->get(def_p_l);
		pData->get(def_p_h);
		pData->get(def_p_rate);
		pData->get(def_magic_l);
		pData->get(def_magic_h);
		pData->get(def_magic_rate);
		pData->get(def_magic_p_l);
		pData->get(def_magic_p_h);
		pData->get(def_magic_p_rate);
		pData->get(damage_add_l);
		pData->get(damage_add_h);
		pData->get(damage_add_rate);
		pData->get(damage_magic_add_l);
		pData->get(damage_magic_add_h);
		pData->get(damage_magic_add_rate);
		pData->get(damage_reduce_l);
		pData->get(damage_reduce_h);
		pData->get(damage_reduce_rate);
		pData->get(damage_magic_reduce_l);
		pData->get(damage_magic_reduce_h);
		pData->get(damage_magic_reduce_rate);
		pData->get(damage_all_reduce_l);
		pData->get(damage_all_reduce_h);
		pData->get(damage_all_reduce_rate);
		pData->get(hit_l);
		pData->get(hit_h);
		pData->get(hit_rate);
		pData->get(dodge_l);
		pData->get(dodge_h);
		pData->get(dodge_rate);
		pData->get(crit_l);
		pData->get(crit_h);
		pData->get(crit_rate);
		pData->get(strength_l);
		pData->get(strength_h);
		pData->get(strength_rate);
		pData->get(agility_l);
		pData->get(agility_h);
		pData->get(agility_rate);
		pData->get(intelligence_l);
		pData->get(intelligence_h);
		pData->get(intelligence_rate);
		pData->get(all_l);
		pData->get(all_h);
		pData->get(all_rate);
		pData->get(speed_l);
		pData->get(speed_h);
		pData->get(speed_rate);
		pData->get(poison_damage_l);
		pData->get(poison_damage_h);
		pData->get(poison_damage_rate);
		pData->get(atk_max_l);
		pData->get(atk_max_h);
		pData->get(atk_max_rate);
		pData->get(atk_magic_max_l);
		pData->get(atk_magic_max_h);
		pData->get(atk_magic_max_rate);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,randtimes,randparam,hp_l,hp_h,hp_rate,hp_p_l,hp_p_h,hp_p_rate,mp_l,mp_h,mp_rate,mp_p_l,mp_p_h,mp_p_rate,atk_l,atk_h,atk_rate,atk_magic_l,atk_magic_h,atk_magic_rate,atk_p_l,atk_p_h,atk_p_rate,atk_magic_p_l,atk_magic_p_h,atk_magic_p_rate,def_l,def_h,def_rate,def_p_l,def_p_h,def_p_rate,def_magic_l,def_magic_h,def_magic_rate,def_magic_p_l,def_magic_p_h,def_magic_p_rate,damage_add_l,damage_add_h,damage_add_rate,damage_magic_add_l,damage_magic_add_h,damage_magic_add_rate,damage_reduce_l,damage_reduce_h,damage_reduce_rate,damage_magic_reduce_l,damage_magic_reduce_h,damage_magic_reduce_rate,damage_all_reduce_l,damage_all_reduce_h,damage_all_reduce_rate,hit_l,hit_h,hit_rate,dodge_l,dodge_h,dodge_rate,crit_l,crit_h,crit_rate,strength_l,strength_h,strength_rate,agility_l,agility_h,agility_rate,intelligence_l,intelligence_h,intelligence_rate,all_l,all_h,all_rate,speed_l,speed_h,speed_rate,poison_damage_l,poison_damage_h,poison_damage_rate,atk_max_l,atk_max_h,atk_max_rate,atk_magic_max_l,atk_magic_max_h,atk_magic_max_rate);
	}
};

struct EquipRefineCostCfg{
	int		id;
	int		item;
	int		item_number;
	int		money;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(item);
		pData->get(item_number);
		pData->get(money);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d",id,item,item_number,money);
	}
};

struct EquipUpgradeCfg{
	int		id;
	int		level;
	int		rate;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(level);
		pData->get(rate);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,level,rate);
	}
};

struct FreefightplayerbaseCfg{
	int		id;
	int		level_up_exp;
	int		free_fight_exp;
	string	property;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(level_up_exp);
		pData->get(free_fight_exp);
		pData->get(property);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%s",id,level_up_exp,free_fight_exp,property.c_str());
	}
};

struct GameProcCfg{
	int		id;
	int		type;
	string	trigger_condition;
	int		func_type;
	string	params;
	int		succ;
	int		fail;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(trigger_condition);
		pData->get(func_type);
		pData->get(params);
		pData->get(succ);
		pData->get(fail);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%d,%s,%d,%d",id,type,trigger_condition.c_str(),func_type,params.c_str(),succ,fail);
	}
};

struct GameStringCfg{
	int		id;
	string	value;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(value);
	}

	void format(char* str){
		sprintf(str,"%d,%s",id,value.c_str());
	}
};

struct GatewayCfg{
	int		id;
	int		srcmap;
	int		srcx;
	int		srcy;
	int		desmap;
	int		desx;
	int		desy;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(srcmap);
		pData->get(srcx);
		pData->get(srcy);
		pData->get(desmap);
		pData->get(desx);
		pData->get(desy);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d",id,srcmap,srcx,srcy,desmap,desx,desy);
	}
};

struct GuideCfg{
	int		id;
	int		mode;
	int		controlid;
	int		clearui;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(mode);
		pData->get(controlid);
		pData->get(clearui);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d",id,mode,controlid,clearui);
	}
};

struct HallTechCfg{
	int		id;
	string	name;
	int		base_lv;
	int		max_lv;
	string	unlock_lv;
	string	gold;
	int		item;
	string	item_number;
	string	time;
	string	description1;
	string	description2;
	string	description3;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(base_lv);
		pData->get(max_lv);
		pData->get(unlock_lv);
		pData->get(gold);
		pData->get(item);
		pData->get(item_number);
		pData->get(time);
		pData->get(description1);
		pData->get(description2);
		pData->get(description3);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%s,%s,%d,%s,%s,%s,%s,%s",id,name.c_str(),base_lv,max_lv,unlock_lv.c_str(),gold.c_str(),item,item_number.c_str(),time.c_str(),description1.c_str(),description2.c_str(),description3.c_str());
	}
};

struct IndexFactorCfg{
	int		id;
	int		physicaldamfactor;
	int		firedamfactor;
	int		icedamfactor;
	int		electricdamfactor;
	int		toxindamfactor;
	int		physicalresfactor;
	int		fireresfactor;
	int		iceresfactor;
	int		electricresfactor;
	int		toxinresfactor;
	int		armorfactor;
	int		hpfactor;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(physicaldamfactor);
		pData->get(firedamfactor);
		pData->get(icedamfactor);
		pData->get(electricdamfactor);
		pData->get(toxindamfactor);
		pData->get(physicalresfactor);
		pData->get(fireresfactor);
		pData->get(iceresfactor);
		pData->get(electricresfactor);
		pData->get(toxinresfactor);
		pData->get(armorfactor);
		pData->get(hpfactor);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,physicaldamfactor,firedamfactor,icedamfactor,electricdamfactor,toxindamfactor,physicalresfactor,fireresfactor,iceresfactor,electricresfactor,toxinresfactor,armorfactor,hpfactor);
	}
};

struct ItemCfg{
	int		id;
	string	name;
	int		type;
	int		subtype;
	int		type_p1;
	int		type_p2;
	int		type_p3;
	int		artid;
	string	icon;
	string	dropicon;
	string	drop_art;
	int		have_only_one;
	int		overlaycnt;
	int		pricesell;
	int		bindtype;
	int		grade;
	int		quality;
	int		uselevel;
	int		career;
	int		sex;
	int		cdtime;
	int		validtime;
	string	desc;
	string	selldesc;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(type);
		pData->get(subtype);
		pData->get(type_p1);
		pData->get(type_p2);
		pData->get(type_p3);
		pData->get(artid);
		pData->get(icon);
		pData->get(dropicon);
		pData->get(drop_art);
		pData->get(have_only_one);
		pData->get(overlaycnt);
		pData->get(pricesell);
		pData->get(bindtype);
		pData->get(grade);
		pData->get(quality);
		pData->get(uselevel);
		pData->get(career);
		pData->get(sex);
		pData->get(cdtime);
		pData->get(validtime);
		pData->get(desc);
		pData->get(selldesc);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s",id,name.c_str(),type,subtype,type_p1,type_p2,type_p3,artid,icon.c_str(),dropicon.c_str(),drop_art.c_str(),have_only_one,overlaycnt,pricesell,bindtype,grade,quality,uselevel,career,sex,cdtime,validtime,desc.c_str(),selldesc.c_str());
	}
};

struct LegionTechCfg{
	int		id;
	string	name;
	string	effect;
	int		base_lv;
	int		max_lv;
	string	unlock_lv;
	string	gold;
	string	item_1;
	string	item_2;
	string	item_3;
	string	item_4;
	string	item_5;
	string	time;
	string	description1;
	string	description2;
	string	description3;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(effect);
		pData->get(base_lv);
		pData->get(max_lv);
		pData->get(unlock_lv);
		pData->get(gold);
		pData->get(item_1);
		pData->get(item_2);
		pData->get(item_3);
		pData->get(item_4);
		pData->get(item_5);
		pData->get(time);
		pData->get(description1);
		pData->get(description2);
		pData->get(description3);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",id,name.c_str(),effect.c_str(),base_lv,max_lv,unlock_lv.c_str(),gold.c_str(),item_1.c_str(),item_2.c_str(),item_3.c_str(),item_4.c_str(),item_5.c_str(),time.c_str(),description1.c_str(),description2.c_str(),description3.c_str());
	}
};

struct LevelawardCfg{
	int		level;
	string	name;
	string	ad1;
	string	ad2;
	string	ad3;
	int		price;
	string	awarditems;
	string	zhanshiawarditems;
	string	daoshiawarditems;
	string	gongjianawarditems;
	int		awardcoin;
	int		awardbindcoin;
	int		awardtreasure;

	int key(){ return level;}

	void read(cfgData* pData){
		pData->get(level);
		pData->get(name);
		pData->get(ad1);
		pData->get(ad2);
		pData->get(ad3);
		pData->get(price);
		pData->get(awarditems);
		pData->get(zhanshiawarditems);
		pData->get(daoshiawarditems);
		pData->get(gongjianawarditems);
		pData->get(awardcoin);
		pData->get(awardbindcoin);
		pData->get(awardtreasure);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d",level,name.c_str(),ad1.c_str(),ad2.c_str(),ad3.c_str(),price,awarditems.c_str(),zhanshiawarditems.c_str(),daoshiawarditems.c_str(),gongjianawarditems.c_str(),awardcoin,awardbindcoin,awardtreasure);
	}
};

struct LocaleCfg{
	int		id;
	string	name;
	int		type;
	int		area_id;
	int		unlock;
	int		unlock_p1;
	string	icon;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(type);
		pData->get(area_id);
		pData->get(unlock);
		pData->get(unlock_p1);
		pData->get(icon);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%d,%d,%s",id,name.c_str(),type,area_id,unlock,unlock_p1,icon.c_str());
	}
};

struct LoginawardCfg{
	int		id;
	int		days;
	string	name;
	string	ad1;
	string	ad2;
	string	ad3;
	string	awarditems;
	string	zhanshiawarditems;
	string	daoshiawarditems;
	string	gongjianawarditems;
	int		awardcoin;
	int		awardbindcoin;
	int		awardtreasure;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(days);
		pData->get(name);
		pData->get(ad1);
		pData->get(ad2);
		pData->get(ad3);
		pData->get(awarditems);
		pData->get(zhanshiawarditems);
		pData->get(daoshiawarditems);
		pData->get(gongjianawarditems);
		pData->get(awardcoin);
		pData->get(awardbindcoin);
		pData->get(awardtreasure);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d",id,days,name.c_str(),ad1.c_str(),ad2.c_str(),ad3.c_str(),awarditems.c_str(),zhanshiawarditems.c_str(),daoshiawarditems.c_str(),gongjianawarditems.c_str(),awardcoin,awardbindcoin,awardtreasure);
	}
};

struct MallCfg{
	int		id;
	int		itemid;
	int		item_type;
	int		number;
	int		discount;
	int		price;
	int		price_discount;
	int		price_lucky;
	int		lucky_chance;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(itemid);
		pData->get(item_type);
		pData->get(number);
		pData->get(discount);
		pData->get(price);
		pData->get(price_discount);
		pData->get(price_lucky);
		pData->get(lucky_chance);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d",id,itemid,item_type,number,discount,price,price_discount,price_lucky,lucky_chance);
	}
};

struct MapCfg{
	int		id;
	string	name;
	string	desc;
	string	map;
	int		enter_condition;
	int		task_copy_type;
	int		enemy_faction;
	int		type;
	int		functiontype;
	int		homemapid;
	int		level_l;
	int		level_h;
	int		maxplayer;
	int		bornx;
	int		borny;
	int		bornw;
	int		bornh;
	string	recover_life_ids;
	int		transmit_directly;
	int		dynamic_block;
	string	drop_orb;
	string	drop_rules;
	int		play_type;
	int		bindgold_bonus;
	int		exp_bonus;
	string	end_item_bonus;
	string	item_bonus_1;
	string	item_bonus_2;
	string	item_bonus_3;
	string	item_bonus_4;
	int		limit_second;
	int		free_cd;
	int		is_support_random;
	int		step_cnt;
	string	copy_steps;
	string	direct_target;
	string	guides;
	int		steps_per_selection;
	int		enter_drama;
	string	step_drama;
	string	param;
	string	sound;
	string	smallmap;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(desc);
		pData->get(map);
		pData->get(enter_condition);
		pData->get(task_copy_type);
		pData->get(enemy_faction);
		pData->get(type);
		pData->get(functiontype);
		pData->get(homemapid);
		pData->get(level_l);
		pData->get(level_h);
		pData->get(maxplayer);
		pData->get(bornx);
		pData->get(borny);
		pData->get(bornw);
		pData->get(bornh);
		pData->get(recover_life_ids);
		pData->get(transmit_directly);
		pData->get(dynamic_block);
		pData->get(drop_orb);
		pData->get(drop_rules);
		pData->get(play_type);
		pData->get(bindgold_bonus);
		pData->get(exp_bonus);
		pData->get(end_item_bonus);
		pData->get(item_bonus_1);
		pData->get(item_bonus_2);
		pData->get(item_bonus_3);
		pData->get(item_bonus_4);
		pData->get(limit_second);
		pData->get(free_cd);
		pData->get(is_support_random);
		pData->get(step_cnt);
		pData->get(copy_steps);
		pData->get(direct_target);
		pData->get(guides);
		pData->get(steps_per_selection);
		pData->get(enter_drama);
		pData->get(step_drama);
		pData->get(param);
		pData->get(sound);
		pData->get(smallmap);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%s,%s,%s,%d,%d,%s,%s,%s,%s",id,name.c_str(),desc.c_str(),map.c_str(),enter_condition,task_copy_type,enemy_faction,type,functiontype,homemapid,level_l,level_h,maxplayer,bornx,borny,bornw,bornh,recover_life_ids.c_str(),transmit_directly,dynamic_block,drop_orb.c_str(),drop_rules.c_str(),play_type,bindgold_bonus,exp_bonus,end_item_bonus.c_str(),item_bonus_1.c_str(),item_bonus_2.c_str(),item_bonus_3.c_str(),item_bonus_4.c_str(),limit_second,free_cd,is_support_random,step_cnt,copy_steps.c_str(),direct_target.c_str(),guides.c_str(),steps_per_selection,enter_drama,step_drama.c_str(),param.c_str(),sound.c_str(),smallmap.c_str());
	}
};

struct MonsterairuleCfg{
	int		id;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
	}

	void format(char* str){
		sprintf(str,"%d",id);
	}
};

struct MonsterBaseCfg{
	int		id;
	string	name;
	string	title;
	string	head;
	int		art_id;
	int		scale;
	int		skin;
	int		height;
	int		body_size;
	int		type;
	int		level;
	int		phy_dam;
	int		fire_dam;
	int		cold_dam;
	int		elec_dam;
	int		toxin_dam;
	int		def_type1;
	int		def_type2;
	int		armor;
	int		hp_max;
	int		accurate;
	int		dodge;
	int		crit;
	int		crit_dam_factor;
	int		speed;
	int		exp;
	int		gethittime;
	int		deadaway;
	int		attention;
	int		freefightexp;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(title);
		pData->get(head);
		pData->get(art_id);
		pData->get(scale);
		pData->get(skin);
		pData->get(height);
		pData->get(body_size);
		pData->get(type);
		pData->get(level);
		pData->get(phy_dam);
		pData->get(fire_dam);
		pData->get(cold_dam);
		pData->get(elec_dam);
		pData->get(toxin_dam);
		pData->get(def_type1);
		pData->get(def_type2);
		pData->get(armor);
		pData->get(hp_max);
		pData->get(accurate);
		pData->get(dodge);
		pData->get(crit);
		pData->get(crit_dam_factor);
		pData->get(speed);
		pData->get(exp);
		pData->get(gethittime);
		pData->get(deadaway);
		pData->get(attention);
		pData->get(freefightexp);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,name.c_str(),title.c_str(),head.c_str(),art_id,scale,skin,height,body_size,type,level,phy_dam,fire_dam,cold_dam,elec_dam,toxin_dam,def_type1,def_type2,armor,hp_max,accurate,dodge,crit,crit_dam_factor,speed,exp,gethittime,deadaway,attention,freefightexp);
	}
};

struct MonsterDoorCfg{
	int		id;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
	}

	void format(char* str){
		sprintf(str,"%d",id);
	}
};

struct MonsterdropCfg{
	int		id;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
	}

	void format(char* str){
		sprintf(str,"%d",id);
	}
};

struct MonsterdropruleCfg{
	int		id;
	int		times;
	int		nodrop;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(times);
		pData->get(nodrop);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,times,nodrop);
	}
};

struct MonsterGenerateCfg{
	int		id;
	int		map_data_id;
	int		refresh_mode;
	int		interval;
	string	fixed_seconds;
	int		monster_type_id;
	int		display_index;
	string	boss_address_img;
	int		boss_type;
	string	interval_des;
	string	rule_des;
	string	drop_item_ids;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(map_data_id);
		pData->get(refresh_mode);
		pData->get(interval);
		pData->get(fixed_seconds);
		pData->get(monster_type_id);
		pData->get(display_index);
		pData->get(boss_address_img);
		pData->get(boss_type);
		pData->get(interval_des);
		pData->get(rule_des);
		pData->get(drop_item_ids);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%s,%d,%d,%s,%d,%s,%s,%s",id,map_data_id,refresh_mode,interval,fixed_seconds.c_str(),monster_type_id,display_index,boss_address_img.c_str(),boss_type,interval_des.c_str(),rule_des.c_str(),drop_item_ids.c_str());
	}
};

struct NpcCfg{
	int		id;
	string	name;
	string	title;
	int		type;
	int		art_id;
	int		scale;
	int		skin;
	int		height;
	int		body_size;
	int		npchead;
	string	talk;
	int		dir;
	string	funcs;
	int		map;
	int		posx;
	int		posy;
	string	name_map;
	int		viewrange;
	string	taskchainlist;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(title);
		pData->get(type);
		pData->get(art_id);
		pData->get(scale);
		pData->get(skin);
		pData->get(height);
		pData->get(body_size);
		pData->get(npchead);
		pData->get(talk);
		pData->get(dir);
		pData->get(funcs);
		pData->get(map);
		pData->get(posx);
		pData->get(posy);
		pData->get(name_map);
		pData->get(viewrange);
		pData->get(taskchainlist);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%s,%d,%s,%d,%d,%d,%s,%d,%s",id,name.c_str(),title.c_str(),type,art_id,scale,skin,height,body_size,npchead,talk.c_str(),dir,funcs.c_str(),map,posx,posy,name_map.c_str(),viewrange,taskchainlist.c_str());
	}
};

struct Npc_functionCfg{
	int		id;
	int		type;
	string	name;
	string	param;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(name);
		pData->get(param);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%s",id,type,name.c_str(),param.c_str());
	}
};

struct Npc_transferCfg{
	int		id;
	int		srcmapid;
	int		 desmapid;
	int		des_x;
	int		des_y;
	int		biaozhi;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(srcmapid);
		pData->get( desmapid);
		pData->get(des_x);
		pData->get(des_y);
		pData->get(biaozhi);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d",id,srcmapid, desmapid,des_x,des_y,biaozhi);
	}
};

struct One_strokeCfg{
	int		id;
	string	dot;
	string	line;
	int		max_time;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(dot);
		pData->get(line);
		pData->get(max_time);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%d",id,dot.c_str(),line.c_str(),max_time);
	}
};

struct Open_lockCfg{
	int		id;
	int		random_min;
	int		random_max;
	int		section;
	int		max_time;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(random_min);
		pData->get(random_max);
		pData->get(section);
		pData->get(max_time);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d",id,random_min,random_max,section,max_time);
	}
};

struct PayCfg{
	int		id;
	int		gamemoney;
	int		ucmoney;
	int		state;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(gamemoney);
		pData->get(ucmoney);
		pData->get(state);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d",id,gamemoney,ucmoney,state);
	}
};

struct PetBaseCfg{
	int		id;
	string	name;
	string	head;
	int		art_id;
	int		type;
	int		phy_dam;
	int		fire_dam;
	int		cold_dam;
	int		elec_dam;
	int		toxin_dam;
	int		crit;
	int		crit_dam_factor;
	int		accurate;
	int		dodge;
	int		hp;
	int		armor;
	int		def_type1;
	int		def_type2;
	int		weaponfix;
	int		speed;
	int		normal_skill;
	string	skill;
	int		gethittime;
	int		view;
	int		body_size;
	int		pursuitrange;
	int		revivetime;
	int		base_capacity;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(head);
		pData->get(art_id);
		pData->get(type);
		pData->get(phy_dam);
		pData->get(fire_dam);
		pData->get(cold_dam);
		pData->get(elec_dam);
		pData->get(toxin_dam);
		pData->get(crit);
		pData->get(crit_dam_factor);
		pData->get(accurate);
		pData->get(dodge);
		pData->get(hp);
		pData->get(armor);
		pData->get(def_type1);
		pData->get(def_type2);
		pData->get(weaponfix);
		pData->get(speed);
		pData->get(normal_skill);
		pData->get(skill);
		pData->get(gethittime);
		pData->get(view);
		pData->get(body_size);
		pData->get(pursuitrange);
		pData->get(revivetime);
		pData->get(base_capacity);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d",id,name.c_str(),head.c_str(),art_id,type,phy_dam,fire_dam,cold_dam,elec_dam,toxin_dam,crit,crit_dam_factor,accurate,dodge,hp,armor,def_type1,def_type2,weaponfix,speed,normal_skill,skill.c_str(),gethittime,view,body_size,pursuitrange,revivetime,base_capacity);
	}
};

struct PetRefineBonusCfg{
	int		id;
	int		gold;
	int		item;
	int		item_number;
	int		refine_dam_factor;
	int		refine_hp;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(gold);
		pData->get(item);
		pData->get(item_number);
		pData->get(refine_dam_factor);
		pData->get(refine_hp);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d",id,gold,item,item_number,refine_dam_factor,refine_hp);
	}
};

struct PetSatiationCfg{
	int		id;
	int		satiation;
	int		dam_hp_factor;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(satiation);
		pData->get(dam_hp_factor);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,satiation,dam_hp_factor);
	}
};

struct PetLevelCfg{
	int		id;
	int		exp;
	int		lv_dam_factor;
	int		lv_hp;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(exp);
		pData->get(lv_dam_factor);
		pData->get(lv_hp);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d",id,exp,lv_dam_factor,lv_hp);
	}
};

struct PlayerExpCfg{
	int		level;
	int		exp;

	int key(){ return level;}

	void read(cfgData* pData){
		pData->get(level);
		pData->get(exp);
	}

	void format(char* str){
		sprintf(str,"%d,%d",level,exp);
	}
};

struct PlayerBaseCfg{
	int		id;
	int		career;
	int		level;
	int		hp_max;
	int		atk_power;
	int		dodge;
	int		speed;
	int		def_type1;
	int		def_type2;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(career);
		pData->get(level);
		pData->get(hp_max);
		pData->get(atk_power);
		pData->get(dodge);
		pData->get(speed);
		pData->get(def_type1);
		pData->get(def_type2);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d",id,career,level,hp_max,atk_power,dodge,speed,def_type1,def_type2);
	}
};

struct PortableShopCfg{
	int		id;
	int		moneytype;
	int		price;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(moneytype);
		pData->get(price);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,moneytype,price);
	}
};

struct QuestionCfg{
	int		id;
	int		type;
	string	title;
	string	a;
	string	b;
	string	c;
	string	d;
	int		optionnum;
	int		answer;
	int		maxerrcnt;
	int		itemdataid;
	string	mod;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(title);
		pData->get(a);
		pData->get(b);
		pData->get(c);
		pData->get(d);
		pData->get(optionnum);
		pData->get(answer);
		pData->get(maxerrcnt);
		pData->get(itemdataid);
		pData->get(mod);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%s",id,type,title.c_str(),a.c_str(),b.c_str(),c.c_str(),d.c_str(),optionnum,answer,maxerrcnt,itemdataid,mod.c_str());
	}
};

struct RandomNameCfg{
	int		id;
	string	name;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
	}

	void format(char* str){
		sprintf(str,"%d,%s",id,name.c_str());
	}
};

struct RecoverLifeRuleCfg{
	int		id;
	int		type;
	int		delay_seconds;
	int		consume_type;
	int		consume_cnt_or_id;
	int		recover_percent;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(delay_seconds);
		pData->get(consume_type);
		pData->get(consume_cnt_or_id);
		pData->get(recover_percent);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d",id,type,delay_seconds,consume_type,consume_cnt_or_id,recover_percent);
	}
};

struct SalebankCfg{
	int		id;
	int		type;
	string	name;
	int		subtype;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(name);
		pData->get(subtype);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%d",id,type,name.c_str(),subtype);
	}
};

struct ScrollUpgradeCfg{
	int		id;
	int		offer_copper;
	int		offer_silver;
	int		offer_golden;
	int		offer_jewel;
	int		offer_copper_core;
	int		offer_silver_core;
	int		offer_golden_core;
	int		offer_jewel_core;
	int		upgrade_copper;
	int		upgrade_silver;
	int		upgrade_golden;
	int		upgrade_jewel;
	int		money_cost_copper;
	int		money_cost_silver;
	int		money_cost_golden;
	int		money_cost_jewel;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(offer_copper);
		pData->get(offer_silver);
		pData->get(offer_golden);
		pData->get(offer_jewel);
		pData->get(offer_copper_core);
		pData->get(offer_silver_core);
		pData->get(offer_golden_core);
		pData->get(offer_jewel_core);
		pData->get(upgrade_copper);
		pData->get(upgrade_silver);
		pData->get(upgrade_golden);
		pData->get(upgrade_jewel);
		pData->get(money_cost_copper);
		pData->get(money_cost_silver);
		pData->get(money_cost_golden);
		pData->get(money_cost_jewel);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,offer_copper,offer_silver,offer_golden,offer_jewel,offer_copper_core,offer_silver_core,offer_golden_core,offer_jewel_core,upgrade_copper,upgrade_silver,upgrade_golden,upgrade_jewel,money_cost_copper,money_cost_silver,money_cost_golden,money_cost_jewel);
	}
};

struct SkillCfg{
	int		id;
	string	name;
	int		type;
	int		comboreset;
	string	comboskill;
	int		career;
	string	level_up;
	int		studylevel;
	int		maxlevel;
	int		atktype;
	int		normal_attack;
	int		passitive;
	int		skill_type;
	string	icon;
	string	specialeffects;
	int		targettype;
	int		rangetype;
	int		angle;
	int		range;
	int		distance;
	int		maxtarget;
	string	dam_p1;
	string	dam_p2;
	int		dam_p3;
	int		heal_property;
	int		dam_times;
	int		hit_judge;
	int		use_judge;
	int		cost;
	int		chanttime;
	int		increasecast;
	int		channelnum;
	int		firsthit;
	int		animationstart;
	int		animationend;
	int		globecooldown;
	int		cdtime;
	int		weaponrevise;
	int		increaseanimation;
	int		sound;
	string	chantanimation;
	string	chantart;
	string	castanimation;
	string	castart;
	string	aim_art;
	string	hitart;
	string	killaway;
	string	desc;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(type);
		pData->get(comboreset);
		pData->get(comboskill);
		pData->get(career);
		pData->get(level_up);
		pData->get(studylevel);
		pData->get(maxlevel);
		pData->get(atktype);
		pData->get(normal_attack);
		pData->get(passitive);
		pData->get(skill_type);
		pData->get(icon);
		pData->get(specialeffects);
		pData->get(targettype);
		pData->get(rangetype);
		pData->get(angle);
		pData->get(range);
		pData->get(distance);
		pData->get(maxtarget);
		pData->get(dam_p1);
		pData->get(dam_p2);
		pData->get(dam_p3);
		pData->get(heal_property);
		pData->get(dam_times);
		pData->get(hit_judge);
		pData->get(use_judge);
		pData->get(cost);
		pData->get(chanttime);
		pData->get(increasecast);
		pData->get(channelnum);
		pData->get(firsthit);
		pData->get(animationstart);
		pData->get(animationend);
		pData->get(globecooldown);
		pData->get(cdtime);
		pData->get(weaponrevise);
		pData->get(increaseanimation);
		pData->get(sound);
		pData->get(chantanimation);
		pData->get(chantart);
		pData->get(castanimation);
		pData->get(castart);
		pData->get(aim_art);
		pData->get(hitart);
		pData->get(killaway);
		pData->get(desc);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s,%s,%s",id,name.c_str(),type,comboreset,comboskill.c_str(),career,level_up.c_str(),studylevel,maxlevel,atktype,normal_attack,passitive,skill_type,icon.c_str(),specialeffects.c_str(),targettype,rangetype,angle,range,distance,maxtarget,dam_p1.c_str(),dam_p2.c_str(),dam_p3,heal_property,dam_times,hit_judge,use_judge,cost,chanttime,increasecast,channelnum,firsthit,animationstart,animationend,globecooldown,cdtime,weaponrevise,increaseanimation,sound,chantanimation.c_str(),chantart.c_str(),castanimation.c_str(),castart.c_str(),aim_art.c_str(),hitart.c_str(),killaway.c_str(),desc.c_str());
	}
};

struct SkillindexCfg{
	int		id;
	int		index1;
	int		index2;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(index1);
		pData->get(index2);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d",id,index1,index2);
	}
};

struct TaskCfg{
	int		id;
	string	title;
	int		type;
	int		copyid;
	int		loopcnt;
	int		previd;
	int		followid;
	int		level;
	int		useitemid;
	int		career;
	int		startnpc;
	int		endnpc;
	int		autogo;
	int		autoreturn;
	int		autoget;
	int		dropid;
	int		delaytime;
	int		awardexp;
	int		awardcoin;
	int		award_bind_treasure;
	int		awardbindcoin;
	int		awardhonour;
	string	awarditems;
	string	zhanshiawarditems;
	string	daoshiawarditems;
	string	gongjianawarditems;
	string	selectawarditems;
	string	target;
	string	targetpos;
	int		completelevel;
	string	targethittext;
	string	targetcontext;
	int		accept_drama;
	int		enter_copy_drama;
	int		quit_copy_drama;
	int		accept_id;
	int		doing_id;
	int		complete_id;
	string	acceptcontext;
	string	doingcontext;
	string	completecontext;
	string	progress;
	string	progresstitle;
	int		difficulty;
	int		weight;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(title);
		pData->get(type);
		pData->get(copyid);
		pData->get(loopcnt);
		pData->get(previd);
		pData->get(followid);
		pData->get(level);
		pData->get(useitemid);
		pData->get(career);
		pData->get(startnpc);
		pData->get(endnpc);
		pData->get(autogo);
		pData->get(autoreturn);
		pData->get(autoget);
		pData->get(dropid);
		pData->get(delaytime);
		pData->get(awardexp);
		pData->get(awardcoin);
		pData->get(award_bind_treasure);
		pData->get(awardbindcoin);
		pData->get(awardhonour);
		pData->get(awarditems);
		pData->get(zhanshiawarditems);
		pData->get(daoshiawarditems);
		pData->get(gongjianawarditems);
		pData->get(selectawarditems);
		pData->get(target);
		pData->get(targetpos);
		pData->get(completelevel);
		pData->get(targethittext);
		pData->get(targetcontext);
		pData->get(accept_drama);
		pData->get(enter_copy_drama);
		pData->get(quit_copy_drama);
		pData->get(accept_id);
		pData->get(doing_id);
		pData->get(complete_id);
		pData->get(acceptcontext);
		pData->get(doingcontext);
		pData->get(completecontext);
		pData->get(progress);
		pData->get(progresstitle);
		pData->get(difficulty);
		pData->get(weight);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%d,%d",id,title.c_str(),type,copyid,loopcnt,previd,followid,level,useitemid,career,startnpc,endnpc,autogo,autoreturn,autoget,dropid,delaytime,awardexp,awardcoin,award_bind_treasure,awardbindcoin,awardhonour,awarditems.c_str(),zhanshiawarditems.c_str(),daoshiawarditems.c_str(),gongjianawarditems.c_str(),selectawarditems.c_str(),target.c_str(),targetpos.c_str(),completelevel,targethittext.c_str(),targetcontext.c_str(),accept_drama,enter_copy_drama,quit_copy_drama,accept_id,doing_id,complete_id,acceptcontext.c_str(),doingcontext.c_str(),completecontext.c_str(),progress.c_str(),progresstitle.c_str(),difficulty,weight);
	}
};

struct TaskChainCfg{
	int		id;
	string	level;
	string	npcidlist;
	string	taskidlist;
	string	awardexp;
	string	awardcoin;
	string	awardbindcoin;
	string	awardhonor;
	string	randaward;
	string	award;
	int		loopcnt;
	int		triggerlevel;
	int		firstnpcid;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(level);
		pData->get(npcidlist);
		pData->get(taskidlist);
		pData->get(awardexp);
		pData->get(awardcoin);
		pData->get(awardbindcoin);
		pData->get(awardhonor);
		pData->get(randaward);
		pData->get(award);
		pData->get(loopcnt);
		pData->get(triggerlevel);
		pData->get(firstnpcid);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d",id,level.c_str(),npcidlist.c_str(),taskidlist.c_str(),awardexp.c_str(),awardcoin.c_str(),awardbindcoin.c_str(),awardhonor.c_str(),randaward.c_str(),award.c_str(),loopcnt,triggerlevel,firstnpcid);
	}
};

struct TransformpropCfg{
	int		id;
	int		atk;
	int		def;
	int		hp;
	int		mp;
	int		crit;
	int		atk_magic;
	int		def_magic;
	int		hit;
	int		dodge;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(atk);
		pData->get(def);
		pData->get(hp);
		pData->get(mp);
		pData->get(crit);
		pData->get(atk_magic);
		pData->get(def_magic);
		pData->get(hit);
		pData->get(dodge);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",id,atk,def,hp,mp,crit,atk_magic,def_magic,hit,dodge);
	}
};

struct TrapCfg{
	int		id;
	int		type;
	string	name;
	int		duration;
	int		resid;
	int		skill_id;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(type);
		pData->get(name);
		pData->get(duration);
		pData->get(resid);
		pData->get(skill_id);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%d,%d,%d",id,type,name.c_str(),duration,resid,skill_id);
	}
};

struct UpdateStringCfg{
	int		id;
	string	value;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(value);
	}

	void format(char* str){
		sprintf(str,"%d,%s",id,value.c_str());
	}
};

struct WeaponDevCfg{
	int		id;
	int		unlock_item;
	string	unlock_lv;
	int		price;
	int		gold;
	string	item_1;
	string	item_2;
	string	item_3;
	string	item_4;
	string	item_5;
	int		time;
	string	description1;
	string	description2;
	string	description3;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(unlock_item);
		pData->get(unlock_lv);
		pData->get(price);
		pData->get(gold);
		pData->get(item_1);
		pData->get(item_2);
		pData->get(item_3);
		pData->get(item_4);
		pData->get(item_5);
		pData->get(time);
		pData->get(description1);
		pData->get(description2);
		pData->get(description3);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%s,%d,%d,%s,%s,%s,%s,%s,%d,%s,%s,%s",id,unlock_item,unlock_lv.c_str(),price,gold,item_1.c_str(),item_2.c_str(),item_3.c_str(),item_4.c_str(),item_5.c_str(),time,description1.c_str(),description2.c_str(),description3.c_str());
	}
};

struct WingCfg{
	int		id;
	int		sub_type;
	int		level;
	int		max_level;
	int		career;
	string	summon_items;
	int		summon_recharge_acc;
	int		summon_level;
	string	upgrade_items;
	int		upgrade_bindmoney;
	string	name;
	string	desc;
	string	add_pro;
	string	special_fun;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(sub_type);
		pData->get(level);
		pData->get(max_level);
		pData->get(career);
		pData->get(summon_items);
		pData->get(summon_recharge_acc);
		pData->get(summon_level);
		pData->get(upgrade_items);
		pData->get(upgrade_bindmoney);
		pData->get(name);
		pData->get(desc);
		pData->get(add_pro);
		pData->get(special_fun);
	}

	void format(char* str){
		sprintf(str,"%d,%d,%d,%d,%d,%s,%d,%d,%s,%d,%s,%s,%s,%s",id,sub_type,level,max_level,career,summon_items.c_str(),summon_recharge_acc,summon_level,upgrade_items.c_str(),upgrade_bindmoney,name.c_str(),desc.c_str(),add_pro.c_str(),special_fun.c_str());
	}
};

struct WorldmapCfg{
	int		id;
	string	name;
	string	locale_id;
	string	display;
	int		unlock;
	int		unlock_p1;
	string	complete;

	int key(){ return id;}

	void read(cfgData* pData){
		pData->get(id);
		pData->get(name);
		pData->get(locale_id);
		pData->get(display);
		pData->get(unlock);
		pData->get(unlock_p1);
		pData->get(complete);
	}

	void format(char* str){
		sprintf(str,"%d,%s,%s,%s,%d,%d,%s",id,name.c_str(),locale_id.c_str(),display.c_str(),unlock,unlock_p1,complete.c_str());
	}
};



#endif