#pragma once
#include "Engine/GameObject.h"

class Fbx;

class Enemy :public GameObject
{
private:
	Fbx* pFbx;
	int hModel_;
	public:
		//�R���X�g���N�^
		Enemy(GameObject * parent);

		//������
		void Initialize() override;

		//�X�V
		void Update() override;

		//�`��
		void Draw() override;

		//�J��
		void Release() override;
};
