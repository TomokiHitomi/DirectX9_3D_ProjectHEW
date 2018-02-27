//=============================================================================
//
// �n�ʏ��� [field.h]
// Author : 
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

#define	TEXTURE_PANEL	"data/TEXTURE/panel.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PANEL_NUM_X		(15)						//���ɕ��ׂ閇��
#define	PANEL_NUM_Z		(7)						//�c�ɕ��ׂ閇��
#define	PANEL_MAX		(PANEL_NUM_X*PANEL_NUM_Z)	//�g�p���閇��
#define	PANEL_SIZE_X	(50)						//�p�l���T�C�Y��
#define	PANEL_SIZE_Z	(50)						//�p�l���T�C�Y�c
#define	PANEL_COL_1P	(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))//1P�J���[
#define	PANEL_COL_2P	(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))//2P�J���[

typedef struct
{
	D3DXMATRIX	mtxWorldField;			// ���[���h�}�g���b�N�X

	D3DXVECTOR3	Pos;					//�|�W�V����
	int			PanelNumber;			//�p�l���i���o�[
	D3DXCOLOR	PanelCol;				//�p�l���J���[
}PANEL;

enum PANEL_PATTERN
{
	PANEL_NORMAL,
	PANEL_1P,
	PANEL_2P,
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

PANEL *GetPanel(int no);

#endif
