#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"
#include "Scene.h"
#include "Item.h"
#define PAUSECHARMAX (6)
typedef struct
{
	int CharId;
	bool Charvisbleflag;
}PAUSECHARDATA;

class Scene;
class Pause : public Scene
{
public:
	Pause();
	~Pause();

	void Init(void);
	void Update(void);
	void Uninit(void);


	void PauseUpdate(void);

private:

	static PAUSECHARDATA PauseData[PAUSECHARMAX];
	static bool CharIdflag[PAUSECHARMAX];
	void ResetPauseChar(void);
	void ReCreate(void);

	Sprite *PauseChar[PAUSECHARMAX];//�L������
	Sprite *CharFream;//�L�����g
	Sprite *ReturnGame;//�Q�[���ɖ߂�
	Sprite *BackStage;//�X�e�[�W�ɖ߂�
	Sprite *ReadOperate;//�������
	Sprite *Carsol;//�I��p�J�[�\��
	Sprite *BG;//�w�i
	int MenuNum;//���j���[�I��p
	int OldItemNum;

	bool AlphaFlag;//���l�������邽�߂̃t���O
};

#endif