#include "Role.h"
#include "RoleState_Dead.h"
#include "RoleEvent.h"
#include "Hero.h"

void DeadState::OnEnter(Role* pTarget)
{
	// 做死亡击飞
	//pTarget->playAction(RoleAction_Injured,0,0);

	//pTarget->stopAllActions();

	pTarget->playAction(RoleAction_Death,0,0);

	//ActionInterval* pAction = FadeIn::create(0.5f);
	//pTarget->runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(DeadState::HitActionCallBack,this,pTarget)),NULL));
}

void DeadState::OnLeave(Role* pTarget)
{

}

void DeadState::OnTimer(Role* pTarget,float dt)
{
	if ( pTarget->HasStateFlag(RoleStateFlag_DeadVirtual))
	{
		if ( pTarget->GetType() == mapObjectType_Player )
		{
			LOGE(" pTarget->GetType() == mapObjectType_Player");
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pTarget);
			if ( pPlayer!=nullptr )
			{
				float deadRestTime_ = pPlayer->GetDeadVirtualDeadRestTime();
				int percent_ = pPlayer->GetDeadVirtualPercent();		// 复活队友的单位点数
				int restPoint_ = pPlayer->GetDeadVirtualRestPoint();	// 复活队友的剩余点数
				int	helpNum_= pPlayer->GetDeadVirtualHelpNum();
				if (helpNum_>0)
				{
					LOGE("percent_(%d);", percent_);
					LOGE("pPlayer->SetDeadVirtualRestPoint(%d);",(int)(restPoint_ - percent_*dt));
					int temp_restPoint_ = (int)(restPoint_ - percent_*dt);
					if (temp_restPoint_<0)
					{
						temp_restPoint_= 0;
					}
					pPlayer->SetDeadVirtualRestPoint(temp_restPoint_);
				}else
				{
					LOGE("deadRestTime_:%f);",deadRestTime_);
					if (deadRestTime_<=0)
					{
						pPlayer->SetDeadVirtualDeadRestTime(0);
					}else
					{
						pPlayer->SetDeadVirtualDeadRestTime(deadRestTime_ - dt);
					}
				}
			}
		}
	}
}

void DeadState::OnEvent(Role* pTarget,IStateEvent* event)
{

}

void DeadState::HitActionCallBack(Role* pTarget)
{
	pTarget->playAction(RoleAction_Death,5000);
}