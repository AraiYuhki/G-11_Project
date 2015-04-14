#include "main.h"
#include "Manager.h"
#include "Input/Keyboard.h"

#include<time.h>
const char* Window::ClassName = "AppClass";
const char* Window::WindowName = "Shooting";
Window* Window::Self = new Window;

int Window::Initialize(HINSTANCE hInstance,int cmdShow)
{
	Size.x = 1280.0f;
	Size.y = 720.0f;
	FullScreen = TRUE;

	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		ClassName,
		NULL
	};
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	
	_hWnd = CreateWindowEx(0,
		ClassName,
		WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(int)(Size.x + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(int)(Size.y + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	srand((unsigned)time(NULL));
	_hInstance = hInstance;
	_CmdShow = cmdShow;
	_Manager = new CManager;

	

	//int result = MessageBox(_hWnd,"�t���X�N���[���ŋN�����܂����H","�N���ݒ�",MB_YESNO | MB_DEFBUTTON2 | MB_ICONINFORMATION);
//	if (result == IDYES)
//	{
//		FullScreen = FALSE;
//	}

	if (FAILED(_Manager->Init(hInstance,_hWnd,FullScreen)))
	{
		return -1;
	}

	
	FPS = 0;
	FPSLimit = 60;
	

	return 0;
}

void Window::Show(void)
{
	ShowWindow(_hWnd,_CmdShow);
	UpdateWindow(_hWnd);
}

void Window::Finalize(void)
{
	Self->Uninit();
	SafeDelete(Self);
}

void Window::Uninit(void)
{
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(ClassName,wcex.hInstance);

	// �I������
	if (_Manager != nullptr)
	{
		_Manager->Uninit();
		delete _Manager;
	}
}

int Window::Run(void)
{
	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	ExecLastTime =
	FPSLastTime = timeGetTime();
	CurrentTime =
	FrameCount = 0;

	MSG msg;
	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			// �X�V����

			CurrentTime = timeGetTime();
			if ((CurrentTime - FPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				FPS = FrameCount * 1000 / (CurrentTime - FPSLastTime);
#endif
				FPSLastTime = CurrentTime;
				FrameCount = 0;
			}

			if ((CurrentTime - ExecLastTime) >= (1000 / FPSLimit))
			{
#ifdef _DEBUG
				if (VC::Instance()->Keyboard()->Trigger(DIK_F))
				{
					(FPSLimit != 60) ? FPSLimit = 60 : FPSLimit = 1000;
				}
#endif
				ExecLastTime = CurrentTime;

				_Manager->Update();

				// �`�揈��
				_Manager->Draw();
				DebugProc::Print("FPS:%d\n",FPS);
				FrameCount++;
			}
		}
	}
	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK Window::WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//=============================================================================
//�N���ݒ�_�C�A���O�v���V�[�W���[
//=============================================================================
LRESULT CALLBACK Window::InitializeDialog(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int num = 0;
	/*switch (uMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);

		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			for (int cnt = 0;cnt < 3;cnt++)
			{
				if (SendMessage(GetDlgItem(hWnd,IDC_RADIO1 + cnt),BM_GETCHECK,0,0))
				{
					num = cnt;
				}
			}
			switch (num)
			{
			case 0:
				Self->Size = D3DXVECTOR2(1280.0f,960.0f);
				break;
			case 1:
				Self->Size = D3DXVECTOR2(1028.0f,768.0f);
				break;
			case 2:
				Self->Size = D3DXVECTOR2(800.0f,600.0f);
				break;
			default:
				break;
			}
			(IsDlgButtonChecked(hWnd,IDC_CHECK1)) ? Self->FullScreen = false : Self->FullScreen = true;
			::EndDialog(hWnd,LOWORD(wParam));
			break;
		}
	default:
		break;
	}


	*/
	return 0;
}

void Window::InitVD(void)
{

	for (int cnt = 0;cnt<VD_MAX;cnt++)
	{
		VertexDeclaration[cnt] = { NULL };
		switch (cnt)
		{
		case VTX_DECL_2D:
		{
			D3DVERTEXELEMENT9 VertexElement[] = {
				//�p�C�v���C���ԍ�	�I�t�Z�b�g	�T�C�Y(�^)	��荇��������	�p�r
					{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
					{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },

					D3DDECL_END()
			};
			_Device->CreateVertexDeclaration(VertexElement,&VertexDeclaration[cnt]);
		}
			break;
		case VTX_DECL_POINT_SPRITE:
		{
			D3DVERTEXELEMENT9 VertexElement[] = {
				//�p�C�v���C���ԍ�	�I�t�Z�b�g	�T�C�Y(�^)	��荇��������	�p�r
					{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
					{ 0,12,D3DDECLTYPE_FLOAT1,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_PSIZE,0 },
					{ 0,16,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },

					D3DDECL_END()
			};
			_Device->CreateVertexDeclaration(VertexElement,&VertexDeclaration[cnt]);
		}
			break;
		case VTX_DECL_CUSTOM:
		{
			D3DVERTEXELEMENT9 VertexElement[] = {
				//�p�C�v���C���ԍ�	�I�t�Z�b�g	�T�C�Y(�^)	��荇��������	�p�r
					{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
					{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
					{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },

					D3DDECL_END()
			};
			_Device->CreateVertexDeclaration(VertexElement,&VertexDeclaration[cnt]);
		}
			break;
		default:
			break;
		}
	}
}