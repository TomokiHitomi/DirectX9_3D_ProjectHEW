//-------------------------------------------------------------------
//
// �o���b�g����[bullet.cpp]
// Author GP11B243 28 �x������
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "field.h"
#include "player.h"

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

//*******************************************************************
// �O���[�o���ϐ�
//*******************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffBullet = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				MtxWorldBullet;				// ���[���h�}�g���b�N�X

BULLET					g_aBullet[MAX_BULLET];			// �o���b�g���[�N

//char *FileNameBullet[BULLET_TYPE] =
//{
//	"data/TEXTURE/bullet_R2.png",
//	"data/TEXTURE/bullet_B2.png"
//};

//===================================================================
// ����������
//===================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_���̍쐬
	MakeVertexBullet(Device);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BULLET,				// �t�@�C���̖��O
								&D3DTextureBullet);		// �ǂݍ��ރ������[

	for (int i = 0; i < MAX_BULLET; i++)
	{
		g_aBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[i].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[i].fSizeX = BULLET_SIZE_X;
		g_aBullet[i].fSizeY = BULLET_SIZE_Y;
		g_aBullet[i].bUse = false;
	}

	return S_OK;
}


//===================================================================
// �I������
//===================================================================
void UninitBullet(void)
{
	if (D3DTextureBullet != NULL)
	{
		// �e�N�X�`���̊J��
		D3DTextureBullet->Release();
		D3DTextureBullet = NULL;
	}

	if (D3DVtxBuffBullet != NULL)
	{
		// ���_�o�b�t�@�̊J��
		D3DVtxBuffBullet->Release();
		D3DVtxBuffBullet = NULL;
	}
}


//===================================================================
// �X�V����
//===================================================================
void UpdateBullet(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	// �v���C���[���擾
	pPlayer = GetPlayer(0);

	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			g_aBullet[i].pos.x += g_aBullet[i].move.x;
			g_aBullet[i].pos.y += g_aBullet[i].move.y;
			g_aBullet[i].pos.z += g_aBullet[i].move.z;

			//g_aBullet[i].move.y -= VALUE_GRAVITY;

			//g_aBullet[i].nTimer--;
			//if (g_aBullet[i].nTimer <= 0)
			//{
			//	//DeleteShadow(g_aBullet[i].nIdxShadow);
			//	g_aBullet[i].bUse = false;
			//}
			//else
			//{
				//// �e�̈ʒu�ݒ�
				//SetPositionShadow(g_aBullet[i].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.1f, g_aBullet[nCntBullet].pos.z));

				//// �G�t�F�N�g�̐ݒ�
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);
				//SetEffect(g_aBullet[i].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//	D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);
			//}

			//if (g_aBullet[i].pos.y < 0.0f)
			//{
			//	
			//	DeleteBullet(i);
			//	//DeleteShadow(g_aBullet[i].nIdxShadow);

			//}

			/*float fSizeX = 8.0f + (g_aBullet[i].pos.y - 4.0f) * 0.05f;
			if (fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aBullet[i].pos.y - 4.0f) * 0.05f;
			if (fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}*/

			//SetVertexShadow(g_aBullet[i].nIdxShadow, fSizeX, fSizeY);

			//float colA = (200.0f - (g_aBullet[i].pos.y - 4.0f)) / 400.0f;
			//if (colA < 0.0f)
			//{
			//	colA = 0.0f;
			//}
			//SetColorShadow(g_aBullet[i].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}
}


//===================================================================
// �`�揈��
//===================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���C�e�B���O�𖳌���
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&MtxWorldBullet);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			MtxWorldBullet._11 = mtxView._11;
			MtxWorldBullet._12 = mtxView._21;
			MtxWorldBullet._13 = mtxView._31;
			MtxWorldBullet._21 = mtxView._12;
			MtxWorldBullet._22 = mtxView._22;
			MtxWorldBullet._23 = mtxView._32;
			MtxWorldBullet._31 = mtxView._13;
			MtxWorldBullet._32 = mtxView._23;
			MtxWorldBullet._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scl.x, g_aBullet[nCntBullet].scl.y, g_aBullet[nCntBullet].scl.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			Device->SetTransform(D3DTS_WORLD, &MtxWorldBullet);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			Device->SetStreamSource(0, D3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			Device->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, D3DTextureBullet);

			// �|���S���̕`��
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBullet * 4), NUM_POLYGON);
		}
	}

	// ���C�e�B���O��L����
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}




//===================================================================
// ���_���W�̍쐬
//===================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
											D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
											FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
											D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
											&D3DVtxBuffBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
											NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_BULLET; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		D3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}



//===================================================================
// ���_���W�̐ݒ�
//===================================================================
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffBullet->Unlock();
	}
}


//===================================================================
// �e�̐ݒ�
//===================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY)
{
	int nIdxBullet = -1;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_aBullet[i].bUse)
		{
			g_aBullet[i].pos = pos;
			g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aBullet[i].move = move;
			g_aBullet[i].fSizeX = fSizeX;
			g_aBullet[i].fSizeY = fSizeY;
			g_aBullet[i].bUse = true;

			//// �e�̐ݒ�
			//g_aBullet[i].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexBullet(i, fSizeX, fSizeY);

			nIdxBullet = i;

			break;
		}
	}

	return nIdxBullet;
}

//===================================================================
// �e�̍폜
//===================================================================
void DeleteBullet(int nIdxBullet)
{
	if (nIdxBullet >= 0 && nIdxBullet < MAX_BULLET)
	{
		//DeleteShadow(g_aBullet[nIdxBullet].nIdxShadow);
		g_aBullet[nIdxBullet].bUse = false;
	}
}
