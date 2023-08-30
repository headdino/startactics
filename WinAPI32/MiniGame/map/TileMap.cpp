#include "stdafx.h"
#include "TileMap.h"
#include <fstream>
#include "MiniGame/unit/Unit.h"

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

HRESULT TileMap::init()
{
	//임의의 초기값 만들어 주기
	m_TileDesc.TileSizeX = 110.0f;
	m_TileDesc.TileSizeY = 100.0f;
	m_TileDesc.TileMaxX = 9;
	m_TileDesc.TileMaxY = 4;

	m_TileDesc.ZeroStartPos.x = m_TileDesc.TileSizeX / 2.0f + 150.0f;
	m_TileDesc.ZeroStartPos.y = m_TileDesc.TileSizeY  + WINSIZEY / 4.0f - 25.0f;




	//m_Tiles는 더블포인터
	m_Tiles = new ST_TILE*[m_TileDesc.TileMaxX];
	m_TileCost = new ST_TILECOST*[m_TileDesc.TileMaxX];
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		//m_Tiles[i]는 포인터
		m_Tiles[i] = new ST_TILE[m_TileDesc.TileMaxY];
		m_TileCost[i] = new ST_TILECOST[m_TileDesc.TileMaxY];
	}

	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			m_Tiles[i][j].State = TILE_NONE;
			m_Tiles[i][j].isObject = false;
			m_Tiles[i][j].inUnit = nullptr;
		}
	}
	//타일 코스트 도 생성
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		
	}

	m_bg = NULL;
	
	return S_OK;
}

void TileMap::release()
{
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		SAFE_DELETE_ARRAY(m_Tiles[i]);
		SAFE_DELETE_ARRAY(m_TileCost[i]);
	}
}

void TileMap::update()
{
	/*if (KEYMANAGER->StayKeyDown('W'))
	{
		g_ptCam.y += g_ETime * 180.0f;
	}
	if (KEYMANAGER->StayKeyDown('S'))
	{
		g_ptCam.y -= g_ETime * 180.0f;
	}
	if (KEYMANAGER->StayKeyDown('A'))
	{
		g_ptCam.x -= g_ETime * 180.0f;
	}
	if (KEYMANAGER->StayKeyDown('D'))
	{
		g_ptCam.x += g_ETime * 180.0f;
	}*/

}

void TileMap::render()
{

	
	Rect* tileRc = IMGMANAGER->Getrect();
	tileRc->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);
	tileRc->SetisFill(false);

	m_bg->Render();

	Image* img = IMGMANAGER->GetImage("ui_cardBoard");
	img->Render();

	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			
			//세팅이 다른값만 갱신
			tileRc->Position(m_TileDesc.ZeroStartPos.x + i * m_TileDesc.TileSizeX,
				m_TileDesc.ZeroStartPos.y + j * m_TileDesc.TileSizeY);

			tileRc->Color(0.0f, 0.0f, 0.0f);

			if (m_Tiles[i][j].isObject)
			{
				tileRc->Color(1.0f, 0.0f, 0.0f);
			}

			if (m_Tiles[i][j].State == TILE_WALL)
			{
				tileRc->Color(0.5f, 0.0f, 0.5f);
			}


			tileRc->Render();


		}

	}


}

void TileMap::Load(int map)
{
	ifstream in;

	switch (map)
	{
	case 0:
		m_bg = IMGMANAGER->GetImage("map1");
		
		in.open("save/map1.txt", ios::in);

		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;
			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].isObject;
					in >> m_Tiles[i][j].State;
				}
			}
		}
		break;
	case 1:
		m_bg = IMGMANAGER->GetImage("map2");
		in.open("save/map2.txt", ios::in);

		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;
			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].isObject;
					in >> m_Tiles[i][j].State;
				}
			}
		}
		break;
	case 2:
		m_bg = IMGMANAGER->GetImage("map3");
		in.open("save/map3.txt", ios::in);

		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;
			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].isObject;
					in >> m_Tiles[i][j].State;
				}
			}
		}
		break;
	case 3:
		m_bg = IMGMANAGER->GetImage("map4");
		in.open("save/map4.txt", ios::in);

		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;
			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].isObject;
					in >> m_Tiles[i][j].State;
				}
			}
		}
		break;
	case 4:
		m_bg = IMGMANAGER->GetImage("map5");
		in.open("save/map5.txt", ios::in);

		if (in.is_open())
		{
			in >> m_TileDesc.TileMaxX >> m_TileDesc.TileMaxY;
			in >> m_TileDesc.TileSizeX >> m_TileDesc.TileSizeY;
			in >> m_TileDesc.ZeroStartPos.x >> m_TileDesc.ZeroStartPos.y;
			for (int i = 0; i < m_TileDesc.TileMaxX; i++)
			{
				for (int j = 0; j < m_TileDesc.TileMaxY; j++)
				{
					in >> m_Tiles[i][j].isObject;
					in >> m_Tiles[i][j].State;
				}
			}
		}
		break;
	}
	
	

}

void TileMap::SetUnit(int idxX, int idxY, Unit * unit)
{
	m_Tiles[idxX][idxY].isObject = true;
	m_Tiles[idxX][idxY].inUnit = unit;
}

void TileMap::RemoveUnit(int idxX, int idxY)
{
	m_Tiles[idxX][idxY].isObject = false;
	m_Tiles[idxX][idxY].inUnit = nullptr;

}

Unit* TileMap::CheckUnit(int idxX, int idxY, int rangeX, int rangeY, int host, int& targetX, int& targetY)
{
	int tempX;

	//내 유닛일때
	if (host == 1)
	{
		tempX = idxX + rangeX;

		if (tempX >= m_TileDesc.TileMaxX) tempX = m_TileDesc.TileMaxX - 1;

		for (int i = idxX; i <= tempX; i++)
		{
			//일단 그냥 y는 해당 idxY가 있는 위치로
			//for (int j = idxY;)
			//{
			//
			//}
			if (idxX == i) continue;
			if (m_Tiles[i][idxY].isObject && m_Tiles[i][idxY].inUnit->Getm_host() != 1)
			{
				targetX = i;
				targetY = idxY;
				return m_Tiles[i][idxY].inUnit;
			}
		}
	}
	//적 유닛일때
	else
	{
		tempX = idxX - rangeX;

		if (tempX < 0) tempX = 0;

		//for (int i = tempX; i < idxX; i++)
		for (int i = idxX; i >= tempX; i--)
		{
			//일단 그냥 y는 해당 idxY가 있는 위치로
			//for (int j = idxY;)
			//{
			//
			//}
			if (idxX == i) continue;
			if (m_Tiles[i][idxY].isObject && m_Tiles[i][idxY].inUnit->Getm_host() == 1)
			{
				targetX = i;
				targetY = idxY;
				return m_Tiles[i][idxY].inUnit;
			}
		}
	}
	 

	

	return nullptr;


}

Unit * TileMap::CheckAllyUnit(int idxX, int idxY, int rangeX, int rangeY, int host)
{
	int tempX;

	//내 유닛일때
	if (host == 1)
	{
		tempX = idxX + rangeX;

		if (tempX >= m_TileDesc.TileMaxX) tempX = m_TileDesc.TileMaxX - 1;

		for (int i = idxX; i <= tempX; i++)
		{
			//일단 그냥 y는 해당 idxY가 있는 위치로
			//for (int j = idxY;)
			//{
			//
			//}
			if (idxX == i) continue;
			if (m_Tiles[i][idxY].isObject && m_Tiles[i][idxY].inUnit->Getm_host() == 1)
			{
				return m_Tiles[i][idxY].inUnit;
			}
		}
	}
	//적 유닛일때
	else
	{
		tempX = idxX - rangeX;

		if (tempX < 0) tempX = 0;

		//for (int i = tempX; i < idxX; i++)
		for (int i = idxX; i >= tempX; i--)
		{
			//일단 그냥 y는 해당 idxY가 있는 위치로
			//for (int j = idxY;)
			//{
			//
			//}
			if (idxX == i) continue;
			if (m_Tiles[i][idxY].isObject && m_Tiles[i][idxY].inUnit->Getm_host() != 1)
			{
				return m_Tiles[i][idxY].inUnit;
			}
		}
	}




	return nullptr;
}

Unit * TileMap::returnInUnit(int idxX, int idxY)
{
	if (idxX < 0 ||
		idxX >= m_TileDesc.TileMaxX ||
		idxY < 0 ||
		idxY >= m_TileDesc.TileMaxY) return nullptr;



	if (m_Tiles[idxX][idxY].isObject)
	{
		return m_Tiles[idxX][idxY].inUnit;
	}
	else
	{
		return nullptr;
	}

	
}

bool TileMap::findTile(vector<POINT>& way, int StartX, int StartY, DIRECTION moveDir, int moveTile, bool& goOver)
{
	int EndX = StartX;
	int EndY = StartY;

	switch (moveDir)
	{
	case DIR_N:
		EndY += moveTile;
		break;
	case DIR_E:
		EndX += moveTile;
		break;
	case DIR_S:
		EndY -= moveTile;
		break;
	case DIR_W:
		EndX -= moveTile;
		break;
	}

	//X,Y값의 최대 최소값을 잡아줌(타일 최대 최소보다 크거나 작을때)
	if (EndX > m_TileDesc.TileMaxX - 1) { EndX = m_TileDesc.TileMaxX - 1; goOver = true; }
	if (EndX < 0) { EndX = 0; goOver = true; }
	if (EndY > m_TileDesc.TileMaxY) EndY = m_TileDesc.TileMaxY;
	if (EndY < 0) EndY = 0;

	/*if (m_Tiles[EndX][EndY].State == TILE_WALL)
	{
		way.clear();
		way.shrink_to_fit();
		return false;
	}*/

	if (StartX == EndX && StartY == EndY)
	{
		POINT temp;
		temp.x = EndX;
		temp.y = EndY;
		way.emplace_back(temp);
		return true;
	}



	//타일 비용, 길 전부 초기화
	way.clear();
	way.shrink_to_fit();
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			//INT32_MAX 최대값 사용하여 초기화 하기
			//__int64
			//__int32
			m_TileCost[i][j].F = INT32_MAX;
			m_TileCost[i][j].G = INT32_MAX;
			m_TileCost[i][j].H = FindH(i, j, EndX, EndY);
			m_TileCost[i][j].prevX = INT32_MAX;
			m_TileCost[i][j].prevY = INT32_MAX;
			m_TileCost[i][j].isCheck = false;
		}
	}
	//처음 시작 타일은 g 비용값이 0이다

	m_TileCost[StartX][StartY].G = 0;




	int count = 0;

	//반복문
	while (1)
	{
		//다 찾아봐도 반복문이 끝나지 않는다면
		if (count == m_TileDesc.TileMaxX*m_TileDesc.TileMaxY)
		{
			way.clear();
			way.shrink_to_fit();
			return false;

		}
		count++;


		//타일의 g값이 갱신된 상황이라면 F값 만들어 주기
		for (int i = 0; i < m_TileDesc.TileMaxX; i++)
		{
			for (int j = 0; j < m_TileDesc.TileMaxY; j++)
			{
				if (m_TileCost[i][j].G != INT32_MAX)
					m_TileCost[i][j].F = m_TileCost[i][j].H + m_TileCost[i][j].G;
			}
		}

		//f의 최소값을 구한다
		POINT MinIndex;
		MinIndex.x = INT32_MAX;
		MinIndex.y = INT32_MAX;
		int minF = INT32_MAX;
		for (int i = 0; i < m_TileDesc.TileMaxX; i++)
		{
			for (int j = 0; j < m_TileDesc.TileMaxY; j++)
			{
				if (!m_TileCost[i][j].isCheck)
				{
					if (m_TileCost[i][j].F != INT32_MAX && m_TileCost[i][j].F < minF)
					{
						//if (m_Tiles[i][j].State == TILE_WALL) break;
							MinIndex.x = i; MinIndex.y = j;
							minF = m_TileCost[i][j].F;
					}
				}
			}
		}

		//탐색했을때 최소값F가 도착지점이였다면 반복문 종료
		if (MinIndex.x == EndX && MinIndex.y == EndY)break;



		//최소값이 없는경우
		if (minF == INT32_MAX)
		{
			way.clear();
			way.shrink_to_fit();
			return false;
		}
		//최소값F 주변에 g값 갱신
		//타일 왼쪽
		if (MinIndex.x != 0)
		{
			//벽은 g값이 갱신되도 최소F탐색때 제외됨
			if (m_TileCost[MinIndex.x - 1][MinIndex.y].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x - 1][MinIndex.y].G =
					10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x - 1][MinIndex.y].prevX = MinIndex.x;
				m_TileCost[MinIndex.x - 1][MinIndex.y].prevY = MinIndex.y;

			}
		}
		//타일 오른쪽
		if (MinIndex.x < m_TileDesc.TileMaxX - 1)
		{
			//벽은 g값이 갱신되도 최소F탐색때 제외됨
			if (m_TileCost[MinIndex.x + 1][MinIndex.y].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x + 1][MinIndex.y].G =
					10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x + 1][MinIndex.y].prevX = MinIndex.x;
				m_TileCost[MinIndex.x + 1][MinIndex.y].prevY = MinIndex.y;

			}
		}
		//타일 아래쪽
		if (MinIndex.y != 0)
		{
			//벽은 g값이 갱신되도 최소F탐색때 제외됨
			if (m_TileCost[MinIndex.x][MinIndex.y - 1].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x][MinIndex.y - 1].G =
					10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x][MinIndex.y - 1].prevX = MinIndex.x;
				m_TileCost[MinIndex.x][MinIndex.y - 1].prevY = MinIndex.y;

			}
		}
		//타일 위쪽
		if (MinIndex.y < m_TileDesc.TileMaxY - 1)
		{
			//벽은 g값이 갱신되도 최소F탐색때 제외됨
			if (m_TileCost[MinIndex.x][MinIndex.y + 1].G >
				10 + m_TileCost[MinIndex.x][MinIndex.y].G)
			{
				m_TileCost[MinIndex.x][MinIndex.y + 1].G =
					10 + m_TileCost[MinIndex.x][MinIndex.y].G;
				m_TileCost[MinIndex.x][MinIndex.y + 1].prevX = MinIndex.x;
				m_TileCost[MinIndex.x][MinIndex.y + 1].prevY = MinIndex.y;

			}
		}

		



		m_TileCost[MinIndex.x][MinIndex.y].isCheck = true;
	}

	//길 도착지점부터 추가해주기 (시작지점까지)

	POINT temp;
	temp.x = EndX;
	temp.y = EndY;
	way.emplace_back(temp);

	while (1)
	{
		POINT temp2;
		temp2.x = m_TileCost[temp.x][temp.y].prevX;
		temp2.y = m_TileCost[temp.x][temp.y].prevY;
		if (temp2.x == StartX && temp2.y == StartY)
		{
			break;
		}
		way.emplace_back(temp2);
		temp.x = temp2.x;
		temp.y = temp2.y;

	}

	return true;

	

	return true;
}

int TileMap::FindH(int StartX, int StartY, int EndX, int EndY)
{
	return (abs(StartX - EndX) + abs(StartY - EndY)) * 10;
}

bool TileMap::CheckTileWall(int idxX, int idxY, TILE_STATE state)
{

	if (m_Tiles[idxX][idxY].State == state) return true;
	else return false;

}

bool TileMap::CheckTileObject(int idxX, int idxY)
{
	if (m_Tiles[idxX][idxY].isObject) return true;
	else return false;
}
