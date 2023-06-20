#include "Transform.h"

Transform::Transform()
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);

	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();

}

Transform::~Transform()
{
}

void Transform::Calclation()
{
	//ˆÚ“®
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//‰ñ“]
	matRotate_= XMMatrixRotationX(XMConvertToDegrees(position_.x)) *
				XMMatrixRotationY(XMConvertToDegrees(position_.y)) *
				XMMatrixRotationZ(XMConvertToDegrees(position_.z));

	//Šg‘å—¦
	matScale_ = XMMatrixScaling(position_.x, position_.y, position_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	Calclation();
	return matScale_ * matRotate_ * matTranslate_;
}
