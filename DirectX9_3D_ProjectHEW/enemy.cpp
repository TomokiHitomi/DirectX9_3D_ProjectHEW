//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : GP11B243-18-���_��
//
//=============================================================================
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "enemy.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetEnemyAnimation(int sec);
D3DXMATRIX* EnemyLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy[ENEMY_ANIM_MAX];			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshEnemy[ENEMY_ANIM_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatEnemy[ENEMY_ANIM_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatEnemy[ENEMY_ANIM_MAX];				// �������̑���

D3DXMATRIX			g_mtxWorldEnemy;			// ���[���h�}�g���b�N�X

float				g_fSizeShadowE;				// �e�̃T�C�Y
D3DXCOLOR			g_colShadowE;				// �e�̐F

ENEMY				enemyWk[ENEMY_MAX];		// �G�l�~�[�i�[���[�N

int					animCnt;		// �A�j���J�E���g

const char *FileNameEnemy[ENEMY_ANIM_MAX] =
{
	"data/MODEL/ENEMY/enemy_a00.x",		// ����
	"data/MODEL/ENEMY/enemy_a01.x",		// �����O�P
	"data/MODEL/ENEMY/enemy_a02.x",		// �����O�Q
	"data/MODEL/ENEMY/enemy_a03.x",		// �����O�R
	"data/MODEL/ENEMY/enemy_a02.x",		// �����O�Q
	"data/MODEL/ENEMY/enemy_a01.x",		// �����O�P
	"data/MODEL/ENEMY/enemy_a00.x",		// ����
	"data/MODEL/ENEMY/enemy_a11.x",		// �E���O�P
	"data/MODEL/ENEMY/enemy_a12.x",		// �E���O�Q
	"data/MODEL/ENEMY/enemy_a13.x",		// �E���O�R
	"data/MODEL/ENEMY/enemy_a12.x",		// �E���O�Q
	"data/MODEL/ENEMY/enemy_a11.x"		// �E���O�P

};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];


	for (int nCntEnemyAnim = 0; nCntEnemyAnim < ENEMY_ANIM_MAX; nCntEnemyAnim++)
	{
		g_pD3DTextureEnemy[nCntEnemyAnim] = NULL;
		g_pD3DXMeshEnemy[nCntEnemyAnim] = NULL;
		g_pD3DXBuffMatEnemy[nCntEnemyAnim] = NULL;


		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(FileNameEnemy[nCntEnemyAnim],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatEnemy[nCntEnemyAnim],
			NULL,
			&g_nNumMatEnemy[nCntEnemyAnim],
			&g_pD3DXMeshEnemy[nCntEnemyAnim])))
		{
			return E_FAIL;
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,		// �t�@�C���̖��O
			&g_pD3DTextureModel);	// �ǂݍ��ރ������[
#endif

	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// �G�l�~�[�̎��_�̏�����
		enemy->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �G�l�~�[�̒����_�̏�����
		enemy->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �G�l�~�[�̏�����̏�����
		enemy->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �G�l�~�[�̌����̏�����
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �G�l�~�[�̈ړ��ʂ̏�����
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �G�l�~�[�̃X�P�[���̏�����
		enemy->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// use�t���O��true�ɐݒ�
		enemy->use = true;

		// �A�j���[�V�����ԍ�������
		// �ŏ��͒�����Ԃɐݒ�
		enemy->anim = 0;

		// �A�j���[�V�����J�E���g������
		animCnt = 0;
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemyAnim = 0; nCntEnemyAnim < ENEMY_ANIM_MAX; nCntEnemyAnim++)
	{
		if (g_pD3DTextureEnemy[nCntEnemyAnim] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureEnemy[nCntEnemyAnim]->Release();
			g_pD3DTextureEnemy[nCntEnemyAnim] = NULL;
		}

		if (g_pD3DXMeshEnemy[nCntEnemyAnim] != NULL)
		{// ���b�V���̊J��
			g_pD3DXMeshEnemy[nCntEnemyAnim]->Release();
			g_pD3DXMeshEnemy[nCntEnemyAnim] = NULL;
		}

		if (g_pD3DXBuffMatEnemy[nCntEnemyAnim] != NULL)
		{// �}�e���A���̊J��
			g_pD3DXBuffMatEnemy[nCntEnemyAnim]->Release();
			g_pD3DXBuffMatEnemy[nCntEnemyAnim] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	CAMERA *camera = GetCamera();


	// �G�l�~�[�̍��W�����J�����̒����_�ɃZ�b�g
	//enemy->Eye = camera->posCameraAt;

	// �G�l�~�[�̒����_���J�����̒����_�ɃZ�b�g
	enemy->At = camera->posCameraAt;

	// �A�j���[�V����
	SetEnemyAnimation(ENEMY_ANIM_SEC);

#ifdef _DEBUG
	// �f�o�b�O���Ɏ蓮�ŃG�l�~�[�ړ�
	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			enemy->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// ����ړ�
			enemy->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else
		{// ���ړ�
			enemy->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
			enemy->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			enemy->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			enemy->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
		}
		else
		{// �E�ړ�
			enemy->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
			enemy->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		enemy->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		enemy->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		enemy->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
		enemy->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_ENEMY;
	}

	// �ړ��ʂɊ�����������
	enemy->move.x += (0.0f - enemy->move.x) * RATE_MOVE_ENEMY;
	enemy->move.y += (0.0f - enemy->move.y) * RATE_MOVE_ENEMY;
	enemy->move.z += (0.0f - enemy->move.z) * RATE_MOVE_ENEMY;

	//if (enemy->Eye.x < -310.0f)
	//{
	//	enemy->Eye.x = -310.0f;
	//}
	//if (enemy->Eye.x > 310.0f)
	//{
	//	enemy->Eye.x = 310.0f;
	//}
	//if (enemy->Eye.z < -310.0f)
	//{
	//	enemy->Eye.z = -310.0f;
	//}
	//if (enemy->Eye.z > 310.0f)
	//{
	//	enemy->Eye.z = 310.0f;
	//}


	/// �ʒu�ړ�
	enemy->Eye.x += enemy->move.x;
	enemy->Eye.y += enemy->move.y;
	//if (enemy->Eye.y < 5.0f)
	//{
	//	enemy->Eye.y = 5.0f;
	//}
	//if (enemy->Eye.y > 75.0f)
	//{
	//	enemy->Eye.y = 75.0f;
	//}
	enemy->Eye.z += enemy->move.z;

#endif

	enemy = &enemyWk[0];
#ifdef _DEBUG
	PrintDebugProc("[�G�l�~�[�̈ʒu  �F(%f : %f : %f)]\n", enemy->Eye.x, enemy->Eye.y, enemy->Eye.z);
	//PrintDebugProc("\n");
#endif


}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	ENEMY *enemy = &enemyWk[0];

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)	// �g�p��ԂȂ�`�悷��
		{
			// ���C�g��on
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, enemy->scl.x,
				enemy->scl.y,
				enemy->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy,
				&g_mtxWorldEnemy, &mtxScale);


			// ��]�𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
			//D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);
			EnemyLookAtMatrix(&mtxRot, &enemy->Eye, &enemy->At, &enemy->Up);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);
			
			//// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy->Eye.x, enemy->Eye.y, enemy->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			// ���͒�����ݒ肵�Ă�O
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemy[enemy->anim]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy[enemy->anim]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemy[enemy->anim]);

				// �`��
				g_pD3DXMeshEnemy[enemy->anim]->DrawSubset(nCntMat);

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
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}
//=============================================================================
// �G�l�~�[�̉�]�s��Z�o�֐�
//=============================================================================
D3DXMATRIX* EnemyLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pAt - *pEye;
	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));


	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

	return pout;
}
//=============================================================================
// �G�l�~�[�A�j���[�V�����ݒ�֐��i�����F�A�j���[�V�����ꏄ�ɂ�����b���j
//=============================================================================
void SetEnemyAnimation(int sec)
{
	ENEMY *enemy = &enemyWk[0];

	// �A�j���[�V�����J�E���g
	animCnt++;

	// �b���̐�Βl�����߂�
	sec = abs(sec);

	// �A�j���[�V������؂�ւ���t���[���������߂�
	sec = (60 * sec) / ENEMY_ANIM_MAX;

	if (animCnt % sec == 0)
	{	// �A�j���[�V������؂�ւ���
		enemy->anim++;
		if (enemy->anim >= ENEMY_ANIM_MAX)
		{	// �ꏄ������ŏ��ɖ߂�
			enemy->anim = 0;
		}
	}

}