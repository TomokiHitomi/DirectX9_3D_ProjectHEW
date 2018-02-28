//=============================================================================
//
// �R���S���� [workYamaguchi.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "workYamaguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// �R���S�����ŕK�v�ȃC���N���[�h
#include "field.h"
#include "wall.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT InitWorkYamaguchi(int nType)
{
	InitField();	//�t�B�[���h
	InitMeshWall(WALL_POS_UP, WALL_ROT_UP, WALL_COL, WALL_NUM_X, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);			//���
	InitMeshWall(WALL_POS_DOWN, WALL_ROT_DOWN, WALL_COL, WALL_NUM_X+2, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);	//����
	InitMeshWall(WALL_POS_RIGHT, WALL_ROT_RIGHT, WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);	//�E��
	InitMeshWall(WALL_POS_LEFT, WALL_ROT_LEFT, WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);		//����
	InitMeshWall(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X, WALL_SIZE_Y, PANEL_NUM_Z*PANEL_SIZE_Z / 2),
		D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f,0.0f), WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);
	InitMeshWall(D3DXVECTOR3(-WALL_SIZE_Y, WALL_SIZE_Y, PANEL_NUM_Z*PANEL_SIZE_Z / 2),
		D3DXVECTOR3(D3DX_PI*0.5f, D3DX_PI*0.5f, 0.0f), WALL_COL, WALL_NUM_Z, WALL_NUM_Y, WALL_SIZE_X, WALL_SIZE_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkYamaguchi(void)
{
	UninitField();	//�t�B�[���h
	UninitMeshWall();//��
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdateField();	//�t�B�[���h
		UpdateMeshWall();//��
		break;
	case STAGE_RESULT:
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawField();	//�t�B�[���h
		DrawMeshWall();//��
		break;
	case STAGE_RESULT:
		break;
	}
}

