#include "Light.h"

Light* Light::Top=NULL;
Light* Light::Cur=NULL;
int Light::LightNum = 0;
//=============================================================================
//���g�����X�g�ɒǉ�
//=============================================================================
void Light::LinkList(void)
{
	if(Top != NULL)//��ڈȍ~�̏���
	{
		Light* pLight = Cur;
		pLight->Next = this;
		Prev = pLight;
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
void Light::UnlinkList(void)
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
//���ׂč폜
//=============================================================================
void Light::ReleaseAll(void)
{
	Light* pLight = Top;
	Light* Next = NULL;
	while(pLight)
	{
		Next = pLight->Next;
		delete pLight;
		
		pLight = Next;
	}
}
//=============================================================================
//���g���폜
//=============================================================================
void Light::Release(int index)
{
	Light* pLight = Top;
	Light* Next = NULL;
	int num=0;
	while(pLight)
	{
		Next = pLight->Next;
		if(num == index)
		{
			AllOff();//��x�S�Ẵ��C�g������
			pLight->UnlinkList();
			pLight->Vector = D3DXVECTOR3(0,0,0);
			pLight->Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pLight->Reset();//�Đݒ肷��
			delete pLight;
			
			break;
		}
		num++;
		pLight = Next;
	}
	
}
//=============================================================================
//�w�������C�g���쐬
//����: Vec �����x�N�g��
//		Color �F
//Create�����͍쐬�������C�g�̃|�C���^���Ԃ��Ă���
//=============================================================================
Light* Light::CreateDirectional(D3DXVECTOR3 Vec,D3DXCOLOR color)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = new Light;

	ZeroMemory(&pLight->_Light,sizeof(D3DLIGHT9));

	pLight->_Light.Type = D3DLIGHT_DIRECTIONAL;
	pLight->_Light.Diffuse = color;
	pLight->Vector = Vec;

	D3DXVec3Normalize((D3DXVECTOR3*)&pLight->_Light.Direction,&pLight->Vector);
	Device->SetLight(LightNum,&pLight->_Light);
	Device->LightEnable(LightNum,TRUE);
	LightNum++;

	return pLight;
}
//=============================================================================
//�|�C���g���C�g���쐬(�X�y�L�����ƃA���r�G���g���f�B�t���[�Y�Ɠ����ɂ���)
//����:	D3DXVECTOR3	Pos		�����ʒu
//		float		Range	�e���͈�
//		float		Attenuation	�����W��	(0.0f�`1.0f 1,0f�Ō����Ȃ�)
//		D3DXCOLOR	diffuse		 �F
//=============================================================================
Light* Light::CreatePoint(D3DXVECTOR3 Pos,float Range,float Attenuation,D3DXCOLOR diffuse)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = new Light;

	ZeroMemory(&pLight->_Light,sizeof(D3DLIGHT9));

	pLight->_Light.Type = D3DLIGHT_POINT;
	pLight->_Light.Diffuse = diffuse;
	pLight->_Light.Ambient = diffuse;
	pLight->_Light.Specular = diffuse;
	pLight->_Light.Position = Pos;
	pLight->_Light.Range = Range;
	pLight->_Light.Attenuation0 = Attenuation;//��팸���W��
	pLight->_Light.Attenuation1 = 0.0f;		//���`�����W��	AttenuationN�͑g�ݍ��킹����ł��낢��ω�����炵��
	pLight->_Light.Attenuation2 = 0.0f;		//���������W��

	D3DXVec3Normalize((D3DXVECTOR3*)&pLight->_Light.Direction,&pLight->Vector);
	Device->SetLight(LightNum,&pLight->_Light);
	Device->LightEnable(LightNum,TRUE);
	LightNum++;

	return pLight;
}
//=============================================================================
//�|�C���g���C�g���쐬(�X�y�L�����ƃA���r�G���g��ʌɐݒ肷��)
//����:	D3DXVECTOR3	Pos		�����ʒu
//		float		Range	�e���͈�
//		float		Attenuation	�����W��	(0.0f�`1.0f 1,0f�Ō����Ȃ�)
//		D3DXCOLOR	diffuse		 �g�U���ˌ��F
//		D3DXCOLOR	Specular	 ���ʔ��ˌ��F
//		D3DXCOLOR	Ambient		 �����F
//=============================================================================
Light* Light::CreatePoint(D3DXVECTOR3 Pos,float Range,float Attenuation,D3DXCOLOR diffuse,D3DXCOLOR Specular,D3DXCOLOR Ambient)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = new Light;

	ZeroMemory(&pLight->_Light,sizeof(D3DLIGHT9));

	pLight->_Light.Type = D3DLIGHT_POINT;
	pLight->_Light.Diffuse = diffuse;
	pLight->_Light.Ambient = Ambient;
	pLight->_Light.Specular = Specular;
	pLight->_Light.Position = Pos;
	pLight->_Light.Range = Range;
	pLight->_Light.Attenuation0 = Attenuation;
	pLight->_Light.Attenuation1 = 0.0f;
	pLight->_Light.Attenuation2 = 0.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&pLight->_Light.Direction,&pLight->Vector);
	Device->SetLight(LightNum,&pLight->_Light);
	Device->LightEnable(LightNum,TRUE);
	LightNum++;

	return pLight;
}
//=============================================================================
//�X�|�b�g���C�g���쐬(�X�y�L�����ƃA���r�G���g���f�B�t���[�Y�Ɠ����ɐݒ肷��)
//����:	D3DXVECTOR3	Pos		�����ʒu
//		float		Range	�e���͈�
//		float		Attenuation	�����W��	(0.0f�`1.0f 1,0f�Ō����Ȃ�)
//		float		Theta	�����̃R�[���̊p�x	(0.0f�`��)
//		float		Phi		�O���̃R�[���̊p�x	(0.0f�`��)
//		float		FallOff	��������O���ւ̌�����(1.0f�ȊO�͏������x�̊֌W�Ŕ񐄏�)
//		D3DXCOLOR	diffuse		 �g�U���ˌ��F
//		D3DXCOLOR	Specular	 ���ʔ��ˌ��F
//		D3DXCOLOR	Ambient		 �����F
//=============================================================================
Light* Light::CreateSpot(D3DXVECTOR3 Vec,D3DXVECTOR3 Pos,float Range,float Attenuation,float Theta,float Phi,float FallOff,D3DXCOLOR diffuse)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = new Light;

	ZeroMemory(&pLight->_Light,sizeof(D3DLIGHT9));

	pLight->Vector = Vec;		//����
	D3DXVec3Normalize((D3DXVECTOR3*)&pLight->_Light.Direction,&pLight->Vector);

	pLight->_Light.Type = D3DLIGHT_SPOT;
	pLight->_Light.Diffuse = diffuse;
	pLight->_Light.Ambient = diffuse;
	pLight->_Light.Specular = diffuse;
	pLight->_Light.Range = Range;
	pLight->_Light.Attenuation0 = Attenuation;
	pLight->_Light.Attenuation1 = 0.0f;
	pLight->_Light.Attenuation2 = 0.0f;
	pLight->_Light.Position = Pos;

	pLight->_Light.Theta = Theta;//�����̃R�[���̊p�x
	pLight->_Light.Phi = Phi;	//�O���̃R�[���̊p�x
	pLight->_Light.Falloff = FallOff;	//��������O���Ɍ������ۂ̌�����
	
	Device->SetLight(LightNum,&pLight->_Light);
	Device->LightEnable(LightNum,TRUE);
	LightNum++;

	return pLight;

}
//=============================================================================
//�X�|�b�g���C�g���쐬(�X�y�L�����ƃA���r�G���g��ʌɐݒ肷��)
//����:	D3DXVECTOR3	Pos		�����ʒu
//		float		Range	�e���͈�
//		float		Attenuation	�����W��	(0.0f�`1.0f 1,0f�Ō����Ȃ�)
//		float		Theta	�����̃R�[���̊p�x	(0.0f�`��)
//		float		Phi		�O���̃R�[���̊p�x	(0.0f�`��)
//		float		FallOff	��������O���ւ̌�����(1.0f�ȊO�͏������x�̊֌W�Ŕ񐄏�)
//		D3DXCOLOR	diffuse		 �g�U���ˌ��F
//		D3DXCOLOR	Specular	 ���ʔ��ˌ��F
//		D3DXCOLOR	Ambient		 �����F
//=============================================================================
Light* Light::CreateSpot(D3DXVECTOR3 Vec,D3DXVECTOR3 Pos,float Range,float Attenuation,float Theta,float Phi,float FallOff,D3DXCOLOR diffuse,D3DXCOLOR Specular,D3DXCOLOR Ambient)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = new Light;

	ZeroMemory(&pLight->_Light,sizeof(D3DLIGHT9));
	
	pLight->_Light.Type = D3DLIGHT_SPOT;
	pLight->_Light.Diffuse = diffuse;
	pLight->_Light.Ambient = Ambient;
	pLight->_Light.Specular = Specular;
	pLight->_Light.Range = Range;
	pLight->_Light.Attenuation0 = Attenuation;
	pLight->_Light.Attenuation1 = 0.0f;
	pLight->_Light.Attenuation2 = 0.0f;
	pLight->_Light.Position = Pos;

	pLight->_Light.Theta = Theta;//�����̃R�[���̊p�x
	pLight->_Light.Phi = Phi;	//�O���̃R�[���̊p�x
	pLight->_Light.Falloff = FallOff;	//��������O���Ɍ������ۂ̌�����
	pLight->Vector = Vec;		//����

	D3DXVec3Normalize((D3DXVECTOR3*)&pLight->_Light.Direction,&pLight->Vector);
	Device->SetLight(LightNum,&pLight->_Light);
	Device->LightEnable(LightNum,TRUE);
	LightNum++;

	return pLight;

}
//=============================================================================
//index�Ԗڂ̃��C�g�̃X�C�b�`�𑀍�
//=============================================================================
void Light::Swicth(int index,bool flag)
{
	Light* pLight = Top;
	Light* Next = NULL;
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	int num=0;
	while(pLight)
	{
		Next = pLight->Next;
		if(num == index)
		{
			BOOL Flag = FALSE;
			if(flag==true)
			{
				Flag = TRUE;
			}
			else
			{
				Flag = FALSE;
			}
			Device->LightEnable(index,Flag);
		}
		pLight = Next;
		num++;
	}
}
//=============================================================================
//Index�Ԗڂ̃��C�g�̃C���X�^���X���擾
//=============================================================================
Light* Light::GetLight(int Index)
{
	Light* pLight = Top;
	Light* Next = NULL;
	int num=0;
	while(pLight)
	{
		Next = pLight->Next;
		if(num == Index)
		{
			return pLight;
		}
		num++;
		pLight = Next;
	}
	return NULL;
}
//=============================================================================
//�Đݒ�
//=============================================================================
void Light::Reset(void)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = Top;
	int num=0;
	while(pLight)
	{
		Device->SetLight(num,&pLight->_Light);
		num++;
		pLight = pLight->Next;
	}
}
//=============================================================================
//�S���̃��C�g��؂�
//=============================================================================
void Light::AllOff(void)
{
	LPDIRECT3DDEVICE9 Device = Window::Instance()->Device();
	Light* pLight = Top;
	int num=0;
	while(pLight)
	{
		Device->LightEnable(num,FALSE);
		num++;
		pLight = pLight->Next;
	}
}
//=============================================================================
//�����ʒu���擾
//�w�������C�g�̏ꍇ�͑S��0���A��
//=============================================================================
D3DXVECTOR3 Light::GetPos(void)
{
	if(_Light.Type != D3DLIGHT_DIRECTIONAL)
	{
		return _Light.Position;
	}
	return D3DXVECTOR3(0,0,0);
}
//=============================================================================
//���̉e���͈͂̎擾
//�w�������C�g�̏ꍇ��-1���A��
//=============================================================================
float Light::GetRange(void)
{
	if(_Light.Type != D3DLIGHT_DIRECTIONAL)
	{
		return _Light.Range;
	}
	return -1;
}
//=============================================================================
//���̉e���͈͂̐ݒ�
//=============================================================================
void Light::SetRange(float range)
{
	_Light.Range = range;
	Reset();
}
//=============================================================================
//�F���Z�b�g
//=============================================================================
void Light::SetColor(D3DXCOLOR color)
{
	_Light.Diffuse = color;
	Reset();

}
//=============================================================================
//�F�����Z
//=============================================================================
void Light::AddColor(D3DXCOLOR color)
{
	_Light.Diffuse.r += color.r;
	_Light.Diffuse.g += color.g;
	_Light.Diffuse.b += color.b;
	_Light.Diffuse.a += color.a;
	Reset();

}
//=============================================================================
//�������Z�b�g
//=============================================================================
void Light::SetVec(D3DXVECTOR3 Vec)
{
	Vector = Vec;
	D3DXVec3Normalize((D3DXVECTOR3*)&_Light.Direction,&Vector);
	Reset();

}
//=============================================================================
//�����ʒu���Z�b�g
//=============================================================================
void Light::SetPos(D3DXVECTOR3 Pos)
{
	_Light.Position = Pos;
	Reset();
}
//=============================================================================
//�����ʒu�����Z
//=============================================================================
void Light::AddPos(D3DXVECTOR3 Pos)
{
	_Light.Position.x += Pos.x;
	_Light.Position.y += Pos.y;
	_Light.Position.z += Pos.z;
	Reset();
}