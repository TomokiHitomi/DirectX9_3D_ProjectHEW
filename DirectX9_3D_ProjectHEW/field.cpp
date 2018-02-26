//=============================================================================
//
// �n�ʏ��� [field.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "field.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void SetDiffuseField(int nField, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PANEL					g_aPanel[PANEL_MAX];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PANEL *panel = GetPanel(0);

	MakeVertexField(pDevice);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PANEL,			// �t�@�C���̖��O
			&g_pD3DTextureField);	// �ǂݍ��ރ������[

	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		panel->Pos.x = i % PANEL_NUM_X * PANEL_SIZE_X;	//X���W�̐ݒ�
		panel->Pos.y = 0.0f;							//Y���W��0�Œ�
		panel->Pos.z = i / PANEL_NUM_X * PANEL_SIZE_Z;	//Z���W�̐ݒ�
		panel->PanelNumber = PANEL_NORMAL;				//�p�l���i���o�[�@��{��0
		panel->PanelCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�p�l���J���[ ��{�͔�
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	if (g_pD3DTextureField != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PANEL *panel = GetPanel(0);

	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		//if (panel->PanelNumber == PANEL_1P)	//�p�l���i���o�[��1P�ɕς������
		//{
		//	panel->PanelCol = PANEL_COL_1P;	//�p�l���J���[��1P��
		//}
		//else if (panel->PanelNumber == PANEL_2P)	//�p�l���i���o�[��2P�ɂȂ�����
		//{
		//	panel->PanelCol = PANEL_COL_2P;			//�p�l���J���[��2P��
		//}
		SetDiffuseField(i, panel->PanelCol);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	PANEL *panel = GetPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&panel->mtxWorldField);


		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, panel->Pos.x, panel->Pos.y, panel->Pos.z);
		D3DXMatrixMultiply(&panel->mtxWorldField, &panel->mtxWorldField, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &panel->mtxWorldField);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureField);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < PANEL_MAX; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
			pVtx[1].vtx = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
			pVtx[2].vtx = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
			pVtx[3].vtx = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffField->Unlock();
	}
	
	return S_OK;
}

//============================================================================= 
// ���ˌ��̐ݒ�֐� 
//============================================================================= 
void SetDiffuseField(int nField, D3DXCOLOR col)
{ 
	{// ���_�o�b�t�@�̒��g�𖄂߂� 
		VERTEX_3D *pVtx; 

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾 
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nField * 4);

		// ���_���W�̐ݒ� 
			pVtx[0].diffuse = 
			pVtx[1].diffuse = 
			pVtx[2].diffuse = 
			pVtx[3].diffuse = col; 


		// ���_�f�[�^���A�����b�N���� 
		g_pD3DVtxBuffField->Unlock();
	} 
} 

//===========================================================
//�p�l���̎擾
//===========================================================
PANEL *GetPanel(int no)
{
	return &g_aPanel[no];
}