#include "stdafx.h"
#include "Unit.h"
#include "MiniGame/map/TileMap.h"

Unit::Unit()
{
}


Unit::~Unit()
{
}

//void Unit::unitType()
//{
//	switch (m_unitType)
//	{
//	case UTYP_MARINE:
//		m_unitImage = IMGMANAGER->GetImage("marine");
//		
//		m_maxHp = 40;
//		m_hp = m_maxHp;
//		m_maxShield = 0;
//		m_shield = m_maxShield = 0 ? 0 : m_maxShield;
//		
//		m_maxMp = 0;
//		m_mp = m_maxMp  = 0 ? 0 : m_maxMp / 3;
//		m_attackDamage = 6;
//		m_defence = 0;
//
//		m_moveSpeed = 1.8f;
//
//		m_attackDelay = 15.0f;
//		m_attackTime = 0.0f;
//		m_attackNumber = 1;
//
//		m_checkInRangeTime = 0;
//
//		m_range = 4;
//		m_population = 1;
//
//		m_attackType = ATKTYPE_N;
//		m_defenceType = DFCTYPE_SM;
//		
//		m_size = D3DXVECTOR2(50.0f,50.0f);
//		m_rc = RectMakeCenter(m_pos.x, m_pos.y, m_size.x, m_size.y);
//		break;
//	case UTYP_SCV:
//		break;
//	default:
//		break;
//	}
//}

HRESULT Unit::init()
{
	return S_OK;
}

HRESULT Unit::init(D3DXVECTOR2 pos, int host, UNIT_TYPE type)
{
	m_pos = pos;
	m_unitType = type;
	m_host = host;
	m_isDead = false;
	m_unitState = UTST_IDLE;

	m_gostop = IMGMANAGER->GetImage("ui_move");
	m_isGo = true;
	m_dir = host == 1 ? DIR_E : DIR_W;
	m_minRange = 0;
	unitInfo();
	m_rc = RectMakeCenter(m_pos.x, m_pos.y, m_size.x, m_size.y);
	//unitType();
	m_isWorkDoneAct = false;
	m_isWorkDoneKill = false;
	m_isWorkDoneMove = false;
	m_attackMotionFinish = false;
	m_deadMotionFinish = false;
	m_isGoOver = false;
	m_isMoveY = false;
	m_isAttackSound = true;

	return S_OK;
}

void Unit::release()
{
}

void Unit::update()
{
	frameMove();
	checkDir();
	unitType();

	if (m_isMoveY)
	{
		moveTileY2();
	}

	//cout << m_unitState << endl;
	//cout << m_isGoOver << endl;
	//cout << "윈포인트" << g_winPoint << "  루즈포인트" << g_losePoint << endl;

	m_rc = RectMakeCenter(m_pos.x, m_pos.y, m_size.x, m_size.y);
}

void Unit::render()
{
	Rect* rc;


	if (g_isDebug)
	{
		rc = IMGMANAGER->Getrect();
		rc->Position(m_pos);
		rc->Scale(m_size);
		rc->Color(0.0f, 0.0f, 0.0f);
		rc->SetisFill(true);
		rc->Render();
	}

	progressBar* prc;
	Image* img;
	prc = IMGMANAGER->Getprogress();
	if (m_host == 1)
	{
		//체력바 렌더
		prc->Direction(DIR_SE);
		prc->Position(m_pos.x - 40.0f, m_pos.y + 10.0f);
		prc->Scale(20.0f, m_hp * 4.0f);
		prc->SetisFill(true);
		prc->Color(1.0f, 1.0f, 0.0f);
		prc->Render();

		//체력바 렌더
		prc->Direction(DIR_SE);
		prc->Position(m_pos.x - 40.0f, m_pos.y + 10.0f);
		prc->Scale(20.0f, m_maxHp * 4.0f);
		prc->SetisFill(false);
		prc->Color(1.0f, 1.0f, 0.0f);
		prc->Render();

		if (m_shield > 0)
		{
			//쉴드바 렌더
			prc->Direction(DIR_SE);
			prc->Position(m_pos.x - 40.0f, m_pos.y + 10.0f - m_maxHp * 4.0f);
			prc->Scale(20.0f, m_shield * 4.0f);
			prc->SetisFill(true);
			prc->Color(0.0f, 0.0f, 1.0f);
			prc->Render();

			//쉴드바 렌더
			prc->Direction(DIR_SE);
			prc->Position(m_pos.x - 40.0f, m_pos.y + 10.0f - m_maxHp * 4.0f);
			prc->Scale(20.0f, m_maxShield * 4.0f);
			prc->SetisFill(false);
			prc->Color(0.0f, 0.0f, 1.0f);
			prc->Render();
		}
		

		//승리포인트 렌더
		img = IMGMANAGER->GetImage("ui_vp");
		img->Position(m_pos.x - 30.0f, m_pos.y - 30.0f);
		img->Render();

		img = IMGMANAGER->GetImage("ui_number");
		img->Scale(20, 15);
		img->GetRefCurrentFrameX() = m_winPoint;
		img->Position(m_pos.x - 30.0f - 15.0f, m_pos.y - 30.0f);
		img->Render();

		//장전 재사용 대기시간 렌더용
		if (m_Creload > 0)
		{
			
			img = IMGMANAGER->GetImage("ui_reload");
			img->Position(m_pos.x + 30.0f, m_pos.y - 30.0f);
			img->Render();

			img = IMGMANAGER->GetImage("ui_number");
			img->Scale(20, 15);
			img->GetRefCurrentFrameX() = m_Creload;
			img->Position(m_pos.x + 30.0f + 15.0f, m_pos.y - 30.0f);
			img->Render();
		}

		if (g_isDebug)
		{
			//사거리 표시용
			prc->Direction(DIR_NE);
			prc->Position(m_pos.x + m_tile->Getm_TileDesc().TileSizeX / 2.0f +
				m_minRange * m_tile->Getm_TileDesc().TileSizeX,
				m_pos.y - m_tile->Getm_TileDesc().TileSizeY / 2.0f);
			prc->Scale(m_tile->Getm_TileDesc().TileSizeX * (m_rangeX - m_minRange),
				m_tile->Getm_TileDesc().TileSizeY * m_rangeY);
			prc->SetisFill(true);
			prc->Color(0.0f, 0.0f, 0.0f, 0.3f);
			prc->Render();
		}
		else if (PtInRect(m_rc, g_ptMouse))
		{
			//사거리 표시용
			prc->Direction(DIR_NE);
			prc->Position(m_pos.x + m_tile->Getm_TileDesc().TileSizeX / 2.0f +
				m_minRange * m_tile->Getm_TileDesc().TileSizeX,
				m_pos.y - m_tile->Getm_TileDesc().TileSizeY / 2.0f);
			prc->Scale(m_tile->Getm_TileDesc().TileSizeX * (m_rangeX - m_minRange),
				m_tile->Getm_TileDesc().TileSizeY * m_rangeY);
			prc->SetisFill(true);
			prc->Color(0.0f, 0.0f, 0.0f, 0.3f);
			prc->Render();
		}
		

		m_gostop->Position(m_pos.x - 30.0f, m_pos.y + 25.0f);
		if (m_isGo)m_gostop->GetRefCurrentFrameX() = 0;
		else m_gostop->GetRefCurrentFrameX() = 1;
		m_gostop->Render();
		
	}
	else
	{
		//체력바 렌더
		prc->Direction(DIR_SE);
		prc->Position(m_pos.x + 30.0f, m_pos.y + 10.0f);
		prc->Scale(20.0f, m_hp * 4.0f);
		prc->SetisFill(true);
		prc->Color(1.0f, 0.0f, 0.0f);
		prc->Render();

		//체력바 렌더
		prc->Direction(DIR_SE);
		prc->Position(m_pos.x + 30.0f, m_pos.y + 10.0f);
		prc->Scale(20.0f, m_maxHp * 4.0f);
		prc->SetisFill(false);
		prc->Color(1.0f, 0.0f, 0.0f);
		prc->Render();


		if (m_shield > 0)
		{
			//쉴드바 렌더
			prc->Direction(DIR_SE);
			prc->Position(m_pos.x + 30.0f, m_pos.y + 10.0f - m_maxHp * 4.0f);
			prc->Scale(20.0f, m_shield * 4.0f);
			prc->SetisFill(true);
			prc->Color(0.0f, 0.0f, 1.0f);
			prc->Render();

			//쉴드바 렌더
			prc->Direction(DIR_SE);
			prc->Position(m_pos.x + 30.0f, m_pos.y + 10.0f - m_maxHp * 4.0f);
			prc->Scale(20.0f, m_maxShield * 4.0f);
			prc->SetisFill(false);
			prc->Color(0.0f, 0.0f, 1.0f);
			prc->Render();
		}
		

		//승리포인트 렌더
		img = IMGMANAGER->GetImage("ui_vp");
		img->Position(m_pos.x + 30.0f, m_pos.y - 30.0f);
		img->Render();

		img = IMGMANAGER->GetImage("ui_number");
		img->Scale(20, 15);
		img->GetRefCurrentFrameX() = m_winPoint;
		img->Position(m_pos.x + 30.0f + 15.0f, m_pos.y - 30.0f);
		img->Render();
		 
		//장전 재사용 대기시간 렌더용
		if (m_Creload > 0)
		{

			img = IMGMANAGER->GetImage("ui_reload");
			img->Position(m_pos.x - 30.0f, m_pos.y - 30.0f);
			img->Render();

			img = IMGMANAGER->GetImage("ui_number");
			img->Scale(20, 15);
			img->GetRefCurrentFrameX() = m_Creload;
			img->Position(m_pos.x - 30.0f - 15.0f, m_pos.y - 30.0f);
			img->Render();
		}

		if (g_isDebug)
		{
			//사거리 표시용
			prc->Direction(DIR_NW);
			prc->Position(m_pos.x - m_tile->Getm_TileDesc().TileSizeX / 2.0f
				- m_minRange * m_tile->Getm_TileDesc().TileSizeX,
				m_pos.y - m_tile->Getm_TileDesc().TileSizeY / 2.0f);
			prc->Scale(m_tile->Getm_TileDesc().TileSizeX * (m_rangeX - m_minRange),
				m_tile->Getm_TileDesc().TileSizeY * m_rangeY);
			prc->SetisFill(true);
			prc->Color(0.5f, 0.0f, 0.0f, 0.3f);
			prc->Render();
		}
		else if (PtInRect(m_rc, g_ptMouse))
		{
			//사거리 표시용
			prc->Direction(DIR_NW);
			prc->Position(m_pos.x - m_tile->Getm_TileDesc().TileSizeX / 2.0f
				- m_minRange * m_tile->Getm_TileDesc().TileSizeX,
				m_pos.y - m_tile->Getm_TileDesc().TileSizeY / 2.0f);
			prc->Scale(m_tile->Getm_TileDesc().TileSizeX * (m_rangeX - m_minRange),
				m_tile->Getm_TileDesc().TileSizeY * m_rangeY);
			prc->SetisFill(true);
			prc->Color(0.5f, 0.0f, 0.0f, 0.3f);
			prc->Render();
		}
		

		m_gostop->Position(m_pos.x + 30.0f, m_pos.y + 25.0f);
		if (m_isGo)m_gostop->GetRefCurrentFrameX() = 2;
		else m_gostop->GetRefCurrentFrameX() = 3;
		m_gostop->Render();
	}




	m_unitImage[m_unitState]->Position(m_pos);
	m_unitImage[m_unitState]->Scale(m_size * 2.0f);
	m_unitImage[m_unitState]->GetRefCurrentFrameX() = m_frameX;
	m_unitImage[m_unitState]->GetRefCurrentFrameY() = m_frameY;
	m_unitImage[m_unitState]->Render();
}

void Unit::frameMove()
{
	//사운드 m_frameX == 0 &&
	if ( m_unitState == UTST_ATT && m_isAttackSound)
	{
		switch (m_unitType)
		{
		case UTYP_MARINE:
			SOUNDMANAGER->play("marineAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_SCV:
			SOUNDMANAGER->play("scvAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_TANKN:
			SOUNDMANAGER->play("tankNAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_TANKS:
			SOUNDMANAGER->play("tankSAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_VURTURE:
			break;
		case UTYP_MEDIC:
			SOUNDMANAGER->play("medicAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_FIREBAT:
			SOUNDMANAGER->play("firebatAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_GHOST:
			SOUNDMANAGER->play("ghostAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_BARIGATE:
			break;
		case UTYP_DRONE:
			SOUNDMANAGER->play("droneAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ZURGLING:
			SOUNDMANAGER->play("zurglingAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_HYDRA:
			SOUNDMANAGER->play("hydraAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_RULKER:
			break;
		case UTYP_RULKER_BURROW:
			SOUNDMANAGER->play("lurkerAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ULTRA:
			SOUNDMANAGER->play("ultraAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_BRU:
			SOUNDMANAGER->play("bruAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_PROBE:
			SOUNDMANAGER->play("proveAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ZEALOT:
			SOUNDMANAGER->play("zealotAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_DRAGON:
			SOUNDMANAGER->play("dragonAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_RIVER:
			SOUNDMANAGER->play("riverAtt", g_masterVolume * g_extraVolume);
			break;
		case UTYP_END:
			break;
		default:
			break;
		}
		m_isAttackSound = false;
	}

	if (m_frameTime >= m_frameDelay)
	{
		m_frameTime = 0.0f;
		m_frameX++;
		if (m_frameX >= static_cast<int>(m_unitImage[m_unitState]->GetRefmaxFrameX()))
		{
			m_frameX = 0;
			if (m_unitState == UTST_ATT)
			{
				m_attackMotionFinish = true;
				m_isAttackSound = true;
			}
			if (m_unitState == UTST_DIE)
			{
				m_deadMotionFinish = true;
			}
		}
	}
	else
	{
		m_frameTime += g_ETime;
	}
}

void Unit::checkDir()
{
	if (m_unitType == UTYP_MARINE)
	{
		switch (m_dir)
		{
		case DIR_N:
			m_frameY = 0;
			break;
		case DIR_NE:
			m_frameY = 1;
			break;
		case DIR_E:
			m_frameY = 2;
			break;
		case DIR_SE:
			m_frameY = 3;
			break;
		case DIR_S:
			m_frameY = 4;
			break;
		case DIR_SW:
			m_frameY = 5;
			break;
		case DIR_W:
			m_frameY = 6;
			break;
		case DIR_NW:
			m_frameY = 7;
			break;
		case DIR_END:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_dir)
		{
		case DIR_E:
			m_frameY = 0;
			break;
		case DIR_W:
			m_frameY = 1;
			break;
		}
	}
	

	if (m_unitState == UTST_DIE) m_frameY = 0;


}

void Unit::changeState(UNIT_STATE state)
{
	m_unitState = state;
	m_frameX = 0;
	if (state == UTST_DIE)
	{
		switch (m_unitType)
		{
		case UTYP_MARINE:
			SOUNDMANAGER->play("marineDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_SCV:
			SOUNDMANAGER->play("scvDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_TANKN:
			
		case UTYP_TANKS:
			SOUNDMANAGER->play("tankDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_VURTURE:
			break;
		case UTYP_MEDIC:
			SOUNDMANAGER->play("medicDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_FIREBAT:
			SOUNDMANAGER->play("firebatDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_GHOST:
			SOUNDMANAGER->play("ghostDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_BARIGATE:
			SOUNDMANAGER->play("barrigateDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_DRONE:
			SOUNDMANAGER->play("droneDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ZURGLING:
			SOUNDMANAGER->play("zurglingDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_HYDRA:
			SOUNDMANAGER->play("hydraDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_RULKER:
		case UTYP_RULKER_BURROW:
			SOUNDMANAGER->play("lurkerDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ULTRA:
			SOUNDMANAGER->play("ultraDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_BRU:
			SOUNDMANAGER->play("bruDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_PROBE:
			SOUNDMANAGER->play("proveDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_ZEALOT:
			SOUNDMANAGER->play("zealotDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_DRAGON:
			SOUNDMANAGER->play("dragonDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_RIVER:
			SOUNDMANAGER->play("riverDie", g_masterVolume * g_extraVolume);
			break;
		case UTYP_END:
			break;
		default:
			break;
		}
	}
	int n;
	if (state == UTST_MOVE)
	{
		switch (m_unitType)
		{
		case UTYP_MARINE:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("marineMove0", g_masterVolume * g_extraVolume);
				break;
			case 1:
				SOUNDMANAGER->play("marineMove1", g_masterVolume * g_extraVolume);
				break;
			case 2:
				SOUNDMANAGER->play("marineMove2", g_masterVolume * g_extraVolume);
				break;
			case 3:
				SOUNDMANAGER->play("marineMove3", g_masterVolume * g_extraVolume);
				break;
			}
			
			break;
		case UTYP_SCV:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("scvMove0", g_masterVolume * g_extraVolume);
				break;
			case 1:
				SOUNDMANAGER->play("scvMove1", g_masterVolume * g_extraVolume);
				break;
			case 2:
				SOUNDMANAGER->play("scvMove2", g_masterVolume * g_extraVolume);
				break;
			case 3:
				SOUNDMANAGER->play("scvMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_TANKN:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("tankMove0", g_masterVolume * g_extraVolume);
				break;
			case 1:
				SOUNDMANAGER->play("tankMove1", g_masterVolume * g_extraVolume);
				break;
			case 2:
				SOUNDMANAGER->play("tankMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("tankMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_TANKS:
			break;
		case UTYP_VURTURE:
			break;
		case UTYP_MEDIC:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("medicMove0", g_masterVolume * g_extraVolume);
				break;
			case 1:
				SOUNDMANAGER->play("medicMove1", g_masterVolume * g_extraVolume);
				break;
			case 2:
				SOUNDMANAGER->play("medicMove2", g_masterVolume * g_extraVolume);
				break;
			case 3:
				SOUNDMANAGER->play("medicMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_FIREBAT:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("firebatMove0", g_masterVolume * g_extraVolume);
				break;
			case 1:
				SOUNDMANAGER->play("firebatMove1", g_masterVolume * g_extraVolume);
				break;
			case 2:
				SOUNDMANAGER->play("firebatMove2", g_masterVolume * g_extraVolume);
				break;
			case 3:
				SOUNDMANAGER->play("firebatMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_GHOST:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("ghostMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("ghostMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("ghostMove2", g_masterVolume * g_extraVolume);
				break;			
			case 3:				
				SOUNDMANAGER->play("ghostMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_BARIGATE:
			break;
		case UTYP_DRONE:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("droneMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("droneMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("droneMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("droneMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_ZURGLING:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("zurglingMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("zurglingMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("zurglingMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("zurglingMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_HYDRA:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("hydraMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("hydraMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("hydraMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("hydraMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_RULKER:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("lurkerMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("lurkerMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("lurkerMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("lurkerMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_RULKER_BURROW:
			break;
		case UTYP_ULTRA:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("ultraMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("ultraMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("ultraMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("ultraMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_BRU:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("bruMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("bruMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("bruMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("bruMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_PROBE:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("proveMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("proveMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("proveMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("proveMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_ZEALOT:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("zealotMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("zealotMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("zealotMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("zealotMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_DRAGON:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("dragonMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("dragonMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("dragonMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("dragonMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_RIVER:
			n = GetInt(4);
			switch (n)
			{
			case 0:
				SOUNDMANAGER->play("riverMove0", g_masterVolume * g_extraVolume);
				break;				
			case 1:					
				SOUNDMANAGER->play("riverMove1", g_masterVolume * g_extraVolume);
				break;				
			case 2:					
				SOUNDMANAGER->play("riverMove2", g_masterVolume * g_extraVolume);
				break;				
			case 3:					
				SOUNDMANAGER->play("riverMove3", g_masterVolume * g_extraVolume);
				break;
			}
			break;
		case UTYP_END:
			break;
		default:
			break;
		}
	}
}

void Unit::unitType()
{
	int idxx, idxy;
	PtinTile(idxx, idxy, m_tile->Getm_TileDesc(), m_pos);
	if (idxx < 0) idxx = 0;
	if (idxx >= m_tile->Getm_TileDesc().TileMaxX) idxx = m_tile->Getm_TileDesc().TileMaxX - 1;
	switch (m_unitState)
	{
	case UTST_MOVE:

		//맵 끝있때는 유닛삭제
		//이동하는 타일이 2이상일때 벽을 뚫고 골인하기도 함
		//지금 구조로는 깔끔하게 정리가 안되기도하고
		//벽있는 맵이 1맵뿐이고 이음.. 모르겠다일단패스
		if (m_isGoOver)
		{
			if (m_host == 1)
			{
				//m_tile->Getm_TileDesc().TileMaxX - m_moveTile + 1
				m_tile->RemoveUnit(idxx, idxy);

				m_pos.x += m_moveSpeed * g_ETime;

				if (m_pos.x > WINSIZEX + 50)
				{
					//m_pos.x = WINSIZEX / 2.0f;
					//changeState(UTST_DIE);
					m_isDead = true;
					m_isWorkDoneMove = true;
					g_winPoint += m_winPoint;
					SOUNDMANAGER->play("ef_coin", g_masterVolume * g_extraVolume);
				}
			}
			else
			{
				m_tile->RemoveUnit(idxx, idxy);

				m_pos.x -= m_moveSpeed * g_ETime;

				if (m_pos.x < -50)
				{
					//m_pos.x = WINSIZEX / 2.0f;
					//changeState(UTST_DIE);
					m_isDead = true;
					m_isWorkDoneMove = true;
					g_losePoint += m_winPoint;
					SOUNDMANAGER->play("ef_coin", g_masterVolume * g_extraVolume);
				}
			}



		}

		//플레이어가 가야될 길이 사이즈가 0보다 크면 길찾기로 가야될 길이 존재한다.
		else if (astarWay.size() > 0)
		{
			if (PtinTile(idxx, idxy, m_tile->Getm_TileDesc(), m_pos))
			{
				//플레이어는 idxx,idxy 에서 m_playerWay.back().x m_playerWay.back().y 로 향해야한다
				//도착타일에 유닛이 존재하면
				if (m_tile->CheckTileObject(astarWay.back().x,astarWay.back().y))
				{
					//그리고 도착타일과 현재 타일에 유닛이 주인이 다를때
					if (m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->Getm_host() !=
						m_tile->returnInUnit(idxx, idxy)->Getm_host())
					{
						//서로 타일들에 있는 놈들이 같은 타입이면
						if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() ==
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->Getm_defenceType())
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//내 타일은 소형인데 저기 타일은 중간사이즈타입일때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_SM &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_ME)
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//내 타일은 소형인데 저기 타일은 대형일때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_SM &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_LA)
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//내 타일은 중형인데 저기 타일은 소형일때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_ME &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_SM)
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//내 타일은 중형인데 저기 타일은 졸라클때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_ME &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_LA)
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//나도 졸라 크지만 저기 타일도 중간은 될때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_LA &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_ME)
						{
							//다음 길로 가지말고 빼줘라
							astarWay.clear();
						}
						//내가 졸라 커서 저기 타일쪼꼬미를 짓밟고 싶을때
						else if (m_tile->returnInUnit(idxx, idxy)->Getm_defenceType() == DFCTYPE_LA &&
							m_tile->returnInUnit(astarWay.back().x, astarWay.back().y)->
							Getm_defenceType() == DFCTYPE_SM)
						{
							
							//갈 타일에 있는놈 빼주고 죽여준다
							//갈 타일에 있는놈이 널이 아닐때(한번만 죽이기 위해서)
							if (m_tile->returnInUnit(astarWay.back().x,
								astarWay.back().y) != nullptr)
							{
								m_tile->returnInUnit(astarWay.back().x,
									astarWay.back().y)->changeState(UTST_DIE);
								m_tile->RemoveUnit(astarWay.back().x, astarWay.back().y);
							}
							
							

							D3DXVECTOR2 dest;
							dest.x = m_tile->Getm_TileDesc().ZeroStartPos.x +
								astarWay.back().x * m_tile->Getm_TileDesc().TileSizeX;

							dest.y = m_tile->Getm_TileDesc().ZeroStartPos.y +
								astarWay.back().y * m_tile->Getm_TileDesc().TileSizeY;

							//m_player.pos -> dest 로 이동
							D3DXVECTOR2 temp;
							D3DXVec2Normalize(&temp, &(dest - m_pos));
							m_pos += temp * g_ETime * m_moveSpeed;

							//거리가 가까워 지면 길벡터에서 끝을 빼준다.
							if (GetDistance(m_pos.x, m_pos.y, dest.x, dest.y) < 2.0f)
							{
								//내가 있던 타일에서 유닛빼주고
								m_tile->RemoveUnit(idxx, idxy);
								//m_targetUnit = m_tile->returnInUnit(astarWay.back().x, astarWay.back().y);
								//m_targetUnit->changeState(UTST_DIE);
								m_tile->SetUnit(astarWay.back().x, astarWay.back().y, this);
								astarWay.pop_back();
							}
						}
					}
					//도착타일에 머가 있긴한데 주인이 같을때
					else if (m_tile->CheckTileObject(astarWay.back().x, astarWay.back().y))
					{
						//다음 길로 가지말고 빼줘라
						astarWay.clear();
					}
					
				}
				////도착지점에 오브젝트가 있을경우
				//if (m_Tiles[EndX][EndY].isObject)
				//{
				//	//갈수있는 경우 1. 난 대형이고 해당타일에는 소형유닛이 있다.
				//	//갈수없는 경우 1. 난 소형이고 상대도 소형(o)
				//	//갈수없는 경우 2. 난 소형이고 해당타일에는 중형유닛이 있다.(o)
				//	//갈수없는 경우 3. 난 소형이고 해당타일에는 대형유닛이 있다.(o)
				//	//갈수없는 경우 4. 난 중형이고 해당타일에는 소형유닛이 있다.(o)
				//	//갈수없는 경우 5. 난 중형이고 해당타일에는 중형유닛이 있다.(o)
				//	//갈수없는 경우 6. 난 중형이고 해당타일에는 대형유닛이 있다.(o)
				//	//갈수없는 경우 7. 난 대형이고 해당타일에는 중형유닛이있다.(o)
				//	//갈수없는 경우 8. 난 대형이고 해당타일에는 대형유닛이 있닷.(o)
				//	if (m_Tiles[StartX][StartY].inUnit->Getm_defenceType() == DFCTYPE_SM &&
				//		m_Tiles[EndX][EndY].inUnit->Getm_defenceType() == DFCTYPE_SM)
				//	{
				//	}

				//}
				//아 근데 벽이면 가지마라
				else if (m_tile->CheckTileWall(astarWay.back().x, astarWay.back().y,TILE_WALL))
				{
					astarWay.clear();
				}
				//도착타일에 오브젝트가 없으면 가던대로 가라
				else
				{
				
				
				//else
				{
					m_tile->RemoveUnit(idxx, idxy);

					D3DXVECTOR2 dest;
					dest.x = m_tile->Getm_TileDesc().ZeroStartPos.x +
						astarWay.back().x * m_tile->Getm_TileDesc().TileSizeX;

					dest.y = m_tile->Getm_TileDesc().ZeroStartPos.y +
						astarWay.back().y * m_tile->Getm_TileDesc().TileSizeY;

					/*if (astarWay.size() == 1)
					{
						dest.x = m_exactTargetPos.x;

						dest.y = m_exactTargetPos.y;

						m_targetPos.x = dest.x;
						m_targetPos.y = dest.y;


					}*/

					//m_player.pos -> dest 로 이동
					D3DXVECTOR2 temp;
					D3DXVec2Normalize(&temp, &(dest - m_pos));
					m_pos += temp * g_ETime * m_moveSpeed;


					//선형 보간 이동
					//D3DXVec2Lerp(&m_player.pos, &m_player.pos, &dest, g_ETime*4.0f);


					//거리가 가까워 지면 길벡터에서 끝을 빼준다.
					if (GetDistance(m_pos.x, m_pos.y, dest.x, dest.y) < 2.0f)
					{
						m_tile->SetUnit(astarWay.back().x, astarWay.back().y, this);
						astarWay.pop_back();
					}
				}
					
					
				}
				

			}

		}
		else
		{
			changeState(UTST_IDLE); 
			m_isWorkDoneMove = true;
		}
		break;

	case UTST_IDLE:

		

		break;

	case UTST_ATT:
		
		if (m_attackMotionFinish)
		{
			if (m_unitType == UTYP_MEDIC)
			{
				m_targetUnit->heal(m_attackDamage);
			}
			else if (!m_isHitAll && m_attackType == ATKTYPE_SPLASH)
			{
				m_targetUnit->dammagged(m_attackDamage, m_attackUpgrade);
				int idxX, idxY;
				PtinTile(idxX, idxY, m_tile->Getm_TileDesc(), m_targetUnit->Getm_pos());

				if (m_tile->returnInUnit(idxX + 1, idxY) != nullptr &&
					m_tile->returnInUnit(idxX + 1,idxY)->Getm_host() != m_host)
				{
					m_tile->returnInUnit(idxX + 1, idxY)->dammagged(m_attackDamage, m_attackUpgrade);
				}
				if (m_tile->returnInUnit(idxX - 1, idxY) != nullptr &&
					m_tile->returnInUnit(idxX - 1, idxY)->Getm_host() != m_host)
				{
					m_tile->returnInUnit(idxX - 1, idxY)->dammagged(m_attackDamage, m_attackUpgrade);
				}
				if (m_tile->returnInUnit(idxX, idxY + 1) != nullptr &&
					m_tile->returnInUnit(idxX, idxY + 1)->Getm_host() != m_host)
				{
					m_tile->returnInUnit(idxX, idxY + 1)->dammagged(m_attackDamage, m_attackUpgrade);
				}
				if (m_tile->returnInUnit(idxX, idxY - 1) != nullptr &&
					m_tile->returnInUnit(idxX, idxY - 1)->Getm_host() != m_host)
				{
					m_tile->returnInUnit(idxX, idxY - 1)->dammagged(m_attackDamage, m_attackUpgrade);
				}
			}
			else if (!m_isHitAll)
			{
				m_targetUnit->dammagged(m_attackDamage, m_attackUpgrade);
			}
			else if (m_isHitAll)
			{
				m_targetUnit->dammagged(m_attackDamage, m_attackUpgrade);


				for (int i = 0; i < m_rangeX; i++)
				{
					int idxX, idxY;
					PtinTile(idxX, idxY, m_tile->Getm_TileDesc(), m_pos);
					int tempX;
					if (m_host == 1)
					{
						tempX = m_targetX - idxX;
					}
					else
					{
						tempX = idxX - m_targetX;
					}
					
					int tempY = m_targetY - idxY;
					int tempRangeX = m_rangeX - abs(tempX);
					int tempRangeY = m_rangeY - abs(tempY);
					if (tempRangeX < 1 || tempRangeY < 1) break;
					if (m_host == 1)
					{
						idxX += tempX;
					}
					else
					{
						idxX -= tempX;
					}
					idxY += tempY;
					m_targetUnit = m_tile->CheckUnit(idxX, idxY, tempRangeX, tempRangeY, m_host, m_targetX, m_targetY);

					if (m_targetUnit != nullptr)
					{
						m_targetUnit->dammagged(m_attackDamage, m_attackUpgrade);
					}
				}
			
				//사거리내 적을 다시 검사해준다.
				//이미 검사한 유닛이 있는곳 다음부터 검사한다.
				//검사할 그 다음곳이 사거리를 벗어나면 반복문 그만
				//새로 검사해서 유닛을 찾아내면 타겟유닛으로 받아서 대미지 줌
			}
			m_attackMotionFinish = false;
			count++;
			m_Creload = m_reload;
		}
		if (count >= m_attackNumber)
		{
			m_isWorkDoneAct = true;
			changeState(UTST_IDLE);
			count = 0;
		}

		break;
	case UTST_DIE:
		if (m_deadMotionFinish)
		{
			m_isDead = true;
			m_isWorkDoneKill = true;
			PtinTile(idxx, idxy, m_tile->Getm_TileDesc(), m_pos);
			if (idxx < 0) idxx = 0;
			if (idxx >= m_tile->Getm_TileDesc().TileMaxX) idxx = m_tile->Getm_TileDesc().TileMaxX - 1;
			m_tile->RemoveUnit(idxx, idxy);
		}
		break;
	}


}

void Unit::move()
{
	if (m_unitState == UTST_MOVE) return;

	int idxx, idxy;

	//유닛이 있는 인덱스를 startX ,Y 로 두기위해 ptinTile 사용
	if (PtinTile(idxx, idxy, m_tile->Getm_TileDesc(), m_pos))
	{
		//길이 존재한다면 m_playerWay에 추가가 된다.
		if (m_tile->findTile(astarWay, idxx, idxy, m_dir, m_moveTile, m_isGoOver))
		{
			changeState(UTST_MOVE);
		}
		else if(m_isGoOver)
		{
			changeState(UTST_MOVE);
		}
		else
		{
			m_isWorkDoneMove = true;
		}
	}
}

void Unit::attack()
{

	if (m_unitState == UTST_ATT || m_isWorkDoneAct) return;

	
	
	if (m_Creload > 0)
	{
		m_Creload--;
		m_isWorkDoneAct = true;
		SOUNDMANAGER->play("ef_reload", g_masterVolume * g_extraVolume);

		return;
	}
	int idxX, idxY;
	PtinTile(idxX, idxY, m_tile->Getm_TileDesc(), m_pos);
	if (m_host == 1)
	{
		m_targetUnit = m_tile->CheckUnit(idxX + m_minRange, idxY, m_rangeX - m_minRange, m_rangeY, m_host, m_targetX, m_targetY);
	}
	else
	{
		m_targetUnit = m_tile->CheckUnit(idxX - m_minRange, idxY, m_rangeX - m_minRange, m_rangeY, m_host, m_targetX, m_targetY);
	}
	if (m_unitType == UTYP_MEDIC) m_targetUnit = m_tile->CheckAllyUnit(idxX, idxY, m_rangeX, m_rangeY, m_host);

	if (m_targetUnit != nullptr) changeState(UTST_ATT);
	else if (m_targetUnit == nullptr) m_isWorkDoneAct = true;




}

void Unit::killSelf()
{
	if (m_unitState == UTST_DIE) return;

	if (m_hp == 0)
	{
		changeState(UTST_DIE);
	}
	else
	{
		m_isWorkDoneKill = true;
	}
}

void Unit::dammagged(int dmg, int atkupg)
{
	//방어력을 계산하고 남은 들어올 데미지
	int temp = dmg + atkupg - m_defence;
	if (temp < 0) temp = 0;

	//쉴드가 있으면 쉴드에서 먼저 빼준다.
	if (m_shield > 0)
	{
		m_shield -= temp;

		//쉴드가 마이너스가 아니면 그대로 종료
		if (m_shield > 0)return;
		//뺀뒤에 쉴드가 마이너스이면 데미지가 그만큼 남았다는 소리니까
		m_hp += m_shield;
		m_shield = 0;
	}
	//쉴드가 없다면
	else
	{
		//그냥 들어올 데미지만큼 체력에서 빼준다.
		m_hp -= temp;
	}





	if (m_hp <= 0)
	{
		m_hp = 0;
		//changeState(UTST_DIE);
	}
}

void Unit::naturalShield()
{

	if (m_maxShield != 0)
	{
		m_shield++;
		if (m_shield > m_maxShield) m_shield = m_maxShield;
	}

}

void Unit::moveTileY(int idxX, int idxY, bool isCrush)
{
	//changeState(UTST_MOVE);
	m_idxx, m_idxy;
	//현재 내 타일검사
	PtinTile(m_idxx, m_idxy, m_tile->Getm_TileDesc(), m_pos);
	//이동전에 내 출발전 위치 유닛삭제
	m_tile->RemoveUnit(m_idxx, m_idxy);
	//만약 뭉개고 갈 유닛이 있다면
	if (isCrush)
	{
		//갈 타일 유닛의 포인터를 받아둔뒤
		Unit* tempUnit = m_tile->returnInUnit(m_idxx, idxY);
		//갈 타일에 유닛도 없애줌
		m_tile->RemoveUnit(m_idxx, idxY);
		tempUnit->changeState(UTST_DIE);
	}
	//내 현제 위치가 더 위면
	if (m_idxy > idxY)
	{
		//아래칸으로 가주고
		m_idxy -= 1;
	}
	else
	{
		//아니면 위칸으로 ㄱㄱ
		m_idxy += 1;
	}

	m_isMoveY = true;

	


}

void Unit::moveTileY2()
{

	D3DXVECTOR2 dest;
	dest.x = m_tile->Getm_TileDesc().ZeroStartPos.x +
		m_idxx * m_tile->Getm_TileDesc().TileSizeX;

	dest.y = m_tile->Getm_TileDesc().ZeroStartPos.y +
		m_idxy * m_tile->Getm_TileDesc().TileSizeY;

	//m_player.pos -> dest 로 이동
	D3DXVECTOR2 temp;
	D3DXVec2Normalize(&temp, &(dest - m_pos));
	m_pos += temp * g_ETime * m_moveSpeed;


	//거리가 가까워 지면 와일문 탈출
	if (GetDistance(m_pos.x, m_pos.y, dest.x, dest.y) < 2.0f)
	{
		m_tile->SetUnit(m_idxx, m_idxy, this);
		m_isMoveY = false;
		//changeState(UTST_IDLE);
	}

}

void Unit::steampack()
{
	SOUNDMANAGER->play("ef_steampack", g_masterVolume * g_extraVolume);
	m_hp -= 1;
	m_attackNumber += 1;
	m_moveTile += 1;
	if (m_Creload > 0) m_Creload -= 1;
}

void Unit::heal(int hp)
{
	m_hp += hp;
	if (m_hp > m_maxHp) m_hp = m_maxHp;
}

void Unit::yamato()
{
	//쉴드가 있으면 쉴드에서 먼저 빼준다.
	if (m_shield > 0)
	{
		m_shield -= 5;

		//쉴드가 마이너스가 아니면 그대로 종료
		if (m_shield > 0)return;
		//뺀뒤에 쉴드가 마이너스이면 데미지가 그만큼 남았다는 소리니까
		m_hp += m_shield;
		m_shield = 0;
	}
	//쉴드가 없다면
	else
	{
		//그냥 들어올 데미지만큼 체력에서 빼준다.
		m_hp -= 5;
	}


	SOUNDMANAGER->play("yamato", g_masterVolume * g_extraVolume);


	if (m_hp <= 0)
	{
		m_hp = 0;
		changeState(UTST_DIE);
		//changeState(UTST_DIE);
	}

}

void Unit::mindControl()
{
	if (m_host == 1)
	{
		m_host = 2;
		m_dir = DIR_W;
	}
	else if (m_host == 2)
	{
		m_host = 1;
		m_dir = DIR_E;
	}

}

void Unit::torasque()
{
	SOUNDMANAGER->play("torasque", g_masterVolume * g_extraVolume);
	m_Creload += 1;
}
