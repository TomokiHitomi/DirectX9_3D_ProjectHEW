//=============================================================================
//
// リザルト勝敗画面処理 [resultwin.h]
// Author : GP11B243 34 吉田太智
//
//=============================================================================
#ifndef _RESULTWIN_
#define _RESULTWIN_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/空001.jpg"		// 読み込むテクスチャファイル名

#define	TEXTURE_RESULTLOGO_DEFEAT1	"data/TEXTURE/1p.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RESULTLOGO_DEFEAT2	"data/TEXTURE/2Pwin.png"	// 読み込むテクスチャファイル名

#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_Y	(100)					// リザルトロゴの位置(Y座標
#define	RESULTLOGO_LOGO_DEFEAT1_WIDTH	(800 / 2)					// リザルトロゴの幅
#define	RESULTLOGO_LOGO_DEFEAT1_HEIGHT	(240 / 2)					// リザルトロゴの高さ

#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_Y	(100)					// リザルトロゴの位置(Y座標
#define	RESULTLOGO_LOGO_DEFEAT2_WIDTH	(800 / 2)					// リザルトロゴの幅
#define	RESULTLOGO_LOGO_DEFEAT2_HEIGHT	(240 / 2)					// リザルトロゴの高さ

#define	COUNT_APPERA_RESULTLOGO	(60)		// リザルトロゴ出現までの待ち時間	



/*******************************************************************************
* 構造体定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultwin(int nType);
void UninitResultwin(void);
void UpdateResultwin(void);
void DrawResultwin(void);

#endif
