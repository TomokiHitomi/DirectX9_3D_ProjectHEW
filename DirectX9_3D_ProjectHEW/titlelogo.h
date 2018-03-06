//=============================================================================
//
// �^�C�g����ʏ��� [titlelogo.h]
// Author : GP11B243 34 �g�c���q
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLELOGO		("data/TEXTURE/aiueo.jpg")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLELOGO_LOGO	("data/TEXTURE/�Ƃ�.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LOGO_START		("data/TEXTURE/�v���G�j.png")// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLELOGO_LOGO_POS_X		(SCREEN_CENTER_X)			// �^�C�g�����S�̈ʒu(X���W)
#define	TITLELOGO_LOGO_POS_Y		(280*SCREEN_SCALE)						// �^�C�g�����S�̈ʒu(Y���W)
#define	TITLELOGO_LOGO_WIDTH		(500 / 1*SCREEN_SCALE)					// �^�C�g�����S�̕�500/2
#define	TITLELOGO_LOGO_HEIGHT		(400 / 2*SCREEN_SCALE)					// �^�C�g�����S�̍���

#define	START_POS_X					(SCREEN_CENTER_X)			// �X�^�[�g�{�^���̈ʒu(X���W)
#define	START_POS_Y					(550*SCREEN_SCALE)						// �X�^�[�g�{�^���̈ʒu(Y���W)
#define	START_WIDTH					(480 / 2*SCREEN_SCALE)					// �X�^�[�g�{�^���̕�
#define	START_HEIGHT				(120 / 2*SCREEN_SCALE)					// �X�^�[�g�{�^���̍���

#define	COUNT_APPERA_START			(60)						// �X�^�[�g�{�^���o���܂ł̎���
#define	INTERVAL_DISP_START			(60)						// �X�^�[�g�{�^���_�ł̎���

#define	COUNT_WAIT_DEMO				(60 * 5)					// �f���܂ł̑҂�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitlelogo(int nType);
void UninitTitlelogo(void);
void UpdateTitlelogo(void);
void DrawTitlelogo(void);

#endif
