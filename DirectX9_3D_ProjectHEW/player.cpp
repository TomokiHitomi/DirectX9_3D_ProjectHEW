//-------------------------------------------------------------------
//
// �v���C���[���� [player.cpp]
// Author : GP11B243 28 �x������
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************

//*******************************************************************
// �O���[�o���ϐ�
//*******************************************************************
LPDIRECT3DTEXTURE9	D3DTexturePlayer/*[PLAYER_MAX]*/;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			D3DXMeshPlayer/*[PLAYER_MAX]*/;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		D3DXMatBuffPlayer/*[PLAYER_MAX]*/;		// ���b�V���̃}�e���A�������i�[
DWORD				NumMatPlayer/*[PLAYER_MAX]*/;			// �������̑���

D3DXMATRIX			MtxWorldPlayer;						// ���[���h�}�g���b�N�X
PLAYER				PlayerWk/*[PLAYER_MAX]*/;				// �v���C���[���[�N

//const char *FileNamePlayer/*[PLAYER_MAX]*/ =
//{
//	"data/MODEL/PLAYER/player01.x",
//	"data/MODEL/PLAYER/player02.x"
//};

//===================================================================
// ����������
//===================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &PlayerWk/*[0]*/;

	//for (int i = 0; i < PLAYER_MAX; i++)
	//{

		D3DTexturePlayer/*[i]*/ = NULL;
		D3DXMeshPlayer/*[i]*/ = NULL;
		D3DXMatBuffPlayer/*[i]*/ = NULL;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_PLAYER/*FileNamePlayer*//*[i]*/,
			D3DXMESH_SYSTEMMEM,
			Device,
			NULL,
			&D3DXMatBuffPlayer/*[i]*/,
			NULL,
			&NumMatPlayer/*[i]*/,
			&D3DXMeshPlayer/*[i]*/)))
		{
			return E_FAIL;
		}

#if 0
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,
			TEXTURE_FILENAME,
			&D3DTexturePlayer);
#endif
	//}

	//�v���C���[�̏���������
	//for (int i = 0; i < PLAYER_MAX; i++, player++)
	//{
		player->use = true;									// use�t���O
		player->pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);		// �ʒu
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �p�x
		player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �X�P�[��
		player->radius = PLAYER_RADIUS;						// ���a
		player->item = 0.0f;								// �A�C�e����0��
	//}
	return S_OK;
}

//===================================================================
// �I������
//===================================================================
void UninitPlayer(void)
{
	//for (int i = 0; i < PLAYER_MAX; i++)
	//{
		if (D3DTexturePlayer != NULL)
		{
			// �e�N�X�`���̊J��
			D3DTexturePlayer/*[i]*/->Release();
			D3DTexturePlayer/*[i]*/ = NULL;
		}

		if (D3DXMeshPlayer != NULL)
		{
			// ���b�V���̊J��
			D3DXMeshPlayer/*[i]*/->Release();
			D3DXMeshPlayer/*[i]*/ = NULL;
		}

		if (D3DXMatBuffPlayer != NULL)
		{
			// �}�e���A���̊J��
			D3DXMatBuffPlayer/*[i]*/->Release();
			D3DXMatBuffPlayer/*[i]*/ = NULL;
		}
	//}
}

//===================================================================
// �X�V����
//===================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &PlayerWk/*[0]*/;
	CAMERA *camera = GetCamera();
	D3DXVECTOR3 rotCamera;

	// �J�����̌����擾
	rotCamera = GetRotCamera();

	bool key = false;

	//�L�[���͂���������
	if (GetKeyboardPress)
	{
		key = true;
	}


	// �ړ�����
	if (GetKeyboardPress(DIK_A))
	{
		player->pos.x -= VALUE_MOVE_PLAYER;
		player->rot.y = rotCamera.y + D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_D))
	{
		player->pos.x += VALUE_MOVE_PLAYER;
		player->rot.y = rotCamera.y - D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_W))
	{
		player->pos.z += VALUE_MOVE_PLAYER;
		player->rot.y = rotCamera.y + D3DX_PI * 1.0f;
	}
	else if (GetKeyboardPress(DIK_S))
	{
		player->pos.z -= VALUE_MOVE_PLAYER;
		player->rot.y = rotCamera.y + D3DX_PI * 0.0f;
	}

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Q))
	{
		player->pos.y += VALUE_MOVE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_E))
	{
		player->pos.y -= VALUE_MOVE_PLAYER;
	}
#endif


#ifdef _DEBUG
	PrintDebugProc("[�v���C���[���W �F(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);
	PrintDebugProc("�v���C���[�ړ� : WASDQE : �O����E�㉺\n");
	PrintDebugProc("\n");
#endif


	////�e���ˏ���
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{


	//}
}

//===================================================================
// �`�揈��
//===================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *D3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER *player = &PlayerWk/*[0]*/;

	//for (int i = 0; i < PLAYER_MAX; i++, player++)
	//{
		if (player->use == true)
		{
			// ���C�g��ON
			Device->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&MtxWorldPlayer);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, player->scl.x, player->scl.y, player->scl.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxScale);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, player->pos.x, player->pos.y, player->pos.z);
			D3DXMatrixMultiply(&MtxWorldPlayer, &MtxWorldPlayer, &mtxTranslate);

			// ���[���h�}�g���N�X�̐ݒ�
			Device->SetTransform(D3DTS_WORLD, &MtxWorldPlayer);

			// ���݂̃}�e���A�����擾
			Device->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			D3DXMat = (D3DXMATERIAL*)D3DXMatBuffPlayer/*[i]*/->GetBufferPointer();

			for (int cntMat = 0; cntMat < (int)NumMatPlayer; cntMat++)
			{
				// �}�e���A���̐ݒ�
				Device->SetMaterial(&D3DXMat[cntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				Device->SetTexture(0, D3DTexturePlayer/*[i]*/);

				// �`��
				D3DXMeshPlayer/*[i]*/->DrawSubset(cntMat);
			}

			// ���C�g��OFF
			Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	//}
	// �}�e���A�����f�t�H���g�ɖ߂�
	{
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		Device->SetMaterial(&mat.MatD3D);
	}

}

//===================================================================
// �v���C���[�擾
//===================================================================
PLAYER *GetPlayer(void/*int no*/)
{
	return &PlayerWk;
}

//===================================================================
// �ʒu�擾
//===================================================================
D3DXVECTOR3 GetPosPlayer(void)
{
	PLAYER *player = &PlayerWk/*[0]*/;
	return player->pos;
}

//===================================================================
// �����擾
//===================================================================
D3DXVECTOR3 GetRotPlayer(void)
{
	PLAYER *player = &PlayerWk/*[0]*/;
	return player->rot;
}
