//-------------------------------------------------------------------
//
// プレイヤー処理 [player.cpp]
// Author : GP11B243 28 堀口昌哉
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "collision.h"
#include "debugproc.h"
#include "enemy.h"
#include "field.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "player.h"
#include "fade.h"

//*******************************************************************
// プロトタイプ宣言
//*******************************************************************
void HitEnemy(void);
void HitItem(void);
void FireBullet(int playernum);

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
		player->use = true;														// useフラグをtrueに
		player->pos = D3DXVECTOR3((i+1)*165.0f, 0.0f, 100.0f);					// 位置
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 角度
		player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);							// スケール
		player->radius = PLAYER_RADIUS;											// 半径
		player->item = 0.0f;													// アイテムを0に
		player->type = i;
		player->oldPos = player->pos;
		player->havetime = 0;
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
		if (player->use)
		{
			player->oldPos.x = player->pos.x;
			player->oldPos.z = player->pos.z;

			// 移動処理
			if (GetKeyboardPress(DIK_A) || IsButtonPressed(i, BUTTON_POV_LEFT) || IsButtonPressed(i, BUTTON_LEFT))
			{
				player->pos.x -= VALUE_MOVE_PLAYER;
				player->rot.y = rotCamera.y + D3DX_PI * 0.5f;
			}
			else if (GetKeyboardPress(DIK_D) || IsButtonPressed(i, BUTTON_POV_RIGHT) || IsButtonPressed(i, BUTTON_RIGHT))
			{
				player->pos.x += VALUE_MOVE_PLAYER;
				player->rot.y = rotCamera.y - D3DX_PI * 0.5f;
			}
			else if (GetKeyboardPress(DIK_W) || IsButtonPressed(i, BUTTON_POV_UP) || IsButtonPressed(i, BUTTON_UP))
			{
				player->pos.z += VALUE_MOVE_PLAYER;
				player->rot.y = rotCamera.y + D3DX_PI * 1.0f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPressed(i, BUTTON_POV_DOWN) || IsButtonPressed(i, BUTTON_DOWN))
			{
				player->pos.z -= VALUE_MOVE_PLAYER;
				player->rot.y = rotCamera.y + D3DX_PI * 0.0f;
			}

			// フィールド外に出てたら戻す処理
			panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));
			if (player->pos.x > panel->Pos.x)
			{
				player->pos.x = player->oldPos.x;
			}
			if (player->pos.z > panel->Pos.z)
			{
				player->pos.z = player->oldPos.z;
			}

			panel = GetPanel(GetPanelNumber(1, 1));
			if (player->pos.x < -panel->Pos.x)
			{
				player->pos.x = player->oldPos.x;
			}
			if (player->pos.z < -panel->Pos.z)
			{
				player->pos.z = player->oldPos.z;
			}

			// 移動先が相手のパネルだったら戻す処理
			panel = GetPanel(0);
			for (int j = 0;j < PANEL_MAX;j++, panel++)
			{
				if (panel->PanelType != PANEL_NORMAL)		// パネルがノーマルじゃないとき
				{
					if (panel->PanelType != i + 1)			// パネルが自色じゃないとき
					{
						//if (CollisionBB(player->pos, panel->Pos, D3DXVECTOR2(PLAYER_SIZE_BOX, PLAYER_SIZE_BOX), D3DXVECTOR2(PANEL_SIZE_X / 2, PANEL_SIZE_Z/  2)))
						if (CollisionBB(player->pos, panel->Pos, D3DXVECTOR2(PLAYER_SIZE_BOX, PLAYER_SIZE_BOX), D3DXVECTOR2(PANEL_SIZE_X / 2, PANEL_SIZE_Z / 2)))
						{
							player->pos.x = player->oldPos.x;
							player->pos.z = player->oldPos.z;
						}
					}
				}
			}

			// デバッグ表示
#ifdef _DEBUG
			PrintDebugProc("[プレイヤー座標 ：(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);

#endif



				// エネミーとの当たり判定
			HitEnemy();

			// アイテム取得
			HitItem();

			if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(i, BUTTON_C))
			{
				if (player->item > 0)
				{
					// 弾発射処理
					FireBullet(i);
				}
			}


			player->item -= 0.003f;
			if (player->item < 0.0f)
			{
				player->item = 0.0f;
			}
			else if (player->item > 3.0f)
			{
				player->item = 3.0f;
			}

		}
	}
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
// エネミーとの当たり判定
//===================================================================
void HitEnemy(void)
{
	// エネミーとぶつかったら
	PLAYER *player = &PlayerWk[0];		// プレイヤー取得
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		ENEMY *enemy = GetEnemy(0);

		if (player->use)
		{
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
						SetStageWinPlayer(i);

						// リザルトへ移行
						SetFade(FADE_OUT, STAGE_RESULT);

						//// SE再生
						//PlaySound(SOUND_LABEL_SE_COIN);
					}
				}
			}
		}
	}
	return;
}

//===================================================================
// アイテムとの当たり判定
//===================================================================
void HitItem(void)
{
	PLAYER *player = &PlayerWk[0];		// プレイヤー取得
	PANEL *panel = GetPanel(0);


	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		ITEM *item = GetItem(0);

		for (int cntItem = 0; cntItem < MAX_ITEM; cntItem++, item++)
		{
			// 当たり判定
			if (item->use == true)
			{
				float length = 0;		// 多分おかしい（でかい）

				length = (player->pos.x - item->pos.x) * (player->pos.x - item->pos.x)
					+ (player->pos.y - item->pos.y) * (player->pos.y - item->pos.y)
					+ (player->pos.z - item->pos.z) * (player->pos.z - item->pos.z);

				if (length < (player->radius + ITEM_SIZE_X) * (player->radius + ITEM_SIZE_X))
				{
					
					if (player->item <= 2.0f)
					{
						//int haveitem = ceil(player->item);	//小数点以下を切りあげ

						//player->item = haveitem + 1.0f;	//所持数を整数に

						player->item += 1.0f;
					}
					

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
	return;
}

//===================================================================
// バレット発射処理
//===================================================================
void FireBullet(int playernum)
{
	PLAYER *player = &PlayerWk[playernum];		// プレイヤー取得

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pos.x = player->pos.x;
			pos.y = player->pos.y + BULLET_HIGHT;
			pos.z = player->pos.z;

			move.x = -sinf(player->rot.y) * VALUE_MOVE_BULLET;
			move.y = BULLET_ANGLE_Y;
			move.z = -cosf(player->rot.y) * VALUE_MOVE_BULLET;

			int item=player->item;	//小数点以下を切り捨て
			
			player->item = item;	//所持数１つ減らす
			player->havetime = 0;

			player->type = playernum;

			SetBullet(pos, move, 20.0f, 20.0f, playernum);

	return;
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

