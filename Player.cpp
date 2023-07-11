#include "Player.h"
#include "Engine/Fbx.h"

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
}

void Player::Update()
{
	this->transform_.rotate_.y++;
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
