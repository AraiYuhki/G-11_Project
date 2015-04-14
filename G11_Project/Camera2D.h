//=============================================================================
// �J�����N���X
//Creater:Arai Yuhki
//=============================================================================
#ifndef _CAMERA2D_H_
#define _CAMERA2D_H_
//======================================================
// �C���N���[�h
//======================================================
#include "main.h"

class Shader2D;
//======================================================
//�J�����N���X
//======================================================
class CCamera2D
{
protected:
	static CCamera2D* Top;
	static CCamera2D* Cur;
	CCamera2D* Prev;
	CCamera2D* Next;
	virtual void Update(void);
	virtual void Set(void);
	void LinkList(void);
	void UnlinkList(void);
	void CreateViewPortMtx(D3DXMATRIX* pViewPort,UINT width,UINT height);

	static Shader2D* _Shader;
	D3DXVECTOR3 Pos;		//�J�����̈ʒu
	D3DXVECTOR3 DestPos;	//�ړ���?
	D3DXVECTOR3 Speed;			//���x
	D3DXVECTOR3 Rot;			//�p�x
	D3DXMATRIX Projection2D;		//�v���W�F�N�V�����}�g���N�X
	D3DVIEWPORT9 ViewPort;		//�r���[�|�[�g
	float ForcusDisXZ;			//XZ���W�̋���
	float ForcusDisXY;			//XY���W�̋���
	D3DXVECTOR3 ClickPos;
	static int CameraNum;		//���݂̃J������
	int frame;

public:
	CCamera2D(const D3DXVECTOR2 &LUPos = D3DXVECTOR2(0,0),D3DXVECTOR2 &size = D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT));//�R�X�g���N�^
	virtual ~CCamera2D();//�f�X�g���N�^
	static CCamera2D* Create(const D3DXVECTOR3 &PPos);//�쐬(���C���J�����p�A��������)
	static CCamera2D* Create(const D3DXVECTOR3 &PPos,const D3DXVECTOR2 &LUPos,D3DXVECTOR2 &size);//�쐬(�r���[�|�[�g�������ɐݒ�)
	static void UpdateAll(void);//�S���X�V
	/*
	DirectXDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	for(int cnt=0;cnt<CCamera::GetCameraNum();cnt++)
	{
	CCamera::Set(cnt);
	�`��
	}
	�ŕ`����B
	*/
	static void Set(int Index);//Index�Ԗڂ̃J�������g�p
	static void ReleaseAll(void);//�S�����
	void Destroy(void);			//�폜
	static void Clear(void);	//Top��Cur���N���A

	static int GetCameraNum(void)			{ return CameraNum; }//�J���������擾
	D3DXVECTOR3 GetPosP(void)const			{ return Pos; }//�J�����ʒu���擾
	D3DXVECTOR3 GetRot(void)const			{ return Rot; }
	D3DXVECTOR2 GetViewPortPos(void)const	{ return D3DXVECTOR2((float)ViewPort.X,(float)ViewPort.Y); }
	D3DXVECTOR2 GetViewPortSize(void)const	{ return D3DXVECTOR2((float)ViewPort.Width,(float)ViewPort.Height); }
	D3DXMATRIX Projection(void){ return Projection2D; }

	void SetPosP	(const D3DXVECTOR3 &pos)			{ Pos = pos; }
	void SetSpeed	(const D3DXVECTOR3 &speed)		{ Speed = speed; }
	void SetRot		(const D3DXVECTOR3 &rot)			{ Rot = rot; }
	void SetViewPortPos(const D3DXVECTOR2 &Pos)	{ ViewPort.X = (DWORD)Pos.x; ViewPort.Y = (DWORD)Pos.y; }
	void SetViewPortSize(const D3DXVECTOR2 &Size)	{ ViewPort.Width = (DWORD)Size.x;ViewPort.Height = (DWORD)Size.y; }
	static void SetShader(Shader2D* shader){_Shader = shader;}
	void AddPosP(const D3DXVECTOR3 &pos)			{ Pos += pos; }
	void AddRot	(const D3DXVECTOR3 &rot)			{ Rot += rot; }
	void AddViewPortPos(const D3DXVECTOR2 &Pos)	{ ViewPort.X += (DWORD)Pos.x; ViewPort.Y += (DWORD)Pos.y; }
	void AddViewPortSize(const D3DXVECTOR2 &Size)	{ ViewPort.Width += (DWORD)Size.x;ViewPort.Height += (DWORD)Size.y; }

	static CCamera2D* GetCamera(int Index);				//Index�Ԗڂ̃J�����̃|�C���^���擾

};

#endif