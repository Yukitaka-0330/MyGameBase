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
	Draw();//Ž©•ª‚ÌdrawŠÖ”‚ðŒÄ‚Ô
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//‚±‚±‚ÅŽq‹Ÿ‚ð’T‚µ‚Ä‚¢‚­‚£
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update(); //Ž©•ª‚ÌUpdateŠÖ”‚ðŒÄ‚Ô
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //‚±‚±‚ÅŽq‹Ÿ‚ð’T‚µ‚Ä‚¢‚­‚£
	{
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();//Ž©•ª‚ÌReleaseŠÖ”‚ðŒÄ‚Ô
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) //‚±‚±‚ÅŽq‹Ÿ‚ð’T‚µ‚Ä‚¢‚­‚£
	{
		(*itr)->ReleaseSub();
	}

}

void GameObject::KillMe()
{

}
