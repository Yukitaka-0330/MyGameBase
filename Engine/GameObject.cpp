#include "GameObject.h"

GameObject::GameObject() : pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const string& name):pParent_(parent),objectName_(name)
{
}

GameObject::~GameObject()
{
	delete pParent_;
}

void GameObject::DrawSub()
{
	Draw();//自分のdraw関数を呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//ここで子供を探していくぅ
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update(); //自分のUpdate関数を呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //ここで子供を探していくぅ
	{
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();//自分のRelease関数を呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //ここで子供を探していくぅ
	{
		(*itr)->ReleaseSub();
	}

}
