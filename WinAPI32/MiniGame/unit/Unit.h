#pragma once
#include "GameNode.h"

class TileMap;

#define CHECKANGLE 22.5f

enum UNIT_ATTACK_TYPE
{
	ATKTYPE_N,		// ��� Ÿ�Կ� 100%
	ATKTYPE_E,		// ���� 100%  ���� 75%  ���� 50%
	ATKTYPE_C,		// ���� 25%	 ���� 75%  ���� 100%
	ATKTYPE_S,		//���Ӽ��̳� ���� ���� ����
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

	//��� �÷��̾� �������� ���п�
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
	//���ݽ� ���� �ѹ��� �����Բ�
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

	//��ã�⸦ ���� ��
protected:
	TileMap* m_tile;
	vector<POINT> astarWay;
	D3DXVECTOR2 m_exactTargetPos;
	bool m_isGoOver = false;
	bool m_isMoveY = false;

	//���̽�Ÿ �����Ÿ��� ���� �����϶�
	//������ ���� Ÿ�ϰ� �����
	int m_idxx, m_idxy;

	//�����Ҷ� Ÿ���� ���Ÿ�Ͽ� �ִ��� ��������
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

	//ī��ȿ���� Y�� �����϶� ȣ���ϴ³�
	void moveTileY(int idxX, int idxY, bool isCrush);
	//������ ���� ���̴� �������� �����ϴ� ��
	void moveTileY2();

	//ī��ȿ���� �������� ��������
	void steampack();

	//ī��ȿ����? �ƹ�ư ȸ���� �ɶ�
	void heal(int hp);

	//ī�� ȿ����? �߸��� ���� ������
	void yamato();

	//ī�� ȿ����? ������ �ٲ�
	void mindControl();

	//ī�� ȿ����? ���ũ ��ȿ�� �¾�����
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

