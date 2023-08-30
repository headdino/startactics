#pragma once
#include "GameNode.h"
#include <algorithm>

struct ST_IMAGE
{
	string imgkey;
	D3DXVECTOR2 pos;
	float bottom;
	//scale

};

class ImgSort :public GameNode
{
private:

	int Num[20];

	ST_IMAGE Img[10];

public:
	ImgSort();
	~ImgSort()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

static bool cmp(int& a, int& b)
{
	//내림차순 정령
	if (a > b)return true;
	else return false;
}

static bool cmp2(const ST_IMAGE& a,const ST_IMAGE& b)
{
	//내림차순 정령
	if (a.pos.y > b.pos.y)return true;
	else return false;
}

static bool cmp3(const ST_IMAGE& a, const ST_IMAGE& b)
{
	//내림차순 정령
	if (a.bottom > b.bottom)return true;
	else return false;
}

