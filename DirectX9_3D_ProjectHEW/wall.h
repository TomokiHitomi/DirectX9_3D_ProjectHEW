//=============================================================================
//
// メッシュ壁の処理 [wall.h]
// Author : 
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "field.h"

#define	MAX_MESH_WALL		(10)							// 壁の総数
#define	TEXTURE_FILENAME	"data/TEXTURE/wall000.jpg"		// 読み込むテクスチャファイル名

#define	WALL_NUM_X			(PANEL_NUM_X)					//壁の使用枚数
#define	WALL_NUM_Y			(1)								//壁の使用枚数
#define	WALL_NUM_Z			(PANEL_NUM_Z)					//壁の使用枚数

#define	WALL_SIZE_X			(PANEL_SIZE_X)					//壁のサイズ
#define	WALL_SIZE_Y			(50)							//壁のサイズ

#define	WALL_COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))//壁の色

#define	WALL_POS_UP			(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X/2,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z))	//壁の設置位置　上
#define	WALL_POS_DOWN		(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X/2,0.0f,0.0f))						//壁の設置位置　下
#define	WALL_POS_RIGHT		(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z/2))	//壁の設置位置　右
#define	WALL_POS_LEFT		(D3DXVECTOR3(0.0f,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z/2))						//壁の設置位置　左

#define	WALL_ROT_UP			(D3DXVECTOR3(0.0f,D3DX_PI*0.0f,0.0f))	//壁の向き
#define	WALL_ROT_DOWN		(D3DXVECTOR3(0.0f,D3DX_PI*0.0f,0.0f))	//壁の向き
#define	WALL_ROT_RIGHT		(D3DXVECTOR3(0.0f,D3DX_PI*0.5f,0.0f))	//壁の向き
#define	WALL_ROT_LEFT		(D3DXVECTOR3(0.0f,-D3DX_PI*0.5f,0.0f))	//壁の向き


typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9 pD3DIdxBuff;			// インデックスバッファインターフェースへのポインタ

	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 pos;							// ポリゴン表示位置の中心座標
	D3DXVECTOR3 rot;							// ポリゴンの回転角
	int nNumBlockX, nNumBlockY;					// ブロック数
	int nNumVertex;								// 総頂点数	
	int nNumVertexIndex;						// 総インデックス数
	int nNumPolygon;							// 総ポリゴン数
	float fBlockSizeX, fBlockSizeY;				// ブロックサイズ
} MESH_WALL;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
	int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

#endif
