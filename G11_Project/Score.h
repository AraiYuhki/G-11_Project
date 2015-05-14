//=============================================================================
//�X�R�A�N���X
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "Polygon.h"

//=============================================================================
//�O���錾
//=============================================================================
class CNumber;

//�N���X��`
class CScore
{
public:
	static CScore* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,int CountPlace,bool camma = true);
	void SetNum(int Num){TargetScore = Num;}
	void SetCurrentNum(int num){ TargetScore = CurrentScore = num; }
	void AddNum(int Num){TargetScore += Num;}

	void SetPos(D3DXVECTOR3 pos){ Pos = DestPos = pos; }
	void SetDestPos(const D3DXVECTOR3& pos,float frame){DestPos = pos;MoveFrame = frame;}
	void SetMoveFrame(float frame){MoveFrame = frame;}
	void SetSize(D3DXVECTOR2 size);
	void SetColor(D3DXCOLOR color);

	void AddPos(D3DXVECTOR3 pos){ Pos += pos;DestPos = Pos; }
	void AddDestPos(const D3DXVECTOR3& pos){DestPos += pos;}
	void AddSize(D3DXVECTOR2 size);
	void AddColor(D3DXCOLOR color);

	D3DXVECTOR3 GetPos(void){ return Pos; }
	D3DXCOLOR GetColor(void){ return Color; }
	unsigned long GetNum(void){ return CurrentScore; }
	void Update(void);
	void Release(void);

private:
	int CountPlace;//����
	unsigned long CurrentScore;//���ݒl
	unsigned long TargetScore;//���̒l��ڎw���đ�������
	unsigned long MaxScore;//�\���\�ȍő�l
	float MoveFrame;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 DestPos;
	D3DXVECTOR2 Size;
	D3DXCOLOR Color;
	CNumber* Number[20];
};

#endif