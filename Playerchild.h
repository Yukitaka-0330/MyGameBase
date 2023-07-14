#pragma once
#include "Engine/GameObject.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //�J������
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;} //�J������


//�O���錾
class Fbx;
//�����V�[�����Ǘ�����N���X
class Playerchild : public GameObject
{
	int hModel_;//���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Playerchild(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


