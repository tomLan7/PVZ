#include "PVZDAO.h"
#include<PVZHeader.h>
#include<strstream>
#include<ostream>
#include<db/sqlite3.h>

using namespace std;
static int handleNameRId(void* pvzdao, int colNumber, char** colValue, char** colName) {
	PVZDAO* pd = (PVZDAO*)pvzdao;

	pd->_id2name.insert(make_pair(atoi(colValue[0]),colValue[1]));
	pd->_name2id.insert(make_pair(colValue[1], atoi(colValue[0])));
	return 0;
}
using namespace std;
void PVZDAO::refresh(const std::string& filename)
{
	if (db==nullptr) {
		sqlite3_open(filename.c_str(), &db);
	}
	
	_id2name.clear();
	_name2id.clear();
	sqlite3_exec(db,R"(
		SELECT id,
		name
		FROM id_mapping;
	)", handleNameRId,this,0);
}
void PVZDAO::destoryINFObject(void* obj)
{
	delete obj;
}
static int handleUserInfo(void* pvzdao, int colNumber, char** colValue, char** colName) {
	PVZDAO::INFO_USER* iu = (PVZDAO::INFO_USER*)pvzdao;
	iu->id = atoi(colValue[0]);
	iu->username = colValue[1];
	iu->coin_count = atoi(colValue[2]);
	iu->current_level = atoi(colValue[3]);

	return 0;
}

PVZDAO::INFO_USER* PVZDAO::getUserInfo(int id)
{
	INFO_USER* infouser=new INFO_USER;
	sqlite3_exec(db, 
		(ostringstream(R"(
		SELECT id,
       username,
       coin_count,
       current_level
	   FROM user_account WHERE id=)") 
	<< id << ";").str().c_str()
	, handleNameRId, infouser, 0);
	return infouser;
}
