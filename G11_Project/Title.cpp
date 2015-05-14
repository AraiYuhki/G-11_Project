//
//Title.cpp
//

#include "Title.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Manager.h"
#include "Shader2D.h"
#include "Input/Keyboard.h"

void Title::Init(void)
{
	Window* window = Window::Instance();

	//�w�i
	Sprite* Bg = Sprite::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f,0), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), WHITE(1.0f), Sprite::LAYER_4);
	Bg->SetTexture(GetTexture(TEX_BG));

	//�_�ŗp���S
	Sprite* Logo = Sprite::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f,0), D3DXVECTOR2(100.0f, 100.0f), WHITE(1.0f), Sprite::LAYER_4);
	Logo->SetTexture(GetTexture(TEX_EFFECT_GEAR));
	m_logo = Logo;
	flahing = 0;
	add_flahing_num = 0.01f;

}

void Title::Uninit(void)
{
	CManager::ReleaseObject();
}

void Title::Update(void)
{
	//�L�[����p�i�m�F�e�X�g�j
	Keyboard *key = Keyboard::Instance();
	
	/*�_�ŏ����i���j*/
	if (flahing > 1.0f || flahing < 0)
	{
		add_flahing_num = -add_flahing_num;
	}
	flahing += add_flahing_num;
	m_logo->SetColor(WHITE(flahing));
	//�����܂�

	//�L�[����p�i�m�F�e�X�g�F���g�Ȃ��j
	if (key->Trigger(DIK_L))
	{
	
	}
}

void Title::Draw(void)
{


}
