//=============================================================================
//
// UI画面処理 [uigage.h]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#ifndef _UIGAGE_H_
#define _UIGAGE_H_

#include "main.h"
#include "uiframe.h"
#include "calculate.h"

#define	TEXTURE_GAGEFRAME			"data/TEXTURE/gage frame.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_GAGEFRAME_WIDTH		(350)								//フレーム横サイズ
#define	TEXTURE_GAGEFRAME_HEIGHT	(70.0f)								//フレーム縦サイズ
#define	MAX_GAGEFRAME				(2)									//フレーム使用数
#define	TEXTUER_GAGEFRAME_POS_X		(320.0f)							//フレームposX
#define	TEXTUER_GAGEFRAME_POS_Y		(TEXTURE_HEIGHT/2)					//フレームposY


#define	TEXTURE_GAGE				"data/TEXTURE/gage.png"				//読み込むテクスチャファイル名
#define	TEXTURE_SIZECHANGE			(7.5f)
#define	TEXTURE_GAGE_WIDTH			(TEXTURE_GAGEFRAME_WIDTH)			//ゲージ横サイズ
#define	TEXTURE_GAGE_HEIGHT			(TEXTURE_GAGEFRAME_HEIGHT-TEXTURE_SIZECHANGE)			//ゲージ縦サイズ
#define	MAX_GAGE					(2)									//ゲージ使用数
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUigage(void);
void UninitUigage(void);
void UpdateUigage(void);
void DrawUigage(void);

GAGE_FRAME *GetGageframe(int no);
GAGE *GetGage(int no);

#endif
