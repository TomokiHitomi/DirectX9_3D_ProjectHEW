//-------------------------------------------------------------------
//
// プレイヤーヘッダー[player.h]
// Author : GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*******************************************************************
// マクロ定義
//*******************************************************************
//#define MODEL_PLAYER		"data/MODEL/PLAYER/player01.x"		// 読み込むモデル
#define PLAYER_RADIUS		(10.0f)								// 半径
#define VALUE_MOVE_PLAYER	(1.5f)								// 移動速度
#define PLAYER_MAX			(2)									// プレイヤーの最大数

//*******************************************************************
// 構造体宣言
//*******************************************************************
typedef struct		// プレイヤー構造体
{
	bool		use;		// true:使用-false:未使用
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	rot;		// 角度
	D3DXVECTOR3	scl;		// スケール
	float		radius;		// 半径
	float		item;		// アイテム
} PLAYER;

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
D3DXVECTOR3 GetPosPlayer(void);
D3DXVECTOR3 GetRotPlayer(void);

#endif