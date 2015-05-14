//=============================================================================
// �}�l�[�W���[�N���X
// CreateBy Arai Yuhki
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
//=============================================================================
// �O���錾
//=============================================================================
class Renderer;
class CSound;
class CPlayer;
class Scene;
class CDebugProc;

typedef void (*Function)(void);
//=============================================================================
// �N���X��`
//=============================================================================
class CManager
{
public:

	typedef enum
	{
		SCENE_TITLE = 0,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX
	}SCENE;

	CManager();
	virtual ~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static Renderer* GetRenderer(void){return _Render;}
	void SetScene(SCENE scene);
	static void ReleaseObject(void);
	static void SetPause(bool flag);

private:
	static Renderer* _Render;
	static CSound* Sound;

	void Control(void);
	void ChangeScene(void);
	
	Scene* Scene;

	SCENE Current;
	SCENE Next;
	bool SceneChangeFlag;

	static CDebugProc* Debug;

	static unsigned __stdcall Thread(void*);
	static unsigned __stdcall SceneInit(void*);
};
#endif