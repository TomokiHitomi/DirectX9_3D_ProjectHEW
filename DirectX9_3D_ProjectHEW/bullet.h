//-------------------------------------------------------------------
//
// �o���b�g�w�b�_�[[bullet.h]
// Author GP11B243 28 �x������
//
//-------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*******************************************************************
// �}�N����`
//*******************************************************************
#define TEXTURE_BULLET			"data/TEXTURE/bullet000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BULLET_SIZE_X			(50.0f)								// �r���{�[�h�̕�
#define BULLET_SIZE_Y			(50.0f)								// �r���{�[�h�̍���
#define VALUE_MOVE_BULLET		(2.0f)								// �ړ����x

#define MAX_BULLET				(3)									// �o���b�g�̍ő吔
#define BULLET_TYPE				(2)									// �o���b�g�̎��

#define	VALUE_GRAVITY			(0.45f)								// �d��

//*******************************************************************
// �\���̒�`
//*******************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scl;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nIdxShadow;			// �eID
	bool bUse;				// �g�p���Ă��邩�ǂ���
} BULLET;

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY);
void DeleteBullet(int nIdxBullet);




#endif
