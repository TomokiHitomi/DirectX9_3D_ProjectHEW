//=============================================================================
//
// �n�ʏ��� [field.h]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

#define	TEXTURE_PANEL	"data/TEXTURE/panel.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PANEL_NUM_X		(15)						//���ɕ��ׂ閇��
#define	PANEL_NUM_Z		(7)							//�c�ɕ��ׂ閇��
#define	PANEL_MAX		(PANEL_NUM_X*PANEL_NUM_Z)	//�g�p���閇��
#define	PANEL_SIZE_X	(35)						//�p�l���T�C�Y��
#define	PANEL_SIZE_Z	(PANEL_SIZE_X)				//�p�l���T�C�Y�c



typedef struct
{
	D3DXMATRIX	mtxWorldField;			// ���[���h�}�g���b�N�X

	D3DXVECTOR3	Pos;					//�|�W�V����
	int			PanelType;				//�p�l���^�C�v
	D3DXCOLOR	PanelCol;				//�p�l���J���[

	bool		ItemSet;				//�A�C�e�����Z�b�g����Ă邩�ۂ�
	int			HitFlag;				//�q�b�g�t���O
}PANEL;

typedef struct
{
	D3DXMATRIX	mtxWorldHitPanel;			// ���[���h�}�g���b�N�X

	D3DXVECTOR3	Pos;					//�|�W�V����
	D3DXVECTOR3	Size;					//�T�C�Y
	D3DXCOLOR	HitCol;					//�ύX��̐F
	bool		Use;					//�G�t�F�N�g���o�����ǂ���

}HIT_PANEL;

enum PANEL_TYPE		//�p�l���^�C�v
{
	PANEL_NORMAL,	//�m�[�}���p�l��
	PANEL_1P,		//1P�p�l��
	PANEL_2P,		//2P�p�l��
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(int nType);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

PANEL *GetPanel(int no);
HIT_PANEL *GetHitPanel(int no);

int GetPanelNumber(int height, int width);
void SetHitPanel(int no, int playernum);


#endif
