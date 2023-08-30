#pragma once
#include "GameNode.h"
//������,���ؽ� �˻��ؼ� �� �����ϼ���
#include <thread>
#include <mutex>

static mutex mtx;

class Loading : public GameNode
{
private:



public:
	Loading();
	~Loading()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void unitImage();
	void heroImage();

	//							i��ŸƮ i��    i�ִ�  j�ִ�        �̹��� Ű��
	static void funcLoadMenu(int a, int b, int e, int f, string imgKey)
	{
		//Loading* loading;
		D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
		//Rect* Rc = IMGMANAGER->Getrect();
		progressBar* Rc = IMGMANAGER->Getprogress();
		Rc->Position(0.0f, 50.0f);
		Rc->Color(1.0f, 0.0f, 0.0f);


		Image* bg = IMGMANAGER->GetImage("bg_loading");
		bg->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		bg->Scale(WINSIZEX, WINSIZEY);

		string str1;
		_tstring str2;

		if (imgKey == "bg_exit")
		{
			str2 = _T("starcraft/background/exit/exit");
		}
		else if (imgKey == "bg_editor")
		{
			str2 = _T("starcraft/background/editor/editor");
		}
		else if (imgKey == "bg_single")
		{
			str2 = _T("starcraft/background/singlePlayer/single");
		}
		else if (imgKey == "bg_multi")
		{
			str2 = _T("starcraft/background/multiPlayer/multi");
		}
		else if (imgKey == "bg_exiton")
		{
			str2 = _T("starcraft/background/exit/exiton");
		}
		else if (imgKey == "bg_editoron")
		{
			str2 = _T("starcraft/background/editor/editoron");
		}
		else if (imgKey == "bg_singleon")
		{
			str2 = _T("starcraft/background/singlePlayer/singleon");
		}
		else if (imgKey == "bg_multion")
		{
			str2 = _T("starcraft/background/multiPlayer/multion");
		}

		for (int i = a; i < b; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if ((i >= e && j > f) || i > e)break;
				_tstring temp;
				//�̹��� �߰�
				str1 = imgKey + to_string(i) + to_string(j);
				temp = str2 + to_wstring(i) + to_wstring(j) + _T(".png");

				IMGMANAGER->AddImage(str1, temp, "PS4");

				LoadingNum++;
				if (LoadingNum % 5 == 0)
				{
					//���ؽ� �� ȣ��ÿ� �ٸ������尡 ���۵Ǵ°��� �ƴ�
					//������� ȣ��ɶ����� ��ٷȴٰ� �ٸ������尡 ����
					mtx.lock();
					CAMMANAGER->SetBuffers();
					DeviceContext->ClearRenderTargetView(RTV, (float *)background);
					bg->Render();
					Rc->Scale(((float)LoadingNum / 250.0f) * 1300.0f, 30.0f);
					Rc->Render();
					SwapChain->Present(0, 0);
					mtx.unlock();
				}


			}





		}

		//SAFE_DELETE(bg);
		//SAFE_DELETE(Rc);

	}


	//							 �̹��� Ű��
	static void funcLoadPlayGame(string imgKey)
	{
		//Loading* loading;
		D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
		//Rect* Rc = IMGMANAGER->Getrect();
		progressBar* Rc = IMGMANAGER->Getprogress();
		Rc->Position(0.0f, 50.0f);
		Rc->Color(1.0f, 0.0f, 0.0f);


		Image* bg = IMGMANAGER->GetImage("bg_mapSelect");
		bg->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		bg->Scale(WINSIZEX, WINSIZEY);

		string str1;
		_tstring str2;

		if (imgKey == "marine")
		{
			str2 = _T("starcraft/unit/marine/marine");
		}

		for (int i = 0; i < 4; i++)
		{
			_tstring temp;
			//�̹��� �߰�
			if (i == 0)
			{
				str1 = imgKey + "Idle";
			}
			else if (i == 1)
			{
				str1 = imgKey + "Move";
			}
			/*str1 = imgKey + to_string(i) + to_string(j);
			temp = str2 + to_wstring(i) + to_wstring(j) + _T(".png");*/

			IMGMANAGER->AddImage(str1, temp, "PS4");

			LoadingNum++;
			if (LoadingNum % 5 == 0)
			{
				//���ؽ� �� ȣ��ÿ� �ٸ������尡 ���۵Ǵ°��� �ƴ�
				//������� ȣ��ɶ����� ��ٷȴٰ� �ٸ������尡 ����
				mtx.lock();
				CAMMANAGER->SetBuffers();
				DeviceContext->ClearRenderTargetView(RTV, (float *)background);
				bg->Render();
				Rc->Scale(((float)LoadingNum / 500.0f) * 800.0f, 30.0f);
				Rc->Render();
				SwapChain->Present(0, 0);
				mtx.unlock();
			}








		}

		//SAFE_DELETE(bg);
		//SAFE_DELETE(Rc);

	}

};

