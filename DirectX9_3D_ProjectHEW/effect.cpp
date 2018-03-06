//=============================================================================
//
// EFFECT処理 [effect.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "camera.h"
#include "effect.h"
#include "main.h"
#include "fade.h"
#include "stage.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT	MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void	SetVtxEffect(int nEffect, float fSizeX, float fSizeY);
void	SetDiffuseEffect(int nEffect, D3DXCOLOR col);
void	SetTexEffect(int nEffect, int nTex);
void	InitStatusEffect(int nEffect);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
D3DXMATRIX				g_mtxWorldEffect;			// ワールドマトリックス

EFFECT					effectWk[EFFECT_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(int nType)
{
	EFFECT *effect = &effectWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (nType == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_EFFECT,
			&g_pD3DTextureEffect);
	}

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		// 位置・回転・スケールの設定
		effect->posEffect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->rotEffect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->sclEffect = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		effect->vec2Size = D3DXVECTOR2(EFFECT_SIZE_X, EFFECT_SIZE_Y);
		InitStatusEffect(i);
	}

	// 頂点情報の作成（ローカル座標の設定）
	MakeVertexEffect(pDevice);

	return S_OK;
}

//=============================================================================
// 再利用処理
//=============================================================================
void InitStatusEffect(int nEffect)
{
	EFFECT *effect = &effectWk[nEffect];

	effect->bUse = false;
	effect->nAnimeCount = 0;
	effect->nAnimePattern = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if (g_pD3DTextureEffect != NULL)
	{// テクスチャの開放
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}

	if (g_pD3DVtxBuffEffect != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEffect->Release();
		g_pD3DVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *effect = &effectWk[0];

#ifdef _DEBUG
	PrintDebugProc("【 EFFECT 】\n");
#endif
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{	// 使用中のオブジェクトのみ処理
		if (effect->bUse)
		{

			effect->nAnimeCount++;
			if (effect->nAnimeCount % TIME_ANIMATION_EFFECT == 0)
			{
				// パターンの切り替え
				effect->nAnimePattern = (effect->nAnimePattern + 1) % TEXTURE_PATTERN_NU_EFFECT;
				SetTexEffect(i, effect->nAnimePattern);
				if (effect->nAnimePattern == TEXTURE_PATTERN_NU_EFFECT - 1)
				{
					// リザルトへ移行
					SetFade(FADE_OUT, STAGE_RESULT);
					InitStatusEffect(i);
				}

				//// アニメーション
				//player->nCountAnim++;
				//if ((player->nCountAnim % TIME_ANIMATION_PLAYER) == 0)
				//{
				//	// パターンの切り替え
				//	player->nPatternAnim = (player->nPatternAnim + 1) % (TEXTURE_PATTERN_DIVIDE_X_PLAYER)+(TEXTURE_PATTERN_DIVIDE_X_PLAYER * player->nDirection);
				//}

				//// アニメーション
				//effect_knockdown->nCountAnim++;
				//if ((effect_knockdown->nCountAnim % TIME_ANIMATION_EFFECT_KNOCKDOWN) == 0)
				//{
				//	// パターンの切り替え
				//	effect_knockdown->nPatternAnim++;
				//}

				//// アニメーション終了でfalse
				//if (effect_knockdown->nPatternAnim >= TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN * (effect_knockdown->nTypeAnim + 1))
				//{
				//	effect_knockdown->bUse = false;
				//}
			}
#ifdef _DEBUG
			PrintDebugProc("Effect[%d]  AnimePt[%d]\n"
				, i, effect->nAnimePattern);
#endif
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// スケール, 回転, 平行移動

	EFFECT *effect = &effectWk[0];

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, EFFECT_ALPHA);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->bUse)
		{
			/******************** ワールド変換 ********************/
			// ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			// ビューマトリックスを取得
			mtxView = GetMtxView();
			// ビルボード化
			g_mtxWorldEffect._11 = mtxView._11;
			g_mtxWorldEffect._12 = mtxView._21;
			g_mtxWorldEffect._13 = mtxView._31;
			g_mtxWorldEffect._21 = mtxView._12;
			g_mtxWorldEffect._22 = mtxView._22;
			g_mtxWorldEffect._23 = mtxView._32;
			g_mtxWorldEffect._31 = mtxView._13;
			g_mtxWorldEffect._32 = mtxView._23;
			g_mtxWorldEffect._33 = mtxView._33;

			// 【S】スケールを反映(Multiplyは行列計算)
			D3DXMatrixScaling(&mtxScl, effect->sclEffect.x, effect->sclEffect.y, effect->sclEffect.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxScl);

			//// 【R】回転を反映(YawPitchRollはy,x,z)
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, effect->rotEffect.y, effect->rotEffect.x, effect->rotEffect.z);
			//D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &GetInvRotateMat(effect->posEffect));
			////D3DXMatrixMultiply(&effect->mtxWorld, &effect->mtxWorld, &mtxRot);

			// 【T】平行移動を反映(オブジェクトを配置している）
			D3DXMatrixTranslation(&mtxTranslate, effect->posEffect.x, effect->posEffect.y, effect->posEffect.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTranslate);

			// ワールドマトリクスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);


			/******************** ビューポート変換 ********************/
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}
	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * EFFECT_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffEffect,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{// 頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < EFFECT_MAX; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X, -EFFECT_SIZE_Y, 0.0f);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			int x = 0 % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
			int y = 0 / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
			float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
			float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;
			pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		}
		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 頂点座標の設定関数
//=============================================================================
void SetVtxEffect(int nEffect, float fSizeX, float fSizeY)
{
	{// 頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffect * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX, -fSizeY, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX, fSizeY, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX, -fSizeY, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX, fSizeY, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// 反射光の設定関数
//=============================================================================
void SetDiffuseEffect(int nEffect, D3DXCOLOR col)
{
	{// 頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffect * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定関数
//=============================================================================
void SetTexEffect(int nEffect, int nTex)
{
	{// 頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffect * 4);

		// テクスチャ座標の設定
		int x = nTex % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		int y = nTex / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// バレットを対象に設置
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{
	EFFECT *effect = &effectWk[0];

	// 未使用を探す
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (!effect->bUse)
		{
			effect->bUse = true;
			effect->posEffect = pos;
			return;
		}
	}
}

//=============================================================================
// 取得関数
//=============================================================================
EFFECT *GetEffect(int no)
{
	return(&effectWk[no]);
}