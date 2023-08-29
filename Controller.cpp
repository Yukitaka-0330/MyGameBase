#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hModel_(-1)
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
    transform_.position_.y = 0;
    transform_.position_.x = 7;
    transform_.position_.z = 7;

    transform_.rotate_.x = 45.0f;
}

//�X�V
void Controller::Update()
{
    //����]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //�E��]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }
    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));


    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
        if (transform_.rotate_.x > 89)
        {
            transform_.rotate_.x = 89;
        }
    }

    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
        if (transform_.rotate_.x < 0)
        {
            transform_.rotate_.x = 0;
        }

    }
    //������transform_.rotate_x�x��]������s����쐬
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //���݈ʒu���x�N�g���ɕϊ����Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //�O��ړ��x�N�g��
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMVECTOR vMove = XMLoadFloat3(&frontMove);          //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]



    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //���E�ړ��x�N�g��
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //�E������XMFLOAT3�\���̂�p�ӂ�
    vMove = XMLoadFloat3(&rightMove);                   //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //��Ԃ̌����ɍ��킹�ĉ�]


    if (Input::IsKey(DIK_D))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_A))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }


    //�J����
    XMVECTOR vCam = XMVectorSet(0, 0, -10, 0); //���B��_�p��
    vCam = XMVector3TransformCoord(vCam, mRotX * mRotateY); //���B��_��]
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos)); //�J�����̈ʒu�͎��B��_�̐�[ (���ݒn+���B��_)
    Camera::SetTarget(XMLoadFloat3(&transform_.position_)); //�J�����̌���ʒu�́u���̃I�u�W�F�N�g�̈ʒu
    //Camera::SetPosition(vPos + vCam); //�J�����̈ʒu�͎��B��_�̐�[ (���ݒn+���B��_)
    //Camera::SetTarget(transform_.position_);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}
