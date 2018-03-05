//-------------------------------------------------------------------
//
// �o���b�g����[bullet.cpp]
// Author GP11B243 28 �x������
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "field.h"
#include "player.h"

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

bool CheckHitPanelBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
BULLET *GetBullet(int no);

//*******************************************************************
// �O���[�o���ϐ�
//*******************************************************************
LPDIRECT3DTEXTURE9		D3DTextureBullet[BULLET_TYPE];		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffBullet;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				MtxWorldBullet;						// ���[���h�}�g���b�N�X

BULLET					BulletWk[BULLET_MAX];				// �o���b�g���[�N

char *FileNameBullet[BULLET_TYPE] =
{
	"data/TEXTURE/bullet_R2.png",
	"data/TEXTURE/bullet_B2.png"
};

//===================================================================
// ����������
//===================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	BULLET *bullet = GetBullet(0);

	// ���_���̍쐬
	MakeVertexBullet(Device);

	for (int i = 0; i < BULLET_TYPE; i++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,					// �f�o�C�X�ւ̃|�C���^
									FileNameBullet[i],		// �t�@�C���̖��O
									&D3DTextureBullet[i]);		// �ǂݍ��ރ������[
	}

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		bullet->move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		bullet->fSizeX = BULLET_SIZE_X;
		bullet->fSizeY = BULLET_SIZE_Y;
		bullet->use = false;
		bullet->type = 0;
	}

	return S_OK;
}


//===================================================================
// �I������
//===================================================================
void UninitBullet(void)
{
	for (int i = 0;i < BULLET_TYPE;i++)
	{
		if (D3DTextureBullet[i] != NULL)
		{
			// �e�N�X�`���̊J��
			D3DTextureBullet[i]->Release();
			D3DTextureBullet[i] = NULL;
		}
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
	PLAYER *player = GetPlayer(0);
	D3DXVECTOR3 rotCamera;
	PANEL *panel = GetPanel(0);
	BULLET *bullet = GetBullet(0);

	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{

		if (bullet->use)		// �o���b�g���g�p����������
		{

			bullet->pos.x += bullet->move.x;
			bullet->pos.y += bullet->move.y;
			bullet->pos.z += bullet->move.z;

			bullet->move.y -= VALUE_GRAVITY;


			panel = GetPanel(0);
			for (int cntPanel = 0; cntPanel < PANEL_MAX; cntPanel++, panel++)
			{

				if (bullet->pos.y < 0.0f)
				{
					if (CheckHitPanelBullet(bullet->pos, panel->Pos))
					{
						SetHitPanel(cntPanel, bullet->type);		// �p�l���̐F�ύX
						DeleteBullet(i);							// �o���b�g�̍폜
					}
				}
			}
		}
			// �f�o�b�O�\��
#ifdef _DEBUG
			PrintDebugProc("[�o���b�g���W �F(X:%f Y: %f Z: %f)]\n", bullet->pos.x, bullet->pos.y, bullet->pos.z);
			PrintDebugProc("\n");
#endif
	}

}


//===================================================================
// �`�揈��
//===================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	BULLET *bullet = GetBullet(0);


	//// ���C�e�B���O�𖳌���
	//Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use)
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
			D3DXMatrixScaling(&mtxScale, bullet->scl.x, bullet->scl.y, bullet->scl.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, bullet->pos.x, bullet->pos.y, bullet->pos.z);
			D3DXMatrixMultiply(&MtxWorldBullet, &MtxWorldBullet, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			Device->SetTransform(D3DTS_WORLD, &MtxWorldBullet);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			Device->SetStreamSource(0, D3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			Device->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, D3DTextureBullet[bullet->type]);

			// �|���S���̕`��
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}
	}

	//// ���C�e�B���O��L����
	//Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}




//===================================================================
// ���_���W�̍쐬
//===================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 Device)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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

		for (int i = 0; i < BULLET_MAX; i++, pVtx += 4)
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
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int type)
{
	BULLET *bullet = GetBullet(0);

	int nIdxBullet = -1;

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (!bullet->use)
		{
			bullet->pos = pos;
			bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bullet->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bullet->move = move;
			bullet->fSizeX = fSizeX;
			bullet->fSizeY = fSizeY;
			bullet->use = true;
			bullet->type = type;

			//// �e�̐ݒ�
			//bullet[i].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexBullet(i, fSizeX, fSizeY);

			nIdxBullet = i;

			break;
		}
	}

	return nIdxBullet;
}

//===================================================================
// �o���b�g�ƃp�l���̓����蔻��
//
// ����1 : ���e���̃o���b�g�̍��W
// ����2 : �p�l���̍��W
//===================================================================
bool CheckHitPanelBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	float bulletPosX = pos1.x;
	float bulletPosZ = pos1.z;
	float panelPosX = pos2.x;
	float panelPosZ = pos2.z;

	if (((bulletPosX) >= (panelPosX - PANEL_SIZE_X / 2)) && ((bulletPosX) <= (panelPosX + PANEL_SIZE_X / 2)) &&
		((bulletPosZ) >= (panelPosZ - PANEL_SIZE_Z / 2)) && ((bulletPosZ) <= (panelPosZ + PANEL_SIZE_Z / 2)))
	{
		return true;
	}

	return false;
}

//===================================================================
// �e�̍폜
//===================================================================
void DeleteBullet(int nIdxBullet)
{
	BULLET *bullet = GetBullet(nIdxBullet);

	if (nIdxBullet >= 0 && nIdxBullet < BULLET_MAX)
	{
		//DeleteShadow(bullet[nIdxBullet].nIdxShadow);
		bullet->use = false;
		bullet->type = 0;
	}
}

//===================================================================
// �o���b�g�̎擾
//===================================================================
BULLET *GetBullet(int no)
{
	return &BulletWk[no];
}