#pragma once
#include "SingletonBase.h"


class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*>				ImgMap;//맵으로 만든 이미지 목록
	typedef map<string, Image*>::iterator	ImgIter;//맵으로 만든 이미지 목록의 반복자

	ImgMap m_ImgMap;
	Rect* rect;
	Circle* circle;
	progressBar* progress;

public:


	Image* AddImage(string strKey, _tstring file, string ps = "PS");
	Image* AddImage(string strKey, _tstring file, UINT MaxFrameX, UINT MaxFrameY, string ps = "PS");

	//이미지 키값으로 찾기
	Image* GetImage(string strkey);
	//이미지 키값으로 삭제
	bool DeleteImage(string strKey);
	//전부 삭제
	void DeleteAll();

	//일반렌더
	void Render(string strKey);
	void LoofRender(string strKey, float x = 0.0f, float y = 0.0f);

	//애니메이션
	void PlayAnimation(string strKey, PlayState ps, bool isFrameX, float nexttime);



	ImageManager() { rect = new Rect(); circle = new Circle(4); progress = new progressBar(); };
	~ImageManager() { SAFE_DELETE(rect) SAFE_DELETE(circle) };

	//렉트랑 서클도 이미지 매니저가 하나씩 들고있다.
	void RectRender() { rect->Render(); }
	void CircleRender() { circle->Render(); }
	void ProgressRender() { progress->Render(); }

	MAKEGET(Rect*, rect);
	MAKEGET(Circle*, circle);
	MAKEGET(progressBar*, progress);


};

