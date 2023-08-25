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
}

//�X�V
void Controller::Update()
{
    
    //A��������Ă�����
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 1.0f;
    }
    //D��������Ă�����
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 1.0f;
    }


    //��Ԃ̌��݈ʒu���x�N�g���^�ɕϊ�����
    XMVECTOR vTankPos = XMLoadFloat3(&transform_.position_);
    //1�t���[�����Ƃ̈ړ��x�N�g�� 4����͎̂l�����܂őΉ����Ă��邩��ł���{�͎g��Ȃ� x y z�̏��ɂȂ��Ă�
    XMVECTOR vTankMove = { 0.0f ,0.0f ,0.05f , 0.0f };//z����0.1�Ȃ̂ŉ������ɐi��ł���
    //XMMATRIX�͍s��������^
    XMMATRIX mRotY;

    //������transform_.rotate_y�x��]������s����쐬
    mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])������  �x�N�g�����s��ɕϊ��@�s��ɕϊ����邱�Ƃňړ������邱�Ƃ��ł���悤�ɂȂ�
    vTankMove = XMVector3TransformCoord(vTankMove, mRotY);//�x�N�g�������s�񂍂ŕό`

    //W��������Ă�����
    if (Input::IsKey(DIK_W))
    {
        vTankPos += vTankMove;

    }

    //W��������Ă�����
    if (Input::IsKey(DIK_S))
    {
        vTankPos -= vTankMove;

    }

    //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
    XMStoreFloat3(&transform_.position_, vTankPos);


    //�J�����̃|�W�V���� tank�ɒǏ]����悤�ɂȂ��Ă�
    Camera::SetTarget(transform_.position_);

    XMVECTOR vCam = { 0, 3, -5, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vTankPos + vCam);
    Camera::SetPosition(camPos);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}
