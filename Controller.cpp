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
}

//�X�V
void Controller::Update()
{

    //�J�����̈ʒu���x�N�g���^�ɕϊ�����
    XMVECTOR vCamPos = XMLoadFloat3(&transform_.position_);

    //1�t���[�����Ƃ̈ړ��x�N�g�� 4����͎̂l�����܂őΉ����Ă��邩��ł���{�͎g��Ȃ� x y z�̏��ɂȂ��Ă�
    XMVECTOR vCamMove = { 0.0f ,0.0f ,0.1f , 0.0f };//z����0.1�Ȃ̂ŉ������ɐi��ł���
    XMVECTOR vCamMoveX = { 0.1f ,0.0f ,0.0f , 0.0f };//x����0.1�Ȃ̂ŉ������ɐi��ł���

    //������transform_.rotate_y�x��]������s����쐬
    //������transform_.rotate_x�x��]������s����쐬
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])������  �x�N�g�����s��ɕϊ��@�s��ɕϊ����邱�Ƃňړ������邱�Ƃ��ł���悤�ɂȂ�
    vCamMove = XMVector3TransformCoord(vCamMove, mRotY);//�x�N�g�������s�񂍂ŕό`

    //W��������Ă�����
    if (Input::IsKey(DIK_W))
    {
        vCamPos += vCamMove;

    }

    //S��������Ă�����
    if (Input::IsKey(DIK_S))
    {
        vCamPos -= vCamMove;

    }

    //A��������Ă�����
    if (Input::IsKey(DIK_A))
    {
        vCamPos -= vCamMoveX;
    }

    //D��������Ă�����
    if (Input::IsKey(DIK_D))
    {
        vCamPos += vCamMoveX;
    }

    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1;
    }

    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1;
    }

    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;     // 1������]
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;     // 1������]
    }

    //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
    XMStoreFloat3(&transform_.position_, vCamPos);
    //�J�����̃|�W�V���� Cam�ɒǏ]����悤�ɂȂ��Ă�
    Camera::SetTarget(transform_.position_);

    //X���ɉ�]
    XMVECTOR vCam = { 0, 6, -10, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotX);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos + vCam);
    Camera::SetPosition(camPos);

    //Y���ɉ�]
    XMVECTOR vCamY = { 0, 6, -10, 0 };
    vCamY = XMVector3TransformCoord(vCam, mRotY);
    XMFLOAT3 camPosY;
    XMStoreFloat3(&camPosY, vCamPos + vCamY);
    Camera::SetPosition(camPosY);

    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //XMVECTOR vCam = XMVectorSet(0.0f, 6.0f, -10.0f, 0.0f);
    //XMFLOAT3 move = XMFLOAT3(0, 0, 0);
    //XMVECTOR vMove;

    //if (Input::IsKey(DIK_A))
    //{
    //    move = XMFLOAT3(-0.1, 0, 0);
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    move = XMFLOAT3(0.1, 0, 0);
    //}

    //if (Input::IsKey(DIK_W))
    //{
    //    move = XMFLOAT3(0, 0, 0.1);
    //}

    //if (Input::IsKey(DIK_S))
    //{
    //    move = XMFLOAT3(0, 0, -0.1);
    //}

    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.rotate_.y += 1;
    //}

    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.rotate_.y -= 1;
    //}
    //if (Input::IsKey(DIK_UP))
    //{
    //  transform_.rotate_.x += 1;
    //}
    //if (Input::IsKey(DIK_DOWN))
    //{
    //    transform_.rotate_.x -= 1;
    //}

    //    vMove = XMLoadFloat3(&move);
    //    vMove = XMVector3TransformCoord(vMove, mRotate);
    //    vPos += vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotate);//vCam����
    //    Camera::SetPosition(vPos + vCam);
    //    Camera::SetTarget(XMVectorSet(transform_.position_.x, transform_.position_.y, transform_.position_.z, 0));
   
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}
