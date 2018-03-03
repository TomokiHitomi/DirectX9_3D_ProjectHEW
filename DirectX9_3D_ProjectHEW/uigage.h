//=============================================================================
//
// UI��ʏ��� [uigage.h]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#ifndef _UIGAGE_H_
#define _UIGAGE_H_

#include "main.h"
#include "uiframe.h"
#include "calculate.h"

#define	TEXTURE_GAGEFRAME			"data/TEXTURE/gage frame.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_GAGEFRAME_WIDTH		(350)								//�t���[�����T�C�Y
#define	TEXTURE_GAGEFRAME_HEIGHT	(70.0f)								//�t���[���c�T�C�Y
#define	MAX_GAGEFRAME				(2)									//�t���[���g�p��
#define	TEXTUER_GAGEFRAME_POS_X		(320.0f)							//�t���[��posX
#define	TEXTUER_GAGEFRAME_POS_Y		(TEXTURE_HEIGHT/2)					//�t���[��posY


#define	TEXTURE_GAGE				"data/TEXTURE/gage.png"				//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SIZECHANGE			(7.5f)
#define	TEXTURE_GAGE_WIDTH			(TEXTURE_GAGEFRAME_WIDTH)			//�Q�[�W���T�C�Y
#define	TEXTURE_GAGE_HEIGHT			(TEXTURE_GAGEFRAME_HEIGHT-TEXTURE_SIZECHANGE)			//�Q�[�W�c�T�C�Y
#define	MAX_GAGE					(2)									//�Q�[�W�g�p��
#define	GAGE_ALPHA					(0.6f)


typedef struct
{
	D3DXVECTOR2	GageframePos;

}GAGE_FRAME;

typedef struct
{
	D3DXVECTOR2	GagePos;
	D3DXCOLOR	GageCol;
	float		GageLong;
	float		GageRot;

}GAGE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUigage(void);
void UninitUigage(void);
void UpdateUigage(void);
void DrawUigage(void);

GAGE_FRAME *GetGageframe(int no);
GAGE *GetGage(int no);

#endif
