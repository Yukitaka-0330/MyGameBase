#include "Playerchild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Playerchild::Playerchild(GameObject* parent) :
	GameObject(parent, "Playerchild"),hModel_(-1)
{
}

void Playerchild::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	assert(hModel_ >= 0);
	/*this->transform_.position_.x = -2.0f;
	this->transform_.position_.y = 1.0f;*/
	this->transform_.rotate_.x = 90;
	this->transform_.scale_.x = 0.2f;
	this->transform_.scale_.y = 0.2f;
	this->transform_.scale_.z = 0.2f;
	SphereCollider* col = new SphereCollider(0.1);
	AddCollider(col);
}

void Playerchild::Update()
{
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 40)
	{
		KillMe();
	}
}

void Playerchild::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Playerchild::Release()
{
	
}
