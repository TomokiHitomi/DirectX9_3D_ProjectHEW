//-------------------------------------------------------------------
//
// �v���C���[���� [player.cpp]
// Author : GP11B243 28 �x������
//
//-------------------------------------------------------------------
#include "bullet.h"
#include "camera.h"
#include "debugproc.h"
#include "enemy.h"
#include "field.h"
#include "input.h"
#include "item.h"
#include "stage.h"
#include "player.h"

//*******************************************************************
// �v���g�^�C�v�錾
//*******************************************************************

//*******************************************************************
// �O���[�o���ϐ�
//*******************************************************************
LPDIRECT3DTEXTURE9	D3DTexturePlayer[PLAYER_MAX];		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			D3DXMeshPlayer[PLAYER_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		D3DXMatBuffPlayer[PLAYER_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				NumMatPlayer[PLAYER_MAX];			// �������̑���

D3DXMATRIX			MtxWorldPlayer;						// ���[���h�}�g���b�N�X
PLAYER				PlayerWk[PLAYER_MAX];				// �v���C���[���[�N

char *FileNamePlayer[PLAYER_MAX] =
{
	"data/MODEL/PLAYER/player01.x",
	"data/MODEL/PLAYER/player02.x"
};

//===================================================================
// ����������
//===================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	PLAYER *player = &PlayerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++)
	{

		D3DTexturePlayer[i] = NULL;
		D3DXMeshPlayer[i] = NULL;
		D3DXMatBuffPlayer[i] = NULL;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(FileNamePlayer[i],		// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,								// �g�p���郁�����̃I�v�V����
			Device,											// �f�o�C�X
			NULL,											// ���g�p
			&D3DXMatBuffPlayer[i],							// �}�e���A���f�[�^�ւ̃|�C���^
			NULL,											// ���g�p
			&NumMatPlayer[i],								// D3DXMATERIAL�\���̂̐�
			&D3DXMeshPlayer[i])))							// ���b�V���f�[�^�ւ̃|�C���^
		{
			return E_FAIL;
		}

#if 0
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(Device,
			TEXTURE_FILENAME,
			&D3DTexturePlayer);
#endif
	}

	//�v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;											// use�t���O��true��
		player->pos = D3DXVECTOR3((i+1)*165.0f, 0.0f, 100.0f);		// �ʒu
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �p�x
		player->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// �X�P�[��
		player->radius = PLAYER_RADIUS;								// ���a
		player->item = 0.0f;										// �A�C�e����0��
	}

	return S_OK;
}

//===================================================================
// �I������
//===================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (D3DTexturePlayer[i] != NULL)
		{
			// �e�N�X�`���̊J��
			D3DTexturePlayer[i]->Release();
			D3DTexturePlayer[i] = NULL;
		}

		if (D3DXMeshPlayer[i] != NULL)
		{
			// ���b�V���̊J��
			D3DXMeshPlayer[i]->Release();
			D3DXMeshPlayer[i] = NULL;
		}

		if (D3DXMatBuffPlayer[i] != NULL)
		{
			// �}�e���A���̊J��
			D3DXMatBuffPlayer[i]->Release();
			D3DXMatBuffPlayer[i] = NULL;
		}
	}
}

//===================================================================
// �X�V����
//===================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &PlayerWk[0];
	CAMERA *camera = GetCamera();
	D3DXVECTOR3 rotCamera;
	PANEL *panel = GetPanel(0);


	// �J�����̌����擾
	rotCamera = GetRotCamera();

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// �ړ������i�ړ��͈͂̐����������ɂ���Ă邯�ǁA�Ⴄ�C������j
		if (GetKeyboardPress(DIK_A) || IsButtonPressed(i, BUTTON_POV_LEFT) || IsButtonPressed(i, BUTTON_LEFT))
		{
			player->pos.x -= VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 0.5f;

			panel = GetPanel(GetPanelNumber(1, 1));
			if (player->pos.x < -panel->Pos.x)
			{
				player->pos.x = panel->Pos.x;
			}

		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPressed(i, BUTTON_POV_RIGHT) || IsButtonPressed(i, BUTTON_RIGHT))
		{
			player->pos.x += VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y - D3DX_PI * 0.5f;

			panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));
			if (player->pos.x > panel->Pos.x)
			{
				player->pos.x = panel->Pos.x;
			}

		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPressed(i, BUTTON_POV_UP) || IsButtonPressed(i, BUTTON_UP))
		{
			player->pos.z += VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 1.0f;

			panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));
			if (player->pos.z > panel->Pos.z)
			{
				player->pos.z = panel->Pos.z;
			}

		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPressed(i, BUTTON_POV_DOWN) || IsButtonPressed(i, BUTTON_DOWN))
		{
			player->pos.z -= VALUE_MOVE_PLAYER;
			player->rot.y = rotCamera.y + D3DX_PI * 0.0f;

			panel = GetPanel(GetPanelNumber(1, 1));
			if (player->pos.z < -panel->Pos.z)
			{
				player->pos.z = panel->Pos.z;
			}

		}

#ifdef _DEBUG
			PrintDebugProc("[�v���C���[���W �F(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);
#endif
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

		// �A�C�e���擾
	player = &PlayerWk[0];		// �v���C���[�擾

		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
				ITEM *item = GetItem(0);

				for (int cntItem = 0; cntItem < MAX_ITEM; cntItem++, item++)
				{
					// �����蔻��
					if (item->use == true)
					{
						float length = 0 ;		// �������������i�ł����j

						length = (player->pos.x - item->pos.x) * (player->pos.x - item->pos.x)
								+ (player->pos.y - item->pos.y) * (player->pos.y - item->pos.y)
								+ (player->pos.z - item->pos.z) * (player->pos.z - item->pos.z);

						if (length < (player->radius + ITEM_SIZE_X) * (player->radius + ITEM_SIZE_X))
						{
							// �����A�C�e�����̑���
							player->item += 1.0f;

							//// �A�C�e������
							item->use = false;

							// �p�l�����Z�b�g��Ԃ�����
							panel[item->no].ItemSet = false;

							//// SE�Đ�
							//PlaySound(SOUND_LABEL_SE_COIN);
						}
					}
				}
		}

		//player = &PlayerWk[0];

	// �e���ˏ���
		for (int i = 0; i < PLAYER_MAX; i++, player++)
		{
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//pos.x = player->pos.x - sinf(player->rot.y) * 10.0f;
				//pos.y = player->pos.y + 20.0f;
				//pos.z = player->pos.z - cosf(player->rot.y) * 10.0f;

				pos.x = player->pos.x;
				pos.y = player->pos.y + 100.0f;
				pos.z = player->pos.z;

				//move.x = -sinf(player->rot.y) * VALUE_MOVE_BULLET;
				//move.y = 0.0f;
				//move.z = -cosf(player->rot.y) * VALUE_MOVE_BULLET;

				move.x += 0.0f;
				move.x += 0.0f;
				move.z += VALUE_MOVE_BULLET;

				SetBullet(pos, move, 4.0f, 4.0f);

			}
		}

	// �G�l�~�[�ƂԂ�������
	player = &PlayerWk[0];		// �v���C���[�擾
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		ENEMY *enemy = GetEnemy(0);

		for (int cntItem = 0; cntItem < MAX_ITEM; cntItem++, enemy++)
		{
			// �����蔻��
			if (enemy->use == true)
			{
				float length = 0;		// �������������i�ł����j

				length = (player->pos.x - enemy->Eye.x) * (player->pos.x - enemy->Eye.x)
					+ (player->pos.y - enemy->Eye.y) * (player->pos.y - enemy->Eye.y)
					+ (player->pos.z - enemy->Eye.z) * (player->pos.z - enemy->Eye.z);

				if (length < (player->radius + ENEMY_SIZE_X) * (player->radius + ENEMY_SIZE_X))
				{
					// �v���C���[������
					player->use = false;

					// �c���Ă������n��
					SetStageWinPlayer(i+1);

					//// SE�Đ�
					//PlaySound(SOUND_LABEL_SE_COIN);
				}
			}
		}
	}



		// �f�o�b�O�\��
#ifdef _DEBUG
		PrintDebugProc("[�v���C���[���W �F(X:%f Y: %f Z: %f)]\n", player->pos.x, player->pos.y, player->pos.z);
		PrintDebugProc("�v���C���[�ړ� : WSADQE : �O�㍶�E�㉺\n");
		PrintDebugProc("\n");
#endif

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

	PLAYER *player = &PlayerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
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
			D3DXMat = (D3DXMATERIAL*)D3DXMatBuffPlayer[i]->GetBufferPointer();

			for (int cntMat = 0; cntMat < (int)NumMatPlayer[i]; cntMat++)
			{
				// �}�e���A���̐ݒ�
				Device->SetMaterial(&D3DXMat[cntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				Device->SetTexture(0, D3DTexturePlayer[i]);

				// �`��
				D3DXMeshPlayer[i]->DrawSubset(cntMat);
			}

			// ���C�g��OFF
			Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}


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
PLAYER *GetPlayer(int no)
{
	return &PlayerWk[no];
}

//===================================================================
// �ʒu�擾
//===================================================================
D3DXVECTOR3 GetPosPlayer(int no)
{
	PLAYER *player = &PlayerWk[no];
	return player->pos;
}

//===================================================================
// �����擾
//===================================================================
D3DXVECTOR3 GetRotPlayer(int no)
{
	PLAYER *player = &PlayerWk[no];
	return player->rot;
}
