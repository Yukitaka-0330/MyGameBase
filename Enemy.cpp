#include "Enemy.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject * parent): GameObject(parent, "Enemy"),hModel_(-1)
{
}

void Enemy::Initialize()
{
	/*hModel_ = Model::Load("Assets/Oden.fbx");
	
	this->transform_.position_.z = 10;
	this->transform_.position_.x = -5;
	this->transform_.scale_.x = 0.3f;
	this->transform_.scale_.y = 0.3f;
	this->transform_.scale_.z = 0.3f;*/

	pFbx = new Fbx;
	pFbx->Load("Assets/Oden.fbx");
	transform_.position_.z = 20.0f;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	/*Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);*/

	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}
