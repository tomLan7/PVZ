#pragma once
class Plant;
class Zombies;
class SelectAble;
class BattlefieldScene;
class PlayerAgent;
class PVZDAO;
#include<string>
#include<Card.h>
class PVZUtil
{
	static PlayerAgent* playerAgent;
	static PVZDAO* pvzDAO;
public:
	static Plant* createPlant(const std::string& plantName);
	static Zombies* createZombie(const std::string& zombieName);
	static SelectAble* createSelectAble(const std::string& targetName,Card::CardType type);
	static BattlefieldScene* getBattleScene();
	/*template<typename T,typename TargetType> static T* as(TargetType&& a) {
		return dynamic_cast<T&&>(a);
	}*/
	static PlayerAgent* getPlayerAgent();
	static PVZDAO* getPVZDAO();
	enum class BodyType {
		Default,Zombie, PlantProjectile, Plant, home
	};
	static constexpr int ZombieFlag = 0x1;
	static constexpr int PlantProjectileFlag = 0x2;
	static constexpr int PlantFlag = 0x4;
	static constexpr int homeFlag = 0x8;
	static constexpr unsigned int bodyArgs[][3] = { {0,0,0}, {ZombieFlag,homeFlag | PlantProjectileFlag,0},
													{PlantProjectileFlag,ZombieFlag,0},{PlantFlag,0,0},{homeFlag,ZombieFlag,0} };
	static void setPhysicsBodyFlag(cocos2d::PhysicsBody* pb, BodyType bt);
	static void createAnimationToCache(const std::string& animationName, int frameCount, float durationTime, unsigned int loopCount = -1);
};