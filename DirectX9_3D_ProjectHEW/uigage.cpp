//=============================================================================
//
// UI��ʏ��� [uigage.cpp]
// Author : GP11B243�@32 �R���P��
//
//=============================================================================
#include "uigage.h"

#ifdef _DEBUG
#include "input.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexUigage(LPDIRECT3DDEVICE9 pDevice);
void SetVertexGage(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureUigageframe = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffUigageframe = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureUigage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffUigage = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


GAGE_FRAME				g_Gageframe[MAX_GAGEFRAME];
GAGE					g_Gage[MAX_GAGE];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUigage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE_FRAME *gageframe = GetGageframe(0);
	GAGE *gage = GetGage(0);

	// ���_���̍쐬
	MakeVertexUigage(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAGEFRAME,				// �t�@�C���̖��O
		&g_pD3DTextureUigageframe);		// �ǂݍ��ރ������[

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAGE,				// �t�@�C���̖��O
		&g_pD3DTextureUigage);		// �ǂݍ��ރ������[

	for (int i = 0; i < MAX_GAGEFRAME; i++, gageframe++,gage++)
	{
		//�t���[��
		gageframe->GageframePos.x = SCREEN_CENTER_X - TEXTUER_GAGEFRAME_POS_X+(i*TEXTUER_GAGEFRAME_POS_X*2);//���S����Ώۂ̈ʒu�ɐݒu
		gageframe->GageframePos.y = TEXTUER_GAGEFRAME_POS_Y;
		
		//�Q�[�W
		gage->GagePos.x = gageframe->GageframePos.x- TEXTURE_GAGEFRAME_WIDTH/2+ TEXTURE_GAGEFRAME_WIDTH*i;
		gage->GagePos.y = gageframe->GageframePos.y;//�t���[���Ɠ����ʒu�ɐݒu
		gage->GageLong = TEXTURE_GAGE_WIDTH;
		gage->GageRot = i*D3DX_PI;
		if (i == 0)
		{
			gage->GageCol = SetColorPallet(COLOR_PALLET_RED);
		}
		else if (i == 1)
		{
			gage->GageCol = SetColorPallet(COLOR_PALLET_BLUE);
		}

	}




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUigage(void)
{
	//�t���[��
	if (g_pD3DTextureUigageframe != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureUigageframe->Release();
		g_pD3DTextureUigageframe = NULL;
	}

	if (g_pD3DVtxBuffUigageframe != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffUigageframe->Release();
		g_pD3DVtxBuffUigageframe = NULL;
	}

	//�Q�[�W
	if (g_pD3DTextureUigage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureUigage->Release();
		g_pD3DTextureUigage = NULL;
	}

	if (g_pD3DVtxBuffUigage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffUigage->Release();
		g_pD3DVtxBuffUigage = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUigage(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUigage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAGE_FRAME *gageframe = GetGageframe(0);

	for (int i = 0; i < MAX_GAGEFRAME; i++, gageframe++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffUigageframe, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureUigageframe);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	GAGE *gage = GetGage(0);
	for (int i = 0; i < MAX_GAGE; i++, gage++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffUigage, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureUigage);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexUigage(LPDIRECT3DDEVICE9 pDevice)
{
	//�t���[��

	GAGE_FRAME *gageframe = GetGageframe(0);
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX*MAX_GAGEFRAME,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffUigageframe,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffUigageframe->Lock(0, 0, (void**)&pVtx, 0);


		for (int i = 0; i < MAX_GAGEFRAME; i++,gageframe++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(gageframe->GageframePos.x - TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y - TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(gageframe->GageframePos.x + TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y - TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(gageframe->GageframePos.x - TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y + TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(gageframe->GageframePos.x + TEXTURE_GAGEFRAME_WIDTH / 2, gageframe->GageframePos.y + TEXTURE_GAGEFRAME_HEIGHT / 2, 0.0f);


			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffUigageframe->Unlock();
	}


	GAGE *gage = GetGage(0);
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX*MAX_GAGE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffUigage,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffUigage->Lock(0, 0, (void**)&pVtx, 0);


		for (int i = 0; i < MAX_GAGE; i++, gage++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx.x = gage->GagePos.x;
			pVtx[0].vtx.y = gage->GagePos.y-cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[0].vtx.z = 0.0f;
			
			pVtx[1].vtx.x = gage->GagePos.x+cosf(gage->GageRot)*gage->GageLong;
			pVtx[1].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[1].vtx.z = 0.0f;
			
			pVtx[2].vtx.x = gage->GagePos.x ;
			pVtx[2].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[2].vtx.z = 0.0f;
			
			pVtx[3].vtx.x = gage->GagePos.x +cosf(gage->GageRot)* gage->GageLong;
			pVtx[3].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
			pVtx[3].vtx.z = 0.0f;

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			D3DXCOLOR col;
			col = D3DXCOLOR(gage->GageCol.r, gage->GageCol.g, gage->GageCol.b, 0.6f);
			// ���ˌ��̐ݒ�
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffUigage->Unlock();
	}


	return S_OK;
}

//================================================================
//���W�ݒ�
//================================================================
void SetVertexGage(int no)
{
	GAGE *gage = GetGage(0);

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;


	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffUigage->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += (no * 4);


	// ���_���W�̐ݒ�
	pVtx[0].vtx.x = gage->GagePos.x;
	pVtx[0].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[0].vtx.z = 0.0f;

	pVtx[1].vtx.x = gage->GagePos.x + cosf(gage->GageRot)*gage->GageLong;
	pVtx[1].vtx.y = gage->GagePos.y - cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[1].vtx.z = 0.0f;

	pVtx[2].vtx.x = gage->GagePos.x;
	pVtx[2].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[2].vtx.z = 0.0f;

	pVtx[3].vtx.x = gage->GagePos.x + cosf(gage->GageRot)* gage->GageLong;
	pVtx[3].vtx.y = gage->GagePos.y + cosf(gage->GageRot)*TEXTURE_GAGE_HEIGHT / 2;
	pVtx[3].vtx.z = 0.0f;

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffUigage->Unlock();

}
//================================================================
//�Q�[�W�t���[���̎擾
//================================================================
GAGE_FRAME *GetGageframe(int no)
{
	return &g_Gageframe[no];
}

//================================================================
//�Q�[�W�̎擾
//================================================================
GAGE *GetGage(int no)
{
	return &g_Gage[no];
}