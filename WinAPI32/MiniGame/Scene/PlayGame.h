#pragma once
#include "GameNode.h"
#include "MiniGame/map/TileMap.h"
#include "MiniGame/unit/UnitManager.h"
#include "MiniGame/Card.h"

class PlayGame : public GameNode
{
private:
	TileMap* m_tile;
	int mapIndex;
	bool m_isMapSelect;
	bool m_isInGame;
	bool m_isText;	//ó���� �ؽ�Ʈ ����ִ� �������� �ƴ���
	int m_textFrame;	//�ؽ�Ʈ ����ٶ� ���° �ؽ�Ʈ ������� 
	int m_frameHero;	//�ؽ�Ʈ ���ϴ� ������ ������
	
	int m_whoHero;		//0�� �����̳� 1�� �潺ũ 2�� �ɸ��� 3�� �������ε� 4�� �Ƹ�Ÿ�Ͻ� 5�� ���//� ���� �̹����� �׷����� �˷��ֱ� ���� ����
	float m_frameTime;
	
	Image*	m_HeroImg[6];	//0�� �����̳� 1�� �潺ũ 2�� �ɸ��� 3�� �������ε� 4�� �Ƹ�Ÿ�Ͻ� 5�� ���//�ؽ�Ʈ ���ϴ� ������ �̹���
	bool goMenu;
private:
	UnitManager* m_unitManager;
private:
	Card* m_card;
	ST_Card* m_deck;
	string m_cardName[20];
	int m_totalCard;
private:
	float m_turnTime;		//���� �귯���� �ð�
	//float m_actionPoint;	//������      �������� ����.
	float m_turnMoneyBase;		//�ϸ��� ������ �� �⺻
	float m_turnMoney;			//�ϸ��� ������ �� (������Ʈ�� ���� �߰�)
	TURN m_turn;			//���� ���� ������ �Ͽ� ���� ������Ʈ�� �ٸ��� ó��
	float m_angle;			//�� �ð�ٴ��� ���ư��� ����

private:
	Image* m_guardImage;
	FRECT m_guardRc;
	D3DXVECTOR2 m_guardPos;
	D3DXVECTOR2 m_guardSize;

private:
	float m_aiUTime;
	float m_aiUDelay;
	float m_aiMTime;
	float m_aiMDelay;

public:
	PlayGame();
	~PlayGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void turn();

	void drawCard();
	//���ϴ� ī�带 ��ο����ִ� �Լ�()
	void drawCard(CARD_TYPE type);
	//�ǳ� ī�带 ������ �Ű��ִ� ���
	void guardCard();
	//ī�� ��ĭ�� �̵��ϴ� �Լ�
	void cardMove();

	//Ŭ���� ���õ� ���� ����ġ��
	void clickUpdate();

	//ap�� �ִ��� �۾��� ap���ִ��� �̹���
	void renderText();

	//���� �������� ���ϴ� �ؽ�Ʈ
	void heroText();

	//�ʺ��� ���� ���ּ�ȯ�ϰ� �ϴ� �뵵
	void AI();
};

