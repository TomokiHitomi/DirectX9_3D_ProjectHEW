//-------------------------------------------------------------------
//
// バレットヘッダー[bullet.h]
// Author GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*******************************************************************
// マクロ定義
//*******************************************************************
#define TEXTURE_BULLET			"data/TEXTURE/bullet000.png"		// 読み込むテクスチャファイル名
#define BULLET_SIZE_X			(50.0f)								// ビルボードの幅
#define BULLET_SIZE_Y			(50.0f)								// ビルボードの高さ
#define VALUE_MOVE_BULLET		(2.5f)								// 移動速度

#define BULLET_HIGHT			(20.0f)								// バレット発射時の高さ
#define BULLET_ANGLE_Y			(2.0f)								// 上方向への射角

#define BULLET_MAX				(2)									// バレットの最大数
#define BULLET_TYPE				(2)									// バレットの種類

#define	VALUE_GRAVITY			(0.45f)								// 重力

//*******************************************************************
// 構造体定義
//*******************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scl;		// スケール
	D3DXVECTOR3 move;		// 移動量
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nIdxShadow;			// 影ID
	bool use;				// 使用しているかどうか

	int type;				// プレイヤーで分ける
} BULLET;

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int type);
void DeleteBullet(int nIdxBullet);




#endif
