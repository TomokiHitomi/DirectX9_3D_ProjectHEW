//=============================================================================
//
// ステージ遷移処理 [stage.cpp]
// Author : GP11B243 24 人見友基
//
// タイトル・ゲーム・リザルトの遷移管理
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Stage */
#include "title.h"
#include "game.h"
#include "result.h"

/* Camera */
#include "camera.h"

/* System */
#include "input.h"
#include "sound.h"
#include "light.h"
#include "fade.h"
#include "sound.h"

/* Work */
#include "workChisaka.h"
#include "workHitomi.h"
#include "workHoriguchi.h"
#include "workYamaguchi.h"
#include "workYoshida.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int					g_nStage;				// 初期ステージ
int					g_nPlayerWin;			// 勝利プレイヤー

#ifdef _DEBUG
bool				g_bDispDebug = true;	// デバッグ表示ON/OFF
#endif

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage(HINSTANCE hInstance, HWND hWnd)
{
	// グローバル変数の初期化
	g_nStage = START_STAGE;			// 初期ステージを設定
	g_nPlayerWin = STAGE_WIN_NON;	// 勝利プレイヤーを初期化

	InitInput(hInstance, hWnd);		// 入力
	InitSound(hWnd);				// サウンド
	InitLight();					// ライト
	InitFade();						// フェード
	InitStageEach(STAGE_INIT_FAST);	// 各ステージの初期化

#ifdef _DEBUG
	InitDebugProc();				// デバッグ表示処理の初期化
#endif
	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
HRESULT InitStageEach(int nType)
{
	InitCamera();				// カメラ
	InitTitle(nType);			// タイトル
	InitGame(nType);			// ゲーム
	InitResult(nType);			// リザルト

	InitWorkChisaka(nType);		// 千坂担当分
	InitWorkHitomi(nType);		// 人見担当分
	InitWorkHoriguchi(nType);	// 堀口担当分
	InitWorkYamaguchi(nType);	// 山口担当分
	InitWorkYoshida(nType);		// 吉田担当分
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	UninitCamera();					// カメラ
	UninitInput();					// 入力
	UninitSound();					// サウンド
	UninitFade();					// フェード
	UninitTitle();					// タイトル
	UninitGame();					// ゲーム
	UninitResult();					// リザルト

	UninitWorkChisaka();		// 千坂担当分
	UninitWorkHitomi();			// 人見担当分
	UninitWorkHoriguchi();		// 堀口担当分
	UninitWorkYamaguchi();		// 山口担当分
	UninitWorkYoshida();		// 吉田担当分

#ifdef _DEBUG
	UninitDebugProc();				// デバッグ表示処理の終了処理
#endif
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{	// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	UpdateDebugProc();				// デバッグ

	PrintDebugProc("【 STAGE 】\n");
	switch (g_nStage)
	{
	case STAGE_TITLE:
		PrintDebugProc("%s (%d)\n", STR(STAGE_TITLE), g_nStage);
		break;
	case STAGE_GAME:
		PrintDebugProc("%s (%d)\n", STR(STAGE_GAME), g_nStage);
		break;
	case STAGE_RESULT:
		PrintDebugProc("%s (%d)\n", STR(STAGE_RESULT), g_nStage);
		break;
	}
	PrintDebugProc("\n");
	// SEテスト（sound.hをincludeして関数を呼ぶ）
	if (GetKeyboardTrigger(DIK_1))
	{	// タイトル・リザルト画面の決定ボタン
		SetSe(SE_BUTTON, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_2))
	{	// バレット発射音
		SetSe(SE_BULLET, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_3))
	{	// ゲージが足りないときにMISS音
		SetSe(SE_MISS, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_4))
	{	// エネミーと衝突時の爆発音
		SetSe(SE_BOMB, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_5))
	{	// アイテム取得音
		SetSe(SE_ITEM, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
#endif

	UpdateInput();					// 入力
	UpdateSound();					// サウンド

	// ステージに応じた更新処理
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();				// タイトル
		SetSoundBgm(STAGE_TITLE);
		break;
	case STAGE_GAME:
		UpdateGame();				// ゲーム
		SetSoundBgm(STAGE_GAME);
		break;
	case STAGE_RESULT:
		UpdateResult();				// リザルト
		SetSoundBgm(STAGE_RESULT);
		break;
	}
	UpdateCamera();					// カメラ
	UpdateFade();					// フェード
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	SetCamera();					// カメラの設定処理

									// ステージに応じた描画処理
	switch (g_nStage)
	{
	case STAGE_TITLE:
		DrawTitle();				// タイトル
		break;
	case STAGE_GAME:
		DrawGame();					// ゲーム
		break;
	case STAGE_RESULT:
		DrawResult();				// リザルト
		break;
	}

	DrawFade();						// フェード

#ifdef _DEBUG
	if (g_bDispDebug)
	{	// デバッグ表示する場合
		DrawDebugProc();			// デバッグ
	}
#endif
}

//=============================================================================
// ステージ設定関数
//=============================================================================
void SetStage(int nStage)
{
	g_nStage = nStage;
}

//=============================================================================
// ステージ取得関数
//=============================================================================
int GetStage(void)
{
	return (g_nStage);
}

//=============================================================================
// 勝利プレイヤー設定関数
//=============================================================================
void SetStageWinPlayer(int nPlayer)
{
	g_nPlayerWin = nPlayer;
}

//=============================================================================
// 勝利プレイヤー取得関数
//=============================================================================
int GetStageWinPlayer(void)
{
	return (g_nPlayerWin);
}