#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this); //�v���C���[�̐e�͎���(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer); //PlayScene�̎q�Ƃ��āA�v���C���[��o�^
	GameObject * pObject = Instantiate<Player>(this);
	GameObject* pEnemy = Instantiate<Enemy>(this);
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
	//for(auto e :)
}

//�J��
void PlayScene::Release()
{
	
}
