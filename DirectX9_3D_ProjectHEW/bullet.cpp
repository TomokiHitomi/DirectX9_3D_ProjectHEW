//-------------------------------------------------------------------
//
// バレット処理[bullet.cpp]
// Author GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "field.h"
#include "player.h"

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

bool CheckHitPanelBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
BULLET *GetBullet(int no);

//*******************************************************************
// グローバル変数
//*******************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBullet[BULLET_TYPE];		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffBullet;					// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				MtxWorldBullet;						// ワールドマトリックス

BULLET					BulletWk[BULLET_MAX];				// バレットワーク

char *FileNameBullet[BULLET_TYPE] =
{
	"data/TEXTURE/bullet_R2.png",
	"data/TEXTURE/bullet_B2.png"
};

//===================================================================
// 初期化処理
//===================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BULLET *bullet = GetBullet(0);

	// 頂点情報の作成
	MakeVertexBullet(Device);

	for (int i = 0; i < BULLET_TYPE; i++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,					// デバイスへのポインタ
									FileNameBullet[i],		// ファイルの名前
									&D3DTextureBullet[i]);		// 読み込むメモリー
	}

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		bullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		bullet->fSizeX = BULLET_SIZE_X;
		bullet->fSizeY = BULLET_SIZE_Y;
		bullet->use = false;
		bullet->type = 0;
	}

	return S_OK;
}


//===================================================================
// 終了処理
//===================================================================
void UninitBullet(void)
{
	for (int i = 0;i < BULLET_TYPE;i++)
	{
		if (D3DTextureBullet[i] != NULL)
		{
			// テクスチャの開放
			D3DTextureBullet[i]->Release();
			D3DTextureBullet[i] = NULL;
		}
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
	PLAYER *player = GetPlayer(0);
	D3DXVECTOR3 rotCamera;
	PANEL *panel = GetPanel(0);
	BULLET *bullet = GetBullet(0);

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{

		if (bullet->use)		// バレットが使用中だったら
		{

			bullet->pos.x += bullet->move.x;
			bullet->pos.y += bullet->move.y;
			bullet->pos.z += bullet->move.z;

			bullet->move.y -= VALUE_GRAVITY;


			panel = GetPanel(0);
			for (int cntPanel = 0; cntPanel < PANEL_MAX; cntPanel++, panel++)
			{

				if (bullet->pos.y < 0.0f)
				{
					if (CheckHitPanelBullet(bullet->pos, panel->Pos))
					{
						SetHitPanel(cntPanel, bullet->type);		// パネルの色変更
						DeleteBullet(i);							// バレットの削除
					}
				}
			}
		}
			// デバッグ表示
#ifdef _DEBUG
			PrintDebugProc("[バレット座標 ：(X:%f Y: %f Z: %f)]\n", bullet->pos.x, bullet->pos.y, bullet->pos.z);
			PrintDebugProc("\n");
#endif
	}

}


//===================================================================
// 描画処理
//===================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	BULLET *bullet = GetBullet(0);


	//// ライティングを無効に
	//Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use)
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
			D3DXMatrixScaling(&mtxScale, bullet->scl.x, bullet->scl.y, bullet->scl.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, bullet->pos.x, bullet->pos.y, bullet->pos.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxTranslate);

			// ワールドマトリックスの設定
			Device->SetTransform(D3DTS_WORLD, &MtxWorldBullet);

			// 頂点バッファをデバイスのデータストリームにバインド
			Device->SetStreamSource(0, D3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			Device->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			Device->SetTexture(0, D3DTextureBullet[bullet->type]);

			// ポリゴンの描画
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}
	}

	//// ライティングを有効に
	//Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}




//===================================================================
// 頂点座標の作成
//===================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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

		for (int i = 0; i < BULLET_MAX; i++, pVtx += 4)
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
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int type)
{
	BULLET *bullet = GetBullet(0);

	int nIdxBullet = -1;

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (!bullet->use)
		{
			bullet->pos = pos;
			bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bullet->move = move;
			bullet->fSizeX = fSizeX;
			bullet->fSizeY = fSizeY;
			bullet->use = true;
			bullet->type = type;

			//// 影の設定
			//bullet[i].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// 影の設定

			// 頂点座標の設定
			SetVertexBullet(i, fSizeX, fSizeY);

			nIdxBullet = i;

			break;
		}
	}

	return nIdxBullet;
}

//===================================================================
// バレットとパネルの当たり判定
//
// 引数1 : 着弾時のバレットの座標
// 引数2 : パネルの座標
//===================================================================
bool CheckHitPanelBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	float bulletPosX = pos1.x;
	float bulletPosZ = pos1.z;
	float panelPosX = pos2.x;
	float panelPosZ = pos2.z;

	if (((bulletPosX) >= (panelPosX - PANEL_SIZE_X / 2)) && ((bulletPosX) <= (panelPosX + PANEL_SIZE_X / 2)) &&
		((bulletPosZ) >= (panelPosZ - PANEL_SIZE_Z / 2)) && ((bulletPosZ) <= (panelPosZ + PANEL_SIZE_Z / 2)))
	{
		return true;
	}

	return false;
}

//===================================================================
// 弾の削除
//===================================================================
void DeleteBullet(int nIdxBullet)
{
	BULLET *bullet = GetBullet(nIdxBullet);

	if (nIdxBullet >= 0 && nIdxBullet < BULLET_MAX)
	{
		//DeleteShadow(bullet[nIdxBullet].nIdxShadow);
		bullet->use = false;
		bullet->type = 0;
	}
}

//===================================================================
// バレットの取得
//===================================================================
BULLET *GetBullet(int no)
{
	return &BulletWk[no];
}