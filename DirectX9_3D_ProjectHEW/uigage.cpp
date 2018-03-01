//=============================================================================
//
// UI画面処理 [uigage.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "uigage.h"

#ifdef _DEBUG
#include "input.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexUigage(LPDIRECT3DDEVICE9 pDevice);
void SetVertexGage(int no);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureUigageframe = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffUigageframe = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureUigage = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffUigage = NULL;		// 頂点バッファインターフェースへのポインタ


GAGE_FRAME				g_Gageframe[MAX_GAGEFRAME];
GAGE					g_Gage[MAX_GAGE];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUigage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE_FRAME *gageframe = GetGageframe(0);
	GAGE *gage = GetGage(0);

	// 頂点情報の作成
	MakeVertexUigage(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_GAGEFRAME,				// ファイルの名前
		&g_pD3DTextureUigageframe);		// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_GAGE,				// ファイルの名前
		&g_pD3DTextureUigage);		// 読み込むメモリー

	for (int i = 0; i < MAX_GAGEFRAME; i++, gageframe++,gage++)
	{
		//フレーム
		gageframe->GageframePos.x = SCREEN_CENTER_X - TEXTUER_GAGEFRAME_POS_X+(i*TEXTUER_GAGEFRAME_POS_X*2);//中心から対象の位置に設置
		gageframe->GageframePos.y = TEXTUER_GAGEFRAME_POS_Y;
		
		//ゲージ
		gage->GagePos.x = gageframe->GageframePos.x- TEXTURE_GAGEFRAME_WIDTH/2+ TEXTURE_GAGEFRAME_WIDTH*i;
		gage->GagePos.y = gageframe->GageframePos.y;//フレームと同じ位置に設置
		gage->GageLong = TEXTURE_GAGE_WIDTH;
		gage->GageRot = i*D3DX_PI;
		if (i == 0)
		{
			gage->GageCol = SetColorPallet(COLOR_PALLET_RED);
		}
		else if (i == 1)
		{
			gage->GageCol = SetColorPallet(COLOR_PALLET_BLUE);
		}

	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUigage(void)
{
	//フレーム
	if (g_pD3DTextureUigageframe != NULL)
	{// テクスチャの開放
		g_pD3DTextureUigageframe->Release();
		g_pD3DTextureUigageframe = NULL;
	}

	if (g_pD3DVtxBuffUigageframe != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffUigageframe->Release();
		g_pD3DVtxBuffUigageframe = NULL;
	}

	//ゲージ
	if (g_pD3DTextureUigage != NULL)
	{// テクスチャの開放
		g_pD3DTextureUigage->Release();
		g_pD3DTextureUigage = NULL;
	}

	if (g_pD3DVtxBuffUigage != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffUigage->Release();
		g_pD3DVtxBuffUigage = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUigage(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUigage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE_FRAME *gageframe = GetGageframe(0);

	for (int i = 0; i < MAX_GAGEFRAME; i++, gageframe++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffUigageframe, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureUigageframe);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	GAGE *gage = GetGage(0);
	for (int i = 0; i < MAX_GAGE; i++, gage++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffUigage, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureUigage);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexUigage(LPDIRECT3DDEVICE9 pDevice)
{
	//フレーム

	GAGE_FRAME *gageframe = GetGageframe(0);
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX*MAX_GAGEFRAME,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffUigageframe,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffUigageframe->Lock(0, 0, (void**)&pVtx, 0);


		for (int i = 0; i < MAX_GAGEFRAME; i++,gageframe++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(gageframe->GageframePos.x - TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y - TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(gageframe->GageframePos.x + TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y - TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(gageframe->GageframePos.x - TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y + TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(gageframe->GageframePos.x + TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y + TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);


			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffUigageframe->Unlock();
	}


	GAGE *gage = GetGage(0);
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX*MAX_GAGE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffUigage,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffUigage->Lock(0, 0, (void**)&pVtx, 0);


		for (int i = 0; i < MAX_GAGE; i++, gage++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx.x = gage->GagePos.x;
			pVtx[0].vtx.y = gage->GagePos.y-cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[0].vtx.z = 0.0f;
			
			pVtx[1].vtx.x = gage->GagePos.x+cosf(gage->GageRot)*gage->GageLong;
			pVtx[1].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[1].vtx.z = 0.0f;
			
			pVtx[2].vtx.x = gage->GagePos.x ;
			pVtx[2].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[2].vtx.z = 0.0f;
			
			pVtx[3].vtx.x = gage->GagePos.x +cosf(gage->GageRot)* gage->GageLong;
			pVtx[3].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[3].vtx.z = 0.0f;

			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			D3DXCOLOR col;
			col = D3DXCOLOR(gage->GageCol.r, gage->GageCol.g, gage->GageCol.b, 0.6f);
			// 反射光の設定
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffUigage->Unlock();
	}


	return S_OK;
}

//================================================================
//座標設定
//================================================================
void SetVertexGage(int no)
{
	GAGE *gage = GetGage(0);

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;


	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffUigage->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += (no * 4);


	// 頂点座標の設定
	pVtx[0].vtx.x = gage->GagePos.x;
	pVtx[0].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[0].vtx.z = 0.0f;

	pVtx[1].vtx.x = gage->GagePos.x + cosf(gage->GageRot)*gage->GageLong;
	pVtx[1].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[1].vtx.z = 0.0f;

	pVtx[2].vtx.x = gage->GagePos.x;
	pVtx[2].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[2].vtx.z = 0.0f;

	pVtx[3].vtx.x = gage->GagePos.x + cosf(gage->GageRot)* gage->GageLong;
	pVtx[3].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[3].vtx.z = 0.0f;

	// 頂点データをアンロックする
	g_pD3DVtxBuffUigage->Unlock();

}
//================================================================
//ゲージフレームの取得
//================================================================
GAGE_FRAME *GetGageframe(int no)
{
	return &g_Gageframe[no];
}

//================================================================
//ゲージの取得
//================================================================
GAGE *GetGage(int no)
{
	return &g_Gage[no];
}