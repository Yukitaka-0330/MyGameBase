#include "GameObject.h"

GameObject::GameObject() : pParent_(nullptr), objectName_(""),isDead(false)
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
	Draw();//������draw�֐����Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//�����Ŏq����T���Ă�����
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update(); //������Update�֐����Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //�����Ŏq����T���Ă�����
	{
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();//������Release�֐����Ă�
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //�����Ŏq����T���Ă�����
	{
		(*itr)->ReleaseSub();
	}

}

void GameObject::KillMe()
{

}
