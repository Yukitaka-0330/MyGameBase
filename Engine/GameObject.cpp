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

// 自分を削除する
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
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();

	Release();
}

//void GameObject::SetTrans(Transform _transform)
//{
//	this->transform_ = _transform;
//}

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

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this); //自分が_objNameのオブジェクトだった!!
	}
	else
	{
		for (auto itr : childList_)
		{

			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}

		//上記と同じ　イテレーターの書き方が異なるだけ
		/*for (auto itr = childList_.begin();itr != childList_.end(); itr++)
		{

			GameObject* obj = (*itr)->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}*/
	}
	return nullptr;
}


/// <summary>
/// 再起呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス(GameObject * 型)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	//自分から見て、ルートジョブを探して、そのルートジョブから全員の子供をたどってobjNameを探す。
	return GetRootJob()->FindChildObject(_objName);
}

