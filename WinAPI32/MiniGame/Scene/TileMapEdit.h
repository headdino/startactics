#pragma once
#include "GameNode.h"
#include "MiniGame/map/TileMap.h"

class TileMapEdit : public GameNode
{
private:
	//Ÿ�� ������� �ƽ������� �ϳ��� �˰��־ �Ǵ�
	//�迭�� �������� �ʴ´�
	TILE_DESC	m_TileDesc;

	//�迭�� ������ ����ü Ÿ��
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

