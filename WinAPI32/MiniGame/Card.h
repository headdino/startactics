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
	//�ٸ��� ������ �����Ϳ�
	UnitManager* m_unitManager;
	TileMap*	m_tile;
	Unit*		m_unit;
	PlayGame*	m_playGame;

private:
	//ui�� �۾�������
	int m_ap;
	int m_atk;
	int m_hp;
	int m_range;
	wstring m_inform;

private:
	//ī�� ���ȿ���� �ߵ��� Ÿ�ϰ�
	//ó�� Ŭ���� �޴� Ÿ�ϰ�
	int idxX, idxY;
	//�ι�° Ŭ���� �޴� Ÿ�ϰ�
	int idxX2, idxY2;
	//�ι� Ŭ���ϴ� �� ������ �ι�° Ŭ���� �������� �˷��ִ� ��
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
	
	//ī��Ÿ���� �ٲ𶧸��� �������ִ� �༮��
	void cardType();

	//���� ������ ī����� ���ʿ��� ���������� ��ĭ�� �̵���Ű�� ���ؼ�
	//����� �Լ�
	//void cardMove();
	//�� �ϸ��� ���� ����ī�带 �ٲ��ֱ� ���� �Լ�
	//void cardDraw();
	//ī�� ����Ѵٰ� �˸��޴³༮
	void cardUse(int idxx, int idxy);
	//ī�� ����ϴµ� �˾ƾ��� ��ǥ�� �α��� �϶� ȣ���
	void cardUseDouble(int idxx, int idxy);
	//���� ī����ȿ���� Ÿ�Ժ��� �������ִ� �༮
	void cardUseType();
};

