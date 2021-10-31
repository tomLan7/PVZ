
#include<PVZHeader.h>
#include<PVZDAO.h>
using namespace cocos2d;
USING_NS_FGUI;
Plant* PVZUtil::createPlant(const std::string& plantName) {
	Plant* plant = nullptr;
	
	if (plantName=="SunFlower") {//匹配
		plant = Sunflower::create(); 
		//plant->setAgentWithSpriteWithFileName("sunFlowerE.png");
		//plant->setAgentWithGMoveClip(UIPackage::createObjectFromURL("ui://mhojugnftm252q")->as<GMovieClip>());
		plant->setAnimate("SunFlower1");
		plant->getAgent()->setColor(Color3B(150, 150, 150));
	}
	else
	if (plantName=="Peashooter") {
		plant=Peashooter::create();
		plant->setAnimate("Peashooter");
		plant->getAgent()->setColor(Color3B(200, 200, 200));
	}
	else
	{
		
		return nullptr;
	}
	plant->getAgent()->setOpacity(150);//让卡牌变得半透明
	plant->attachLifeBarToUnit(plant);
	plant->setPhysicBodyBySelfContentSize();
	return plant;
}

Zombies* PVZUtil::createZombie(const std::string& zombieName)
{
	Zombies* zombie=nullptr;
	if (zombieName=="Zombie") {

		zombie=Zombies::create();
		zombie->setAnimate("ZombieStand1");
		//zombie->setAgentWithSpriteWithFileName("Zombies1.png");
		zombie->setPhysicBodyBySelfContentSize();
		zombie->attachLifeBarToUnit(zombie);//会自动根据节点大小设置自己大小
	}
	else
	{
		
	}
	return zombie;
}

SelectAble* PVZUtil::createSelectAble(const std::string& targetName, Card::CardType type)
{
	switch (type)
	{
	case Card::CardType::Plant:
		return createPlant(targetName);
		break;
	case Card::CardType::Zombie:
		return createZombie(targetName);
		break;
	default:
		return nullptr;
		break;
	}
}

BattlefieldScene* PVZUtil::getBattleScene() {
	return  dynamic_cast<BattlefieldScene*>(Director::getInstance()->getRunningScene());
}

PlayerAgent* PVZUtil::getPlayerAgent()
{
	if (playerAgent == nullptr) {
		playerAgent = PlayerAgent::create();
		playerAgent->retain();//增加一个引用计数，防止被cocos释放
		playerAgent->setLocalZOrder(100);
	}
	return playerAgent;
}
PlayerAgent* PVZUtil::playerAgent = nullptr;
PVZDAO* PVZUtil::getPVZDAO()
{
	if (pvzDAO == nullptr) {
		pvzDAO = new PVZDAO();
		
	}
	return pvzDAO;
}
PVZDAO* PVZUtil::pvzDAO = nullptr;
void PVZUtil::setPhysicsBodyFlag(PhysicsBody* pb, BodyType bt) {
	pb->setCategoryBitmask(bodyArgs[(int)bt][0]);
	pb->setContactTestBitmask(bodyArgs[(int)bt][1]);
	pb->setCollisionBitmask(bodyArgs[(int)bt][2]);
}
void PVZUtil::createAnimationToCache(const std::string& animationName,int frameCount,float durationTime,unsigned int loopCount)
{
	auto a1 = Animation::create();

	char buff[512];
	for (int i = 0; i < frameCount; i++) {
		sprintf(buff, "animation/%s_%04d.png",animationName.c_str(), i);
		a1->addSpriteFrameWithFile(buff);
	}
	a1->setDelayPerUnit(durationTime/frameCount);
	a1->setLoops(loopCount);
	
	AnimationCache::getInstance()->addAnimation(a1, animationName);
}