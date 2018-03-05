//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
bool CollisionBoxToPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1);
bool CollisionRayToSphere(D3DXVECTOR3 posRay, D3DXVECTOR3 vecRay, D3DXVECTOR3 posTag, float nLength);

#endif
