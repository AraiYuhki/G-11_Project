#include "Polygon.h"
#include "Renderer.h"
#include "Shader3D.h"

CPolygon* CPolygon::_Top = nullptr;
CPolygon* CPolygon::_Cur = nullptr;
int CPolygon::CPolygon3DNum = 0;
int CPolygon::CPolygon3DMax = 0;
bool CPolygon::PauseFlag = false;
Shader3D* CPolygon::_Shader = nullptr;


CPolygon::CPolygon()
{
	_Pos = D3DXVECTOR3(0,0,0);
	_Scl = D3DXVECTOR3(0,0,0);
	_Speed = D3DXVECTOR3(0,0,0);
	_Rot = D3DXVECTOR3(0,0,0);
	_Scl = D3DXVECTOR3(0,0,0);
	LinkList();
}
CPolygon::~CPolygon()
{
	CPolygon3DNum--;
}
//=============================================================================
//���炩���ߗp�ӂ���|���S�����̐ݒ�(�l�p�x�[�X)
//=============================================================================
HRESULT CPolygon::Init(void)
{
	return S_OK;
}

void CPolygon::Uninit(void)
{
	ReleaseAll();
	
}

void CPolygon::Release(void)
{
	UnlinkList();
	_Pos = D3DXVECTOR3(0,0,0);
	_Scl = D3DXVECTOR3(0,0,0);
	_Speed = D3DXVECTOR3(0,0,0);
	_Rot = D3DXVECTOR3(0,0,0);
	_Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	delete this;
}

void CPolygon::ReleaseAll(void)
{
	CPolygon* Polygon = _Top;
	CPolygon* Next = NULL;
	while(Polygon)
	{
		Next = Polygon->_Next;
		Polygon->Release();
		Polygon = Next;
	}
}

//=============================================================================
//���g�����X�g�ɒǉ�
//=============================================================================
void CPolygon::LinkList(void)
{
	if(_Top != NULL)//��ڈȍ~�̏���
	{
		CPolygon* CPolygon = _Cur;
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
	CPolygon3DNum++;
}
//=============================================================================
//���g�����X�g����폜
//=============================================================================
void CPolygon::UnlinkList(void)
{
	if(_Prev == NULL)//�擪
	{
		if(_Next != NULL)//��������
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
	else if(_Next == NULL)//�I�[
	{
		if(_Prev != NULL)//�O������
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

}
//=============================================================================
//�쐬
//	D3DXVECTOR3 pos	�쐬�ʒu(�|���S���̒��S)
//	D3DXVECTOR3 size �傫��(xz�̂݉e��)
//	D3DXVECTOR3 rot �X��	���W�A���l
//	D3DXCOLOR	color �|���S���̐F
//�m�ۍς݂̃o�b�t�@���z���Ȃ���΍쐬����A���ꂽ�|���S���̃|�C���^���Ԃ�
//�I�[�o�[�����ꍇ��NULL���Ԃ�
//=============================================================================
CPolygon* CPolygon::Create(const D3DXVECTOR3 &pos,const D3DXVECTOR2 &size,const D3DXCOLOR &color,const D3DXVECTOR3 &rot)
{

	CPolygon* Polygon = new CPolygon;

	Polygon->_Pos = pos;
	Polygon->_Rot = rot;
	Polygon->_Color = color;
	Polygon->_Scl = D3DXVECTOR3(size.x,size.y,100.0f);
	Polygon->uv.x	= 0.0f;
	Polygon->uv.y	= 0.0f;
	Polygon->uv.z	= 1.0f;
	Polygon->uv.w	= 1.0f;
	Polygon->Texture = GetTexture(TEX_NONE);


	return Polygon;
}
//=============================================================================
//�X�V
//=============================================================================
void CPolygon::Update(void)
{

}
void CPolygon::Pause(void)
{

}
//=============================================================================
//�S�čX�V
//=============================================================================
void CPolygon::UpdateAll(void)
{
	CPolygon* Polygon = _Top;
	CPolygon* Next = NULL;
	
	while(Polygon)
	{
		Next = Polygon->_Next;
		if(PauseFlag)
		{
			Polygon->Pause();
		}
		else
		{
			Polygon->Update();
		}
		Polygon = Next;
		
	}
	
}
//=============================================================================
//�`��
//=============================================================================
void CPolygon::Draw(void)
{
	D3DXMATRIX MtxScl,MtxRot,MtxTrans;

	_Shader->SetFloatArray(Shader3D::SIZE,_Scl,3);
	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&MtxRot,_Rot.y,_Rot.x,_Rot.z);
	_Shader->SetMatrix(Shader3D::ROT_MTX,MtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&MtxTrans,_Pos.x,_Pos.y,_Pos.z);
	_Shader->SetMatrix(Shader3D::POS_MTX,MtxTrans);
	_Shader->SetFloatArray(Shader3D::DIFFUSE,_Color,4);
	_Shader->SetFloatArray(Shader3D::UV,uv,4);
	//���[���h�}�g���b�N�X�̓K�p
	_Shader->SetTexture(Texture);

	_Shader->Draw(Shader3D::NORMAL,D3DPT_TRIANGLESTRIP);
}
//=============================================================================
//�S�ĕ`��
//=============================================================================
void CPolygon::DrawAll(void)
{
	CPolygon* Polygon = _Top;
	CPolygon* Next = NULL;
	if (_Shader == nullptr){ _Shader = Shader3D::Instance(); }

	_Shader->DrawBegin();
	while(Polygon)
	{
		Next = Polygon->_Next;
		Polygon->Draw();
		Polygon = Next;
		
	}
	_Shader->DrawEnd();
}
//=============================================================================
//Index�Ԗڂ̃|���S���̃|�C���^���擾����
//=============================================================================
CPolygon* CPolygon::GetCPolygon3D(int Index)
{
	CPolygon* Polygon = _Top;
	CPolygon* Next = NULL;
	int num=0;
	while(Polygon)
	{
		Next = Polygon->_Next;
		if(num==Index)
		{
			return Polygon;
		}
		Polygon = Next;
		num++;
	}
	return NULL;
}

//=============================================================================
//UV�l�̐ݒ�
//	UNum	�����牽�Ԗڂ��H
//	VNum	�ォ�牽�Ԗڂ��H
//	DivideUNum	���̕�����(�Œ�1)
//	DivideVNum	�c�̕�����(�Œ�1);
//=============================================================================
void CPolygon::SetUV(int UNum,int VNum,int DivideUNum,int DivideVNum)
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
