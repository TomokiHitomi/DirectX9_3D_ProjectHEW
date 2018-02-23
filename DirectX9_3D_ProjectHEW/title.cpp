//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "title.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// タイトルで必要なインクルード
#include "titlelogo.h"


// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(int nType)
{
	InitTitlelogo(nType);		// タイトルロゴ
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	UninitTitlelogo();			// タイトルロゴ
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	UpdateTitlelogo();			// タイトルロゴ

	// エンターキーでステージ遷移（テスト）
	if (GetKeyboardPress(DIK_RETURN))
	{
		SetFade(FADE_OUT, STAGE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	DrawTitlelogo();			// タイトルロゴ
}

