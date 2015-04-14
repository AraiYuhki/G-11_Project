//=============================================================================
//�C���N���[�h
//=============================================================================
#include "ShimmerParticle2D.h"
#include "Renderer.h"
#include "Shader2D.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
int ShimmerParticle2D::_Num = 0;
ShimmerParticle2D* ShimmerParticle2D::_Top = NULL;
ShimmerParticle2D* ShimmerParticle2D::_Cur = NULL;
bool ShimmerParticle2D::PauseFlag = false;
Shader2D* ShimmerParticle2D::_Shader = nullptr;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
ShimmerParticle2D::ShimmerParticle2D(void)
{

	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	//�o�b�t�@�̍쐬

	//�X�e�[�^�X�̏�����
	_Pos = D3DXVECTOR3(0,0,0);
	_Size = D3DXVECTOR3(1.0f,1.0f,1.0f);
	_Speed = D3DXVECTOR3(0,0,0);
	_Rot = D3DXVECTOR3(0,0,0);
	uv = D3DXVECTOR4(0,0,1.0f,1.0f);
	Texture = GetTexture(TEX_NONE);
	ReleaseFlag = false;
	frame = 0;
	_Num++;
	LinkList();
}
//=============================================================================
//���g�����X�g�ɒǉ�
//=============================================================================
void ShimmerParticle2D::LinkList(void)
{
	if (_Top != NULL)//��ڈȍ~�̏���
	{
		ShimmerParticle2D* CPolygon = _Cur;
		CPolygon->_Next = this;
		_Prev = CPolygon;
		_Next = NULL;
		_Cur = this;
	}
	else//�ŏ��̈�̎��̏���
	{
		_Top = this;
		_Cur = this;
		_Prev = NULL;
		_Next = NULL;
	}
}
//=============================================================================
//���g�����X�g����폜
//=============================================================================
void ShimmerParticle2D::UnlinkList(void)
{
	if (_Prev == NULL)//�擪
	{
		if (_Next != NULL)//��������
		{
			_Next->_Prev = NULL;
			_Top = _Next;
		}
		else//�Ō�̈������
		{
			_Top = NULL;
			_Cur = NULL;
		}
	}
	else if (_Next == NULL)//�I�[
	{
		if (_Prev != NULL)//�O������
		{
			_Prev->_Next = NULL;
			_Cur = _Prev;
		}
		else//�Ō�̈������
		{
			_Top = NULL;
			_Cur = NULL;
		}
	}
	else//�O��Ƀf�[�^������Ƃ�
	{
		_Prev->_Next = _Next;
		_Next->_Prev = _Prev;
	}

	_Prev = NULL;
	_Next = NULL;
	_Num--;
}
//=============================================================================
//���E�֐�
//=============================================================================
void ShimmerParticle2D::Release(void)
{
	UnlinkList();
	_Pos = D3DXVECTOR3(0,0,0);
	_Size = D3DXVECTOR3(0,0,0);
	_Speed = D3DXVECTOR3(0,0,0);
	_Rot = D3DXVECTOR3(0,0,0);
	frame = 0;

	delete this;

}
//=============================================================================
//�S����
//=============================================================================
void ShimmerParticle2D::ReleaseAll(void)
{
	ShimmerParticle2D* CPolygon = _Top;
	ShimmerParticle2D* CPolygonNext;
	while (CPolygon)
	{
		CPolygonNext = CPolygon->_Next;
		CPolygon->Release();
		CPolygon = CPolygonNext;
	}
	ShimmerParticle2D::Clear();

}
//=============================================================================
//�擪�ƏI�[��NULL��
//=============================================================================
void ShimmerParticle2D::Clear(void)
{
	_Top = nullptr;
	_Cur = nullptr;
}

//=============================================================================
//�|���S�����쐬
//=============================================================================
ShimmerParticle2D* ShimmerParticle2D::Create(const D3DXVECTOR3 &pos,const D3DXVECTOR2 &size,const D3DXCOLOR &color)
{
	ShimmerParticle2D* CPolygon = new ShimmerParticle2D;
	CPolygon->_Pos = pos;
	CPolygon->_Size = D3DXVECTOR3(size.x,size.y,0);
	CPolygon->_Color = color;

	return CPolygon;
}
//=============================================================================
//�X�V
//=============================================================================
void ShimmerParticle2D::Update(void)
{
	if (ReleaseFlag)
	{
		Release();
		return;
	}

	_Pos += _Speed;

}
//=============================================================================
//�|�[�Y����
//=============================================================================
void ShimmerParticle2D::Pause(void)
{
	if (ReleaseFlag)
	{
		Release();
		return;
	}

}
//=============================================================================
//�S�̍X�V
//=============================================================================
void ShimmerParticle2D::UpdateAll(void)
{
	ShimmerParticle2D* CPolygon = _Top;
	ShimmerParticle2D* Next = NULL;
	while (CPolygon)
	{
		Next = CPolygon->_Next;
		if (PauseFlag)
		{
			CPolygon->Pause();
		}
		else
		{
			CPolygon->Update();
		}

		CPolygon = Next;
	}
}
//=============================================================================
//�|���S����`��
//=============================================================================
void ShimmerParticle2D::Draw(void)
{
	if (_Color.a > 0.01f)
	{
		D3DXMATRIX MtxScl,MtxRot,MtxTrans;
		WorldMtx = _Shader->Identity();


		D3DXMatrixScaling(&MtxScl,_Size.x,_Size.y,_Size.z);
		D3DXMatrixMultiply(&WorldMtx,&WorldMtx,&MtxScl);
		//��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&MtxRot,_Rot.y,_Rot.x,_Rot.z);
		D3DXMatrixMultiply(&WorldMtx,&WorldMtx,&MtxRot);


		//�ʒu�𔽉f
		D3DXMatrixTranslation(&MtxTrans,_Pos.x,_Pos.y,_Pos.z);
		D3DXMatrixMultiply(&WorldMtx,&WorldMtx,&MtxTrans);

		_Shader->SetMatrix(Shader2D::WORLD_MTX,WorldMtx);
		/*
		_Shader->SetFloatArray(Shader2D::SIZE,_Size,3);
		_Shader->SetMatrix(Shader2D::ROT_MTX,MtxRot);
		_Shader->SetMatrix(Shader2D::POS_MTX,MtxTrans);
		*/

		_Shader->SetFloatArray(Shader2D::DIFFUSE,_Color,4);
		_Shader->SetFloatArray(Shader2D::UV,uv,4);
		//�e�N�X�`���̐ݒ�
		_Shader->SetTexture(Texture);

		//�|���S����`��
		_Shader->Draw(Shader2D::ADD,D3DPT_TRIANGLESTRIP);
	}
}
//=============================================================================
//���݂��Ă�|���S�������ׂĕ`��
//=============================================================================
void ShimmerParticle2D::DrawAll(void)
{
	if (_Shader == nullptr){ _Shader = Shader2D::Instance(); }

	ShimmerParticle2D* CPolygon = _Top;

	_Shader->DrawBegin();
	while (CPolygon)
	{
		CPolygon->Draw();
		CPolygon = CPolygon->_Next;
	}

	_Shader->DrawEnd();
}

void ShimmerParticle2D::SetSpeed(const float base,float radian)
{
	_Speed.x = Sin_Rad(-radian)*base;
	_Speed.y = Cos_Rad(-radian)*base;
}

//=============================================================================
//UV�l�̐ݒ�
//	UNum	�����牽�Ԗڂ��H
//	VNum	�ォ�牽�Ԗڂ��H
//	DivideUNum	���̕�����(�Œ�1)
//	DivideVNum	�c�̕�����(�Œ�1);
//=============================================================================
void ShimmerParticle2D::SetUV(int UNum,int VNum,int DivideUNum,int DivideVNum)
{
	//�[���f�B�o�C�h�h�~
	if (DivideUNum == 0)
	{
		DivideUNum = 1;
	}
	if (DivideVNum == 0)
	{
		DivideVNum = 1;
	}
	float DivideU = 1.0f / DivideUNum;
	float DivideV = 1.0f / DivideVNum;

	uv.x = DivideU*UNum;
	uv.y = DivideV*VNum;
	uv.z = DivideU;
	uv.w = DivideV;
}
