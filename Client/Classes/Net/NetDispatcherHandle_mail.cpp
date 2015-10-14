#include "GameDef.h"
#include "pk_mail.h"
#include "pk_item.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/MessageCenter.h"
#include "UI/GamePrompt.h"
#include "Common/DataPool.h"
#include "UI/MailUI.h"

namespace pk{

	bool OnGS2C_All_Mail_Info(struct pk::GS2C_All_Mail_Info *value)
	{
		if(value)
		{
			gDataPool->setMailList(value->vec);
		}

		return true;
	}


	bool OnGS2C_Send_Mail(GS2C_Send_Mail *value)
	{
		gDataPool->addMailToList(value->st);
		CMailUI* pUI = dynamic_cast<CMailUI*>(gGameUILayer->getActiveUI(IDU_MailUI));
		if (pUI)
		{
			pUI->updateMailList();
		}
		return true;
	}

	bool OnGS2C_Send_Mail_Result(GS2C_Send_Mail_Result *value)
	{
		if (value->retCode == 1)
		{
			gMessageCenter->SystemMessage(89);
			gCocosAudio->PlayEffect(69);
		}
		return true;
	}

	bool OnGS2C_Read_Mail_Result(GS2C_Read_Mail_Result *value)
	{
		if (value->retCode == 1)
		{
			int64 mail_id_ =value->mailId;
			gDataPool->setMailStateByID(mail_id_,1);
		}
		return true;
	}

	bool OnGS2C_Delete_Mail_Result(GS2C_Delete_Mail_Result *value)
	{
		switch(value->retCode)
		{
		case 1:
			break;
			//邮件不存在
		case -1:
			gMessageCenter->SystemMessage(431);
			break;
			// 有附件不能删除
		case -2:
			gMessageCenter->SystemMessage(430);
			break;
		default:
			break;
		}
		return true;
	}

	bool OnGS2C_Get_Attach_Result(GS2C_Get_Attach_Result *value)
	{
		switch(value->retCode)
		{
		case 1:
			{
				int64 mail_id_ = value->mailId;
				gDataPool->setMailStateByID(mail_id_,2);
				CMailUI* pUI = dynamic_cast<CMailUI*>(gGameUILayer->getActiveUI(IDU_MailUI));
				if (pUI)
				{
					pUI->updateMailContent(mail_id_);
				}
			}
			break;
		// 背包已经满了
		case -2:
			gMessageCenter->SystemMessage(322);
			gCocosAudio->PlayEffect(67);
			break;
		// 金钱超过界限
		case -3:
			gMessageCenter->SystemMessage(432);
			gCocosAudio->PlayEffect(67);
			break;
		default:
			break;
		}
		return true;
	}

	bool OnGS2C_Delete_Mail_List_Result(GS2C_Delete_Mail_List_Result *value)
	{
		switch(value->retCode)
		{
		case 1:
			{
				auto mail_id_list_ = value->mailIdList;
				for(auto iter = mail_id_list_.begin(); iter != mail_id_list_.end(); ++iter)
				{
					gDataPool->deleteMailByID((*iter));
				}
				CMailUI* pUI = dynamic_cast<CMailUI*>(gGameUILayer->getActiveUI(IDU_MailUI));
				if (pUI)
				{
					pUI->updateMailList();
				}
			}
			break;
		default:
			// 没有成功
			break;
		}
		return true;
	}
	bool OnGS2C_Get_Attach_List_Result(GS2C_Get_Attach_List_Result *value)
	{
		switch(value->retCode)
		{
		case 1:
			{
				auto mail_id_list_ = value->mailIdList;
				for(auto iter = mail_id_list_.begin(); iter != mail_id_list_.end(); ++iter)
				{
					gDataPool->setMailStateByID((*iter), 2);
				}
				CMailUI* pUI = dynamic_cast<CMailUI*>(gGameUILayer->getActiveUI(IDU_MailUI));
				if (pUI)
				{
					pUI->updateMailList();
				}
			}
			break;
		default:
			// 没有成功
			break;
		}
		return true;
	}

	
}

