//================================================================================
//	�v���C���[�N���X
//	Author:Tsukagoshi Toshiyuki
//================================================================================

//================================================================================
//	include
//================================================================================
#include "Player.h"
#include "Shader2D.h"
#include "Texture.h"
#include "Input\VC.h"
#include "Item.h"
#include "Interface.h"

//================================================================================
//	�萔
//================================================================================
//�ړ��X�s�[�h
#define PLAYER_SPEED		(0.5f)

//�����̌�����
#define PLAYER_INERTIA		(0.95f)


//================================================================================
//	�R���X�g���N�^
//================================================================================
Player::Player(int Priority) :Eatan(Priority)
{

}

//================================================================================
//	�v���C���[����
//================================================================================
Player* Player::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXCOLOR &color, int priority)
{
	Player* player = new Player(priority);
	player->_Pos = pos;
	player->_Size = D3DXVECTOR3(size.x, size.y, 0);
	player->_Color = color;

	player->SetTexture(GetTexture(TEX_EATAN));
	player->SetSwayFlag(true);
	player->SetState(EATAN_STATE_STOP);

	return player;
}

//================================================================================
//	�X�V����
//================================================================================
void Player::Update()
{
	VC* vc = VC::Instance();

	//****************************************
	//	�ړ�
	//****************************************
	_Speed += D3DXVECTOR3(vc->LStickX(), vc->LStickY(), 0.0f) * PLAYER_SPEED;
	_Speed *= PLAYER_INERTIA;
		
	//****************************************
	//	�U��
	//****************************************
	if (vc->Trigger(COMMAND_B))
	{
		SetState(EATAN_STATE_ATTACK);
	}

	//****************************************
	//	�H�ׂ�
	//****************************************
	if (vc->Trigger(COMMAND_A))
	{
		SetState(EATAN_STATE_EAT);

	}

	//�H�ׂ锻��
	if (_State == EATAN_STATE_EAT)
	{
		//�����J���؂����Ƃ�
		if (AnimationCount >= AnimationPartition[EATAN_STATE_EAT] / 2.0f)
		{
			//�����蔻��
			Item* item = Item::HitCheck(_Pos, _Size);
			if ( item != nullptr )
			{
				float score = item->Score();
				Interface::AddScore(score);
				item->SetRelease();
			}
		}
	}

	

	Eatan::Update();
}

//================================================================================
//	�`�揈��
//================================================================================
void Player::Draw()
{

	Eatan::Draw();
}