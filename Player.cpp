#include "Player.h"
#include "Playerchild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Player::Player(GameObject* parent):
	GameObject(parent,"Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	assert(hModel_ >= 0);
	this->transform_.scale_.x = 0.5f;
	this->transform_.scale_.y = 0.5f;
	this->transform_.scale_.z = 0.5f;
	/*Instantiate<Playerchild>(this);

	GameObject * pCo2 = Instantiate<Playerchild>(this);
	pCo2->SetPosition(XMFLOAT3(2, 1, 0));*/
}

void Player::Update()
{
	this->transform_.rotate_.y++;

	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject * pBullet = Instantiate<Playerchild>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
