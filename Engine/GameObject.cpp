#include "GameObject.h"
#include "Direct3D.h"
GameObject::GameObject() : pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :pParent_(parent), objectName_(name),isDead(false)
{
	if (parent != nullptr)
	{
		this->transform_.pParent_ = &(parent->transform_);
	}
	
}

GameObject::~GameObject()
{
	SAFE_RELEASE(pParent_);
}

// Ž©•ª‚ðíœ‚·‚é
void GameObject::KillMe()
{
	isDead = true;
}


void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else 
			itr++;
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();
}

void GameObject::SetTrans(Transform _transform)
{
	this->transform_ = _transform;
}

void GameObject::SetPosition(XMFLOAT3 _position)
{
	this->transform_.position_ = _position;
}

void GameObject::SetRotate(XMFLOAT3 _rotate)
{
	this->transform_.rotate_ = _rotate;
}

void GameObject::SetScale(XMFLOAT3 _scale)
{
	this->transform_.scale_ = _scale;
}

//void GameObject::SetPosition(float x, float y, float z)
//{
//	SetPosition(XMFLOAT3(x, y, z));
//}


