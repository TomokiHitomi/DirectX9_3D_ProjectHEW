//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#include "item.h"
#include "field.h"
#include "main.h"
#include "debugproc.h"

//#include "stdlib.h"
//#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE_ITEM		(D3DX_PI * 0.025f)		// 回転速度
#define	ITEM_RADIUS				(10.0f)					// 半径

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureItem[ITEMTYPE_MAX];	// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatItem[ITEMTYPE_MAX];		// 属性情報の総数

D3DXMATRIX			g_mtxWorldItem;						// ワールドマトリックス

ITEM				itemWk[MAX_ITEM];					// アイテムワーク

int					poptime;							// ポップする間隔
const char *FileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/ITEM/item.x",			// コイン
	"data/MODEL/ITEM/item001.x",		// ライフ
	"data/MODEL/ITEM/item002.x"			// タイマー
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM *item = &itemWk[0];
	int one = 0;

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		g_pD3DTextureItem[nCntItemType] = NULL;
		g_pMeshItem[nCntItemType] = NULL;
		g_pD3DXMatBuffItem[nCntItemType] = NULL;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(FileNameItem[nCntItemType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXMatBuffItem[nCntItemType],
			NULL,
			&g_aNumMatItem[nCntItemType],
			&g_pMeshItem[nCntItemType])))
		{
			return E_FAIL;
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,									// デバイスへのポインタ
			TEXTURE_FILENAME,						// ファイルの名前
			&g_pD3DTextureModelItem[nCntItemType]);	// 読み込むメモリー
#endif
	}

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		item->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item->fRadius = 0.0f;
		item->nIdxShadow = -1;
		item->nType = ITEMTYPE_COIN;
		item->life = 0;
		item->no = PANEL_MAX;
		item->use = false;
	}

	poptime = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for (int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		if (g_pD3DTextureItem[nCntItemType] != NULL)
		{// テクスチャの開放
			g_pD3DTextureItem[nCntItemType]->Release();
			g_pD3DTextureItem[nCntItemType] = NULL;
		}

		if (g_pMeshItem[nCntItemType] != NULL)
		{// メッシュの開放
			g_pMeshItem[nCntItemType]->Release();
			g_pMeshItem[nCntItemType] = NULL;
		}

		if (g_pD3DXMatBuffItem[nCntItemType] != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffItem[nCntItemType]->Release();
			g_pD3DXMatBuffItem[nCntItemType] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	ITEM *item = &itemWk[0];
	PANEL *panel = GetPanel(0);

	if(poptime % 20 == 0)
	{	
		SetItem(D3DXVECTOR3(0.0f, 10.0f, 0.0f), ITEMTYPE_COIN, ITEM_LIFE);
		poptime = 0;
	}
	poptime++;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,item++)
	{
		if (item->use)
		{
			// アイテムを回転させる
			item->rot.y += VALUE_ROTATE_ITEM;
			if (item->rot.y > D3DX_PI)
			{
				item->rot.y -= D3DX_PI * 2.0f;
			}

			// アイテムの寿命を減らす
			item->life--;

			if (item->life <= 0)
			{	// アイテムを徐々に下方向に移動
				item->pos.y -= VALUE_MOVE_ITEM;
			}


			//if (item->life <= 0)
			//{	// 寿命が尽きたアイテムを消去
			//	item->use = false;
			//}

			// 完全にフィールドの下に行ったら消去
			if (item->pos.y < -ITEM_SIZE_Y)
			{
				// アイテムを消去
				item->use = false;

				// パネルをセット状態から解放してあげる
				panel[item->no].ItemSet = false;

			}

			// 影の位置設定
			//SetPositionShadow(item->nIdxShadow, D3DXVECTOR3(item->pos.x, 0.1f, item->pos.z));

			float fSizeX = 20.0f + (item->pos.y - 10.0f) * 0.05f;
			if (fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (item->pos.y - 10.0f) * 0.05f;
			if (fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			//SetVertexShadow(item->nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (item->pos.y - 10.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			//SetColorShadow(item->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


#ifdef _DEBUG
	PrintDebugProc("[アイテムの生存数]  ：(%d)]\n", GetExistItemNum());
	PrintDebugProc("\n");
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	ITEM *item = &itemWk[0];


	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,item++)
	{
		if (item->use)
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldItem);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, item->rot.y, item->rot.x, item->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, item->pos.x, item->pos.y, item->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldItem);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffItem[item->nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatItem[item->nType]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureItem[item->nType]);

				// 描画
				g_pMeshItem[item->nType]->DrawSubset(nCntMat);
			}

			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		}
	}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// アイテムの設定
// 引数１：ポップさせる座標調整用
// 引数２：アイテムの種類
// 引数３：アイテムがポップしてから消えるまでの時間
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nType, int life)
{
	ITEM *item = &itemWk[0];
	PANEL *panel = GetPanel(0);
	int no = 0;		// パネル番号格納
	
	for (int i = 0; i < NUM_POP; i++)
	{	// アイテムをポップさせる分だけループ

		item = &itemWk[0];

		while (1)
		{
			no = rand() % PANEL_MAX;

			panel = GetPanel(no);

			// 選ばれたパネルが使用中かどうかのチェック
			if (!panel->ItemSet)
			{	// 未使用ならば

				// アイテムセット状態にする
				panel->ItemSet = true;


				break;
			}

		}

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
		{
			if (!item->use)
			{
				// アイテムをセットしたパネルの番号を保存
				item->no = no;

				// ポップ位置の設定
				item->pos = panel->Pos;		// ランダムで選んだパネルの座標にセット
				// ポップ位置を微調整
				item->pos.x += pos.x;
				item->pos.y += pos.y;
				item->pos.z += pos.z;

				item->fRadius = ITEM_RADIUS;
				item->nType = nType;
				item->life = life;
				item->use = true;

				// 影の設定
				//item->nIdxShadow = SetShadow(item->pos, item->fRadius * 2.0f, item->fRadius * 2.0f);

				break;
			}
		}

		// アイテムの生存数がMAXになったら抜ける
		if (GetExistItemNum() >= MAX_ITEM_POP) break;

	}
}
//=============================================================================
// アイテムの取得
//=============================================================================
ITEM *GetItem(void)
{
	return &itemWk[0];
}
//=============================================================================
// アイテムの生存数取得
//=============================================================================
int GetExistItemNum(void)
{
	ITEM *item = &itemWk[0];
	int Cnt = 0;

	for (int i = 0; i < MAX_ITEM; i++, item++)
	{
		if (item->use)
		{
			Cnt++;
		}
	}

	return Cnt;
}