//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : GP11B243-18-���_��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE_ENEMY	(0.50f)							// �ړ����x�W��
#define	RATE_MOVE_ENEMY		(0.20f)							// �ړ������W��
#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.05f)				// ��]���x
#define	RATE_ROTATE_ENEMY	(0.20f)							// ��]�����W��

#define	ENEMY_MAX			(1)								// �G�l�~�[�̍ő吔

#define	ENEMY_SIZE_X		(20.0f)							// �G�l�~�[�̕�
#define	ENEMY_SIZE_Y		(20.0f)							// �G�l�~�[�̍���

#define	ENEMY_ANIM_MAX		(12)							// �G�l�~�[�̃A�j���[�V�����p�^�[����
#define	ENEMY_ANIM_SEC		(1)								// �A�j���[�V�����ꏄ�ɂ�����b��

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct		// �G�l�~�[�\����
{
	bool			use;							// true:�g�p  false:���g�p

	D3DXVECTOR3		scl;							// �X�P�[��

	D3DXVECTOR3		EnemyEye;						// �G�l�~�[�̎��_
	D3DXVECTOR3		EnemyAt;						// �G�l�~�[�̒����_
	D3DXVECTOR3		EnemyUp;						// �G�l�~�[�̏����

	VERTEX_2D		vertexWk[NUM_VERTEX];			// ���_���i�[���[�N

	int				anim;							// �A�j���[�V�����ԍ�

} ENEMY;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(int no);

#endif
