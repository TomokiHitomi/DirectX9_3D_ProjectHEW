//=============================================================================
//
// EFFECT処理 [effect.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT	"data/TEXTURE/effect_bomb.png"
#define EFFECT_MAX			(1)			// 最大数
#define	EFFECT_SIZE_X		(100.0f)		// サイズX
#define	EFFECT_SIZE_Y		(100.0f)		// サイズY
#define	EFFECT_ALPHA		(30)		// αテスト値
#define	EFFECT_Y			(100.0f)		// αテスト値

// テクスチャ内分割数
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(7)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)
// テクスチャ分割パターン
#define TEXTURE_PATTERN_NU_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)
// アニメーション
#define TIME_ANIMATION_EFFECT			(5)

typedef struct
{
	D3DXVECTOR3			posEffect;			// 位置
	D3DXVECTOR3			rotEffect;			// 向き(回転)
	D3DXVECTOR3			sclEffect;			// 大きさ(スケール)
	D3DXVECTOR2			vec2Size;				// サイズ
	int					nAnimeCount;			// アニメーションカウント
	int					nAnimePattern;			// アニメーションパターン
	bool				bUse;					// 使用フラグ
}EFFECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(int nType);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos);
EFFECT *GetEffect(int no);

#endif
