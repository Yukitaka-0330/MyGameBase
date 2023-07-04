#include "GameObject.h"

GameObject::GameObject() : pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const string& name):pParent_(parent),objectName_(name)
{
}

GameObject::~GameObject()
{
}
