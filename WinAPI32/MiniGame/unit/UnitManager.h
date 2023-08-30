#pragma once
#include "GameNode.h"
#include "terran.h"
#include "zerg.h"
#include "protoss.h"

#define UNITMAX 400

class TileMap;

class UnitManager : public GameNode
{
private:
	Unit* m_UnitArray;
	TileMap* m_tile;

	//���ϸ��� ȸ���Ǵ� ���带 ���� ����
	int m_shieldCount;
private:
	bool m_isWorkDoneAct = false;
	bool m_isWorkDoneKill = false;
	bool m_isWorkDoneMove = false;

public:
	UnitManager();
	~UnitManager()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void actUpdate();
	void killUpdate();
	void moveUpdate();

	void createUnit(D3DXVECTOR2 pos, int host, UNIT_TYPE type);

	//���� Ŭ��, ����, �巡�׵� �úƱ� �Ⱦ ���� �ھƳ־�Ѷ��
	void clickupdate();

	void clickUnitStop();

	//���ũ ȿ���� �ߵ�
	void cardTorasque();


	//ai���� ������ �� �����Լ���
	void AISiege();
	void AIManeuver();
	void AIFieldRepair();
	void AISteamPack();
	void AIYamato();
	void AIRulker();
	void AITorasque();
	void AIBru();
	void AISudden();
	void AIBurrow();
	void AIMakeDragon();
	void AIMindControl();
	void AIKMindControl();
	void AIRecall();




	void setTile(TileMap* tile) { m_tile = tile; }

	MAKEGETSET(bool, m_isWorkDoneAct);
	MAKEGETSET(bool, m_isWorkDoneKill);
	MAKEGETSET(bool, m_isWorkDoneMove);
	MAKEREFGET(int, m_shieldCount);
};

