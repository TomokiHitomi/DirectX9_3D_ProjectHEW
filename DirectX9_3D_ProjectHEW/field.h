//=============================================================================
//
// 地面処理 [field.h]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

#define	TEXTURE_PANEL	"data/TEXTURE/panel.png"	// 読み込むテクスチャファイル名
#define	PANEL_NUM_X		(15)						//横に並べる枚数
#define	PANEL_NUM_Z		(7)							//縦に並べる枚数
#define	PANEL_MAX		(PANEL_NUM_X*PANEL_NUM_Z)	//使用する枚数
#define	PANEL_SIZE_X	(35)						//パネルサイズ横
#define	PANEL_SIZE_Z	(PANEL_SIZE_X)				//パネルサイズ縦



typedef struct
{
	D3DXMATRIX	mtxWorldField;			// ワールドマトリックス

	D3DXVECTOR3	Pos;					//ポジション
	int			PanelType;				//パネルタイプ
	D3DXCOLOR	PanelCol;				//パネルカラー

	bool		ItemSet;				//アイテムがセットされてるか否か
	int			HitFlag;				//ヒットフラグ
}PANEL;

typedef struct
{
	D3DXMATRIX	mtxWorldHitPanel;			// ワールドマトリックス

	D3DXVECTOR3	Pos;					//ポジション
	D3DXVECTOR3	Size;					//サイズ
	D3DXCOLOR	HitCol;					//変更先の色
	bool		Use;					//エフェクトを出すかどうか

}HIT_PANEL;

enum PANEL_TYPE		//パネルタイプ
{
	PANEL_NORMAL,	//ノーマルパネル
	PANEL_1P,		//1Pパネル
	PANEL_2P,		//2Pパネル
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(int nType);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

PANEL *GetPanel(int no);
HIT_PANEL *GetHitPanel(int no);

int GetPanelNumber(int height, int width);
void SetHitPanel(int no, int playernum);


#endif
