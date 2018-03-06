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
#define PLAYER_RADIUS		(10.0f)			// 半径
#define PLAYER_SIZE_BOX		(5.0f)			// ボックスの当たり判定サイズ
#define VALUE_MOVE_PLAYER	(2.0f)			// 移動速度
#define PLAYER_MAX			(2)				// プレイヤーの最大数

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
	D3DXVECTOR3	oldPos;		// 座標を戻す用

	int			type;		// プレイヤーで分ける

	int			havetime;	//アイテムの所持時間
} PLAYER;

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
HRESULT InitPlayer(int nType);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);
D3DXVECTOR3 GetPosPlayer(int no);
D3DXVECTOR3 GetRotPlayer(int no);

#endif