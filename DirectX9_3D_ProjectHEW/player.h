//-------------------------------------------------------------------
//
// �v���C���[�w�b�_�[[player.h]
// Author : GP11B243 28 �x������
//
//-------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*******************************************************************
// �}�N����`
//*******************************************************************
//#define MODEL_PLAYER		"data/MODEL/PLAYER/player01.x"		// �ǂݍ��ރ��f��
#define PLAYER_RADIUS		(10.0f)								// ���a
#define VALUE_MOVE_PLAYER	(1.5f)								// �ړ����x
#define PLAYER_MAX			(2)									// �v���C���[�̍ő吔

//*******************************************************************
// �\���̐錾
//*******************************************************************
typedef struct		// �v���C���[�\����
{
	bool		use;		// true:�g�p-false:���g�p
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	rot;		// �p�x
	D3DXVECTOR3	scl;		// �X�P�[��
	float		radius;		// ���a
	float		item;		// �A�C�e��
} PLAYER;

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
D3DXVECTOR3 GetPosPlayer(void);
D3DXVECTOR3 GetRotPlayer(void);

#endif