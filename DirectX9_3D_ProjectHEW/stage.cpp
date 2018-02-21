//=============================================================================
//
// Stage���� [stage.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Stage */
#include "title.h"



/* Camera */
#include "camera.h"

/* System */
#include "sound.h"
#include "light.h"
#include "input.h"
#include "fade.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
STAGE_SYS					stageSysWk;

int					g_nStage = START_STAGE;	// �X�e�[�W

#ifdef _DEBUG
bool				g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF
#endif

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStage(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);		// ����
	InitSound(hWnd);				// �T�E���h
	InitFade();						// �t�F�[�h
#ifdef _DEBUG
	InitDebugProc();				// �f�o�b�O�\�������̏�����
#endif

	InitTitle(0);					// �^�C�g��
	InitLight();				// ���C�g
	InitCamera();					// �J����
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage(void)
{
	UninitInput();					// ���͂̏I������
	UninitSound();					// �T�E���h
	UninitFade();					// �t�F�[�h

#ifdef _DEBUG
	UninitDebugProc();				// �f�o�b�O�\�������̏I������
#endif

	UninitTitle();					// �^�C�g��
	UninitCamera();					// �J����
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
	UpdateInput();					// ���͂̍X�V����

	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle;				// �^�C�g��
		break;
	case STAGE_GAME:
		break;
	case STAGE_RESULT:
		break;
	}
	UpdateCamera();					// �J����

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	UpdateDebugProc();				// �f�o�b�O
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage(void)
{
	SetCamera();					// �J�����̐ݒ菈��
	DrawTitle();					// �^�C�g��
	DrawFade();						// �t�F�[�h

#ifdef _DEBUG
	if (g_bDispDebug)
	{	// �f�o�b�O�\������ꍇ
		DrawDebugProc();			// �f�o�b�O
	}
#endif
}




//=============================================================================
// �擾�֐�
//=============================================================================
STAGE_SYS *GetStageSys(void)
{
	return(&stageSysWk);
}

//=============================================================================
// �J�E���g�擾�֐�
//=============================================================================
void SetResultTime(int nTime)
{
	STAGE_SYS *stageSys = &stageSysWk;
	stageSys->nTime = nTime;
}

//=============================================================================
// �J�E���g�擾�֐�
//=============================================================================
int GetResultTime(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->nTime);
}

//=============================================================================
// �N���A�t���O�擾�֐�
//=============================================================================
void SetClearFlag(bool bClearFlag)
{
	STAGE_SYS *stageSys = &stageSysWk;
	stageSys->bClearFlag = bClearFlag;
	stageSys->bEndFlag = true;
}

//=============================================================================
// �N���A�t���O�擾�֐�
//=============================================================================
bool GetClearFlag(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->bClearFlag);
}

//=============================================================================
// �I���t���O�擾�֐�
//=============================================================================
bool GetEndFlag(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->bEndFlag);
}