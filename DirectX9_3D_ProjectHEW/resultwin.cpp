//=============================================================================
//
// ���U���g���s��ʏ��� [resultwin.cpp]
// Author : 
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "resultwin.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/��001.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_RESULTLOGO_DEFEAT1	"data/TEXTURE/1p.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULTLOGO_DEFEAT2	"data/TEXTURE/2Pwin.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	TEXTURE_RESULTLOGO_DEFEAT1_POS_Y	(100)					// ���U���g���S�̈ʒu(Y���W
#define	RESULTLOGO_LOGO_DEFEAT1_WIDTH	(800 / 2)					// ���U���g���S�̕�
#define	RESULTLOGO_LOGO_DEFEAT1_HEIGHT	(240 / 2)					// ���U���g���S�̍���

#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	TEXTURE_RESULTLOGO_DEFEAT2_POS_Y	(100)					// ���U���g���S�̈ʒu(Y���W
#define	RESULTLOGO_LOGO_DEFEAT2_WIDTH	(800 / 2)					// ���U���g���S�̕�
#define	RESULTLOGO_LOGO_DEFEAT2_HEIGHT	(240 / 2)					// ���U���g���S�̍���

#define	COUNT_APPERA_RESULTLOGO	(60)		// ���U���g���S�o���܂ł̑҂�����	
#define	LIMIT_COUNT_WAIT	(60 * 5)		// �҂�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultwin(LPDIRECT3DDEVICE9 pDevice);
void SetColorResultlogowin(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultwin = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultwin = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogowin = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogowin = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
int						g_nCountAppearResultwin = 0;		// �o���܂ł̑҂�����
float					g_fAlphaResultwin = 0.0f;			// ���U���g���S�̃��l
int						g_nCountWaitResultwin = 0;			// �҂�����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultwin(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResultwin = 0;
	g_fAlphaResultwin = 0.0f;
	g_nCountWaitResultwin = 0;

	// ���_���̍쐬
	MakeVertexResultwin(pDevice);

	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO,				// �t�@�C���̖��O
			&g_pD3DTextureResultwin);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO_DEFEAT1,		// �t�@�C���̖��O
			&g_pD3DTextureResultlogowin);	// �ǂݍ��ރ������[

	}

	if (nType == STAGE_INIT_FAST)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO,				// �t�@�C���̖��O
			&g_pD3DTextureResultwin);		// �ǂݍ��ރ������[

											// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RESULTLOGO_DEFEAT2,		// �t�@�C���̖��O
			&g_pD3DTextureResultlogowin);	// �ǂݍ��ރ������[

	}





	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultwin(void)
{
	if (g_pD3DTextureResultwin != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultwin->Release();
		g_pD3DTextureResultwin = NULL;
	}

	if (g_pD3DVtxBuffResultwin != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultwin->Release();
		g_pD3DVtxBuffResultwin = NULL;
	}

	if (g_pD3DTextureResultlogowin != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultlogowin->Release();
		g_pD3DTextureResultlogowin = NULL;
	}

	if (g_pD3DVtxBuffResultlogowin != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultlogowin->Release();
		g_pD3DVtxBuffResultlogowin = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultwin(void)
{
	g_nCountAppearResultwin++;
	if (g_nCountAppearResultwin >= COUNT_APPERA_RESULTLOGO)
	{
		if (g_fAlphaResultwin < 1.0f)
		{
			g_fAlphaResultwin += 0.05f;
			if (g_fAlphaResultwin >= 1.0f)
			{
				g_fAlphaResultwin = 1.0f;
			}

			SetColorResultlogowin();
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�t�F�[�h�A�E�g���ă��[�h��؂�ւ�����
		SetFade(FADE_OUT, STAGE_TITLE);
	}

	g_nCountWaitResultwin++;
	if (g_nCountWaitResultwin == LIMIT_COUNT_WAIT)
	{
		SetFade(FADE_OUT, STAGE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultwin(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultwin, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultwin);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogowin, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultlogowin);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultwin(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultwin,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultwin->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultwin->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultlogowin,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X - RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y - RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X + RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y - RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X - RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y + RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT1_POS_X + RESULTLOGO_LOGO_DEFEAT1_WIDTH, TEXTURE_RESULTLOGO_DEFEAT1_POS_Y + RESULTLOGO_LOGO_DEFEAT1_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogowin->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_�̍쐬2
//=============================================================================
HRESULT MakeVertexResultlogowin(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultwin,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultwin->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultwin->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultlogowin,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X - RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y - RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X + RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y - RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X - RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y + RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_RESULTLOGO_DEFEAT2_POS_X + RESULTLOGO_LOGO_DEFEAT2_WIDTH, TEXTURE_RESULTLOGO_DEFEAT2_POS_Y + RESULTLOGO_LOGO_DEFEAT2_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogowin->Unlock();
	}

	return S_OK;
}



//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorResultlogowin(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultlogowin->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultwin);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultlogowin->Unlock();
	}
}

