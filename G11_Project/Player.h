//================================================================================
//	�v���C���[�N���X
//	Author:Tsukagoshi Toshiyuki
//================================================================================
#pragma once 

//================================================================================
//	include
//================================================================================
#include "Sprite.h"

//================================================================================
//	�v���C���[�N���X
//================================================================================
class Player :public Sprite
{
public:
	typedef enum
	{
		PLAYER_STATE_STOP = 0,		//�������ĂȂ�
		PLAYER_STATE_MOVE,		//�ړ�
		PLAYER_STATE_EAT,		//�H�ׂ�
		PLAYER_STATE_GLAD,		//���
		PLAYER_STATE_MAX,
		PLAYER_SATAE_NON,
	}PLAYER_STATE;

	static Player* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXCOLOR &color, int priority = 0);

	Player(int priority = 0);
	~Player(){}

	void Update();
	void Draw();

	void SetState(PLAYER_STATE State);
	PLAYER_STATE State(){ return _State; }

private:
	PLAYER_STATE _State;
	PLAYER_STATE OldState;

	float AnimationCount;			//�A�j���[�V�����p�J�E���^�[
	short AnimationPartition[PLAYER_STATE_MAX];	//�A�j���[�V����������
	float AnimationSpeed[PLAYER_STATE_MAX];		//�A�j���[�V�����X�s�[�h
	int   MaxPartition;				//�A�j���[�V���������̍ő�l

	float SwayCount;				//�㉺�ɗh���p�J�E���^�[

};

