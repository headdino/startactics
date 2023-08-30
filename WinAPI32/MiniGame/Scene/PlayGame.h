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
	bool m_isText;	//처음에 텍스트 띄워주는 상태인지 아닌지
	int m_textFrame;	//텍스트 띄워줄때 몇번째 텍스트 출력할지 
	int m_frameHero;	//텍스트 말하는 영웅용 프레임
	
	int m_whoHero;		//0은 짐레이너 1은 멩스크 2는 케리건 3은 오버마인드 4는 아르타니스 5는 듀란//어떤 영웅 이미지를 그려줄지 알려주기 위한 변수
	float m_frameTime;
	
	Image*	m_HeroImg[6];	//0은 짐레이너 1은 멩스크 2는 케리건 3은 오버마인드 4는 아르타니스 5는 듀란//텍스트 말하는 영웅용 이미지
	bool goMenu;
private:
	UnitManager* m_unitManager;
private:
	Card* m_card;
	ST_Card* m_deck;
	string m_cardName[20];
	int m_totalCard;
private:
	float m_turnTime;		//턴이 흘러가는 시간
	//float m_actionPoint;	//소지금      전역으로 뺀다.
	float m_turnMoneyBase;		//턴마다 들어오는 돈 기본
	float m_turnMoney;			//턴마다 들어오는 돈 (오브젝트에 따라 추가)
	TURN m_turn;			//현제 무슨 턴인지 턴에 따라서 업데이트를 다르게 처리
	float m_angle;			//턴 시계바늘이 돌아가는 각도

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
	//원하는 카드를 드로우해주는 함수()
	void drawCard(CARD_TYPE type);
	//맨끝 카드를 앞으로 옮겨주는 기능
	void guardCard();
	//카드 한칸씩 이동하는 함수
	void cardMove();

	//클릭과 관련된 모든것 총합치기
	void clickUpdate();

	//ap얼마 주는지 글씨랑 ap얼마있는지 이미지
	void renderText();

	//게임 시작전에 말하는 텍스트
	void heroText();

	//맵별로 적이 유닛소환하고 하는 용도
	void AI();
};

