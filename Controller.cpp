#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#define CAM_TYPE_FIXED 0 //�Œ�
#define CAM_TYPE_TPS_NO_ROT 1//�O�l�̉�]�Ȃ�
#define CAM_TYPE_TPS_ 2 //�O�l��
#define CAM_TYPE_FPS_ 3 //��l��

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
    XMVECTOR vCamPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vCamMove = { 0.0f ,0.0f ,0.05f , 0.0f };
    XMMATRIX mRotY;
    mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCamMove = XMVector3TransformCoord(vCamMove, mRotY);

    if (Input::IsKey(DIK_W))
    {
        vCamPos += vCamMove;
    }
    if (Input::IsKey(DIK_S))
    {
        vCamPos -= vCamMove;
    }

    XMStoreFloat3(&transform_.position_, vCamPos);
    

    XMVECTOR vCam = { 0, 3, -5, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos + vCam);
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
