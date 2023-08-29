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
    transform_.position_.y = 0;
    transform_.position_.x = 7;
    transform_.position_.z = 7;

    transform_.rotate_.x = 45.0f;
}

//更新
void Controller::Update()
{
    //左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }
    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
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
    //ここでtransform_.rotate_x度回転させる行列を作成
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //現在位置をベクトルに変換しておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //前後移動ベクトル
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //奥向きのXMFLOAT3構造体を用意し
    XMVECTOR vMove = XMLoadFloat3(&frontMove);          //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //戦車の向きに合わせて回転



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

    //左右移動ベクトル
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //右向きのXMFLOAT3構造体を用意し
    vMove = XMLoadFloat3(&rightMove);                   //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotateY);    //戦車の向きに合わせて回転


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


    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 0, -10, 0); //自撮り棒用意
    vCam = XMVector3TransformCoord(vCam, mRotX * mRotateY); //自撮り棒回転
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos)); //カメラの位置は自撮り棒の先端 (現在地+自撮り棒)
    Camera::SetTarget(XMLoadFloat3(&transform_.position_)); //カメラの見る位置は「このオブジェクトの位置
    //Camera::SetPosition(vPos + vCam); //カメラの位置は自撮り棒の先端 (現在地+自撮り棒)
    //Camera::SetTarget(transform_.position_);
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}
