//=============================================================================
//
// アイテム処理 [item.h]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM				(128)						// アイテム最大数
#define	MAX_ITEM_POP			(5)							// アイテム同時存在可能数
#define	NUM_POP					(2)							// SetItem関数で一回当たりポップさせる数
#define	ITEM_LIFE				(300)						// アイテムの寿命
#define	VALUE_MOVE_ITEM			(0.5f)						// アイテムの移動速度
#define	ITEM_SIZE_X				(40.0f)						// アイテムの幅
#define	ITEM_SIZE_Y				(40.0f)						// アイテムの高さ
#define	ITEM_POP_FREQUENCY		(60*6)						// アイテムのポップ頻度(フレーム×秒数)


//**************************************
// 種類
//**************************************
enum
{
	ITEMTYPE_COIN = 0,		// コイン
	ITEMTYPE_LIFE,			// ライフ
	ITEMTYPE_TIMER,			// タイマー
	ITEMTYPE_MAX
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;				// 現在の位置
	D3DXVECTOR3	rot;				// 現在の向き
	D3DXVECTOR3	scl;				// スケール

	float		fRadius;			// 半径
	int			nIdxShadow;			// 影ID
	int			nType;				// 種類
	int			life;				// 寿命
	int			no;					// ポップしているパネル番号
	bool		use;				// 使用しているかどうか
} ITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, int nType, int life);
ITEM *GetItem(int no);
int GetExistItemNum(void);

#endif
