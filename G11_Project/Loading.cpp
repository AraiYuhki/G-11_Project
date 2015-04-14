#include "Loading.h"
#include "Mutex.h"
#include "Renderer.h"
#include "Shader2D.h"
#include "Camera2D.h"

Loading* Loading::Self = new Loading;
ScreenRender* Loading::_ScreenRender = nullptr;

Loading::Loading()
{
	Texture = nullptr;
}

Loading::~Loading()
{

}

void Loading::Init(void)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	if (FAILED(D3DXCreateTextureFromFile(Device,"data/texture/LoadGear.png",&Texture)))
	{
		MessageBox(NULL,"���[�h��ʂ̃e�N�X�`���̐����Ɏ��s���܂���","ERROR",MB_OK | MB_ICONERROR);
		return ;
	}

	_Pos[0].x = SCREEN_WIDTH - 200.0f;
	_Pos[0].y = SCREEN_HEIGHT - 200.0f;
	_Pos[1].x = SCREEN_WIDTH - 100.0f;
	_Pos[1].y = SCREEN_HEIGHT - 100.0f;

	_Pos[0].z = _Pos[1].z = 0;

	_Size[0] = D3DXVECTOR3(200.0f,200.0f,1.0f);
	_Size[1] = _Size[0] * 0.8f;
	_Rot[0] = 0;
	_Rot[1] = DEG2RAD(15.0f);
	mutex = Mutex::Instance();
}

void Loading::Uninit(void)
{
	SafeRelease(Texture);
}

void Loading::Finalize(void)
{
	Self->Uninit();

	SafeDelete(Self);
}

void Loading::Update(void)
{
	if (_ScreenRender != nullptr)
	{
		LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
		CCamera2D::Set(0);
		Shader2D* shader = Shader2D::Instance();
		CastMatrix();
		CRenderer::SetStream2D();

		_Rot[0] += DEG2RAD(0.1f);
		_Rot[1] -= DEG2RAD(0.1f);
		mutex->Enter();

		if (SUCCEEDED(Device->BeginScene()))	//�`��J�n
		{
			Device->Clear(0L,nullptr,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0x0,1.0f,0L);
			shader->SetTexture(Texture);
			shader->SetFloatArray(Shader2D::UV,D3DXVECTOR4(0,0,1.0f,1.0f),4);
			shader->SetFloatArray(Shader2D::DIFFUSE,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),4);
			shader->DrawBegin();
			for (int cnt = 0;cnt < 2;cnt++)
			{
				shader->SetMatrix(Shader2D::WORLD_MTX,WorldMatrix[cnt]);
				shader->Draw(Shader2D::NORMAL,D3DPT_TRIANGLESTRIP);
			}
			shader->DrawEnd();
			//ScreenRender->RenderWindow(Texture);
			Device->EndScene();
		}
		Device->Present(NULL,NULL,NULL,NULL);
		mutex->Leave();
	}
}

void Loading::SetRenderer(ScreenRender* sr)
{
	_ScreenRender = sr;
}

void Loading::CastMatrix(void)
{
	Shader2D* shader = Shader2D::Instance();
	WorldMatrix[0] = WorldMatrix[1] = shader->Identity();
	D3DXMATRIX SclMtx,RotMtx,TransMtx;

	for (int cnt = 0;cnt < 2;cnt++)
	{
		D3DXMatrixScaling(&SclMtx,_Size[cnt].x,_Size[cnt].y,_Size[cnt].z);
		D3DXMatrixRotationYawPitchRoll(&RotMtx,0,0,_Rot[cnt]);
		D3DXMatrixTranslation(&TransMtx,_Pos[cnt].x,_Pos[cnt].y,_Pos[cnt].z);
		D3DXMatrixMultiply(&WorldMatrix[cnt],&WorldMatrix[cnt],&SclMtx);
		D3DXMatrixMultiply(&WorldMatrix[cnt],&WorldMatrix[cnt],&RotMtx);
		D3DXMatrixMultiply(&WorldMatrix[cnt],&WorldMatrix[cnt],&TransMtx);
		
	}
}