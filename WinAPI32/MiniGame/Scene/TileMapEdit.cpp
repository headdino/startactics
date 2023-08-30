#include "stdafx.h"
#include "TileMapEdit.h"

TileMapEdit::TileMapEdit()
{
}


TileMapEdit::~TileMapEdit()
{
}

HRESULT TileMapEdit::init()
{
	m_TileDesc.TileSizeX = 110.0f;
	m_TileDesc.TileSizeY = 100.0f;
	m_TileDesc.TileMaxX = 9;
	m_TileDesc.TileMaxY = 4;

	m_TileDesc.ZeroStartPos.x = m_TileDesc.TileSizeX / 2.0f + 150.0f;
	m_TileDesc.ZeroStartPos.y = m_TileDesc.TileSizeY + WINSIZEY / 4.0f - 25.0f;




	//m_Tiles는 더블포인터
	m_Tiles = new ST_TILE*[m_TileDesc.TileMaxX];
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		//m_Tiles[i]는 포인터
		m_Tiles[i] = new ST_TILE[m_TileDesc.TileMaxY];;
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

	goMenu = false;
	return S_OK;
}

void TileMapEdit::release()
{
	SAFE_DELETE_ARRAY(m_Tiles);
}

void TileMapEdit::update()
{



	//if (KEYMANAGER->StayKeyDown('W'))
	//{
	//	g_ptCam.y += g_ETime * 180.0f;
	//}
	//if (KEYMANAGER->StayKeyDown('S'))
	//{
	//	g_ptCam.y -= g_ETime * 180.0f;
	//}
	//if (KEYMANAGER->StayKeyDown('A'))
	//{
	//	g_ptCam.x -= g_ETime * 180.0f;
	//}
	//if (KEYMANAGER->StayKeyDown('D'))
	//{
	//	g_ptCam.x += g_ETime * 180.0f;
	//}

	int indxx, indxy;
	if (KEYMANAGER->StayKeyDown(VK_LBUTTON) && KEYMANAGER->StayKeyDown(VK_CONTROL))
	{
		if (PtinTile(indxx, indxy, m_TileDesc, g_ptCam + g_ptMouse))
		{
			m_Tiles[indxx][indxy].State = MouseTileState;
		}

	}


	if (goMenu)
		SCENEMANAGER->ChangeScene("Loading", MENU);
}

void TileMapEdit::render()
{

	ImGui::Checkbox("SaveLoad", &show_another_window);

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		/*ImGui::InputInt("TileMaxX", &m_TileDesc.TileMaxX, 1, 0);
		ImGui::InputInt("TileMaxY", &m_TileDesc.TileMaxY, 1, 0);*/

		static char fileName[64] = ""; ImGui::InputText("fileName", fileName, 64);
		//string str(fileName[0], sizeof(fileName));
		//string str = string(fileName[0],sizeof(fileName));
		//str = "save/" + str + ".txt";
		if (ImGui::Button("save"))
		{
			ofstream out;

			out.open(fileName, ios::out | ios::trunc);

			if (out.is_open())
			{
				out << m_TileDesc.TileMaxX << " " << m_TileDesc.TileMaxY << endl;
				out << m_TileDesc.TileSizeX << " " << m_TileDesc.TileSizeY << endl;
				out << m_TileDesc.ZeroStartPos.x << " " << m_TileDesc.ZeroStartPos.y << endl;

				for (int i = 0; i < m_TileDesc.TileMaxX; i++)
				{
					for (int j = 0; j < m_TileDesc.TileMaxY; j++)
					{
						out << m_Tiles[i][j].isObject << endl;
						out << m_Tiles[i][j].State << endl;
					}
				}
			}
			out.flush();
			out.close();

		}
		if (ImGui::Button("load"))
		{
			ifstream in;
			in.open(fileName, ios::in);

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
		}
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		if (ImGui::Button("Go to Menu"))
			goMenu = true;
		ImGui::End();
	}

	ImGui::Text("CurrentTile");
	ImGui::Columns(2, "mycolumns"); // 4-ways, with border
	ImGui::Separator();
	ImGui::Text("TileIndex"); ImGui::NextColumn();
	ImGui::Text("TileState"); ImGui::NextColumn();
	//ImGui::Text("Path"); ImGui::NextColumn();
	//ImGui::Text("Hovered"); ImGui::NextColumn();
	ImGui::Separator();
	static int selected = -1;


	char label[32];
	sprintf_s(label, "%d", MouseIndexX);

	//sprintf_s(label2, "%d", MouseTileState);

	char label2[32];
	const char* State[6] = { "TILE_NONE", "TILE_WALL", "TILE_ZERG",
		"TILE_NOT_BUILD" };

	sprintf_s(label2, "%s", State[MouseTileState]);

	//if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}


	//sprintf_s(label, "%04d", i);
	//if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
	//	selected = i;
	bool hovered = ImGui::IsItemHovered();

	ImGui::Text(label); //ImGui::NextColumn();
	ImGui::NextColumn();
	ImGui::Text(label2); ImGui::NextColumn();
	//ImGui::Text("%d", hovered); ImGui::NextColumn();
	ImGui::Columns(1);

	if (ImGui::TreeNode("TileSelect"))
	{



		ImGui::Text("TileState");
		ImGui::Columns(3, "mycolumns3", false);  // 3-ways, no border
		ImGui::Separator();
		for (int n = 0; n < 4; n++)
		{
			char label[32];
			const char* State[4] = { "TILE_NONE", "TILE_WALL", "TILE_ZERG",
				 "TILE_NOT_BUILD" };
			sprintf_s(label, "%s", State[n]);
			if (ImGui::Selectable(label))
			{
				MouseTileState = n;
			}
			//if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();





		ImGui::Columns(1);
		ImGui::Separator();


		ImGui::TreePop();
	}

	ImGui::Text("BGMAP");
	ImGui::Columns(3, "mycolumns3", false);  // 3-ways, no border
	ImGui::Separator();
	for (int n = 0; n < 5; n++)
	{
		char label[32];
		const char* State[5] = { "map1", "map2", "map3",
			 "map4","map5" };
		sprintf_s(label, "%s", State[n]);
		if (ImGui::Selectable(label))
		{
			map = n;
		}
		//if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
		ImGui::NextColumn();
	}
	ImGui::Columns(1);
	ImGui::Separator();


	Image* img2 = IMGMANAGER->GetImage("TileSelect");
	img2->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);

	

	Image* img;
	img = IMGMANAGER->GetImage("map1");
	switch (map)
	{
	case 0:
		img = IMGMANAGER->GetImage("map1");
		break;
	case 1:
		img = IMGMANAGER->GetImage("map2");
		break;
	case 2:
		img = IMGMANAGER->GetImage("map3");
		break;
	case 3:
		img = IMGMANAGER->GetImage("map4");
		break;
	case 4:
		img = IMGMANAGER->GetImage("map5");
		break;
	}
	img->Render();

	Rect* tileRc = IMGMANAGER->Getrect();
	tileRc->Scale(m_TileDesc.TileSizeX, m_TileDesc.TileSizeY);

	
	for (int i = 0; i < m_TileDesc.TileMaxX; i++)
	{
		for (int j = 0; j < m_TileDesc.TileMaxY; j++)
		{
			tileRc->Position(m_TileDesc.ZeroStartPos.x + i * m_TileDesc.TileSizeX,
				m_TileDesc.ZeroStartPos.y + j * m_TileDesc.TileSizeY);
			tileRc->SetisFill(false);
			tileRc->Color(0.0f, 0.0f, 0.0f);

			if (m_Tiles[i][j].State == TILE_WALL)
			{
				tileRc->Color(0.5f, 0.0f, 0.5f);
			}

			int idxX, idxY;
			if (PtinTile(idxX, idxY, m_TileDesc, g_ptCam + g_ptMouse))
			{
				if (idxX == i && idxY == j)
				{
					img2->Position(m_TileDesc.ZeroStartPos.x + i * m_TileDesc.TileSizeX,
						m_TileDesc.ZeroStartPos.y + j * m_TileDesc.TileSizeY);

				}
			}


			tileRc->Render();
		}
	}

	img2->Render();


	//카드판 렌더
	img = IMGMANAGER->GetImage("ui_cardBoard");
	img->Render();


}