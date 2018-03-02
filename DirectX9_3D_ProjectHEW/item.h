//=============================================================================
//
// �A�C�e������ [item.h]
// Author : GP11B243-18-���_��
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM				(128)						// �A�C�e���ő吔
#define	MAX_ITEM_POP			(5)							// �A�C�e���������݉\��
#define	NUM_POP					(2)							// SetItem�֐��ň�񓖂���|�b�v�����鐔
#define	ITEM_LIFE				(300)						// �A�C�e���̎���
#define	VALUE_MOVE_ITEM			(0.5f)						// �A�C�e���̈ړ����x
#define	ITEM_SIZE_X				(40.0f)						// �A�C�e���̕�
#define	ITEM_SIZE_Y				(40.0f)						// �A�C�e���̍���
#define	ITEM_POP_FREQUENCY		(60*6)						// �A�C�e���̃|�b�v�p�x(�t���[���~�b��)


//**************************************
// ���
//**************************************
enum
{
	ITEMTYPE_COIN = 0,		// �R�C��
	ITEMTYPE_LIFE,			// ���C�t
	ITEMTYPE_TIMER,			// �^�C�}�[
	ITEMTYPE_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;				// ���݂̈ʒu
	D3DXVECTOR3	rot;				// ���݂̌���
	D3DXVECTOR3	scl;				// �X�P�[��

	float		fRadius;			// ���a
	int			nIdxShadow;			// �eID
	int			nType;				// ���
	int			life;				// ����
	int			no;					// �|�b�v���Ă���p�l���ԍ�
	bool		use;				// �g�p���Ă��邩�ǂ���
} ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, int nType, int life);
ITEM *GetItem(int no);
int GetExistItemNum(void);

#endif
