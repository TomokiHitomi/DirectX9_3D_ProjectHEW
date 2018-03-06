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
#define PLAYER_RADIUS		(10.0f)			// ���a
#define PLAYER_SIZE_BOX		(5.0f)			// �{�b�N�X�̓����蔻��T�C�Y
#define VALUE_MOVE_PLAYER	(2.0f)			// �ړ����x
#define PLAYER_MAX			(2)				// �v���C���[�̍ő吔

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
	D3DXVECTOR3	oldPos;		// ���W��߂��p

	int			type;		// �v���C���[�ŕ�����

	int			havetime;	//�A�C�e���̏�������
} PLAYER;

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************
HRESULT InitPlayer(int nType);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);
D3DXVECTOR3 GetPosPlayer(int no);
D3DXVECTOR3 GetRotPlayer(int no);

#endif