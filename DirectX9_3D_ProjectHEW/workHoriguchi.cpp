//=============================================================================
//
// 堀口担当分 [workHoriguchi.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "workHoriguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 堀口担当分で必要なインクルード
#include "player.h"
#include "bullet.h"

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
HRESULT InitWorkHoriguchi(int nType)
{
	InitPlayer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkHoriguchi(void)
{
	UninitPlayer();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkHoriguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdatePlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkHoriguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawPlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

