#pragma once
#include "GameNode.h"

class TileMap;

#define CHECKANGLE 22.5f

enum UNIT_ATTACK_TYPE
{
	ATKTYPE_N,		// 모든 타입에 100%
	ATKTYPE_E,		// 대형 100%  중형 75%  소형 50%
	ATKTYPE_C,		// 대형 25%	 중형 75%  소형 100%
	ATKTYPE_S,		//방어속성이나 방어력 영향 없음
	ATKTYPE_SPLASH
};

enum UNIT_DEFENCE_TYPE
{
	DFCTYPE_SM,
	DFCTYPE_ME,
	DFCTYPE_LA
};

enum UNIT_STATE
{
	UTST_IDLE,
	UTST_ATT,
	UTST_MOVE,
	UTST_DIE,
	UTST_END
};

class Unit : public GameNode
{
protected:
	Image* m_unitImage[UTST_END];
	Image* m_gostop;
	bool m_isGo;

	FRECT m_rc;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_size;

	int m_hp;
	int m_maxHp;
	int m_shield;
	int m_maxShield;

	int m_attackDamage;
	int m_defence;

	int m_attackUpgrade = 0;
	int m_defenceUpgrade = 0;

	int m_winPoint;

	float m_moveSpeed;

	float m_attackDelay;
	float m_attackTime;
	int m_attackNumber;

	int m_reload;
	int m_Creload;

	int m_rangeX;
	int m_minRange;
	int m_rangeY;

	bool m_isDead = true;

	//어느 플레이어 소유인지 구분용
	int m_host;
	UNIT_ATTACK_TYPE m_attackType;
	UNIT_DEFENCE_TYPE m_defenceType;
	UNIT_TYPE			m_unitType;
	UNIT_STATE			m_unitState;

	int m_cost;

protected:
	bool m_attackFrameStart = true;
	bool m_isAttackFinish = false;
	bool m_isInRange = false;
	bool m_isHitAll;
	//공격시 사운드 한번만 들어오게끔
	bool m_isAttackSound;

protected:
	float m_frameTime = 0.0f;
	float m_frameDelay;
	int m_frameX = 0, m_frameY = 0;

protected:
	DIRECTION m_dir;
	int		m_moveTile;

protected:
	bool m_isWorkDoneAct  = false;
	bool m_isWorkDoneKill = false;
	bool m_isWorkDoneMove = false;

	//길찾기를 위한 것
protected:
	TileMap* m_tile;
	vector<POINT> astarWay;
	D3DXVECTOR2 m_exactTargetPos;
	bool m_isGoOver = false;
	bool m_isMoveY = false;

	//에이스타 담은거말고 따로 움직일때
	//움직임 이전 타일값 저장용
	int m_idxx, m_idxy;

	//공격할때 타겟이 어느타일에 있는지 값받을때
	int m_targetX, m_targetY;

protected:
	Unit* m_targetUnit;
	bool m_attackMotionFinish;
	bool m_deadMotionFinish;
	int count = 0;

public:
	Unit();
	~Unit() override;
	HRESULT init() override;
	HRESULT init(D3DXVECTOR2 pos, int host, UNIT_TYPE type);
	virtual void unitInfo() {};
	void release() override;
	void update() override;
	void render() override;

	void frameMove();
	void checkDir();
	void changeState(UNIT_STATE state);


	void move();
	void unitType();

	void attack();
	void killSelf();

	void dammagged(int dmg, int atkupg);

	void naturalShield();

	//카드효과로 Y를 움직일때 호출하는놈
	void moveTileY(int idxX, int idxY, bool isCrush);
	//실제로 눈에 보이는 움직임을 동작하는 놈
	void moveTileY2();

	//카드효과로 스팀팩을 빨았을때
	void steampack();

	//카드효과로? 아무튼 회복이 될때
	void heal(int hp);

	//카드 효과로? 야마토 포를 맞을때
	void yamato();

	//카드 효과로? 주인이 바뀔때
	void mindControl();

	//카드 효과로? 토라스크 포효를 맞았을때
	void torasque();

	void stopOrMove()
	{
		m_isGo = m_isGo ? false : true;
	};

	MAKEGETSET(bool, m_isDead);
	MAKEGET(FRECT, m_rc);
	MAKEGET(UNIT_STATE, m_unitState);
	MAKEGET(UNIT_TYPE, m_unitType);
	MAKEGET(UNIT_DEFENCE_TYPE, m_defenceType);
	MAKEGETSET(int, m_host);
	MAKEGETSET(bool, m_isWorkDoneAct);
	MAKEGETSET(bool, m_isWorkDoneKill);
	MAKEGETSET(bool, m_isWorkDoneMove);
	MAKEGET(bool, m_isGo);
	MAKEGET(D3DXVECTOR2, m_pos);
	MAKEGET(int, m_cost);
	
	int Getm_hp() { return m_maxHp - m_hp; }



	void setTile(TileMap* tile) { m_tile = tile; }
};

