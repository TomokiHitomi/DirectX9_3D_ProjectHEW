//=============================================================================
//
// UI画面処理 [uiframe.h]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#ifndef _UIFRAME_H_
#define _UIFRAME_H_

#include "main.h"

#define	TEXTURE_UIFRAME		"data/TEXTURE/UI板.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_WIDTH		(SCREEN_WIDTH)
#define	TEXTURE_HEIGHT		(180)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUiframe(void);
void UninitUiframe(void);
void UpdateUiframe(void);
void DrawUiframe(void);

#endif
