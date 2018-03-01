//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : GP11B243-18-���_��
//
//=============================================================================
#include "item.h"
#include "field.h"
#include "main.h"
#include "debugproc.h"

//#include "stdlib.h"
//#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE_ITEM		(D3DX_PI * 0.025f)		// ��]���x
#define	ITEM_RADIUS				(10.0f)					// ���a

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureItem[ITEMTYPE_MAX];	// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];	// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatItem[ITEMTYPE_MAX];		// �������̑���

D3DXMATRIX			g_mtxWorldItem;						// ���[���h�}�g���b�N�X

ITEM				itemWk[MAX_ITEM];					// �A�C�e�����[�N

int					poptime;							// �|�b�v����Ԋu
const char *FileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/ITEM/item.x",			// �R�C��
	"data/MODEL/ITEM/item001.x",		// ���C�t
	"data/MODEL/ITEM/item002.x"			// �^�C�}�[
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ITEM *item = &itemWk[0];
	int one = 0;

	for (int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		g_pD3DTextureItem[nCntItemType] = NULL;
		g_pMeshItem[nCntItemType] = NULL;
		g_pD3DXMatBuffItem[nCntItemType] = NULL;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(FileNameItem[nCntItemType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXMatBuffItem[nCntItemType],
			NULL,
			&g_aNumMatItem[nCntItemType],
			&g_pMeshItem[nCntItemType])))
		{
			return E_FAIL;
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,									// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,						// �t�@�C���̖��O
			&g_pD3DTextureModelItem[nCntItemType]);	// �ǂݍ��ރ������[
#endif
	}

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		item->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		item->fRadius = 0.0f;
		item->nIdxShadow = -1;
		item->nType = ITEMTYPE_COIN;
		item->life = 0;
		item->no = PANEL_MAX;
		item->use = false;
	}

	poptime = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	for (int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		if (g_pD3DTextureItem[nCntItemType] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureItem[nCntItemType]->Release();
			g_pD3DTextureItem[nCntItemType] = NULL;
		}

		if (g_pMeshItem[nCntItemType] != NULL)
		{// ���b�V���̊J��
			g_pMeshItem[nCntItemType]->Release();
			g_pMeshItem[nCntItemType] = NULL;
		}

		if (g_pD3DXMatBuffItem[nCntItemType] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXMatBuffItem[nCntItemType]->Release();
			g_pD3DXMatBuffItem[nCntItemType] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	ITEM *item = &itemWk[0];
	PANEL *panel = GetPanel(0);

	if(poptime % 20 == 0)
	{	
		SetItem(D3DXVECTOR3(0.0f, 10.0f, 0.0f), ITEMTYPE_COIN, ITEM_LIFE);
		poptime = 0;
	}
	poptime++;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,item++)
	{
		if (item->use)
		{
			// �A�C�e������]������
			item->rot.y += VALUE_ROTATE_ITEM;
			if (item->rot.y > D3DX_PI)
			{
				item->rot.y -= D3DX_PI * 2.0f;
			}

			// �A�C�e���̎��������炷
			item->life--;

			if (item->life <= 0)
			{	// �A�C�e�������X�ɉ������Ɉړ�
				item->pos.y -= VALUE_MOVE_ITEM;
			}


			//if (item->life <= 0)
			//{	// �������s�����A�C�e��������
			//	item->use = false;
			//}

			// ���S�Ƀt�B�[���h�̉��ɍs���������
			if (item->pos.y < -ITEM_SIZE_Y)
			{
				// �A�C�e��������
				item->use = false;

				// �p�l�����Z�b�g��Ԃ��������Ă�����
				panel[item->no].ItemSet = false;

			}

			// �e�̈ʒu�ݒ�
			//SetPositionShadow(item->nIdxShadow, D3DXVECTOR3(item->pos.x, 0.1f, item->pos.z));

			float fSizeX = 20.0f + (item->pos.y - 10.0f) * 0.05f;
			if (fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (item->pos.y - 10.0f) * 0.05f;
			if (fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			//SetVertexShadow(item->nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (item->pos.y - 10.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			//SetColorShadow(item->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


#ifdef _DEBUG
	PrintDebugProc("[�A�C�e���̐�����]  �F(%d)]\n", GetExistItemNum());
	PrintDebugProc("\n");
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	ITEM *item = &itemWk[0];


	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,item++)
	{
		if (item->use)
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldItem);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, item->rot.y, item->rot.x, item->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, item->pos.x, item->pos.y, item->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldItem);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffItem[item->nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatItem[item->nType]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureItem[item->nType]);

				// �`��
				g_pMeshItem[item->nType]->DrawSubset(nCntMat);
			}

			// ���C�g��off
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		}
	}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
// �����P�F�|�b�v��������W�����p
// �����Q�F�A�C�e���̎��
// �����R�F�A�C�e�����|�b�v���Ă��������܂ł̎���
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nType, int life)
{
	ITEM *item = &itemWk[0];
	PANEL *panel = GetPanel(0);
	int no = 0;		// �p�l���ԍ��i�[
	
	for (int i = 0; i < NUM_POP; i++)
	{	// �A�C�e�����|�b�v�����镪�������[�v

		item = &itemWk[0];

		while (1)
		{
			no = rand() % PANEL_MAX;

			panel = GetPanel(no);

			// �I�΂ꂽ�p�l�����g�p�����ǂ����̃`�F�b�N
			if (!panel->ItemSet)
			{	// ���g�p�Ȃ��

				// �A�C�e���Z�b�g��Ԃɂ���
				panel->ItemSet = true;


				break;
			}

		}

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
		{
			if (!item->use)
			{
				// �A�C�e�����Z�b�g�����p�l���̔ԍ���ۑ�
				item->no = no;

				// �|�b�v�ʒu�̐ݒ�
				item->pos = panel->Pos;		// �����_���őI�񂾃p�l���̍��W�ɃZ�b�g
				// �|�b�v�ʒu�������
				item->pos.x += pos.x;
				item->pos.y += pos.y;
				item->pos.z += pos.z;

				item->fRadius = ITEM_RADIUS;
				item->nType = nType;
				item->life = life;
				item->use = true;

				// �e�̐ݒ�
				//item->nIdxShadow = SetShadow(item->pos, item->fRadius * 2.0f, item->fRadius * 2.0f);

				break;
			}
		}

		// �A�C�e���̐�������MAX�ɂȂ����甲����
		if (GetExistItemNum() >= MAX_ITEM_POP) break;

	}
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
ITEM *GetItem(void)
{
	return &itemWk[0];
}
//=============================================================================
// �A�C�e���̐������擾
//=============================================================================
int GetExistItemNum(void)
{
	ITEM *item = &itemWk[0];
	int Cnt = 0;

	for (int i = 0; i < MAX_ITEM; i++, item++)
	{
		if (item->use)
		{
			Cnt++;
		}
	}

	return Cnt;
}