//-------------------------------------------------------------------
//
// バレット処理[bullet.cpp]
// Author GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "field.h"
#include "player.h"

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

//*******************************************************************
// グローバル変数
//*******************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBullet = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffBullet = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				MtxWorldBullet;				// ワールドマトリックス

BULLET					g_aBullet[MAX_BULLET];			// バレットワーク

//char *FileNameBullet[BULLET_TYPE] =
//{
//	"data/TEXTURE/bullet_R2.png",
//	"data/TEXTURE/bullet_B2.png"
//};

//===================================================================
// 初期化処理
//===================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点情報の作成
	MakeVertexBullet(Device);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,						// デバイスへのポインタ
								TEXTURE_BULLET,				// ファイルの名前
								&D3DTextureBullet);		// 読み込むメモリー

	for (int i = 0; i < MAX_BULLET; i++)
	{
		g_aBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[i].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[i].fSizeX = BULLET_SIZE_X;
		g_aBullet[i].fSizeY = BULLET_SIZE_Y;
		g_aBullet[i].bUse = false;
	}

	return S_OK;
}


//===================================================================
// 終了処理
//===================================================================
void UninitBullet(void)
{
	if (D3DTextureBullet != NULL)
	{
		// テクスチャの開放
		D3DTextureBullet->Release();
		D3DTextureBullet = NULL;
	}

	if (D3DVtxBuffBullet != NULL)
	{
		// 頂点バッファの開放
		D3DVtxBuffBullet->Release();
		D3DVtxBuffBullet = NULL;
	}
}


//===================================================================
// 更新処理
//===================================================================
void UpdateBullet(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	// プレイヤーを取得
	pPlayer = GetPlayer(0);

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			g_aBullet[i].pos.x += g_aBullet[i].move.x;
			g_aBullet[i].pos.y += g_aBullet[i].move.y;
			g_aBullet[i].pos.z += g_aBullet[i].move.z;

			//g_aBullet[i].move.y -= VALUE_GRAVITY;

			//g_aBullet[i].nTimer--;
			//if (g_aBullet[i].nTimer <= 0)
			//{
			//	//DeleteShadow(g_aBullet[i].nIdxShadow);
			//	g_aBullet[i].bUse = false;
			//}
			//else
			//{
				//// 影の位置設定
				//SetPositionShadow(g_aBullet[i].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.1f, g_aBullet[nCntBullet].pos.z));

				//// エフェクトの設定
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);
			//}

			//if (g_aBullet[i].pos.y < 0.0f)
			//{
			//	
			//	DeleteBullet(i);
			//	//DeleteShadow(g_aBullet[i].nIdxShadow);

			//}

			/*float fSizeX = 8.0f + (g_aBullet[i].pos.y - 4.0f) * 0.05f;
			if (fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aBullet[i].pos.y - 4.0f) * 0.05f;
			if (fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}*/

			//SetVertexShadow(g_aBullet[i].nIdxShadow, fSizeX, fSizeY);

			//float colA = (200.0f - (g_aBullet[i].pos.y - 4.0f)) / 400.0f;
			//if (colA < 0.0f)
			//{
			//	colA = 0.0f;
			//}
			//SetColorShadow(g_aBullet[i].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}
}


//===================================================================
// 描画処理
//===================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ライティングを無効に
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&MtxWorldBullet);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			MtxWorldBullet._11 = mtxView._11;
			MtxWorldBullet._12 = mtxView._21;
			MtxWorldBullet._13 = mtxView._31;
			MtxWorldBullet._21 = mtxView._12;
			MtxWorldBullet._22 = mtxView._22;
			MtxWorldBullet._23 = mtxView._32;
			MtxWorldBullet._31 = mtxView._13;
			MtxWorldBullet._32 = mtxView._23;
			MtxWorldBullet._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scl.x, g_aBullet[nCntBullet].scl.y, g_aBullet[nCntBullet].scl.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxTranslate);

			// ワールドマトリックスの設定
			Device->SetTransform(D3DTS_WORLD, &MtxWorldBullet);

			// 頂点バッファをデバイスのデータストリームにバインド
			Device->SetStreamSource(0, D3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			Device->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			Device->SetTexture(0, D3DTextureBullet);

			// ポリゴンの描画
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBullet * 4), NUM_POLYGON);
		}
	}

	// ライティングを有効に
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}




//===================================================================
// 頂点座標の作成
//===================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// 頂点データ用に確保するバッファサイズ(バイト単位)
											D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
											FVF_VERTEX_3D,								// 使用する頂点フォーマット
											D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
											&D3DVtxBuffBullet,						// 頂点バッファインターフェースへのポインタ
											NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_BULLET; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// 法線の設定
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
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		D3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}



//===================================================================
// 頂点座標の設定
//===================================================================
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBuffBullet->Unlock();
	}
}


//===================================================================
// 弾の設定
//===================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY)
{
	int nIdxBullet = -1;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_aBullet[i].bUse)
		{
			g_aBullet[i].pos = pos;
			g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aBullet[i].move = move;
			g_aBullet[i].fSizeX = fSizeX;
			g_aBullet[i].fSizeY = fSizeY;
			g_aBullet[i].bUse = true;

			//// 影の設定
			//g_aBullet[i].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// 影の設定

			// 頂点座標の設定
			SetVertexBullet(i, fSizeX, fSizeY);

			nIdxBullet = i;

			break;
		}
	}

	return nIdxBullet;
}

//===================================================================
// 弾の削除
//===================================================================
void DeleteBullet(int nIdxBullet)
{
	if (nIdxBullet >= 0 && nIdxBullet < MAX_BULLET)
	{
		//DeleteShadow(g_aBullet[nIdxBullet].nIdxShadow);
		g_aBullet[nIdxBullet].bUse = false;
	}
}
