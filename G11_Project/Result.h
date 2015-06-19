//
//Result.h
//
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "Scene.h"
#include "Item.h"

#define RESULTCHARMAX (6)
class Sprite;
class Gauge;


typedef struct 
{
	int id;
	bool vis;
}VIS_CHAR;


class Result :public Scene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static void SetResultCharId(int id);
private:
	Sprite *BG;//�w�i
	Sprite *Push;//Push�{�^��
	Sprite *REatan;//���U���g�p���[����
	Sprite *CharFream;//�R���N�V�����p�L�����g

	Sprite *ResultChar[RESULTCHARMAX];//�L�����N�^��

	Sprite *GaugeFream;//�Q�[�W�O�g
	Gauge *GlowGauge;//�Q�[�W

	static VIS_CHAR ResultCharId[RESULTCHARMAX];//�L�����̕\����\��
	float flahing, add_flahing_num;//���l,������l 
	bool charFlag;//�L�����N�^��
	int charVisTime;//�擾�L�����\������
	int charVisCnt;
	int gaugeCnt;//�Q�[�W�p�J�E���g���A�S�̂ɑ΂��擾�����A�C�e�����̃Q�[�W�㏸�p
	int gaugeChangeColor;//�Q�[�W�̐F�ς��p�ϐ�
	void ResetResultChar(void);

};

#endif