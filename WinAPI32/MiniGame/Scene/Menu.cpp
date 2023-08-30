#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

HRESULT Menu::init()
{
	m_exit.pos = D3DXVECTOR2(WINSIZEX / 2.0f + WINSIZEX / 4.0f, WINSIZEY / 2.0f - WINSIZEY / 4.0f);
	m_exit.size = D3DXVECTOR2(200.0f, 200.0f);
	m_exit.isTouch = false;
	m_exit.isClick = false;
	m_exit.frame = 0;
	m_exit.frameT = 0;
	m_exit.imageName = "bg_exit00";
	m_exit.frmaeTime = 0.0f;
	m_exit.frameDelay = 0.15f;

	m_exit.frame2 = 0;
	m_exit.frameT2 = 0;
	m_exit.imageName2 = "bg_exiton00";


	m_editor.pos = D3DXVECTOR2(WINSIZEX / 2.0f + WINSIZEX / 4.0f, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	m_editor.size = D3DXVECTOR2(200.0f, 200.0f);
	m_editor.isTouch = false;
	m_editor.isClick = false;
	m_editor.frame = 0;
	m_editor.frameT = 0;
	m_editor.imageName = "bg_editor00";
	m_editor.frmaeTime = 0.0f;
	m_editor.frameDelay = 0.15f;

	m_editor.frame2 = 0;
	m_editor.frameT2 = 0;
	m_editor.imageName2 = "bg_editoron00";


	m_multi.pos = D3DXVECTOR2(WINSIZEX / 2.0f - WINSIZEX / 4.0f, WINSIZEY / 2.0f - WINSIZEY / 4.0f);
	m_multi.size = D3DXVECTOR2(200.0f, 200.0f);
	m_multi.isTouch = false;
	m_multi.isClick = false;
	m_multi.frame = 0;
	m_multi.frameT = 0;
	m_multi.imageName = "bg_multi00";
	m_multi.frmaeTime = 0.0f;
	m_multi.frameDelay = 0.15f;

	m_multi.frame2 = 0;
	m_multi.frameT2 = 0;
	m_multi.imageName2 = "bg_multion00";


	m_single.pos = D3DXVECTOR2(WINSIZEX / 2.0f - WINSIZEX / 4.0f, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	m_single.size = D3DXVECTOR2(200.0f, 200.0f);
	m_single.isTouch = false;
	m_single.isClick = false;
	m_single.frame = 0;
	m_single.frameT = 0;
	m_single.imageName = "bg_single00";
	m_single.frmaeTime = 0.0f;
	m_single.frameDelay = 0.15f;

	m_single.frame2 = 0;
	m_single.frameT2 = 0;
	m_single.imageName2 = "bg_singleon00";



	return S_OK;
}

void Menu::release()
{
}

void Menu::update()
{
	frameMove();

	if (m_exit.isClick)
	{
		PostQuitMessage(0);
	}
	if (m_editor.isClick)
	{
		SCENEMANAGER->ChangeScene("TileMap");
	}
	if (m_single.isClick)
	{
		//SCENEMANAGER->ChangeScene("PlayGame");
		SCENEMANAGER->ChangeScene("Loading", PLAY_GAME);
	}
	if (m_multi.isClick)
	{
		SCENEMANAGER->ChangeScene("Loading", DECK);
	}


	if (KEYMANAGER->isKeyDown('X'))
	{
		m_exit.isClick = true;
	}
	if (KEYMANAGER->isKeyDown('S'))
	{
		m_single.isClick = true;
	}
	if (KEYMANAGER->isKeyDown('E'))
	{
		m_editor.isClick = true;
	}
	if (KEYMANAGER->isKeyDown('D'))
	{
		m_multi.isClick = true;
	}



	FRECT rc;
	rc = FRECT{ m_exit.pos.x - m_exit.size.x / 2.0f,
		m_exit.pos.y + m_exit.size.y / 2.0f,
		m_exit.pos.x + m_exit.size.x / 2.0f,
		 m_exit.pos.y - m_exit.size.y / 2.0f };

	if (PtInRect(rc, g_ptMouse))
	{
		m_exit.isTouch = true;
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_exit.isClick = true;
		}
	}
	else
	{
		m_exit.isTouch = false;
	}

	rc = FRECT{ m_editor.pos.x - m_editor.size.x / 2.0f,
		m_editor.pos.y + m_editor.size.y / 2.0f,
		m_editor.pos.x + m_editor.size.x / 2.0f,
		 m_editor.pos.y - m_editor.size.y / 2.0f };

	if (PtInRect(rc, g_ptMouse))
	{
		m_editor.isTouch = true;
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_editor.isClick = true;
		}
	}
	else
	{
		m_editor.isTouch = false;
	}

	rc = FRECT{ m_single.pos.x - m_single.size.x / 2.0f,
		m_single.pos.y + m_single.size.y / 2.0f,
		m_single.pos.x + m_single.size.x / 2.0f,
		 m_single.pos.y - m_single.size.y / 2.0f };

	if (PtInRect(rc, g_ptMouse))
	{
		m_single.isTouch = true;
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_single.isClick = true;
		}
	}
	else
	{
		m_single.isTouch = false;
	}


	rc = FRECT{ m_multi.pos.x - m_multi.size.x / 2.0f,
		m_multi.pos.y + m_multi.size.y / 2.0f,
		m_multi.pos.x + m_multi.size.x / 2.0f,
		 m_multi.pos.y - m_multi.size.y / 2.0f };

	if (PtInRect(rc, g_ptMouse))
	{
		m_multi.isTouch = true;
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_multi.isClick = true;
		}
	}
	else
	{
		m_multi.isTouch = false;
	}
}

void Menu::render()
{
	Image* bg = IMGMANAGER->GetImage("bg_menu");
	bg->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
	bg->Scale(WINSIZEX, WINSIZEY);

	bg->Render();

	bg = IMGMANAGER->GetImage("bg_exit00");
	bg = IMGMANAGER->GetImage(m_exit.imageName);
	bg->Position(m_exit.pos.x, m_exit.pos.y);
	bg->Scale(m_exit.size.x, m_exit.size.y);
	bg->Render();

	if (m_exit.isTouch)
	{
		bg = IMGMANAGER->GetImage(m_exit.imageName2);
		bg->Position(m_exit.pos.x + 30.0f, m_exit.pos.y);
		bg->Scale(m_exit.size.x, m_exit.size.y);
		bg->Render();
	}

	bg = IMGMANAGER->GetImage(m_editor.imageName);
	bg->Position(m_editor.pos.x, m_editor.pos.y);
	bg->Scale(m_editor.size.x, m_editor.size.y);
	bg->Render();

	if (m_editor.isTouch)
	{
		bg = IMGMANAGER->GetImage(m_editor.imageName2);
		bg->Position(m_editor.pos.x + 40.0f, m_editor.pos.y - 20.0f);
		bg->Scale(m_editor.size.x + 20.0f, m_editor.size.y);
		bg->Render();
	}

	bg = IMGMANAGER->GetImage(m_single.imageName);
	bg->Position(m_single.pos.x, m_single.pos.y);
	bg->Scale(m_single.size.x, m_single.size.y);
	bg->Render();

	if (m_single.isTouch)
	{
		bg = IMGMANAGER->GetImage(m_single.imageName2);
		bg->Position(m_single.pos.x, m_single.pos.y - 80.0f);
		bg->Scale(m_single.size.x, m_single.size.y);
		bg->Render();
	}

	bg = IMGMANAGER->GetImage(m_multi.imageName);
	bg->Position(m_multi.pos.x, m_multi.pos.y);
	bg->Scale(m_multi.size.x, m_multi.size.y);
	bg->Render();

	if (m_multi.isTouch)
	{
		bg = IMGMANAGER->GetImage(m_multi.imageName2);
		bg->Position(m_multi.pos.x + 30.0f, m_multi.pos.y);
		bg->Scale(m_multi.size.x, m_multi.size.y);
		bg->Render();
	}



	renderText();

}


void Menu::frameMove()
{
	if (m_exit.frmaeTime >= m_exit.frameDelay)
	{
		//프레임 시간을 빼준다.
		m_exit.frmaeTime -= m_exit.frameDelay;

		m_exit.frame++;


		if (m_exit.frame > 9)
		{
			m_exit.frame = 0;
			m_exit.frameT++;
		}
		if (m_exit.frameT > 4)
		{
			m_exit.frame = 0;
			m_exit.frameT = 0;
		}

		m_exit.frame2++;


		if (m_exit.frame2 > 9)
		{
			m_exit.frame2 = 0;
			m_exit.frameT2++;
		}
		if (m_exit.frameT2 > 2)
		{
			m_exit.frame2 = 0;
			m_exit.frameT2 = 0;
		}

	}
	else
	{
		m_exit.frmaeTime += g_ETime;
	}

	m_exit.imageName = "bg_exit" + to_string(m_exit.frameT) + to_string(m_exit.frame);

	m_exit.imageName2 = "bg_exiton" + to_string(m_exit.frameT2) + to_string(m_exit.frame2);



	if (m_editor.frmaeTime >= m_editor.frameDelay)
	{
		//프레임 시간을 빼준다.
		m_editor.frmaeTime -= m_editor.frameDelay;

		m_editor.frame++;


		if (m_editor.frame > 9)
		{
			m_editor.frame = 0;
			m_editor.frameT++;
		}
		if (m_editor.frameT > 7 && m_editor.frame > 4)
		{
			m_editor.frame = 0;
			m_editor.frameT = 0;
		}

		m_editor.frame2++;


		if (m_editor.frame2 > 9)
		{
			m_editor.frame2 = 0;
			m_editor.frameT2++;
		}
		if (m_editor.frameT2 > 1)
		{
			m_editor.frame2 = 0;
			m_editor.frameT2 = 0;
		}

	}
	else
	{
		m_editor.frmaeTime += g_ETime;
	}

	m_editor.imageName = "bg_editor" + to_string(m_editor.frameT) + to_string(m_editor.frame);

	m_editor.imageName2 = "bg_editoron" + to_string(m_editor.frameT2) + to_string(m_editor.frame2);


	if (m_single.frmaeTime >= m_single.frameDelay)
	{
		//프레임 시간을 빼준다.
		m_single.frmaeTime -= m_single.frameDelay;

		m_single.frame++;


		if (m_single.frame > 9)
		{
			m_single.frame = 0;
			m_single.frameT++;
		}
		if (m_single.frameT > 2 && m_single.frame > 4)
		{
			m_single.frame = 0;
			m_single.frameT = 0;
		}

		m_single.frame2++;


		if (m_single.frame2 > 9)
		{
			m_single.frame2 = 0;
			m_single.frameT2++;
		}
		if (m_single.frameT2 > 5)
		{
			m_single.frame2 = 0;
			m_single.frameT2 = 0;
		}

	}
	else
	{
		m_single.frmaeTime += g_ETime;
	}

	m_single.imageName = "bg_single" + to_string(m_single.frameT) + to_string(m_single.frame);

	m_single.imageName2 = "bg_singleon" + to_string(m_single.frameT2) + to_string(m_single.frame2);


	if (m_multi.frmaeTime >= m_multi.frameDelay)
	{
		//프레임 시간을 빼준다.
		m_multi.frmaeTime -= m_multi.frameDelay;

		m_multi.frame++;


		if (m_multi.frame > 9)
		{
			m_multi.frame = 0;
			m_multi.frameT++;
		}
		if (m_multi.frameT > 4)
		{
			m_multi.frame = 0;
			m_multi.frameT = 0;
		}

		m_multi.frame2++;


		if (m_multi.frame2 > 9)
		{
			m_multi.frame2 = 0;
			m_multi.frameT2++;
		}
		if (m_multi.frameT2 > 1)
		{
			m_multi.frame2 = 0;
			m_multi.frameT2 = 0;
		}

	}
	else
	{
		m_multi.frmaeTime += g_ETime;
	}

	m_multi.imageName = "bg_multi" + to_string(m_multi.frameT) + to_string(m_multi.frame);

	m_multi.imageName2 = "bg_multion" + to_string(m_multi.frameT2) + to_string(m_multi.frame2);

}

void Menu::renderText()
{

	//왼쪽위부터 항상 나오는 글씨들(single play)
	_tstring str = L"Single Player";

	RECT rect = { (long)(m_multi.pos.x - m_multi.size.x / 2.0f),
	(long)(m_multi.pos.y - m_multi.size.y / 2.0f),
	(long)(m_multi.pos.x + m_multi.size.x / 2.0f),
	(long)(m_multi.pos.y + m_multi.size.y / 2.0f) };
	WRITEMANAGER->RenderText(str, rect, 30, L"궁서체", D3DXCOLOR(0, 1, 0, 1));

	str = L"Editor";

	rect = { (long)(m_exit.pos.x - m_exit.size.x / 2.0f),
	(long)(m_exit.pos.y - m_exit.size.y / 2.0f),
	(long)(m_exit.pos.x + m_exit.size.x / 2.0f),
	(long)(m_exit.pos.y + m_exit.size.y / 2.0f) };
	WRITEMANAGER->RenderText(str, rect, 30, L"궁서체", D3DXCOLOR(0, 1, 0, 1));

	str = L"Card Deck";

	rect = { (long)(m_single.pos.x - m_single.size.x / 2.0f),
		(long)(m_single.pos.y - m_single.size.y / 2.0f),
		(long)(m_single.pos.x + m_single.size.x / 2.0f),
		(long)(m_single.pos.y + m_single.size.y / 2.0f) };
	WRITEMANAGER->RenderText(str, rect, 30, L"궁서체", D3DXCOLOR(0, 1, 0, 1));

	str = L"eXit";

	rect = { (long)(m_editor.pos.x - m_editor.size.x / 2.0f + 50.0f),
	(long)(m_editor.pos.y - m_editor.size.y / 2.0f),
	(long)(m_editor.pos.x + m_editor.size.x / 2.0f),
	(long)(m_editor.pos.y + m_editor.size.y / 2.0f) };
	WRITEMANAGER->RenderText(str, rect, 30, L"궁서체", D3DXCOLOR(0, 1, 0, 1));


	if (m_multi.isClick)
	{
		//cout << "클릭됨" << endl;

		//str = L"인터넷 환경이 불안정합니다.\n확인후 다시 시도해주십시오";
		str = L"X";

		rect = { (long)(m_single.pos.x - m_single.size.x / 2.0f + 50.0f),
			(long)(m_single.pos.y - m_single.size.y / 2.0f),
			(long)(m_single.pos.x + m_single.size.x),
			(long)(m_single.pos.y + m_single.size.y / 2.0f) };
		WRITEMANAGER->RenderText(str, rect, 200, L"궁서체", D3DXCOLOR(1, 0, 0, 1));


	}

	if (m_editor.isClick)
	{
		//cout << "클릭됨" << endl;

		//str = L"인터넷 환경이 불안정합니다.\n확인후 다시 시도해주십시오";
		str = L"X";

		rect = { (long)(m_exit.pos.x - m_exit.size.x / 2.0f + 50.0f),
			(long)(m_exit.pos.y - m_exit.size.y / 2.0f),
			(long)(m_exit.pos.x + m_exit.size.x),
			(long)(m_exit.pos.y + m_exit.size.y / 2.0f) };
		WRITEMANAGER->RenderText(str, rect, 200, L"궁서체", D3DXCOLOR(1, 0, 0, 1));


	}

}
