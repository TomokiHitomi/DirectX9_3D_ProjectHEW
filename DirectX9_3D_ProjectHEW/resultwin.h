//=============================================================================
//
// ���U���g���s��ʏ��� [resultwin.h]
// Author : GP11B243 34 �g�c���q
//
//=============================================================================
#ifndef _RESULTWIN_
#define _RESULTWIN_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/��001.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_RESULTLOGO_DEFEAT1	"data/TEXTURE/1p.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULTLOGO_DEFEAT2	"data/TEXTURE/2Pwin.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_Y	(100)					// ���U���g���S�̈ʒu(Y���W
#define	RESULTLOGO_LOGO_DEFEAT1_WIDTH	(800 / 2)					// ���U���g���S�̕�
#define	RESULTLOGO_LOGO_DEFEAT1_HEIGHT	(240 / 2)					// ���U���g���S�̍���

#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_Y	(100)					// ���U���g���S�̈ʒu(Y���W
#define	RESULTLOGO_LOGO_DEFEAT2_WIDTH	(800 / 2)					// ���U���g���S�̕�
#define	RESULTLOGO_LOGO_DEFEAT2_HEIGHT	(240 / 2)					// ���U���g���S�̍���

#define	COUNT_APPERA_RESULTLOGO	(60)		// ���U���g���S�o���܂ł̑҂�����	



/*******************************************************************************
* �\���̒�`
*******************************************************************************/

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultwin(int nType);
void UninitResultwin(void);
void UpdateResultwin(void);
void DrawResultwin(void);

#endif
