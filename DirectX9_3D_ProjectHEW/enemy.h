//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_MOVE_ENEMY	(0.50f)							// 移動速度係数
#define	RATE_MOVE_ENEMY		(0.20f)							// 移動慣性係数
#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.05f)				// 回転速度
#define	RATE_ROTATE_ENEMY	(0.20f)							// 回転慣性係数

#define	ENEMY_MAX			(1)								// エネミーの最大数

#define	ENEMY_SIZE_X		(20.0f)							// エネミーの幅
#define	ENEMY_SIZE_Y		(20.0f)							// エネミーの高さ

#define	ENEMY_ANIM_MAX		(12)							// エネミーのアニメーションパターン数
#define	ENEMY_ANIM_SEC		(1)								// アニメーション一巡にかかる秒数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct		// エネミー構造体
{
	bool			use;							// true:使用  false:未使用

	D3DXVECTOR3		scl;							// スケール

	D3DXVECTOR3		EnemyEye;						// エネミーの視点
	D3DXVECTOR3		EnemyAt;						// エネミーの注視点
	D3DXVECTOR3		EnemyUp;						// エネミーの上方向

	VERTEX_2D		vertexWk[NUM_VERTEX];			// 頂点情報格納ワーク

	int				anim;							// アニメーション番号

} ENEMY;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(int no);

#endif
