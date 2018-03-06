//=============================================================================
//
// タイトル画面処理 [titlelogo.h]
// Author : GP11B243 34 吉田太智
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLELOGO		("data/TEXTURE/aiueo.jpg")		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLELOGO_LOGO	("data/TEXTURE/とま.png")	// 読み込むテクスチャファイル名
#define	TEXTURE_LOGO_START		("data/TEXTURE/プリエニ.png")// 読み込むテクスチャファイル名

#define	TITLELOGO_LOGO_POS_X		(SCREEN_CENTER_X)			// タイトルロゴの位置(X座標)
#define	TITLELOGO_LOGO_POS_Y		(280*SCREEN_SCALE)						// タイトルロゴの位置(Y座標)
#define	TITLELOGO_LOGO_WIDTH		(500 / 1*SCREEN_SCALE)					// タイトルロゴの幅500/2
#define	TITLELOGO_LOGO_HEIGHT		(400 / 2*SCREEN_SCALE)					// タイトルロゴの高さ

#define	START_POS_X					(SCREEN_CENTER_X)			// スタートボタンの位置(X座標)
#define	START_POS_Y					(550*SCREEN_SCALE)						// スタートボタンの位置(Y座標)
#define	START_WIDTH					(480 / 2*SCREEN_SCALE)					// スタートボタンの幅
#define	START_HEIGHT				(120 / 2*SCREEN_SCALE)					// スタートボタンの高さ

#define	COUNT_APPERA_START			(60)						// スタートボタン出現までの時間
#define	INTERVAL_DISP_START			(60)						// スタートボタン点滅の時間

#define	COUNT_WAIT_DEMO				(60 * 5)					// デモまでの待ち時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitlelogo(int nType);
void UninitTitlelogo(void);
void UpdateTitlelogo(void);
void DrawTitlelogo(void);

#endif
