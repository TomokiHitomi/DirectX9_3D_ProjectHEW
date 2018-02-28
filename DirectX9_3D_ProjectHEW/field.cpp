//=============================================================================
//
// 地面処理 [field.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "field.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void SetDiffuseField(int nField, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// 頂点バッファへのポインタ

PANEL					g_aPanel[PANEL_MAX];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PANEL *panel = GetPanel(0);

	MakeVertexField(pDevice);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_PANEL,			// ファイルの名前
			&g_pD3DTextureField);	// 読み込むメモリー

	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		panel->Pos.x = i % PANEL_NUM_X * PANEL_SIZE_X;	//X座標の設定
		panel->Pos.y = 0.0f;							//Y座標は0固定
		panel->Pos.z = i / PANEL_NUM_X * PANEL_SIZE_Z;	//Z座標の設定
		panel->PanelType = PANEL_NORMAL;				//パネルタイプ　基本はノーマル
		panel->PanelCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//パネルカラー 基本は白
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	if (g_pD3DTextureField != NULL)
	{// テクスチャの開放
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PANEL *panel = GetPanel(0);

	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		if (panel->PanelType == PANEL_1P)	//パネルタイプが1Pに変わったら
		{
			panel->PanelCol = PANEL_COL_1P;	//パネルカラーを1Pに
		}
		else if (panel->PanelType == PANEL_2P)	//パネルタイプが2Pになったら
		{
			panel->PanelCol = PANEL_COL_2P;		//パネルカラーを2Pに
		}
		SetDiffuseField(i, panel->PanelCol);
	}


#ifdef _DEBUG
	//パネル位置確認用
	PANEL *panelcheck1 = GetPanel(GetPanelNumber(1, 1));
	PANEL *panelcheck2 = GetPanel(GetPanelNumber(1, 15));
	PANEL *panelcheck3 = GetPanel(GetPanelNumber(7, 1));
	PANEL *panelcheck4 = GetPanel(GetPanelNumber(7, 15));
	PrintDebugProc("パネル[ 1][ 1] : (%f,%f,%f)\n", panelcheck1->Pos.x, panelcheck1->Pos.y, panelcheck1->Pos.z);
	PrintDebugProc("パネル[ 1][15] : (%f,%f,%f)\n", panelcheck2->Pos.x, panelcheck2->Pos.y, panelcheck2->Pos.z);
	PrintDebugProc("パネル[ 7][ 1] : (%f,%f,%f)\n", panelcheck3->Pos.x, panelcheck3->Pos.y, panelcheck3->Pos.z);
	PrintDebugProc("パネル[ 7][15] : (%f,%f,%f)\n", panelcheck4->Pos.x, panelcheck4->Pos.y, panelcheck4->Pos.z);



#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	PANEL *panel = GetPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&panel->mtxWorldField);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, panel->Pos.x, panel->Pos.y, panel->Pos.z);
		D3DXMatrixMultiply(&panel->mtxWorldField, &panel->mtxWorldField, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &panel->mtxWorldField);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureField);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffField,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//for (int i = 0; i < PANEL_MAX; i++)
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
		
		for (int i = 0; i < PANEL_MAX; i++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, PANEL_SIZE_Z/2);
			pVtx[1].vtx = D3DXVECTOR3(PANEL_SIZE_X/2, 0.0f, PANEL_SIZE_Z/2);
			pVtx[2].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, -PANEL_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(PANEL_SIZE_X/2, 0.0f, -PANEL_SIZE_Z / 2);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 頂点データをアンロックする
		g_pD3DVtxBuffField->Unlock();
	}
	
	return S_OK;
}

//============================================================================= 
// 反射光の設定関数 
//============================================================================= 
void SetDiffuseField(int nField, D3DXCOLOR col)
{ 
	{// 頂点バッファの中身を埋める 
		VERTEX_3D *pVtx; 

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得 
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nField * 4);

		// 頂点座標の設定 
			pVtx[0].diffuse = 
			pVtx[1].diffuse = 
			pVtx[2].diffuse = 
			pVtx[3].diffuse = col; 


		// 頂点データをアンロックする 
		g_pD3DVtxBuffField->Unlock();
	} 
} 

//===========================================================
//パネルの取得
//===========================================================
PANEL *GetPanel(int no)
{
	return &g_aPanel[no];
}

//===========================================================
//パネル番号の計算
//height(引数１)	下(手前)から数えて何番目のパネルか
//width(引数２)		左から数えて何番目のパネルか
//===========================================================
int GetPanelNumber(int height, int width)
{
	return (height-1)*PANEL_NUM_X + (width-1);
}