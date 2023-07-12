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
	Instantiate<Playerchild>(this);

	GameObject * pCo2 = Instantiate<Playerchild>(this);
	pCo2->SetPosition(XMFLOAT3(2, 1, 0));
}

void Player::Update()
{
	this->transform_.rotate_.y++;

	if (Input::IsKey(DIK_K))
	{
		transform_.position_.x -= 0.1f;
		//KillMe();
	}

	if (Input::IsKey(DIK_L))
	{
		transform_.position_.x += 0.1f;
		//KillMe();
	}
}

void Player::Draw()
{
	
	pFbx->Draw(this->transform_);
}

void Player::Release()
{
	SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
