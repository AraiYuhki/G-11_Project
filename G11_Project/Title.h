//
//Title.h
//
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "Scene.h"
class Sprite;

class Title :public Scene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sprite *m_logo;//�_�ŗp�摜
	float flahing,add_flahing_num;//���l,������l

};

#endif