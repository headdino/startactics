#pragma once
#include "GameNode.h"
#include "MiniGame/map/TileMap.h"

class TileMapEdit : public GameNode
{
private:
	//타일 사이즈와 맥스갯수는 하나만 알고있어도 되니
	//배열로 저장하지 않는다
	TILE_DESC	m_TileDesc;

	//배열로 저장할 구조체 타일
	ST_TILE**	m_Tiles;


	int MouseIndexX = 0;
	int MouseIndexY = 0;
	int map = 0;
	int MouseTileState = TILE_NONE;

	bool show_another_window = true;
	bool show_tile_image = false;
	int Tile_frameX = 0, Tile_frameY = 0;
	bool show_tile_map = true;
	bool goMenu;

public:
	TileMapEdit();
	~TileMapEdit()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

