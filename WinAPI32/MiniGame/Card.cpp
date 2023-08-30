#include "stdafx.h"
#include "Card.h"
#include "MiniGame/unit/UnitManager.h"
#include "MiniGame/unit/Unit.h"
#include "MiniGame/map/TileMap.h"
#include "MiniGame/Scene/PlayGame.h"


Card::Card()
{
}


Card::~Card()
{
}

HRESULT Card::init()
{
	m_cardImage = IMGMANAGER->GetImage("card_marine");
	m_pos.x = 200.0f;
	m_pos.y = 100.0f;

	return S_OK;
}

HRESULT Card::init(D3DXVECTOR2 pos)
{
	m_cardImage = nullptr;
	m_type = CARD_NULL;
	m_pos = pos;
	m_isSelect = false;
	m_isUse = false;
	m_isMove = false;
	m_isClickDouble = false;
	m_attribute = CLICK_ONE;
	m_unit = nullptr;
	m_isCrush = false;

	return S_OK;
}

void Card::release()
{
}

void Card::update()
{
	

	if (m_isSelect)
	{
		m_pos.y = 150.0f;
	}
	else
	{
		m_pos.y = 100.0f;
	}

	//if (m_isUse)
	//{
	//	cardUseType();
	//}

	m_rc = RectMakeCenter(m_pos.x, m_pos.y, 150.0f, 150.0f);

}

void Card::render()
{
	if (m_cardImage != nullptr)
	{
		m_cardImage->Position(m_pos);
		m_cardImage->Scale(150.0f, 150.0f);
		m_cardImage->Render();

		//비용 숫자 표시
		Image* img = IMGMANAGER->GetImage("ui_number");
		img->Scale(40, 30);
		img->GetRefCurrentFrameX() = m_ap;
		img->Position(m_pos.x + 40, m_pos.y + 60);
		img->Render();

		if (m_isSelect)
		{
			RECT rect = { (long)(m_pos.x - 70.0f),
			(long)(WINSIZEY - 110.0f),
			(long)(m_pos.x + 75.0f),
			(long)(WINSIZEY) };
			WRITEMANAGER->RenderText(m_inform, rect, 15, L"궁서체", D3DXCOLOR(0, 0, 0, 1));
		}
		else
		{
			RECT rect = { (long)(m_pos.x - 70.0f),
			(long)(WINSIZEY - 60.0f),
			(long)(m_pos.x + 75.0f),
			(long)(WINSIZEY) };
			WRITEMANAGER->RenderText(m_inform, rect, 15, L"궁서체", D3DXCOLOR(0, 0, 0, 1));
		}
		
	}
	
}

void Card::selectOnOff()
{

	m_isSelect = m_isSelect ? false : true;

}

bool Card::checkAp(int myap)
{
	if (m_ap > myap) return false;

	return true;
}

void Card::cardType()
{
	switch (m_type)
	{
	case CARD_NULL:
		m_cardImage = nullptr;
		m_ap = NULL;
		m_atk = NULL;
		m_hp = NULL;
		m_range = NULL;
		m_inform = L"";
		break;
	case CARD_MARINE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";//\nDamage:" + tempFile + L" Range : ";// +m_range;
		break;
	default:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";
		break;
	case CARD_SCV:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_scv");
		m_ap = 3;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"이야~ 야근이다!";
		break;
	case CARD_BARRIGATE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Barrigate");
		m_ap = 2;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"SCV를 벽으로 바꿉니다.";
		break;
	case CARD_TANK:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Tank");
		m_ap = 5;
		m_atk = 1;
		m_hp = 1;
		m_range = 0;
		m_inform = L"Ready to roll out!";
		break;
	case CARD_MANEUVER:
		m_attribute = CLICK_TWO;
		m_cardImage = IMGMANAGER->GetImage("card_Maneuver");
		m_ap = 1;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"선택한 아군유닛을 다른 라인으로 움직입니다.";
		break;
	case CARD_FIELD_REPAIR:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Field Repair");
		m_ap = 3;
		m_atk = 0;
		m_hp = 2;
		m_range = 0;
		m_inform = L"무엇이든 체력을 2 회복시켜줍니다.";
		break;
	case CARD_STEAMPACK:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_StimPack");
		m_ap = 2;
		m_atk = 1;
		m_hp = 1;
		m_range = 0;
		m_inform = L"기분좋은 향기가 솔솔 피어난다";
		break;
	case CARD_MEDIC:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_medic");
		m_ap = 3;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"이랏샤이마세~";
		break;
	case CARD_FIREBAT:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_firebat");
		m_ap = 4;
		m_atk = 2;
		m_hp = 3;
		m_range = 2;
		m_inform = L"확, 불 질러 버릴까요?";
		break;
	case CARD_GHOST:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_ghost");
		m_ap = 5;
		m_atk = 1;
		m_hp = 2;
		m_range = 5;
		m_inform = L"숫가락 구부리기 보여드릴까요?";
		break;
	case CARD_SIEGE_MODE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_SiegeMode");
		m_ap = 5;
		m_atk = 1;
		m_hp = 2;
		m_range = 5;
		m_inform = L"일부는 시즈모드 일부는 퉁퉁퉁";
		break; 
	case CARD_YAMATO:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Yamato");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"지정한 유닛에게 5데미지를 줍니다.";
		break;
	case CARD_DRONE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_drone");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"드론은 카드낭비";
		break;
	case CARD_ZURGLING:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zurgling");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"애완용 저글링이 단돈 2원!";
		break;
	case CARD_ZURGLING_TOKEN:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zurgling");
		m_ap = 0;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"토큰으로 만들어진 저글링입니다.";
		break;
	case CARD_HYDRA:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_hydra");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"S라인을 지니고 있는 저그유닛입니다.";
		break;
	case CARD_LURKER:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_lurker");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"히드라를 럴커로 변신시킵니다.";
		break;
	case CARD_BURROW:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_burrow");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"럴커를 버로우시킵니다.";
		break;
	case CARD_BRUDLING:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_bru");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"선택한 타일에 있는 유닛을 브루들링의 밥으로 만듭니다.";
		break;
	case CARD_ULTRA:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_ultra");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"아주 점잖은 신사입니다.\n정말로요!";
		break;
	case CARD_SUDDEN_RAID:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_sudden");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"클릭한 아군 유닛이 있는 Y타일에 저글링을 소환합니다.";
		break;
	case CARD_TORASQUE_ROAR:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_torasque");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"모든 적 유닛의 공격을 한번방해합니다.";
		break;
	case CARD_PROVE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_prove");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"작은 프로토스 기계입니다.";
		break;
	case CARD_ZEALOT:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zealot");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"엔 타로 아둔!";
		break;
	case CARD_DRAGON:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_dragon");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"하지만 드라군이 출동한다면 어떨까?";
		break;
	case CARD_RIVER:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_river");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"이런! 불발이네요";
		break;
	case CARD_MIND_CONTROL:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_mindcontrol");
		m_ap = 7;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"선택한 유닛을 내 유닛으로 만듭니다.";
		break;
	case CARD_MAKE_HIM_DRAGON:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_makehimdragon");
		m_ap = 8;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"움직일수 없는 자들을 모두 용기병으로 만들어라!";
		break;
	case CARD_RECALL:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_recall");
		m_ap = 1;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"선택한 아군유닛을 귀환시키고 AP를 돌려받습니다.";
		break;
	case CARD_END:
		break;
	}
}

void Card::cardUse(int idxx, int idxy)
{
	idxX = idxx;
	idxY = idxy;
	if (m_attribute == CLICK_ONE)
	{
		m_isSelect = false;
		m_isUse = true;
		//cout << "클릭 한번짜리 들어옴" << endl;
	}
	else
	{
		//cout << "클릭 두번짜리니까 한번더 클릭가능한 상태만들어줌" << endl;
		m_isClickDouble = true;
	}

}

void Card::cardUseDouble(int idxx, int idxy)
{
	//cout << "클릭 두번째 들어왔어요" << endl;
	//cout << idxx << " " << idxy << "  두번쨰 클릭때 받은 인덱스값" << endl;
	idxX2 = idxx;
	idxY2 = idxy;
	m_isSelect = false;
	m_isUse = true;
	m_isClickDouble = false;
}

void Card::cardUseType()
{
	switch (m_type)
	{
	case CARD_NULL:
		
		break;
	case CARD_MARINE:

		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
			m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_MARINE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	default:
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";
		break;
	case CARD_SCV:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_SCV);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_BARRIGATE);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_MEDIC:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_MEDIC);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_FIREBAT:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_FIREBAT);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_GHOST:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_GHOST);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_TANK:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_TANKN);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_MANEUVER:
		//cout << "여까지 왔어요" << endl;
		//처음 클릭시 움직일 유닛타일을 받음
		//고로 idxX,idxY는 움직일 유닛이 있는 타일
		//두번째 클릭시 움직일 타일을 받음
		//고로 idxX2,idxY2는 움직일 타일이다.
		//우선 움직일 유닛의 포인터주소를 받아옴
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}
		//그 후 움직일수 있는 타일인지 판별해본다.
		//우선 서있는 곳이랑 y값이 같으면 움직일필요없으니 컷
		if (idxY == idxY2 ||
			//또는 갈 위치에 벽이 있으면 빠꾸
			m_tile->CheckTileWall(idxX,idxY2,TILE_WALL) ||
			//또는 돈이 없을때
			g_actionPoint < m_ap
			//또는 오브젝트가 있을때 근데 그게 난 대형 개는 소형인 예외가 있음
			)
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
			//cout << "움직일수 있는 타일이 아니거나" << endl;
			//cout << "돈이 없대요" << endl;
			//cout << idxY << " " << idxY2 << " 첫번째는 유닛위치 두번째는 움직일 Y위치에요" << endl;
			return;
		}

		//그래서 따로 빼서 검사해준다.
		//오브젝트가 있을땐 난 대형 갠 소형인 그 경우일때만 밑으로 가고
		//나머지는 전부 빠꾸
		if (m_tile->CheckTileObject(idxX, idxY2))
		{
			//cout << "갈 타일에 오브젝트가 있대요" << endl;
			//우선 갈 방향에 있는 그 유닛의 포인터를 받아옴
			Unit* tempUnit = m_tile->returnInUnit(idxX, idxY2);

			//갈 녀석은 크고 갈곳에 있는건 작을땐 
			//을 제외하면 못가는 상황이니 빠꾸
			if (m_unit->Getm_defenceType() == DFCTYPE_LA && tempUnit->Getm_defenceType() == DFCTYPE_SM)
			{
				//cout << "큰놈앞에 작은놈이 있대요 뭉개시져" << endl;
				m_isCrush = true;
			}
			else
			{
				m_isUse = false;
				g_mouseState = M_NORMAL;
				//cout << "큰놈도 아니면 갈생각좀 하지마라 씨발새꺄" << endl;

				return;
			}
		}
		//위 조건 안걸리고 오브젝트도 없으면
		//이동시켜주면 된다.
		//cout << "험난한 과정이었습니다 이동해도 좋습니다" << endl;
		m_unit->moveTileY(idxX, idxY2, m_isCrush);
		SOUNDMANAGER->play("maneuver", g_masterVolume * g_extraVolume);
		m_isUse = false;
		m_isSelect = false;
		g_mouseState = M_NORMAL;
		g_actionPoint -= m_ap;
		m_type = CARD_NULL;
		m_isCrush = false;
		cardType();

		//m_playGame->drawCard(CARD_SCV);

		
		break;
	case CARD_FIELD_REPAIR:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->heal(m_hp);
			SOUNDMANAGER->play("repair", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_STEAMPACK:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if ((m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_MARINE || 
			m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_FIREBAT )&&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->steampack();
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BARRIGATE:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_SCV &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_BARIGATE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_SIEGE_MODE:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_TANKN &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX ,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_TANKS);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_YAMATO:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->yamato();
			SOUNDMANAGER->play("yamato", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_DRONE:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRONE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_ZURGLING:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZURGLING);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_ZURGLING_TOKEN);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		
		break;
	case CARD_ZURGLING_TOKEN:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZURGLING);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_HYDRA:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_HYDRA);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_LURKER:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_HYDRA &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RULKER);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_BURROW);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BURROW:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_RULKER &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RULKER_BURROW);
			//m_playGame->drawCard(CARD_UNBURROW);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BRUDLING:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->changeState(UTST_DIE);
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_BRU);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_ULTRA:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ULTRA);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_SUDDEN_RAID:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			for (int i = 0; i < 4; i++)
			{
				if (!m_tile->CheckTileObject(idxX, i) &&
					!m_tile->CheckTileWall(idxX, i, TILE_WALL))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						idxX * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						i * m_tile->Getm_TileDesc().TileSizeY),
						1, UTYP_ZURGLING); 
					SOUNDMANAGER->play("sudden", g_masterVolume * g_extraVolume);
				}
			}
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_TORASQUE_ROAR:
		if (g_actionPoint >= m_ap)
		{
			m_unitManager->cardTorasque();
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		
		break;
	case CARD_PROVE:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_PROBE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_ZEALOT:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZEALOT);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_DRAGON:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRAGON);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_RIVER:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RIVER);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_MIND_CONTROL:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() != 1 && 
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->mindControl();
			SOUNDMANAGER->play("mindcontrol", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_MAKE_HIM_DRAGON:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->changeState(UTST_DIE);
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRAGON);
			SOUNDMANAGER->play("makedragon", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_RECALL:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//근데 그 타일에 유닛이 없다면?
		//내보내준다.
		if (m_unit == nullptr)
		{
			//cout << "근데 유닛이 널??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			g_actionPoint += m_tile->returnInUnit(idxX, idxY)->Getm_cost();
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			SOUNDMANAGER->play("recall", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_END:
		break;
	}


}
