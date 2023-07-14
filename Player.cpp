#include "Player.h"
#include"Playerchild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent):
	GameObject(parent,"Player"), pFbx(nullptr)
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/Oden.fbx");
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
	
	pFbx->Draw(this->transform_);
}

void Player::Release()
{
}
