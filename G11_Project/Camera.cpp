//======================================================
//�J�����N���X
//Creater:Arai Yuhki
//======================================================
//======================================================
//�C���N���[�h
//======================================================
#include "Camera.h"
#include "Renderer.h"
#include "Shader3D.h"
#define CAMERA_SPEED (2.0f)
//======================================================
//�O���[�o���ϐ�
//======================================================
int CCamera::CameraNum = 0;
CCamera* CCamera::Top = NULL;
CCamera* CCamera::Cur = NULL;

//======================================================
//�R���X�g���N�^
//�����FLUPos �`��J�n�_(����̍��W)
//		Size (�`�悷��傫��)
//======================================================
CCamera::CCamera(const D3DXVECTOR2 &LUPos,D3DXVECTOR2 &size)
{
	if(size.x <0)
	{
		size.x *= -1;
	}
	if(size.y<0)
	{
		size.y *= -1;
	}
	ViewPort.X = (DWORD)LUPos.x;
	ViewPort.Y = (DWORD)LUPos.y;
	ViewPort.Width = (DWORD)size.x;
	ViewPort.Height = (DWORD)size.y;
	ViewPort.MaxZ = 1.0f;
	ViewPort.MinZ = 0.0f;
	_Size = Window::Instance()->WindowSize();
	CameraNum++;
	
	LinkList();

}
//======================================================
//�f�X�g���N�^
//======================================================
CCamera::~CCamera()
{
	CameraNum--;
}
//=============================================================================
//���g�����X�g�ɒǉ�
//=============================================================================
void CCamera::LinkList(void)
{
	if(Top != NULL)//��ڈȍ~�̏���
	{
		CCamera* pCamera = Cur;
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
void CCamera::UnlinkList(void)
{
	if(Prev == NULL)//�擪
	{
		if(Next != NULL)//��������
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
	else if(Next == NULL)//�I�[
	{
		if(Prev != NULL)//�O������
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
void CCamera::ReleaseAll(void)
{
	CCamera* pCamera = Top;
	CCamera* CameraNext;
	while(pCamera)
	{
		CameraNext = pCamera->Next;
		delete pCamera;
		pCamera = CameraNext;
	}
	CCamera::Clear();
	
}
//=============================================================================
//�擪�ƏI�[��NULL��
//=============================================================================
void CCamera::Clear(void)
{
	Top = NULL;
	Cur = NULL;
}

//=============================================================================
//���E�֐�
//=============================================================================
void CCamera::Destroy(void)
{
	UnlinkList();
	
	
	PosCameraP = D3DXVECTOR3(0,0,0);
	PosCameraR = D3DXVECTOR3(0,0,0);
	VecCameraU = D3DXVECTOR3(0,0,0);
	Rot = D3DXVECTOR3(0,0,0);
	ForcusDisXZ = 1;
	ForcusDisXY = 1;
	delete this;

}
//=============================================================================
//�쐬
//=============================================================================
CCamera* CCamera::Create(const D3DXVECTOR3 &PPos,const D3DXVECTOR3 &RPos)
{
	CCamera* pCamera = NULL;
	pCamera = new CCamera();
	pCamera->PosCameraP = PPos;
	pCamera->DestPosCameraP = PPos;
	pCamera->PosCameraR = RPos;
	pCamera->VecCameraU = D3DXVECTOR3(0,1.0f,0);
	D3DXVECTOR3 dis = D3DXVECTOR3((PPos.x-RPos.x),(PPos.y-RPos.y),(PPos.z-RPos.z));
	pCamera->ForcusDisXZ = sqrtf(dis.x*dis.x+dis.z*dis.z);
	pCamera->ForcusDisXZ = sqrtf(dis.x*dis.x+dis.y*dis.y);
	pCamera->Rot.y = atan2(dis.x,dis.z);
	pCamera->Rot.x = atan2(dis.x,dis.y);

	return pCamera;
}
//=============================================================================
//�쐬(�r���[�|�[�g���ݒ�)
//=============================================================================
CCamera* CCamera::Create(const D3DXVECTOR3 &PPos,const D3DXVECTOR3 &RPos,const D3DXVECTOR2 &LUPos,D3DXVECTOR2 &size)
{
	CCamera* pCamera = NULL;
	pCamera = new CCamera(LUPos,size);
	pCamera->PosCameraP = PPos;
	pCamera->PosCameraR = RPos;
	pCamera->DestPosCameraP = PPos;
	pCamera->VecCameraU = D3DXVECTOR3(0,1.0f,0);
	D3DXVECTOR3 dis = D3DXVECTOR3((PPos.x-RPos.x),(PPos.y-RPos.y),(PPos.z-RPos.z));
	pCamera->ForcusDisXZ = sqrtf(dis.x*dis.x+dis.z*dis.z);
	pCamera->ForcusDisXZ = sqrtf(dis.x*dis.x+dis.y*dis.y);
	pCamera->Rot.y = atan2(dis.x,dis.z);
	pCamera->Rot.x = atan2(dis.x,dis.y);
	pCamera->Speed.x = 0;
	pCamera->Speed.y = 0;
	pCamera->Speed.z = 0;
	return pCamera;
}
//======================================================
//�X�V
//======================================================
void CCamera::Update(void)
{
}
//======================================================
//�K�p
//======================================================
void CCamera::Set(void)
{
	Shader3D* shader = Shader3D::Instance();
	

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ViewMatrix);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&ViewMatrix,&PosCameraP,&PosCameraR,&VecCameraU);
	shader->SetMatrix(Shader3D::VIEW_MTX,ViewMatrix);
	D3DXMATRIX Inverce;
	D3DXMatrixIdentity(&Inverce);
	D3DXMatrixInverse(&Inverce,NULL,&ViewMatrix);
	Inverce._41 = 0;
	Inverce._42 = 0;
	Inverce._43 = 0;
	shader->SetMatrix(Shader3D::INV_VIEW_MTX,Inverce);
	
	D3DXMATRIX view;

	//�v���W�F�N�V�����̏�����
	D3DXMatrixIdentity(&Projection);
	//�v���W�F�N�V�����̍쐬
	D3DXMatrixPerspectiveFovLH(&Projection,(45.0f*(D3DX_PI/180.0f)),//����p
													_Size.x/_Size.y,	//�A�X�y�N�g��
													10.0f,		//���E���E�ŒZ����
													3000.0f);	//���E���E�Œ�����


	shader->SetMatrix(Shader3D::PROJECTION,Projection);

}
//======================================================
//�S���X�V
//======================================================
void CCamera::UpdateAll(void)
{
	CCamera* pCamera = Top;
	CCamera* Next = NULL;
	while(pCamera)
	{
		Next = pCamera->Next;
		pCamera->Update();
		pCamera = Next;
	}
}
//======================================================
//Index�Ԗڂ̃J������K�p
//======================================================
void CCamera::Set(int Index)
{
	
	if(Index < CameraNum && Index >= 0)
	{
		
		CCamera* pCamera = Top;
		CCamera* Next = NULL;
		int num=0;
		while(pCamera)
		{
			Next = pCamera->Next;
			if(num == Index)
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
CCamera* CCamera::GetCamera(int Index)
{
	CCamera* pCamera = Top;
	CCamera* Next = NULL;
	int num=0;
	while(pCamera)
	{
		Next = pCamera->Next;
		if(Index == num)
		{
			return pCamera;
		}
		num++;
		pCamera = Next;
	}
	return NULL;
}

void CCamera::CreateViewPortMtx(D3DXMATRIX* pViewPort,const UINT width,const UINT height)
{
	float Width = (float)width / 2;
	float Height = (float)height / 2;
	pViewPort->_11 = Width;	pViewPort->_12 = 0.0f;		pViewPort->_13 = 0.0f;	pViewPort->_14 = 0.0f;
	pViewPort->_21 = 0.0f;	pViewPort->_22 = -Height;	pViewPort->_23 = 0.0f;	pViewPort->_24 = 0.0f;
	pViewPort->_31 = 0.0f;	pViewPort->_32 = 0.0f;		pViewPort->_33 = 1.0f;	pViewPort->_34 = 0.0f;
	pViewPort->_41 = Width;	pViewPort->_42 = Height;	pViewPort->_43 = 0.0f;	pViewPort->_44 = 1.0f;

}