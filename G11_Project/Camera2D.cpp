//======================================================
//�J�����N���X
//Creater:Arai Yuhki
//======================================================
//======================================================
//�C���N���[�h
//======================================================
#include "Camera2D.h"
#include "Renderer.h"
#include "Shader2D.h"
#define CAMERA_SPEED (2.0f)
//======================================================
//�O���[�o���ϐ�
//======================================================
int CCamera2D::CameraNum = 0;
CCamera2D* CCamera2D::Top = NULL;
CCamera2D* CCamera2D::Cur = NULL;
Shader2D* CCamera2D::_Shader = nullptr;
//======================================================
//�R���X�g���N�^
//�����FLUPos �`��J�n�_(����̍��W)
//		Size (�`�悷��傫��)
//======================================================
CCamera2D::CCamera2D(const D3DXVECTOR2 &LUPos,D3DXVECTOR2 &size)
{
	if (size.x <0)
	{
		size.x *= -1;
	}
	if (size.y<0)
	{
		size.y *= -1;
	}
	ViewPort.X = (DWORD)LUPos.x;
	ViewPort.Y = (DWORD)LUPos.y;
	ViewPort.Width = (DWORD)size.x;
	ViewPort.Height = (DWORD)size.y;
	ViewPort.MaxZ = 1.0f;
	ViewPort.MinZ = 0.0f;

	CameraNum++;

	LinkList();

}
//======================================================
//�f�X�g���N�^
//======================================================
CCamera2D::~CCamera2D()
{
	CameraNum--;
}
//=============================================================================
//���g�����X�g�ɒǉ�
//=============================================================================
void CCamera2D::LinkList(void)
{
	if (Top != NULL)//��ڈȍ~�̏���
	{
		CCamera2D* pCamera = Cur;
		pCamera->Next = this;
		Prev = pCamera;
		Next = NULL;
		Cur = this;
	}
	else//�ŏ��̈�̎��̏���
	{
		Top = this;
		Cur = this;
		Prev = NULL;
		Next = NULL;
	}
}

//=============================================================================
//���g�����X�g����폜
//=============================================================================
void CCamera2D::UnlinkList(void)
{
	if (Prev == NULL)//�擪
	{
		if (Next != NULL)//��������
		{
			Next->Prev = NULL;
			Top = Next;
		}
		else//�Ō�̈������
		{
			Top = NULL;
			Cur = NULL;
		}
	}
	else if (Next == NULL)//�I�[
	{
		if (Prev != NULL)//�O������
		{
			Prev->Next = NULL;
			Cur = Prev;
		}
		else//�Ō�̈������
		{
			Top = NULL;
			Cur = NULL;
		}
	}
	else//�O��Ƀf�[�^������Ƃ�
	{
		Prev->Next = Next;
		Next->Prev = Prev;
	}

	Prev = NULL;
	Next = NULL;
}

//=============================================================================
//�S����
//=============================================================================
void CCamera2D::ReleaseAll(void)
{
	CCamera2D* pCamera = Top;
	CCamera2D* CameraNext;
	while (pCamera)
	{
		CameraNext = pCamera->Next;
		delete pCamera;
		pCamera = CameraNext;
	}
	CCamera2D::Clear();

}
//=============================================================================
//�擪�ƏI�[��NULL��
//=============================================================================
void CCamera2D::Clear(void)
{
	Top = NULL;
	Cur = NULL;
}

//=============================================================================
//���E�֐�
//=============================================================================
void CCamera2D::Destroy(void)
{
	UnlinkList();


	Pos = D3DXVECTOR3(0,0,0);
	Rot = D3DXVECTOR3(0,0,0);
	ForcusDisXZ = 1;
	ForcusDisXY = 1;
	delete this;

}
//=============================================================================
//�쐬
//=============================================================================
CCamera2D* CCamera2D::Create(const D3DXVECTOR3 &PPos)
{
	CCamera2D* pCamera = NULL;
	pCamera = new CCamera2D();
	pCamera->Pos = PPos;
	pCamera->DestPos = PPos;
	pCamera->Projection2D = D3DXMATRIX(
		2.0f / SCREEN_WIDTH,0,0,0,
		0,-2.0f / SCREEN_HEIGHT,0,0,
		0,0,1.0f,0,
		-1.0f,1.0f,0,1.0f);
	return pCamera;
}
//=============================================================================
//�쐬(�r���[�|�[�g���ݒ�)
//=============================================================================
CCamera2D* CCamera2D::Create(const D3DXVECTOR3 &PPos,const D3DXVECTOR2 &LUPos,D3DXVECTOR2 &size)
{
	CCamera2D* pCamera = NULL;
	pCamera = new CCamera2D(LUPos,size);
	pCamera->Pos = PPos;
	pCamera->DestPos = PPos;
	pCamera->Speed.x = 0;
	pCamera->Speed.y = 0;
	pCamera->Speed.z = 0;
	pCamera->Projection2D = D3DXMATRIX(
		2.0f / SCREEN_WIDTH,0,0,0,
		0,-2.0f / SCREEN_HEIGHT,0,0,
		0,0,1.0f,0,
		-1.0f,1.0f,0,1.0f);
	return pCamera;
}
//======================================================
//�X�V
//======================================================
void CCamera2D::Update(void)
{
}
//======================================================
//�K�p
//======================================================
void CCamera2D::Set(void)
{
	
	if (_Shader == nullptr){ _Shader = Shader2D::Instance(); }

	Projection2D._41 = -1.0f - Pos.x / (SCREEN_WIDTH*2.0f);
	Projection2D._42 = 1.0f - Pos.y / (SCREEN_HEIGHT*2.0f);
	
	_Shader->SetMatrix(Shader2D::PROJECTION,Projection2D);
}
//======================================================
//�S���X�V
//======================================================
void CCamera2D::UpdateAll(void)
{
	CCamera2D* pCamera = Top;
	CCamera2D* Next = NULL;
	while (pCamera)
	{
		Next = pCamera->Next;
		pCamera->Update();
		pCamera = Next;
	}
}
//======================================================
//Index�Ԗڂ̃J������K�p
//======================================================
void CCamera2D::Set(int Index)
{

	if (Index < CameraNum && Index >= 0)
	{

		CCamera2D* pCamera = Top;
		CCamera2D* Next = NULL;
		int num = 0;
		while (pCamera)
		{
			Next = pCamera->Next;
			if (num == Index)
			{
				pCamera->Set();
				break;
			}
			num++;
			pCamera = Next;
		}
	}
}
//======================================================
//Index�Ԗڂ̃J�����̃|�C���^���擾
//======================================================
CCamera2D* CCamera2D::GetCamera(int Index)
{
	CCamera2D* pCamera = Top;
	CCamera2D* Next = NULL;
	int num = 0;
	while (pCamera)
	{
		Next = pCamera->Next;
		if (Index == num)
		{
			return pCamera;
		}
		num++;
		pCamera = Next;
	}
	return NULL;
}
