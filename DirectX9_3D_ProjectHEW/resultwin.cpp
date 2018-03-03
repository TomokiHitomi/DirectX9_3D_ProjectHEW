//=============================================================================
//
// リザルト勝敗画面処理 [resultwin.cpp]
// Author : 
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "resultwin.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/空001.jpg"		// 読み込むテクスチャファイル名

#define	TEXTURE_RESULTLOGO_DEFEAT1	"data/TEXTURE/1p.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RESULTLOGO_DEFEAT2	"data/TEXTURE/2Pwin.png"	// 読み込むテクスチャファイル名

#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_Y	(100)					// リザルトロゴの位置(Y座標
#define	RESULTLOGO_LOGO_DEFEAT1_WIDTH	(800 / 2)					// リザルトロゴの幅
#define	RESULTLOGO_LOGO_DEFEAT1_HEIGHT	(240 / 2)					// リザルトロゴの高さ

#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_Y	(100)					// リザルトロゴの位置(Y座標
#define	RESULTLOGO_LOGO_DEFEAT2_WIDTH	(800 / 2)					// リザルトロゴの幅
#define	RESULTLOGO_LOGO_DEFEAT2_HEIGHT	(240 / 2)					// リザルトロゴの高さ

#define	COUNT_APPERA_RESULTLOGO	(60)		// リザルトロゴ出現までの待ち時間	
#define	LIMIT_COUNT_WAIT	(60 * 5)		// 待ち時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultwin(LPDIRECT3DDEVICE9 pDevice);
void SetColorResultlogowin(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultwin = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultwin = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogowin = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogowin = NULL;	// 頂点バッファインターフェースへのポインタ
int						g_nCountAppearResultwin = 0;		// 出現までの待ち時間
float					g_fAlphaResultwin = 0.0f;			// リザルトロゴのα値
int						g_nCountWaitResultwin = 0;			// 待ち時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultwin(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResultwin = 0;
	g_fAlphaResultwin = 0.0f;
	g_nCountWaitResultwin = 0;

	// 頂点情報の作成
	MakeVertexResultwin(pDevice);

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO,				// ファイルの名前
			&g_pD3DTextureResultwin);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO_DEFEAT1,		// ファイルの名前
			&g_pD3DTextureResultlogowin);	// 読み込むメモリー

	}

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO,				// ファイルの名前
			&g_pD3DTextureResultwin);		// 読み込むメモリー

											// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO_DEFEAT2,		// ファイルの名前
			&g_pD3DTextureResultlogowin);	// 読み込むメモリー

	}





	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultwin(void)
{
	if (g_pD3DTextureResultwin != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultwin->Release();
		g_pD3DTextureResultwin = NULL;
	}

	if (g_pD3DVtxBuffResultwin != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultwin->Release();
		g_pD3DVtxBuffResultwin = NULL;
	}

	if (g_pD3DTextureResultlogowin != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultlogowin->Release();
		g_pD3DTextureResultlogowin = NULL;
	}

	if (g_pD3DVtxBuffResultlogowin != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultlogowin->Release();
		g_pD3DVtxBuffResultlogowin = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultwin(void)
{
	g_nCountAppearResultwin++;
	if (g_nCountAppearResultwin >= COUNT_APPERA_RESULTLOGO)
	{
		if (g_fAlphaResultwin < 1.0f)
		{
			g_fAlphaResultwin += 0.05f;
			if (g_fAlphaResultwin >= 1.0f)
			{
				g_fAlphaResultwin = 1.0f;
			}

			SetColorResultlogowin();
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、フェードアウトしてモードを切り替えいく
		SetFade(FADE_OUT, STAGE_TITLE);
	}

	g_nCountWaitResultwin++;
	if (g_nCountWaitResultwin == LIMIT_COUNT_WAIT)
	{
		SetFade(FADE_OUT, STAGE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultwin(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultwin, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultwin);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogowin, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultlogowin);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultwin(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultwin,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultwin->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultwin->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultlogowin,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X - RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y - RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X + RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y - RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X - RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y + RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X + RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y + RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogowin->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点の作成2
//=============================================================================
HRESULT MakeVertexResultlogowin(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultwin,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultwin->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultwin->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultlogowin,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X - RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y - RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X + RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y - RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X - RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y + RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X + RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y + RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogowin->Unlock();
	}

	return S_OK;
}



//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorResultlogowin(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogowin->Unlock();
	}
}

