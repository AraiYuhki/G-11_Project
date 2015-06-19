#include "Stage_1.h"
#include "Game.h"
#include "Gimmick.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "Wall.h"
#include "BoundObject.h"
#include "BreakObject.h"
#include "StartDevice.h"
#include "Camera2D.h"

#include "Ivy.h"
#include "Gate.h"
#include "Stump.h"
#include "Clog.h"
#include "Item.h"
#include "Goal.h"
#include "Taizou.h"

#define ITEM_SIZE (D3DXVECTOR2(84.0f,84.0f))
//=============================================================================
//�R���X�g���N�^
//=============================================================================
Stage_1::Stage_1()
{
	//�X�e�[�W�T�C�Y 1280*4x900
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
Stage_1::~Stage_1()
{

}

//=============================================================================
//����
//=============================================================================
Stage_1 *Stage_1::Create()
{
	Stage_1 *stage1 = new Stage_1();

	stage1->Init();

	return stage1;
}

//=============================================================================
//������
//=============================================================================
void Stage_1::Init(void)
{
	Camera2D *camera = Camera2D::GetCamera(0);

	D3DXVECTOR3* quad;

	// ��
	Wall *wall = Wall::Create(D3DXVECTOR2(SCREEN_WIDTH * 3.0f, 945.0f), D3DXVECTOR2(SCREEN_WIDTH * 6.0f, 150.0f), TEX_FLOOR1_BG, Sprite::LAYER_1);
	quad = wall->LocalQuadBase();
	quad[0].y = -0.255f;
	quad[1].y = -0.255f;
	wall->SetLocalQuadBase(quad);
	camera->SetFloor(wall);

	// �V��
	wall = Wall::Create(D3DXVECTOR2(SCREEN_WIDTH * 3.0f, 45.0f), D3DXVECTOR2(SCREEN_WIDTH * 6.0f, 150.0f), TEX_CILLING1_BG, Sprite::LAYER_1);
	quad = wall->LocalQuadBase();
	quad[2].y = 0.255f;
	quad[3].y = 0.255f;
	wall->SetLocalQuadBase(quad);
	camera->SetCilling(wall);

	// ���̕�
	wall = Wall::Create(D3DXVECTOR2(0.0f,450.0f),D3DXVECTOR2(1280.0f,256.0f),TEX_FLOOR1_BG,Sprite::LAYER_1);
	quad = wall->LocalQuadBase();
	quad[0].y = -0.255f;
	quad[1].y = -0.255f;
	wall->SetLocalQuadBase(quad);
	wall->SetRot(PI/2.0f);

	wall = Wall::Create(D3DXVECTOR2(SCREEN_WIDTH*6.0f,450.0f),D3DXVECTOR2(1280.0f,256.0f),TEX_FLOOR1_BG,Sprite::LAYER_1);
	quad = wall->LocalQuadBase();
	quad[0].y = -0.255f;
	quad[1].y = -0.255f;
	wall->SetLocalQuadBase(quad);
	wall->SetRot(-(PI / 2.0f));

	camera->SetLeftLimit(560.0f);
	camera->SetRightLimit(SCREEN_WIDTH*6.0f - 560.0f);

	// ���̃A�C�e�����W�@���ꎞ�I�ɏ���������
	D3DXVECTOR2 itemPos = D3DXVECTOR2(1000.0f, SCREEN_HEIGHT / 2.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(64.0f, 128.0f);
	Item::Create(D3DXVECTOR3(1000.0f,SCREEN_HEIGHT / 2.0f,0),ITEM_SIZE,WHITE(1.0f),ITEM_ID_USAGI,Sprite::LAYER_2);

	wall = Wall::Create(D3DXVECTOR2(1000.0f,245.0f),D3DXVECTOR2(192.0f,64.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);

	wall = Wall::Create(D3DXVECTOR2(1130.0f, 340.0f), D3DXVECTOR2(64.0f,256.0f),TEX_BREAKABLE_OBJ, Sprite::LAYER_2);

	wall = Wall::Create(D3DXVECTOR2(1000.0f, 435.0f), D3DXVECTOR2(192.0f,64.0f),TEX_BREAKABLE_OBJ, Sprite::LAYER_2);

	StartDevice *start = Ivy::Create(D3DXVECTOR2(850.0f,160.0f),D3DXVECTOR2(130.0f,260.0f),Sprite::LAYER_0);
	

	Gimmick* gimmick = Gimmick::Create(D3DXVECTOR2(850.0f,340.0f),D3DXVECTOR2(128.0f,256.0f),Sprite::LAYER_2);
	gimmick->SetTexture(GetTexture(TEX_MARUTA));
	gimmick->SetAction([](Gimmick* gimmick){ 
		gimmick->AddSpeedY(0.48f);
		gimmick->AddPos(gimmick->Speed());
		if (gimmick->Pos().y > 1000.0f){ 
			gimmick->SetRelease();
		}
	});
	gimmick->AddStartDevice(start);

	start = Stump::Create(D3DXVECTOR2(1350.0f,943.5f),D3DXVECTOR2(128.0f,128.0f),Sprite::LAYER_0);

	Clog::Create(D3DXVECTOR2(1000.0f,800.0f),D3DXVECTOR2(75.0f,75.0f));

	//�ŏ��̃Q�[�g
	gimmick = Gate::Create(D3DXVECTOR2(1700.0f,700.0f),D3DXVECTOR2(128.0f,500.0f),TEX_MARUTA,Sprite::LAYER_0);
	gimmick->SetAction([](Gimmick* gimmick){
		D3DXVECTOR3 pos = (D3DXVECTOR3(1700.0f,1250.0f,0) - gimmick->Pos())*0.01f;
		gimmick->AddPos(pos);
	});
	
	gimmick->AddStartDevice(start);

	gimmick = Gate::Create(D3DXVECTOR2(1700.0f,250.0f),D3DXVECTOR2(128.0f,500.0f),TEX_MARUTA,Sprite::LAYER_0);
	
	gimmick->SetAction([](Gimmick* gimmick){
		D3DXVECTOR3 pos = (D3DXVECTOR3(1700.0f,-350.0f,0) - gimmick->Pos())*0.01f;
		gimmick->AddPos(pos);
	});
	gimmick->AddStartDevice(start);

	wall = Wall::Create(D3DXVECTOR2(2000.0f,256.0f),D3DXVECTOR2(256.0f,512.0f),TEX_BREAKABLE_OBJ);

	Item::Create(D3DXVECTOR3(2500.0f,890.0f,0),ITEM_SIZE,WHITE(1.0f),ITEM_ID_KUMA,Sprite::LAYER_0);
	for (int num = 0;num < 3;num++)
	{
		for (int cnt = 0;cnt < 3;cnt++)
		{
			BreakObject* breakObj = BreakObject::Create(D3DXVECTOR2(2200.0f + num*300.0f,890.0f - cnt*64.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA);
			breakObj->SetRot(PI / 2.0f);
		}
	}
	
	wall = Wall::Create(D3DXVECTOR2(2350.0f, 300.0f), D3DXVECTOR2(256.0f, 128.0f), TEX_BREAKABLE_OBJ,Sprite::LAYER_1);
	wall = Wall::Create(D3DXVECTOR2(2610.0f, 270.0f), D3DXVECTOR2(256.0f, 128.0f), TEX_BREAKABLE_OBJ,Sprite::LAYER_1);
	wall = Wall::Create(D3DXVECTOR2(2870.0f, 240.0f), D3DXVECTOR2(256.0f, 128.0f), TEX_BREAKABLE_OBJ,Sprite::LAYER_1);

	wall = Wall::Create(D3DXVECTOR2(3000.0f, 120.0f), D3DXVECTOR2(128.0f, 256.0f), TEX_BREAKABLE_OBJ);

	start = StartDevice::CreateTrigger(D3DXVECTOR2(2550.0f, 100.0f), D3DXVECTOR2(64.0f, 64.0f));
	start->SetTexture(GetTexture(TEX_UNBREAKABLE_OBJ));

	gimmick = Gimmick::Create(D3DXVECTOR2(2740.0f, 120.0f), D3DXVECTOR2(64.0f, 256.0f), Sprite::LAYER_0);
	gimmick->SetTexture(GetTexture(TEX_BREAKABLE_OBJ));
	gimmick->SetAction([](Gimmick* act){
		act->AddPosY((-200 - act->Pos().y) * 0.05f);
	});
	gimmick->AddStartDevice(start);

	Item::Create(D3DXVECTOR3(2870.0f, 100.0f, 0.0f), ITEM_SIZE, WHITE(1.0f), ITEM_ID_USI);

	wall = Wall::Create(D3DXVECTOR2(3800.0f, 370.0f), D3DXVECTOR2(1000.0f, 50.0f), TEX_BREAKABLE_OBJ, Sprite::LAYER_1);
	wall = Wall::Create(D3DXVECTOR2(4325.0f, 200.0f), D3DXVECTOR2(50.0f, 400.0f), TEX_BREAKABLE_OBJ, Sprite::LAYER_0);

	wall = Wall::Create(D3DXVECTOR2(3800.0f, 670.0f), D3DXVECTOR2(1000.0f, 50.0f), TEX_BREAKABLE_OBJ, Sprite::LAYER_1);
	wall = Wall::Create(D3DXVECTOR2(4325.0f, 850.0f), D3DXVECTOR2(50.0f, 400.0f), TEX_BREAKABLE_OBJ, Sprite::LAYER_0);

	// ��i
	for (int cnt = 0; cnt < 5; cnt++)
	{
		wall = BreakObject::Create(D3DXVECTOR2(3370.0f + 150.0f * cnt, 200.0f), D3DXVECTOR2(150.0f, 300.0f), TEX_MARUTA, true, Sprite::LAYER_0);
	}

	// ���i
	for (int cnt = 0; cnt < 7; cnt++)
	{
		wall = BreakObject::Create(D3DXVECTOR2(3370.0f + 150.0f * cnt, 525.0f), D3DXVECTOR2(150.0f, 300.0f), TEX_MARUTA, true, Sprite::LAYER_0);
	}

	// ���i
	for (int cnt = 0; cnt < 5; cnt++)
	{
		wall = BreakObject::Create(D3DXVECTOR2(3370.0f + 150.0f * cnt, 850.0f), D3DXVECTOR2(150.0f, 300.0f), TEX_MARUTA, true, Sprite::LAYER_0);
	}

	Item::Create(D3DXVECTOR3(4150.0f, 200.0f, 0.0f), ITEM_SIZE, WHITE(1.0f), ITEM_ID_SAI);
	Item::Create(D3DXVECTOR3(4150.0f, 850.0f, 0.0f), ITEM_SIZE, WHITE(1.0f), ITEM_ID_NEKO);

	Wall::Create(D3DXVECTOR2(5590.0f,100.0f),D3DXVECTOR2(1280.0f,128.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);
	Wall::Create(D3DXVECTOR2(5654.0f,850.0f),D3DXVECTOR2(1408.0f,128.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);
	Wall::Create(D3DXVECTOR2(5000.0f,480.0f),D3DXVECTOR2(128.0f,128.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);

	wall = Wall::Create(D3DXVECTOR2(5000.0f,288.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA,Sprite::LAYER_0);
	wall->SetUVHeight(-1.0f);

	BoundObject* boundObj =  BoundObject::Create(D3DXVECTOR2(5000.0f,810.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA,4,Sprite::LAYER_0);
	boundObj->SetOffsetY(-0.5f);
	boundObj->SetAction([](BoundObject* obj)
	{
		if (obj->Rot().z < PI / 2.0f)
		{
			obj->AddRot(DEG2RAD(10.0f));
		}
		else
		{
			obj->SetRot(DEG2RAD(90.0f));
		}
	});

	boundObj = BoundObject::Create(D3DXVECTOR2(5070.0f,480.0f),D3DXVECTOR2(128.0f,384.0f),TEX_MARUTA,4,Sprite::LAYER_0);
	boundObj->SetOffsetY(-0.5f);
	boundObj->SetRot(PI/2.0f);
	boundObj->SetAction([](BoundObject* obj)
	{
		if (obj->Rot().z > 0)
		{
			obj->AddRot(DEG2RAD(-10.0f));
		}
		else
		{
			obj->SetRot(0);
		}
	});
	Wall::Create(D3DXVECTOR2(5490.0f,480.0f),D3DXVECTOR2(128.0f,128.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);

	wall = Wall::Create(D3DXVECTOR2(5480.0f,680.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA,Sprite::LAYER_0);
	wall->SetUVHeight(1.0f);

	boundObj = BoundObject::Create(D3DXVECTOR2(5480.0f,148.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA,4,Sprite::LAYER_0);
	boundObj->SetOffsetY(-0.5f);
	boundObj->SetRot(PI);
	boundObj->SetAction([](BoundObject* obj)
	{
		if (obj->Rot().z > PI / 2.0f)
		{
			obj->AddRot(DEG2RAD(-10.0f));
		}
		else
		{
			obj->SetRot(DEG2RAD(90.0f));
		}
	});

	boundObj = BoundObject::Create(D3DXVECTOR2(5560.0f,480.0f),D3DXVECTOR2(128.0f,384.0f),TEX_MARUTA,4,Sprite::LAYER_0);
	boundObj->SetOffsetY(-0.5f);
	boundObj->SetRot(PI / 2.0f);
	boundObj->SetAction([](BoundObject* obj)
	{
		if (obj->Rot().z < PI)
		{
			obj->AddRot(DEG2RAD(10.0f));
		}
		else
		{
			obj->SetRot(PI);
		}
	});
	Wall::Create(D3DXVECTOR2(6032.0f,590.0f),D3DXVECTOR2(128.0f,384.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);
	Wall::Create(D3DXVECTOR2(6160.0f,590.0f),D3DXVECTOR2(128.0f,384.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);
	Wall::Create(D3DXVECTOR2(6288.0f,590.0f),D3DXVECTOR2(128.0f,384.0f),TEX_BREAKABLE_OBJ,Sprite::LAYER_2);
	
	boundObj = BoundObject::Create(D3DXVECTOR2(6000.0f,148.0f),D3DXVECTOR2(128.0f,256.0f),TEX_MARUTA,4,Sprite::LAYER_0);
	boundObj->SetOffsetY(-0.5f);
	boundObj->SetRot(PI);
	boundObj->SetAction([](BoundObject* obj)
	{
		if (obj->Rot().z > PI / 2.0f)
		{
			obj->AddRot(DEG2RAD(-10.0f));
		}
		else
		{
			obj->SetRot(DEG2RAD(90.0f));
		}
	});

	Clog::Create(D3DXVECTOR2(5750.0f,700.0f),D3DXVECTOR2(75.0f,75.0f));

	for (int cnt = 0;cnt < 14;cnt++)
	{
		wall = BreakObject::Create(D3DXVECTOR2(6480.0f,470.0f+cnt*32.0f),D3DXVECTOR2(64.0f,256.0f),TEX_MARUTA,false);
		wall->SetRot(PI / 2.0f);
	}

	Wall::Create(D3DXVECTOR2(6730.0f,384.0f),D3DXVECTOR2(256.0f,768.0f),TEX_BREAKABLE_OBJ);

	Taizou::Create(D3DXVECTOR2(7000.0f,600.0f));

	//�S�[��
	Goal* goal = Goal::Create(D3DXVECTOR3(7500.0f,800.0f,0.0f),D3DXVECTOR2(256.0f,256.0f),WHITE(1.0f),Sprite::LAYER_2);

}

//=============================================================================
//�X�V
//=============================================================================
void Stage_1::Update(void)
{
	
}

//=============================================================================
//�X�V
//=============================================================================
void Stage_1::Release(void)
{
	delete this;
}