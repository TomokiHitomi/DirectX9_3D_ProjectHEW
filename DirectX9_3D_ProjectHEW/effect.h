//=============================================================================
//
// EFFECT���� [effect.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT	"data/TEXTURE/effect_bomb.png"
#define EFFECT_MAX			(1)			// �ő吔
#define	EFFECT_SIZE_X		(100.0f)		// �T�C�YX
#define	EFFECT_SIZE_Y		(100.0f)		// �T�C�YY
#define	EFFECT_ALPHA		(30)		// ���e�X�g�l
#define	EFFECT_Y			(100.0f)		// ���e�X�g�l

// �e�N�X�`����������
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(7)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)
// �e�N�X�`�������p�^�[��
#define TEXTURE_PATTERN_NU_EFFECT			(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)
// �A�j���[�V����
#define TIME_ANIMATION_EFFECT			(5)

typedef struct
{
	D3DXVECTOR3			posEffect;			// �ʒu
	D3DXVECTOR3			rotEffect;			// ����(��])
	D3DXVECTOR3			sclEffect;			// �傫��(�X�P�[��)
	D3DXVECTOR2			vec2Size;				// �T�C�Y
	int					nAnimeCount;			// �A�j���[�V�����J�E���g
	int					nAnimePattern;			// �A�j���[�V�����p�^�[��
	bool				bUse;					// �g�p�t���O
}EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int nType);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos);
EFFECT *GetEffect(int no);

#endif
