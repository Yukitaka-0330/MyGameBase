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
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//Šg‘å—¦
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
