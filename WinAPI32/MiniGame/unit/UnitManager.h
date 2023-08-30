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

	//두턴마다 회복되는 쉴드를 위한 변수
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

	//유닛 클릭, 무브, 드래그등 꼴뵈기 싫어서 여기 박아넣어둘라고
	void clickupdate();

	void clickUnitStop();

	//토라스크 효과로 발동
	void cardTorasque();


	//ai들이 가져다 쓸 마법함수들
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

