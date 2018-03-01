//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "enemy.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetEnemyAnimation(int sec);
D3DXMATRIX* EnemyLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy[ENEMY_ANIM_MAX];			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshEnemy[ENEMY_ANIM_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatEnemy[ENEMY_ANIM_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatEnemy[ENEMY_ANIM_MAX];				// 属性情報の総数

D3DXMATRIX			g_mtxWorldEnemy;			// ワールドマトリックス

float				g_fSizeShadowE;				// 影のサイズ
D3DXCOLOR			g_colShadowE;				// 影の色

ENEMY				enemyWk[ENEMY_MAX];		// エネミー格納ワーク

int					animCnt;		// アニメカウント

const char *FileNameEnemy[ENEMY_ANIM_MAX] =
{
	"data/MODEL/ENEMY/enemy_a00.x",		// 直立
	"data/MODEL/ENEMY/enemy_a01.x",		// 左足前１
	"data/MODEL/ENEMY/enemy_a02.x",		// 左足前２
	"data/MODEL/ENEMY/enemy_a03.x",		// 左足前３
	"data/MODEL/ENEMY/enemy_a02.x",		// 左足前２
	"data/MODEL/ENEMY/enemy_a01.x",		// 左足前１
	"data/MODEL/ENEMY/enemy_a00.x",		// 直立
	"data/MODEL/ENEMY/enemy_a11.x",		// 右足前１
	"data/MODEL/ENEMY/enemy_a12.x",		// 右足前２
	"data/MODEL/ENEMY/enemy_a13.x",		// 右足前３
	"data/MODEL/ENEMY/enemy_a12.x",		// 右足前２
	"data/MODEL/ENEMY/enemy_a11.x"		// 右足前１

};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];


	for (int nCntEnemyAnim = 0; nCntEnemyAnim < ENEMY_ANIM_MAX; nCntEnemyAnim++)
	{
		g_pD3DTextureEnemy[nCntEnemyAnim] = NULL;
		g_pD3DXMeshEnemy[nCntEnemyAnim] = NULL;
		g_pD3DXBuffMatEnemy[nCntEnemyAnim] = NULL;


		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(FileNameEnemy[nCntEnemyAnim],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatEnemy[nCntEnemyAnim],
			NULL,
			&g_nNumMatEnemy[nCntEnemyAnim],
			&g_pD3DXMeshEnemy[nCntEnemyAnim])))
		{
			return E_FAIL;
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FILENAME,		// ファイルの名前
			&g_pD3DTextureModel);	// 読み込むメモリー
#endif

	}

	// エネミーの初期化処理
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// エネミーの視点の初期化
		enemy->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// エネミーの注視点の初期化
		enemy->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// エネミーの上方向の初期化
		enemy->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// エネミーの向きの初期化
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// エネミーの移動量の初期化
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// エネミーのスケールの初期化
		enemy->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// useフラグをtrueに設定
		enemy->use = true;

		// アニメーション番号初期化
		// 最初は直立状態に設定
		enemy->anim = 0;

		// アニメーションカウント初期化
		animCnt = 0;
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemyAnim = 0; nCntEnemyAnim < ENEMY_ANIM_MAX; nCntEnemyAnim++)
	{
		if (g_pD3DTextureEnemy[nCntEnemyAnim] != NULL)
		{// テクスチャの開放
			g_pD3DTextureEnemy[nCntEnemyAnim]->Release();
			g_pD3DTextureEnemy[nCntEnemyAnim] = NULL;
		}

		if (g_pD3DXMeshEnemy[nCntEnemyAnim] != NULL)
		{// メッシュの開放
			g_pD3DXMeshEnemy[nCntEnemyAnim]->Release();
			g_pD3DXMeshEnemy[nCntEnemyAnim] = NULL;
		}

		if (g_pD3DXBuffMatEnemy[nCntEnemyAnim] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatEnemy[nCntEnemyAnim]->Release();
			g_pD3DXBuffMatEnemy[nCntEnemyAnim] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	CAMERA *camera = GetCamera();


	// エネミーの座標ををカメラの注視点にセット
	//enemy->Eye = camera->posCameraAt;

	// エネミーの注視点をカメラの注視点にセット
	enemy->At = camera->posCameraAt;

	// アニメーション
	SetEnemyAnimation(ENEMY_ANIM_SEC);

#ifdef _DEBUG
	// デバッグ時に手動でエネミー移動
	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 左前移動
			enemy->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 左後移動
			enemy->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else
		{// 左移動
			enemy->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 右前移動
			enemy->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 右後移動
			enemy->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else
		{// 右移動
			enemy->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// 前移動
		enemy->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		enemy->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// 後移動
		enemy->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		enemy->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
	}

	// 移動量に慣性をかける
	enemy->move.x += (0.0f - enemy->move.x) * RATE_MOVE_ENEMY;
	enemy->move.y += (0.0f - enemy->move.y) * RATE_MOVE_ENEMY;
	enemy->move.z += (0.0f - enemy->move.z) * RATE_MOVE_ENEMY;

	//if (enemy->Eye.x < -310.0f)
	//{
	//	enemy->Eye.x = -310.0f;
	//}
	//if (enemy->Eye.x > 310.0f)
	//{
	//	enemy->Eye.x = 310.0f;
	//}
	//if (enemy->Eye.z < -310.0f)
	//{
	//	enemy->Eye.z = -310.0f;
	//}
	//if (enemy->Eye.z > 310.0f)
	//{
	//	enemy->Eye.z = 310.0f;
	//}


	/// 位置移動
	enemy->Eye.x += enemy->move.x;
	enemy->Eye.y += enemy->move.y;
	//if (enemy->Eye.y < 5.0f)
	//{
	//	enemy->Eye.y = 5.0f;
	//}
	//if (enemy->Eye.y > 75.0f)
	//{
	//	enemy->Eye.y = 75.0f;
	//}
	enemy->Eye.z += enemy->move.z;

#endif

	enemy = &enemyWk[0];
#ifdef _DEBUG
	PrintDebugProc("[エネミーの位置  ：(%f : %f : %f)]\n", enemy->Eye.x, enemy->Eye.y, enemy->Eye.z);
	//PrintDebugProc("\n");
#endif


}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	ENEMY *enemy = &enemyWk[0];

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)	// 使用状態なら描画する
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, enemy->scl.x,
				enemy->scl.y,
				enemy->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy,
				&g_mtxWorldEnemy, &mtxScale);


			// 回転を反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
			//D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);
			EnemyLookAtMatrix(&mtxRot, &enemy->Eye, &enemy->At, &enemy->Up);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);
			
			//// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemy->Eye.x, enemy->Eye.y, enemy->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			// 今は直立を設定してる０
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemy[enemy->anim]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy[enemy->anim]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemy[enemy->anim]);

				// 描画
				g_pD3DXMeshEnemy[enemy->anim]->DrawSubset(nCntMat);

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
// エネミー取得関数
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}
//=============================================================================
// エネミーの回転行列算出関数
//=============================================================================
D3DXMATRIX* EnemyLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pAt - *pEye;
	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));


	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

	return pout;
}
//=============================================================================
// エネミーアニメーション設定関数（引数：アニメーション一巡にかかる秒数）
//=============================================================================
void SetEnemyAnimation(int sec)
{
	ENEMY *enemy = &enemyWk[0];

	// アニメーションカウント
	animCnt++;

	// 秒数の絶対値を求める
	sec = abs(sec);

	// アニメーションを切り替えるフレーム数を求める
	sec = (60 * sec) / ENEMY_ANIM_MAX;

	if (animCnt % sec == 0)
	{	// アニメーションを切り替える
		enemy->anim++;
		if (enemy->anim >= ENEMY_ANIM_MAX)
		{	// 一巡したら最初に戻す
			enemy->anim = 0;
		}
	}

}