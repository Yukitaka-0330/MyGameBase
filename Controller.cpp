#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hModel_(-1)
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
}

//更新
void Controller::Update()
{
    //Aが押されていたら
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 1.0f;
    }
    //Dが押されていたら
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 1.0f;
    }

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

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}
