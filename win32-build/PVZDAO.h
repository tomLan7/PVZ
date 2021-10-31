#pragma once
#include<string>
#include<unordered_map>
#include<vector>
#include<db/sqlite3.h>
class PVZDAO
{
protected:
	//idת����
	std::string _DB_filename;
	//��ǰ��user�����浽�ڴ��У�flush��ˢ�µ����ݿ���
	
	sqlite3* db=nullptr;
	PVZDAO()=default;
	friend class PVZUtil; 
	struct INFO_USER;
	INFO_USER* currentUser = nullptr;
public:
	//����ӳ��id
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
	//�ͷű��ഴ����Ԫ�ص�ͨ�÷���
	void destoryINFObject(void* obj);
	
};

