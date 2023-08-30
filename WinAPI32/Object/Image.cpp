#include "stdafx.h"
#include "Image.h"

Image::Image(_tstring file, string ps): parent(nullptr)
{
	ZeroMemory(&angle, sizeof(angle));
	ZeroMemory(&angle2, sizeof(angle));
	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//uv좌표는 0~1값
	vertices[0].Uv = D3DXVECTOR2(0.0f, 1.0f);
	vertices[1].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[2].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[4].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[5].Uv = D3DXVECTOR2(1.0f, 0.0f);

	HRESULT hr;
	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	//Create ColorBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(ColorBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = Device->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}

	//CreateBlendState
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		//0번은 알파값처리 끄기
		desc.RenderTarget[0].BlendEnable = false;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Device->CreateBlendState(&desc, &blendState[0]);
		//1번은 알파값처리 켜기
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Device->CreateBlendState(&desc, &blendState[1]);
	}



	shader = new Shader(_T("./Object/Image.hlsl"),"VS", ps);
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 2);

	_tstring textureFile = _T("./images/") + file;
	//텍스쳐(이미지파일)을 읽어서 srv에 저장
	
	D3DX11CreateShaderResourceViewFromFile
	(
		Device,//디바이스
		textureFile.c_str(),//파일 이름
		NULL,//추가적인 이미지정보 (NULL이면 원본크기)
		NULL,//널값
		&srv,//저장할 쉐이더 자원
		&hr
	);
	assert(SUCCEEDED(hr)&&"이미지생성실패");
}

Image::Image(_tstring file, UINT MaxFrameX, UINT MaxFrameY, string ps)
	:parent(nullptr)
{
	ZeroMemory(&angle, sizeof(angle));
	ZeroMemory(&angle2, sizeof(angle));
	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//uv 좌표는 왼쪽상단이 0,0 최대값은 1이다
	vertices[0].Uv = D3DXVECTOR2(0.0f, 1.0f);
	vertices[1].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[2].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[4].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[5].Uv = D3DXVECTOR2(1.0f, 0.0f);


	HRESULT hr;

	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create ColorBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(ColorBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = Device->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}



	//CreateBlendState
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.RenderTarget[0].BlendEnable = false;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Device->CreateBlendState(&desc, &blendState[0]);

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Device->CreateBlendState(&desc, &blendState[1]);
	}


	//프레임uv 버퍼 세팅
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(FrameUvBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = Device->CreateBuffer(&desc, NULL, &FrameUvBuffer);
		assert(SUCCEEDED(hr));
	}
	maxFrameX = MaxFrameX;
	maxFrameY = MaxFrameY;

	shader = new Shader(_T("./Object/image.hlsl"), "VS2", ps);
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 2);


	_tstring textureFile = _T("./images/") + file;
	//텍스쳐(이미지파일)을 읽어서 srv에 저장
	D3DX11CreateShaderResourceViewFromFile
	(
		Device,//디바이스
		textureFile.c_str(),//파일이름
		NULL, //추가적인 이미지 정보 NULL값은 원본크기
		NULL,//널값
		&srv,//쉐이더자원
		&hr
	);
	assert(SUCCEEDED(hr));


}


Image::~Image()
{
	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(FrameUvBuffer);
	SAFE_RELEASE(colorBuffer);
	SAFE_RELEASE(blendState[0]);
	SAFE_RELEASE(blendState[1]);
}

void Image::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Image::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Image::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Image::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}


void Image::Rotate(D3DXVECTOR3 x)
{
	angle = x;
}
void Image::Rotate(float x, float y, float z)
{
	Rotate(D3DXVECTOR3(x, y, z));
}
void Image::Rotate2(D3DXVECTOR3 x)
{
	angle2 = x;
}
void Image::Rotate2(float x, float y, float z)
{
	Rotate2(D3DXVECTOR3(x, y, z));
}

void Image::Update()
{
	D3DXMATRIX S, R, T, W, R2;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixRotationYawPitchRoll(&R, angle.y,angle.x, angle.z);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	D3DXMatrixRotationYawPitchRoll(&R2, angle2.y, angle2.x, angle2.z);

	W = S * R * T*R2;
	RT = R * T*R2;
	
	if (parent)
	{
		W *= *parent;
		RT *= *parent;
	}
	shader->World(W);
}

void Image::Render()
{
	Update();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	shader->SetBuffers();

	//색상 값
	DeviceContext->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DeviceContext->PSSetConstantBuffers(0, 1, &colorBuffer);

	//프레임이 있는 이미지 라면
	if (maxFrameX != 1 || maxFrameY != 1)
	{
		FrameUvBufferData.FrameUv.x = 1.0f / maxFrameX * CurrentFrameX;
		FrameUvBufferData.FrameUv.y = 1.0f / maxFrameY * CurrentFrameY;
		FrameUvBufferData.FrameUv.z = 1.0f / maxFrameX * (CurrentFrameX + 1);
		FrameUvBufferData.FrameUv.w = 1.0f / maxFrameY * (CurrentFrameY + 1);
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
	}




	//픽셀셰이더에 쉐이더 자원값 세팅
	DeviceContext->PSSetShaderResources(0,//스타트 슬롯
		1,//리소스갯수
		&srv);//쉐이더 자원

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//알파블렌드 켜기
	DeviceContext->OMSetBlendState(blendState[1], NULL, 0xFF);
	DeviceContext->Draw(VertexCount, 0);
	//알파블렌드 끄기
	DeviceContext->OMSetBlendState(blendState[0], NULL, 0xFF);
}

void Image::LoofRender(float x, float y)
{
	// 이미지 좌표값 벗어나지않게 값을 잡아주기
	if (x > 1.0f) x -= floorf(x);
	if (y > 1.0f) y -= floorf(y);
	if (x < 0.0f)
	{
		//-부호 떼기
		x = fabs(x);
		//          소수점앞 버리기
		x = 1.0f - (x - floorf(x));
	}
	if (y < 0.0f)
	{
		//-부호 떼기
		y = fabs(y);
		//          소수점앞 버리기
		y = 1.0f - (y - floorf(y));
	}

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	//처음 사이즈, 처음 위치값을 저장해놓는다
	D3DXVECTOR2 tempSize = scale;
	D3DXVECTOR2 tempPos = position;

	//색상 값
	DeviceContext->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DeviceContext->PSSetConstantBuffers(0, 1, &colorBuffer);


	//알파블렌드 켜기
	DeviceContext->OMSetBlendState(blendState[1], NULL, 0xFF);

	//픽셀셰이더에 쉐이더 자원값 세팅
	DeviceContext->PSSetShaderResources(0,//스타트 슬롯
		1,//리소스갯수
		&srv);//쉐이더 자원

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//왼 상단 이미지
	//이미지 좌표 세팅
	FrameUvBufferData.FrameUv.x = x;
	FrameUvBufferData.FrameUv.y = y;
	FrameUvBufferData.FrameUv.z = 1.0f;
	FrameUvBufferData.FrameUv.w = 1.0f;
	DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
	DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
	//스케일 포지션 잡아주기
	scale.x = tempSize.x *(1.0f - x);
	scale.y = tempSize.y *(1.0f - y);
	position.x = position.x - (tempSize.x - scale.x)*0.5f;
	position.y = position.y + (tempSize.y - scale.y)*0.5f;
	//월드 재갱신
	Update();
	shader->SetBuffers();
	//그런다음 그리기
	DeviceContext->Draw(VertexCount, 0);

	//원래 값으로 돌려주기
	scale = tempSize;
	position = tempPos;

	//오른 상단이미지
	if (x != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = 0.0f;
		FrameUvBufferData.FrameUv.y = y;
		FrameUvBufferData.FrameUv.z = x;
		FrameUvBufferData.FrameUv.w = 1.0f;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		//스케일 포지션 잡아주기
		scale.x = tempSize.x *x;
		scale.y = tempSize.y *(1.0f - y);
		position.x = position.x + (tempSize.x - scale.x)*0.5f;
		position.y = position.y + (tempSize.y - scale.y)*0.5f;
		//월드 재갱신
		Update();
		shader->SetBuffers();
		//그런다음 그리기
		DeviceContext->Draw(VertexCount, 0);

		//원래 값으로 돌려주기
		scale = tempSize;
		position = tempPos;
	}

	//왼 하단이미지
	if (y != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = x;
		FrameUvBufferData.FrameUv.y = 0.0f;
		FrameUvBufferData.FrameUv.z = 1.0f;
		FrameUvBufferData.FrameUv.w = y;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		//스케일 포지션 잡아주기
		scale.x = tempSize.x *(1.0f - x);
		scale.y = tempSize.y *y;
		position.x = position.x - (tempSize.x - scale.x)*0.5f;
		position.y = position.y - (tempSize.y - scale.y)*0.5f;
		//월드 재갱신
		Update();
		shader->SetBuffers();
		//그런다음 그리기
		DeviceContext->Draw(VertexCount, 0);

		//원래 값으로 돌려주기
		scale = tempSize;
		position = tempPos;
	}


	//오른 하단이미지
	if (x != 0.0f && y != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = 0.0f;
		FrameUvBufferData.FrameUv.y = 0.0f;
		FrameUvBufferData.FrameUv.z = x;
		FrameUvBufferData.FrameUv.w = y;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		//스케일 포지션 잡아주기
		scale.x = tempSize.x *x;
		scale.y = tempSize.y *y;
		position.x = position.x + (tempSize.x - scale.x)*0.5f;
		position.y = position.y - (tempSize.y - scale.y)*0.5f;
		//월드 재갱신
		Update();
		shader->SetBuffers();
		//그런다음 그리기
		DeviceContext->Draw(VertexCount, 0);

		//원래 값으로 돌려주기
		scale = tempSize;
		position = tempPos;
	}
	
	
	




	
	




	//알파블렌드 끄기
	DeviceContext->OMSetBlendState(blendState[0], NULL, 0xFF);


}

void Image::PlayAnimation(PlayState ps, bool isFrameX, float nexttime)
{
	//시간 증가
	time += g_ETime;
	if (time >= nexttime)
	{
		//다음 프레임경과 시간을 빼준다
		time -= nexttime;
		//x가 증가하는 이미지라면
		if (isFrameX)
		{
			switch (ps)
			{
				//정방향 루프
			case ANI_LOOP:
				if (maxFrameX - 1 > CurrentFrameX)
					CurrentFrameX++;
				else
					CurrentFrameX = 0;
				break;
				//역방향 루프
			case ANI_REVERSE:
				if(CurrentFrameX >0)
					CurrentFrameX--;
				else
					CurrentFrameX = maxFrameX - 1;
				break;
			}
		}
		//y가 증가하는 이미지 라면
		else
		{
			switch (ps)
			{
				//정방향 루프
			case ANI_LOOP:
				if (maxFrameY - 1 > CurrentFrameY)
					CurrentFrameY++;
				else
					CurrentFrameY = 0;
				break;
				//역방향 루프
			case ANI_REVERSE:
				if (CurrentFrameY > 0)
					CurrentFrameY--;
				else
					CurrentFrameY = maxFrameY - 1;
				break;
			}
		}


	}
	Render();

}

void Image::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Image::Color(D3DXCOLOR vec)
{
	colorBufferData.Color = vec;
}
