#include "Enemy.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Enemy::Enemy(GameObject * parent): GameObject(parent, "Enemy"),hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	
	this->transform_.position_.z = 10;
	this->transform_.position_.x = -5;
	this->transform_.scale_.x = 0.3f;
	this->transform_.scale_.y = 0.3f;
	this->transform_.scale_.z = 0.3f;

	SphereCollider* col = new SphereCollider(1);
	AddCollider(col);

}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

//‰½‚©‚É“–‚½‚Á‚½
void Enemy::OnCollision(GameObject* pTarget)
{
	KillMe();
}
