//=============================================================================
//
// UI��ʏ��� [uiframe.h]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#ifndef _UIFRAME_H_
#define _UIFRAME_H_

#include "main.h"

#define	TEXTURE_UIFRAME		"data/TEXTURE/UI��.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_WIDTH		(SCREEN_WIDTH)
#define	TEXTURE_HEIGHT		(180)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUiframe(void);
void UninitUiframe(void);
void UpdateUiframe(void);
void DrawUiframe(void);

#endif
