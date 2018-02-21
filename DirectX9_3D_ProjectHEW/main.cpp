//=============================================================================
//
// ���C������ [main.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)

int					g_nTotalCount = 0;		// �g�[�^���J�E���^
int					g_nGameCount = 0;		// �g�[�^���J�E���^
int					g_nCountFPS = 0;		// FPS�J�E���^

bool				g_bEndFlag = true;		// �I���t���O

//float g_fFogDensity = 0.8f;
//D3DXCOLOR g_xFogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);




//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),									// �\���̂̃T�C�Y
		CS_CLASSDC,											// �N���X�̃X�^�C��
		WndProc,											// �E�B���h�v���V�[�W��
		0,													// �⏕������
		0,													// �⏕������
		hInstance,											// �C���X�^���X�n���h��
		NULL,												// �A�C�R���摜
		LoadCursor(NULL, IDC_ARROW),						// �J�[�\���摜
		(HBRUSH)(COLOR_WINDOW + 1),							// �w�i�F
		NULL,												// ���j���[��
		CLASS_NAME,											// �N���X��
		NULL												// �A�C�R��16x16
	};
	HWND hWnd;
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	bool flag = false; // �t���X�N���[�����[�h�ŏ�����
	if (MessageBox(hWnd, "�E�B���h�E���[�h�ŋN�����܂����H", "�N���m�F", MB_YESNO) == IDYES)
	{
		flag = true;
	}

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, flag)))
	{
		return -1;
	}

	//�����_���̏�����
	srand((unsigned)time(NULL));

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{	// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
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
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#ifdef _DEBUG
				PrintDebugProc("FPS:%d  TotalCount:%u", g_nCountFPS, g_nTotalCount);
#endif

				dwExecLastTime = dwCurrentTime;

				// �E�B���h�E���A�N�e�B�u�̏ꍇ
				if (hWnd == GetActiveWindow())
				{
					// �E�B���h�E�̍��W���擾
					RECT	lpScreen;
					GetWindowRect(hWnd, &lpScreen);

					// �}�E�X�J�[�\���̈ړ��͈͂��w��
					lpScreen.left = lpScreen.left + (long)MOUSE_MARGIN;
					lpScreen.top = lpScreen.bottom - (long)SCREEN_HEIGHT + (long)MOUSE_MARGIN;
					lpScreen.right = lpScreen.right - (long)MOUSE_MARGIN;
					lpScreen.bottom = lpScreen.bottom - (long)MOUSE_MARGIN;

					// �}�E�X�J�[�\���̈ړ�����
					ClipCursor(&lpScreen);

#ifdef _DEBUG
					PrintDebugProc("Screen L[%l]  T[%l]  R[%l]  B[%l]\n",	// �E�B���h�E���W��\��
						lpScreen.left, lpScreen.top, lpScreen.right, lpScreen.bottom);
#endif
				}

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
				g_nTotalCount++;
			}
		}
	}
	
	DestroyWindow(hWnd);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;					// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;		// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;							// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;			// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;			// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����



	// �e�평���������i�X�e�[�W�j
	InitSystem(STAGE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}




	UninitSkydome();		// �X�J�C�h�[��
	UninitSkydomeeffect();	// �X�J�C�h�[���G�t�F�N�g
	UninitEnemy();			// �G�l�~�[
	UninitEnemy_normal();	// �G�l�~�[�m�[�}��
	UninitEnemy_boss();		// �G�l�~�[�{�X
	//UninitField();		// �n��
	//UninitWall();			// ��
	UninitMeshcloud();		// �_�C
	UninitCloud();			// �_
	UninitEnemybullet();	// �G�l�~�[�o���b�g
	UninitBullet();			// �o���b�g
	UninitBulletQua();		// �o���b�g�N�H�[�^�j�I���i�G�l�~�[�j
	UninitHiteffect();		// �q�b�g�G�t�F�N�g
	UninitModel();			// ���f��
	UninitShadow();			// �e
	UninitEffect();			// �G�t�F�N�g
	UninitReticle();		// ���e�B�N��
	UninitMagic();			// ���@�w
	UninitMagiccircle();	// ���@�T�[�N��
	UninitPointer();		// �|�C���g
	UninitMinimap();		// �~�j�}�b�v
	UninitLockon();			// ���b�N�I��
	UninitTitle();			// �^�C�g��
	UninitTitlemenu();		// �^�C�g�����j���[
	UninitVersion();		// �o�[�W����
	UninitCopyright();		// �R�s�[���C�g
	UninitResult();			// ���U���g
	UninitParameter();		// �G�l�~�[HP�Q�[�W
	UninitDamageeffect();	// �_���[�W�G�t�F�N�g
	UninitGage();			// �Q�[�W
	UninitGagefream();		// �Q�[�W�t���[��
	UninitGageback();		// �Q�[�W�o�b�N
	UninitGageselect();		// �Q�[�W�Z���N�g
	UninitMagiceffect();	// �}�W�b�N�G�t�F�N�g
	UninitRanking();		// �����L���O
	UninitRank();			// �����N
	UninitJoyconhelp();		// Joycon�w���v
	UninitTimefream();		// �^�C���t���[��
	UninitTime();			// �^�C��
	UninitTimeranking();	// �^�C�������L���O
	UninitPause();			// �|�[�Y
	UninitPausemenu();		// �|�[�Y���j���[

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	PAUSE *pause = GetPause(0);



	E_STAGE eStageTemp = g_eStage;
	switch (g_eStage)
	{
	case STAGE_TITLE:					// �^�C�g��
		UpdateMeshcloud();		// �_�C
		UpdateShadow();			// �e
		UpdateModel();			// ���f��
		UpdateSkydome();		// �X�J�C�h�[��
		UpdateSkydomeeffect();	// �X�J�C�h�[���G�t�F�N�g
		UpdateTitle();			// �^�C�g��
		UpdateTitlemenu();		// �^�C�g�����j���[
		UpdateVersion();
		UpdateCopyright();
		break;
	case STAGE_TUTORIAL:				// �`���[�g���A��
		break;
	case STAGE_CREDIT:					// �N���W�b�g
		break;
	case STAGE_GAME:					// �Q�[��
		UpdatePause();		// �|�[�Y
		if (!pause->bUse)	// �|�[�Y�L�����͊��ʈȉ����A�b�v�f�[�g���Ȃ�
		{
			//UpdateField();		// �n��
			//UpdateWall();			// ��
			UpdateShadow();			// �e
			UpdateGame();
			UpdateMeshcloud();		// �_�C
			UpdateCloud();			// �_
			UpdateEnemy();			// �G�l�~�[
			UpdateEnemy_normal();	// �G�l�~�[�m�[�}��
			UpdateEnemy_boss();		// �G�l�~�[�{�X
			UpdateEnemybullet();	// �o���b�g
			UpdateBulletQua();		// �o���b�g�N�H�[�^�j�I���i�G�l�~�[�j
			UpdateHiteffect();		// �q�b�g�G�t�F�N�g
			UpdateEffect();			// �G�t�F�N�g
			UpdateModel();			// ���f��
			UpdateBullet();			// �o���b�g
			UpdateLockon();			// ���b�N�I��
			UpdateParameter();
			UpdateSkydome();		// �X�J�C�h�[��
			UpdateSkydomeeffect();	// �X�J�C�h�[���G�t�F�N�g
			UpdateReticle();		// ���e�B�N��
			UpdateMagic();			// ���@�w
			UpdateMagiccircle();	// ���@�T�[�N��
			UpdateMinimap();		// �~�j�}�b�v
			UpdateGageback();		// �Q�[�W�o�b�N
			UpdateGage();			// �Q�[�W
			UpdateGagefream();		// �Q�[�W�t���[��
			UpdateGageselect();		// �Q�[�W�Z���N�g
			UpdateMagiceffect();	// �}�W�b�N�G�t�F�N�g
			UpdateTimefream();		// �^�C���t���[��
			UpdateTime();			// �^�C��
			UpdatePointer();		// �|�C���g
			UpdateDamageeffect();	// �_���[�W�G�t�F�N�g
			UpdateJoyconhelp();		// Joycon�w���v
			ChackHit();				// �����蔻��
		}
		UpdatePausemenu();	// �|�[�Y���j���[
		break;
	case STAGE_RESULT:					// ���U���g
		UpdateMeshcloud();		// �_�C
		UpdateShadow();			// �e
		UpdateModel();			// ���f��
		UpdateSkydome();		// �X�J�C�h�[��
		UpdateSkydomeeffect();	// �X�J�C�h�[���G�t�F�N�g
		UpdateRank();			// �����N
		UpdateRanking();		// �����L���O
		UpdateReticle();		// ���e�B�N��
		UpdateTimefream();		// �^�C���t���[��
		UpdateTimeranking();	// �^�C�������L���O
		UpdateTime();			// �^�C��
		UpdateResult();			// ���U���g
		break;
	}


	UpdateSound();
	UpdateFade();

	if (eStageTemp != g_eStage)
	{

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{




		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


//=============================================================================
// �g�[�^���J�E���g�擾�֐�
//=============================================================================
int *GetTotalCount(void)
{
	return(&g_nTotalCount);
}

//=============================================================================
// ������
//=====================asas========================================================
void InitSystem(int nType)
{

}

//=============================================================================
// �X�e�[�W�J�ڏ���
//=============================================================================
void SetStage(E_STAGE eStage)
{
	g_eStage = eStage;
}

//=============================================================================
// �X�e�[�W�擾����
//=============================================================================
E_STAGE GetStage(void)
{
	return g_eStage;
}

//=============================================================================
// �I���t���O
//=============================================================================
void SetEndFlag(void)
{
	g_bEndFlag = false;
}
