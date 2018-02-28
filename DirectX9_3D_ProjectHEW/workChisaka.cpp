//=============================================================================
//
// 千坂担当分 [workChisaka.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "workChisaka.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 千坂担当分で必要なインクルード
#include "enemy.h"
#include "item.h"
#include "field.h"

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
HRESULT InitWorkChisaka(int nType)
{
	InitEnemy();
	InitItem();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkChisaka(void)
{
	UninitEnemy();
	UninitItem();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkChisaka(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdateEnemy();
		UpdateItem();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkChisaka(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawEnemy();
		DrawItem();
		break;
	case STAGE_RESULT:
		break;
	}
}

