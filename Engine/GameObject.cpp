#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name):pParent_(nullptr),objectName_(NULL)
{
}

GameObject::~GameObject()
{
}
