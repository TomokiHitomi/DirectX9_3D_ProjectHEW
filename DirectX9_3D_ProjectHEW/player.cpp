//-------------------------------------------------------------------
//
// プレイヤー処理 [player.cpp]
// Author : GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "enemy.h"
#include "field.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "player.h"

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************

//*******************************************************************
// グローバル変数
//*******************************************************************
LPDIRECT3DTEXTURE9	D3DTexturePlayer[PLAYER_MAX];		// テクスチャ読み込み場所
LPD3DXMESH			D3DXMeshPlayer[PLAYER_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		D3DXMatBuffPlayer[PLAYER_MAX];		// メッシュのマテリアル情報を格納
DWORD				NumMatPlayer[PLAYER_MAX];			// 属性情報の総数

D3DXMATRIX			MtxWorldPlayer;						// ワールドマトリックス
PLAYER				PlayerWk[PLAYER_MAX];				// プレイヤーワーク

char *FileNamePlayer[PLAYER_MAX] =
{
	"data/MODEL/PLAYER/player01.x",
	"data/MODEL/PLAYER/player02.x"
};

//===================================================================
// 初期化処理
//===================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &PlayerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++)
	{

		D3DTexturePlayer[i] = NULL;
		D3DXMeshPlayer[i] = NULL;
		D3DXMatBuffPlayer[i] = NULL;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(FileNamePlayer[i],		// モデルデータ
			D3DXMESH_SYSTEMMEM,								// 使用するメモリのオプション
			Device,											// デバイス
			NULL,											// 未使用
			&D3DXMatBuffPlayer[i],							// マテリアルデータへのポインタ
			NULL,											// 未使用
			&NumMatPlayer[i],								// D3DXMATERIAL構造体の数
			&D3DXMeshPlayer[i])))							// メッシュデータへのポインタ
		{
			return E_FAIL;
		}

#if 0
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(Device,
			TEXTURE_FILENAME,
			&D3DTexturePlayer);
#endif
	}

	//プレイヤーの初期化処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;											// useフラグをtrueに
		player->pos = D3DXVECTOR3((i+1)*165.0f, 0.0f, 100.0f);		// 位置
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 角度
		player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// スケール
		player->radius = PLAYER_RADIUS;								// 半径
		player->item = 0.0f;										// アイテムを0に
	}

	return S_OK;
}

//===================================================================
// 終了処理
//===================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (D3DTexturePlayer[i] != NULL)
		{
			// テクスチャの開放
			D3DTexturePlayer[i]->Release();
			D3DTexturePlayer[i] = NULL;
		}

		if (D3DXMeshPlayer[i] != NULL)
		{
			// メッシュの開放
			D3DXMeshPlayer[i]->Release();
			D3DXMeshPlayer[i] = NULL;
		}

		if (D3DXMatBuffPlayer[i] != NULL)
		{
			// マテリアルの開放
			D3DXMatBuffPlayer[i]->Release();
			D3DXMatBuffPlayer[i] = NULL;
		}
	}
}

//===================================================================
// 更新処理
//===================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &PlayerWk[0];
	CAMERA *camera = GetCamera();
	D3DXVECTOR3 rotCamera;
	PANEL *panel = GetPanel(0);


	// カメラの向き取得
	rotCamera = GetRotCamera();

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// 移動処理（移動範囲の制限も同時にやってるけど、違う気がする）
		if (GetKeyboardPress(DIK_A) || IsButtonPressed(i, BUTTON_POV_LEFT) || IsButtonPressed(i, BUTTON_LEFT))
		{
			player->pos.x -= VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 0.5f;

			panel = GetPanel(GetPanelNumber(1, 1));
			if (player->pos.x < -panel->Pos.x)
			{
				player->pos.x = panel->Pos.x;
			}

		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPressed(i, BUTTON_POV_RIGHT) || IsButtonPressed(i, BUTTON_RIGHT))
		{
			player->pos.x += VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y - D3DX_PI * 0.5f;

			panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));
			if (player->pos.x > panel->Pos.x)
			{
				player->pos.x = panel->Pos.x;
			}

		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPressed(i, BUTTON_POV_UP) || IsButtonPressed(i, BUTTON_UP))
		{
			player->pos.z += VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 1.0f;

			panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));
			if (player->pos.z > panel->Pos.z)
			{
				player->pos.z = panel->Pos.z;
			}

		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPressed(i, BUTTON_POV_DOWN) || IsButtonPressed(i, BUTTON_DOWN))
		{
			player->pos.z -= VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 0.0f;

			panel = GetPanel(GetPanelNumber(1, 1));
			if (player->pos.z < -panel->Pos.z)
			{
				player->pos.z = panel->Pos.z;
			}

		}

#ifdef _DEBUG
			PrintDebugProc("[プレイヤー座標 ：(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);
#endif
	}

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Q))
	{
		player->pos.y += VALUE_MOVE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_E))
	{
		player->pos.y -= VALUE_MOVE_PLAYER;
	}
#endif

		// アイテム取得
	player = &PlayerWk[0];		// プレイヤー取得

		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
				ITEM *item = GetItem(0);

				for (int cntItem = 0; cntItem < MAX_ITEM; cntItem++, item++)
				{
					// 当たり判定
					if (item->use == true)
					{
						float length = 0 ;		// 多分おかしい（でかい）

						length = (player->pos.x - item->pos.x) * (player->pos.x - item->pos.x)
								+ (player->pos.y - item->pos.y) * (player->pos.y - item->pos.y)
								+ (player->pos.z - item->pos.z) * (player->pos.z - item->pos.z);

						if (length < (player->radius + ITEM_SIZE_X) * (player->radius + ITEM_SIZE_X))
						{
							// 所持アイテム数の増加
							player->item += 1.0f;

							//// アイテム消去
							item->use = false;

							// パネルをセット状態から解放
							panel[item->no].ItemSet = false;

							//// SE再生
							//PlaySound(SOUND_LABEL_SE_COIN);
						}
					}
				}
		}

		//player = &PlayerWk[0];

	// 弾発射処理
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//pos.x = player->pos.x - sinf(player->rot.y) * 10.0f;
				//pos.y = player->pos.y + 20.0f;
				//pos.z = player->pos.z - cosf(player->rot.y) * 10.0f;

				pos.x = player->pos.x;
				pos.y = player->pos.y + 100.0f;
				pos.z = player->pos.z;

				//move.x = -sinf(player->rot.y) * VALUE_MOVE_BULLET;
				//move.y = 0.0f;
				//move.z = -cosf(player->rot.y) * VALUE_MOVE_BULLET;

				move.x += 0.0f;
				move.x += 0.0f;
				move.z += VALUE_MOVE_BULLET;

				SetBullet(pos, move, 4.0f, 4.0f);

			}
		}

	// エネミーとぶつかったら
	player = &PlayerWk[0];		// プレイヤー取得
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		ENEMY *enemy = GetEnemy(0);

		for (int cntItem = 0; cntItem < MAX_ITEM; cntItem++, enemy++)
		{
			// 当たり判定
			if (enemy->use == true)
			{
				float length = 0;		// 多分おかしい（でかい）

				length = (player->pos.x - enemy->Eye.x) * (player->pos.x - enemy->Eye.x)
					+ (player->pos.y - enemy->Eye.y) * (player->pos.y - enemy->Eye.y)
					+ (player->pos.z - enemy->Eye.z) * (player->pos.z - enemy->Eye.z);

				if (length < (player->radius + ENEMY_SIZE_X) * (player->radius + ENEMY_SIZE_X))
				{
					// プレイヤーを消す
					player->use = false;

					// 残っている方を渡す
					SetStageWinPlayer(i+1);

					//// SE再生
					//PlaySound(SOUND_LABEL_SE_COIN);
				}
			}
		}
	}



		// デバッグ表示
#ifdef _DEBUG
		PrintDebugProc("[プレイヤー座標 ：(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);
		PrintDebugProc("プレイヤー移動 : WSADQE : 前後左右上下\n");
		PrintDebugProc("\n");
#endif

}

//===================================================================
// 描画処理
//===================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *D3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER *player = &PlayerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)
		{
			// ライトをON
			Device->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリクスの初期化
			D3DXMatrixIdentity(&MtxWorldPlayer);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, player->scl.x, player->scl.y, player->scl.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxScale);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, player->pos.x, player->pos.y, player->pos.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxTranslate);

			// ワールドマトリクスの設定
			Device->SetTransform(D3DTS_WORLD, &MtxWorldPlayer);

			// 現在のマテリアルを取得
			Device->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			D3DXMat = (D3DXMATERIAL*)D3DXMatBuffPlayer[i]->GetBufferPointer();

			for (int cntMat = 0; cntMat < (int)NumMatPlayer[i]; cntMat++)
			{
				// マテリアルの設定
				Device->SetMaterial(&D3DXMat[cntMat].MatD3D);

				// テクスチャの設定
				Device->SetTexture(0, D3DTexturePlayer[i]);

				// 描画
				D3DXMeshPlayer[i]->DrawSubset(cntMat);
			}

			// ライトをOFF
			Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}


	// マテリアルをデフォルトに戻す
	{
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		Device->SetMaterial(&mat.MatD3D);
	}

}

//===================================================================
// プレイヤー取得
//===================================================================
PLAYER *GetPlayer(int no)
{
	return &PlayerWk[no];
}

//===================================================================
// 位置取得
//===================================================================
D3DXVECTOR3 GetPosPlayer(int no)
{
	PLAYER *player = &PlayerWk[no];
	return player->pos;
}

//===================================================================
// 向き取得
//===================================================================
D3DXVECTOR3 GetRotPlayer(int no)
{
	PLAYER *player = &PlayerWk[no];
	return player->rot;
}
