//=============================================================================
//
// 地面処理 [field.h]
// Author : 
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

#define	TEXTURE_PANEL	"data/TEXTURE/panel.png"	// 読み込むテクスチャファイル名
#define	PANEL_NUM_X		(15)						//横に並べる枚数
#define	PANEL_NUM_Z		(7)						//縦に並べる枚数
#define	PANEL_MAX		(PANEL_NUM_X*PANEL_NUM_Z)	//使用する枚数
#define	PANEL_SIZE_X	(50)						//パネルサイズ横
#define	PANEL_SIZE_Z	(50)						//パネルサイズ縦
#define	PANEL_COL_1P	(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))//1Pカラー
#define	PANEL_COL_2P	(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))//2Pカラー

typedef struct
{
	D3DXMATRIX	mtxWorldField;			// ワールドマトリックス

	D3DXVECTOR3	Pos;					//ポジション
	int			PanelNumber;			//パネルナンバー
	D3DXCOLOR	PanelCol;				//パネルカラー
}PANEL;

enum PANEL_PATTERN
{
	PANEL_NORMAL,
	PANEL_1P,
	PANEL_2P,
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

PANEL *GetPanel(int no);

#endif
