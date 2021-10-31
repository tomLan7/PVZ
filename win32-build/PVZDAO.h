#pragma once
#include<string>
#include<unordered_map>
#include<vector>
#include<db/sqlite3.h>
class PVZDAO
{
protected:
	//id转名称
	std::string _DB_filename;
	//当前的user，缓存到内存中，flush会刷新到数据库中
	
	sqlite3* db=nullptr;
	PVZDAO()=default;
	friend class PVZUtil; 
	struct INFO_USER;
	INFO_USER* currentUser = nullptr;
public:
	//名称映射id
	std::unordered_map<int, std::string> _id2name;
	std::unordered_map<std::string, int> _name2id;

	struct INFO_USER {
		int id;
		std::string username;
		int coin_count;
		int current_level;
	} ;
	struct INFO_ZOMBIE {
		int id;
		std::string animation;
		int atk;
		float atk_freq;
		int hp;
		int moving_speed;
		int value_coin;
		std::string args;
	};
	struct INFO_PLANT {
		int id;
		std::string animation;
		int atk;
		float atk_freq;
		int hp;
		int value_sun;
		float cooling_time;
		std::string args;
	};
	int getId(std::string name); 
	std::string getName(int id);
	std::vector<int> allUserId();
	INFO_USER* getUserInfo(int id);
	INFO_ZOMBIE getZombieInfo(int id);
	INFO_PLANT getPlantInfo(int id);
	void flush(const std::string& filename="pvz_db.db");
	void refresh(const std::string& filename="pvz_db.db");
	//释放本类创建的元素的通用方法
	void destoryINFObject(void* obj);
	
};

