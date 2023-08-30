#pragma once 
#include "GameNode.h"

class Unit;
class UnitManager;
class TileMap;
class PlayGame;

#define CARDMAX 5

enum CARD_TYPE
{
	CARD_NULL,
	CARD_MARINE,
	CARD_SCV,
	CARD_BARRIGATE,
	CARD_FIREBAT,
	CARD_MEDIC,
	CARD_GHOST,
	CARD_ROCKET,
	CARD_TANK,
	CARD_DRONE,
	CARD_ZURGLING,
	CARD_ZURGLING_TOKEN,
	CARD_HYDRA,
	CARD_ULTRA,
	CARD_PROVE,
	CARD_ZEALOT,
	CARD_DRAGON,
	CARD_RIVER,
	CARD_MANEUVER,
	CARD_FIELD_REPAIR,
	CARD_STEAMPACK,
	CARD_SIEGE_MODE,
	CARD_SUDDEN_RAID,
	CARD_LURKER,
	CARD_BURROW,
	CARD_UNBURROW,
	CARD_TORASQUE_ROAR,
	CARD_DEFENSIVE_MATRIX,
	CARD_YAMATO,
	CARD_BRUDLING,
	CARD_MAKE_HIM_DRAGON,
	CARD_MIND_CONTROL,
	CARD_RECALL,
	CARD_END
};

enum CARD_ATTRIBUTE
{
	CLICK_ONE,
	CLICK_TWO
};

class Card : public GameNode
{
private:
	Image* m_cardImage;
	D3DXVECTOR2 m_pos;
	CARD_TYPE m_type;
	FRECT m_rc;
	CARD_ATTRIBUTE m_attribute;
	//Card* m_nextCard = nullptr;

private:
	//다른데 참고할 포인터용
	UnitManager* m_unitManager;
	TileMap*	m_tile;
	Unit*		m_unit;
	PlayGame*	m_playGame;

private:
	//ui용 글씨정보값
	int m_ap;
	int m_atk;
	int m_hp;
	int m_range;
	wstring m_inform;

private:
	//카드 사용효과시 발동될 타일값
	//처음 클릭시 받는 타일값
	int idxX, idxY;
	//두번째 클릭시 받는 타일값
	int idxX2, idxY2;
	//두번 클릭하는 일 있을때 두번째 클릭이 끝났는지 알려주는 용
	bool m_isClickDouble;

private:
	bool m_isSelect;
	bool m_isUse;
	bool m_isMove;

	bool m_isCrush;
public:
	Card();
	~Card() override;
	HRESULT init() override;
	HRESULT init(D3DXVECTOR2 pos);
	void release() override;
	void update() override;
	void render() override;

	void selectOnOff();

	bool checkAp(int myap);

	MAKEGETSET(CARD_TYPE, m_type);
	MAKEGET(FRECT, m_rc);
	MAKEGETSET(bool, m_isSelect);
	MAKEGET(bool, m_isUse);
	MAKEGETSET(bool, m_isMove);
	MAKEGET(bool, m_isClickDouble);
	//MAKEGETSET(Card*, m_nextCard);

	void SetUnitManager(UnitManager* um) { m_unitManager = um; }
	void SetTileMap(TileMap* tmp) { m_tile = tmp; }
	void SetUnit(Unit* unit) { m_unit = unit; }
	void SetPlayGame(PlayGame* pg) { m_playGame = pg; }
	
	//카드타입이 바뀔때마다 갱신해주는 녀석들
	void cardType();

	//턴이 지날때 카드들을 왼쪽에서 오른쪽으로 한칸씩 이동시키기 위해서
	//만드는 함수
	//void cardMove();
	//매 턴마다 제일 왼쪽카드를 바꿔주기 위한 함수
	//void cardDraw();
	//카드 사용한다고 알림받는녀석
	void cardUse(int idxx, int idxy);
	//카드 사용하는데 알아야할 좌표가 두군데 일때 호출용
	void cardUseDouble(int idxx, int idxy);
	//실제 카드사용효과를 타입별로 실행해주는 녀석
	void cardUseType();
};

