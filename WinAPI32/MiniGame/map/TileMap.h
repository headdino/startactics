#pragma once
#include "GameNode.h"

class Unit;

//Ÿ�� ���°�(�ʿ��Ѱ� �߰� �ؼ� �����)
enum TILE_STATE
{
	TILE_NONE,
	TILE_WALL,
	TILE_ZERG,
	TILE_NOT_BUILD
};




struct ST_TILE
{
	int		State;
	bool	isObject;
	Unit*	inUnit;
};

struct ST_TILECOST
{
	int F;			//�Ѻ�� g+h
	int G;			//������������ ������ ���
	int H;			//�������� ������ ���� ���
	int prevX;		//���� �Դ� Ÿ�� �ε���
	int prevY;		//���� �Դ� Ÿ�� �ε���
	bool isCheck;	//�˻縦 ������ �ִ���

};

class TileMap : public GameNode
{
private:
	Image* m_bg;
	//Ÿ�� ������� �ƽ������� �ϳ��� �˰��־ �Ǵ�
	//�迭�� �������� �ʴ´�
	TILE_DESC	m_TileDesc;

	//�迭�� ������ ����ü Ÿ��
	ST_TILE**	m_Tiles;

	//�׸� ���� ���� �ε�����
	int StartIndexX; int StartIndexY;
	int EndIndexX; int EndIndexY;

	//��ã�� ��� ����ü�� ���� ����� �д�(Ÿ�ϸʴ�1��)
	ST_TILECOST**	m_TileCost;

public:
	TileMap();
	~TileMap()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void Load(int map);

	void SetUnit(int idxX, int idxY, Unit* unit);
	void RemoveUnit(int idxX, int idxY);

	//��Ÿ� Ÿ�Ͼȿ� ������ �ִ��� ������ �������� ��ȯ���ش�.
	Unit* CheckUnit(int idxX, int idxY, int rangeX, int rangeY, int host, int& targetX, int& targetY);
	//��Ÿ� Ÿ�Ͼȿ� ������ �ִ��� ������ �Ʊ������� ��ȯ���ش�.(�޵��)
	Unit* CheckAllyUnit(int idxX, int idxY, int rangeX, int rangeY, int host);
	//�ش� Ÿ�Ͽ� �ִ� ������ �����͸� ��ȯ���ִ� �༮
	Unit* returnInUnit(int idxX, int idxY);


	//Ÿ�ϸ� ��ã��
	bool findTile(vector<POINT>& way, int StartX, int StartY, DIRECTION moveDir, int moveTile, bool& goOver);

	//���� Ÿ�Ͽ��� ���� �������� �ʿ��� ������
	int FindH(int StartX, int StartY, int EndX, int EndY);

	//Ÿ�� �ε����� ���ϴ� ���¸� ������ �� Ÿ���� �� �������� �ƴ��� ��ȯ���ش�.
	bool CheckTileWall(int idxX, int idxY, TILE_STATE state);
	bool CheckTileObject(int idxX, int idxY);

	MAKEGETSET(TILE_DESC, m_TileDesc);
};

