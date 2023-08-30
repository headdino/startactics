#pragma once
#include "GameNode.h"

class Unit;

//타일 상태값(필요한것 추가 해서 만들것)
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
	int F;			//총비용 g+h
	int G;			//시작지점에서 부터의 비용
	int H;			//도착지점 까지의 예상 비용
	int prevX;		//전에 왔던 타일 인덱스
	int prevY;		//전에 왔던 타일 인덱스
	bool isCheck;	//검사를 한적이 있는지

};

class TileMap : public GameNode
{
private:
	Image* m_bg;
	//타일 사이즈와 맥스갯수는 하나만 알고있어도 되니
	//배열로 저장하지 않는다
	TILE_DESC	m_TileDesc;

	//배열로 저장할 구조체 타일
	ST_TILE**	m_Tiles;

	//그릴 영역 안의 인덱스값
	int StartIndexX; int StartIndexY;
	int EndIndexX; int EndIndexY;

	//길찾기 비용 구조체는 따로 만들어 둔다(타일맵당1개)
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

	//사거리 타일안에 유닛이 있는지 없는지 적유닛을 반환해준다.
	Unit* CheckUnit(int idxX, int idxY, int rangeX, int rangeY, int host, int& targetX, int& targetY);
	//사거리 타일안에 유닛이 있는지 없는지 아군유닛을 반환해준다.(메딕용)
	Unit* CheckAllyUnit(int idxX, int idxY, int rangeX, int rangeY, int host);
	//해당 타일에 있는 유닛의 포인터를 반환해주는 녀석
	Unit* returnInUnit(int idxX, int idxY);


	//타일맵 길찾기
	bool findTile(vector<POINT>& way, int StartX, int StartY, DIRECTION moveDir, int moveTile, bool& goOver);

	//현재 타일에서 도착 지점까지 필요한 예상비용
	int FindH(int StartX, int StartY, int EndX, int EndY);

	//타일 인덱스와 원하는 상태를 넣으면 그 타일이 그 상태인지 아닌지 반환해준다.
	bool CheckTileWall(int idxX, int idxY, TILE_STATE state);
	bool CheckTileObject(int idxX, int idxY);

	MAKEGETSET(TILE_DESC, m_TileDesc);
};

