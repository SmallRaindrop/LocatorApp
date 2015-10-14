#include "ArmatureManager.h"
#include "Effect.h"
#include "Role.h"

ArmatureManager::ArmatureManager()
{

}

ArmatureManager::~ArmatureManager()
{
	ArmatureDataManager::destroyInstance();
}

void ArmatureManager::loadArmatureFileForEffect(int dataid,Effect* pEffect)
{
	__String str;
	str.initWithFormat("assets/effect/%d.ExportJson",dataid);
	// 注册前先retain一次
	pEffect->retain();
	m_ncEffect.registerElement(dataid,pEffect);
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(ArmatureManager::onArmatureComplete));
}

void ArmatureManager::loadArmatureFileForRole(int dataid,Role* pRole)
{
	__String str;
	str.initWithFormat("assets/role/%d.ExportJson",dataid);
	// 注册前先retain一次
	pRole->retain();
	m_ncRole.registerElement(dataid,pRole);
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(ArmatureManager::onArmatureComplete));
}

void ArmatureManager::onArmatureComplete(float percent)
{
	// 全部加载完毕
	if ( percent == 1.0f )
	{
		m_ncEffect.postNotifyAll();
		m_ncRole.postNotifyAll();
	}
}

Armature* ArmatureManager::getArmature(const string& name)
{
	ArmatureMap::iterator itr = m_mapArmatures.find(name);
	if ( itr != m_mapArmatures.end() )
	{
		return itr->second;
	}

	Armature* ret = Armature::create(name);
	if ( ret )
	{
		//m_mapArmatures[name] = ret;
		return ret;
	}

	return NULL;
}

Armature* ArmatureManager::cloneArmature(const Armature* armature)
{
	Armature *ret = new Armature();
	if ( !ret )
	{
		return NULL;
	}

	//bool bRet = false;
	//do
	//{
	//	ArmatureAnimation* animation = new ArmatureAnimation();
	//	animation->init(ret);
	//	ret->setAnimation(animation);

	//	

	//	_boneDic.clear();
	//	_topBoneList.clear();

	//	string name = armature->getName();

	//	ret->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
	//	ret->setName(name);
	//	ret->setBatchNode(armature->getBatchNode());
	//	ret->setParentBone(armature->getParentBone());
	//	ret->setVersion(armature->getVersion());

	//	ArmatureDataManager *armatureDataManager = ArmatureDataManager::getInstance();

	//	if(!_name.empty())
	//	{
	//		AnimationData *animationData = armatureDataManager->getAnimationData(name);
	//		CCASSERT(animationData, "AnimationData not exist! ");

	//		ret->getAnimation()->setAnimationData(animationData);


	//		ArmatureData *armatureData = armatureDataManager->getArmatureData(name);
	//		CCASSERT(armatureData, "");

	//		ret->setArmatureData(armatureData);

	//		for (auto& element : armatureData->boneDataDic)
	//		{
	//			Bone *bone = createBone(element.first.c_str());
	//			//! init bone's  Tween to 1st movement's 1st frame
	//			do
	//			{
	//				MovementData *movData = animationData->getMovement(animationData->movementNames.at(0).c_str());
	//				CC_BREAK_IF(!movData);

	//				MovementBoneData *movBoneData = movData->getMovementBoneData(bone->getName().c_str());
	//				CC_BREAK_IF(!movBoneData || movBoneData->frameList.size() <= 0);

	//				FrameData *frameData = movBoneData->getFrameData(0);
	//				CC_BREAK_IF(!frameData);

	//				bone->getTweenData()->copy(frameData);

	//				bone->changeDisplayWithIndex(frameData->displayIndex, false);
	//			}
	//			while (0);
	//		}
	//		ret->update(0);
	//		ret->updateOffsetPoint();
	//	}

	//	ret->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

	//	ret->setCascadeOpacityEnabled(true);
	//	ret->setCascadeColorEnabled(true);
	//	bRet = true;
	//}
	//while (0);

	//return bRet;
	//
	return ret;
}