#pragma once
#include<cocos2d.h>
#include<functional>
class Plant;
/*
* Card �̳��˲˵�����Ե�����Ժ󲻻������̳в˵����������ʹ��
*/
class CardBar;
class Card:public cocos2d::MenuItemImage
{
	float maxCd=5;
	float remainCD=5;
	int sunValue=0;
	bool _ready=true;
	cocos2d::ProgressTimer* cdP=nullptr;
	std::string targetName="Ĭ��";
protected:
	bool initWithTwoPicture(const std::string& normal, const std::string& disable);
	bool init()override;
public:
	enum class CardType {//��������
		Plant, Zombie
	}cardType;

	CREATE_FUNC(Card);
	//maxCd��ֲ��CD��sunValue���������ġ�normal����ͨʱͼƬ��disable��ת����ͼƬ,initCd�ǳ�ʼCD�İٷֱ�0����ʼ��ɫ��1��ʼ����
	static Card* create(float maxCd,int sunValue,const std::string& normal,const std::string& disable,float initCd=1) {
		auto c=Card::create();
		c->initWithTwoPicture(normal,disable);
		c->setCardConfig(maxCd,sunValue,1);
		return c;
	}

	void doCdComplete(float=0) {
		_ready = true;
		setEnabled(true);
	}
	void setTargetName(const std::string& name, CardType type) {
		targetName = name;
		cardType = type;
	}
	void setCardConfig(float CD,int sunValue, float initCd);
	void update(float f)override;
	Card();
	//Ĭ�ϵ����õĳ�ʼ��
	bool isEnoughPaySun();
	//ʹ�������ļ�������ʼ��
	virtual ~Card();
	//�����ȴʱ��
	float getCD(); 
	//��û�ʣ��ò��ܿ��Ʋ�����ȴ��ϡ�
	float RemainingCD();
	int getSunValue();
	//�ж��Ƿ�׼������
	bool isReady();
	//�����ť����õĺ������ѵ�ǰ��������С�
	void onClick();
	//��ǰclick��ֲ�ﱻ���á���ʼ��ȴ��ʱ��
	void place();
	//��������ֲ�����ʼ��ȴ��ʱ��
	void undoPlace();
	CardBar* getCardBar();
};

