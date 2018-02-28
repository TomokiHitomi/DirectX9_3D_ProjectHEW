//=============================================================================
//
// ���b�V���ǂ̏��� [wall.h]
// Author : 
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "field.h"

#define	MAX_MESH_WALL		(10)							// �ǂ̑���
#define	TEXTURE_FILENAME	"data/TEXTURE/wall000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	WALL_NUM_X			(PANEL_NUM_X)					//�ǂ̎g�p����
#define	WALL_NUM_Y			(1)								//�ǂ̎g�p����
#define	WALL_NUM_Z			(PANEL_NUM_Z)					//�ǂ̎g�p����

#define	WALL_SIZE_X			(PANEL_SIZE_X)					//�ǂ̃T�C�Y
#define	WALL_SIZE_Y			(50)							//�ǂ̃T�C�Y

#define	WALL_COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))//�ǂ̐F

#define	WALL_POS_UP			(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X/2,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z))	//�ǂ̐ݒu�ʒu�@��
#define	WALL_POS_DOWN		(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X/2,0.0f,0.0f))						//�ǂ̐ݒu�ʒu�@��
#define	WALL_POS_RIGHT		(D3DXVECTOR3(PANEL_NUM_X*PANEL_SIZE_X,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z/2))	//�ǂ̐ݒu�ʒu�@�E
#define	WALL_POS_LEFT		(D3DXVECTOR3(0.0f,0.0f,PANEL_NUM_Z*PANEL_SIZE_Z/2))						//�ǂ̐ݒu�ʒu�@��

#define	WALL_ROT_UP			(D3DXVECTOR3(0.0f,D3DX_PI*0.0f,0.0f))	//�ǂ̌���
#define	WALL_ROT_DOWN		(D3DXVECTOR3(0.0f,D3DX_PI*0.0f,0.0f))	//�ǂ̌���
#define	WALL_ROT_RIGHT		(D3DXVECTOR3(0.0f,D3DX_PI*0.5f,0.0f))	//�ǂ̌���
#define	WALL_ROT_LEFT		(D3DXVECTOR3(0.0f,-D3DX_PI*0.5f,0.0f))	//�ǂ̌���


typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pD3DIdxBuff;			// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;							// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 rot;							// �|���S���̉�]�p
	int nNumBlockX, nNumBlockY;					// �u���b�N��
	int nNumVertex;								// �����_��	
	int nNumVertexIndex;						// ���C���f�b�N�X��
	int nNumPolygon;							// ���|���S����
	float fBlockSizeX, fBlockSizeY;				// �u���b�N�T�C�Y
} MESH_WALL;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
	int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

#endif
