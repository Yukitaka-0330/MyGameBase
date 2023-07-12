#include "Playerchild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

Playerchild::Playerchild(GameObject* parent) :
	GameObject(parent, "Playerchild"), pFbx(nullptr)
{
}

void Playerchild::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/Oden.fbx");
	this->transform_.position_.x = -2.0f;
	this->transform_.position_.y = 1.0f;
	this->transform_.scale_.x = 0.2f;
	this->transform_.scale_.y = 0.2f;
	this->transform_.scale_.z = 0.2f;
}

void Playerchild::Update()
{
	//this->transform_.rotate_.y++;
	if (Input::IsKey(DIK_ESCAPE))
	{
		this->KillMe();
	}
}

void Playerchild::Draw()
{
	pFbx->Draw(this->transform_);
}

void Playerchild::Release()
{
	SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
