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
class CRenderer;
class CSound;
class CPlayer;
class CScene;
class DebugProc;

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
		SCENE_WEAPON_SELECT,
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
	static CRenderer* GetRenderer(void){return Render;}
	void SetScene(SCENE scene);
	static void ReleaseObject(void);
	static void SetPause(bool flag);

private:
	static CRenderer* Render;
	static CSound* Sound;

	void Control(void);
	void ChangeScene(void);
	
	CScene* Scene;

	SCENE Current;
	SCENE Next;
	bool SceneChangeFlag;

	static DebugProc* Debug;

	static unsigned __stdcall Thread(void*);
	static unsigned __stdcall SceneInit(void*);
};
#endif