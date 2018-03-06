//=============================================================================
//
// 山口担当分 [workYamaguchi.cpp]
// Author : GP11B243 24 人見友基
//			GP11B243　32 山口輝明
//=============================================================================
#include "workYamaguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 山口担当分で必要なインクルード
#include "field.h"
#include "wall.h"
#include "uiframe.h"
#include "uigage.h"
#include "shadow.h"

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
HRESULT InitWorkYamaguchi(int nType)
{
	InitField(nType);	//フィールド
	InitMeshWall(WALL_POS_UP, WALL_ROT_UP, WALL_COL, WALL_NUM_X+2, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);		//上壁
	InitMeshWall(WALL_POS_DOWN, WALL_ROT_DOWN, WALL_COL, WALL_NUM_X+2, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);	//下壁
	InitMeshWall(WALL_POS_RIGHT, WALL_ROT_RIGHT, WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);	//右壁
	InitMeshWall(WALL_POS_LEFT, WALL_ROT_LEFT, WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);		//左壁
	InitMeshWall(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X-PANEL_SIZE_X / 2, WALL_SIZE_Y, PANEL_NUM_Z*PANEL_SIZE_Z / 2 - PANEL_SIZE_Z / 2),
		D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f,0.0f), WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);
	InitMeshWall(D3DXVECTOR3(-WALL_SIZE_Y - PANEL_SIZE_Z / 2, WALL_SIZE_Y, PANEL_NUM_Z*PANEL_SIZE_Z / 2 - PANEL_SIZE_Z / 2),
		D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y, nType);
	InitUiframe(nType);	//UI画面
	InitUigage(nType);	//UIゲージ
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkYamaguchi(void)
{
	UninitField();	//フィールド
	UninitMeshWall();//壁
	UninitUiframe();//UI画面
	UninitUigage();	//UIゲージ

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdateField();	//フィールド
		UpdateMeshWall();//壁
		UpdateUiframe();//UI画面
		UpdateUigage();	//UIゲージ
		break;
	case STAGE_RESULT:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawField();	//フィールド
		DrawShadow();	// シャドウ
		DrawMeshWall();	//壁
		DrawUiframe();	//UI画面
		DrawUigage();	//UIゲージ
		break;
	case STAGE_RESULT:
		break;
	}
}

