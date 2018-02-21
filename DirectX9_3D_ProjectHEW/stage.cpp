//=============================================================================
//
// Stage処理 [stage.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Stage */
#include "title.h"



/* Camera */
#include "camera.h"

/* System */
#include "sound.h"
#include "light.h"
#include "input.h"
#include "fade.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
STAGE_SYS					stageSysWk;

int					g_nStage = START_STAGE;	// ステージ

#ifdef _DEBUG
bool				g_bDispDebug = true;	// デバッグ表示ON/OFF
#endif

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage(HINSTANCE hInstance, HWND hWnd)
{
	InitInput(hInstance, hWnd);		// 入力
	InitSound(hWnd);				// サウンド
	InitFade();						// フェード
#ifdef _DEBUG
	InitDebugProc();				// デバッグ表示処理の初期化
#endif

	InitTitle(0);					// タイトル
	InitLight();				// ライト
	InitCamera();					// カメラ
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	UninitInput();					// 入力の終了処理
	UninitSound();					// サウンド
	UninitFade();					// フェード

#ifdef _DEBUG
	UninitDebugProc();				// デバッグ表示処理の終了処理
#endif

	UninitTitle();					// タイトル
	UninitCamera();					// カメラ
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
	UpdateInput();					// 入力の更新処理

	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle;				// タイトル
		break;
	case STAGE_GAME:
		break;
	case STAGE_RESULT:
		break;
	}
	UpdateCamera();					// カメラ

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	UpdateDebugProc();				// デバッグ
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	SetCamera();					// カメラの設定処理
	DrawTitle();					// タイトル
	DrawFade();						// フェード

#ifdef _DEBUG
	if (g_bDispDebug)
	{	// デバッグ表示する場合
		DrawDebugProc();			// デバッグ
	}
#endif
}




//=============================================================================
// 取得関数
//=============================================================================
STAGE_SYS *GetStageSys(void)
{
	return(&stageSysWk);
}

//=============================================================================
// カウント取得関数
//=============================================================================
void SetResultTime(int nTime)
{
	STAGE_SYS *stageSys = &stageSysWk;
	stageSys->nTime = nTime;
}

//=============================================================================
// カウント取得関数
//=============================================================================
int GetResultTime(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->nTime);
}

//=============================================================================
// クリアフラグ取得関数
//=============================================================================
void SetClearFlag(bool bClearFlag)
{
	STAGE_SYS *stageSys = &stageSysWk;
	stageSys->bClearFlag = bClearFlag;
	stageSys->bEndFlag = true;
}

//=============================================================================
// クリアフラグ取得関数
//=============================================================================
bool GetClearFlag(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->bClearFlag);
}

//=============================================================================
// 終了フラグ取得関数
//=============================================================================
bool GetEndFlag(void)
{
	STAGE_SYS *stageSys = &stageSysWk;
	return(stageSys->bEndFlag);
}