#include "stdafx.h"
#include "ImgSort.h"


ImgSort::ImgSort()
{
}


ImgSort::~ImgSort()
{
}

HRESULT ImgSort::init()
{

	//cout << "���� ��" << endl;
	for (int i = 0; i < 20; i++)
	{
		Num[i] = GetInt(100);
		//cout << Num[i] << endl;
	}

	sort(Num, Num + 20, cmp);

	//cout << "���� ��" << endl;
	for (int i = 0; i < 20; i++)
	{
		//cout << Num[i] << endl;
	}

	IMGMANAGER->AddImage("player", _T("�ϸ�.bmp"), 10, 2, "PS2");
	IMGMANAGER->AddImage("egg", _T("��.bmp"), "PS2");

	for (int i = 0; i < 10; i++)
	{
		Img[i].imgkey = "egg";
		Img[i].pos.y = GetInt(6) * 100.0f + 100.0f;	//100������ 100~700������
		Img[i].pos.x = 400.0f;
	}

	Img[0].imgkey = "player";
	Img[0].pos.y = 300.0f;
	Img[0].pos.x = 400.0f;


	return S_OK;
}

void ImgSort::release()
{
}

void ImgSort::update()
{
	int  player = 0;
	for (int i = 0; i < 10; i++)
	{
		//���� ��� ���Ұ� ����ֱ�

		Img[i].bottom = Img[i].pos.y - 50.0f;


		if (Img[i].imgkey == "player")
		{
			player = i;
			Img[i].bottom = Img[i].pos.y - 25.0f;
		}
	}

	if (KEYMANAGER->StayKeyDown(VK_LEFT))
	{
		Img[player].pos.x -= g_ETime * 160.0f;
	}
	if (KEYMANAGER->StayKeyDown(VK_RIGHT))
	{
		Img[player].pos.x += g_ETime * 160.0f;
	}
	if (KEYMANAGER->StayKeyDown(VK_UP))
	{
		Img[player].pos.y += g_ETime * 160.0f;
	}
	if (KEYMANAGER->StayKeyDown(VK_DOWN))
	{
		Img[player].pos.y -= g_ETime * 160.0f;
	}

}

void ImgSort::render()
{
	//����ü ����
	stable_sort(Img, Img + 10, cmp3);

	for (int i = 0; i < 10; i++)
	{
		Image* img = IMGMANAGER->GetImage(Img[i].imgkey);
		img->Scale(100.0f, 100.0f);
		img->Position(Img[i].pos);
		if (Img[i].imgkey == "player")
		{
			img->Scale(50.0f, 50.0f);
			img->PlayAnimation(ANI_LOOP, true, 0.4f);
		}
		else
		{
			img->Render();
		}
	}


}
