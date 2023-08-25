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


    //戦車の現在位置をベクトル型に変換する
    XMVECTOR vTankPos = XMLoadFloat3(&transform_.position_);
    //1フレームごとの移動ベクトル 4つあるのは四次元まで対応しているからでも基本は使わない x y zの順になってる
    XMVECTOR vTankMove = { 0.0f ,0.0f ,0.05f , 0.0f };//z軸が0.1なので奥方向に進んでいく
    //XMMATRIXは行列を扱う型
    XMMATRIX mRotY;

    //ここでtransform_.rotate_y度回転させる行列を作成
    mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //移動ベクトルを変形(戦車と同じ向きに回転)させる  ベクトルを行列に変換　行列に変換することで移動させることができるようになる
    vTankMove = XMVector3TransformCoord(vTankMove, mRotY);//ベクトルｖを行列ｍで変形

    //Wが押されていたら
    if (Input::IsKey(DIK_W))
    {
        vTankPos += vTankMove;

    }

    //Wが押されていたら
    if (Input::IsKey(DIK_S))
    {
        vTankPos -= vTankMove;

    }

    //現在地をベクトルからいつものtransform_.position_に戻す
    XMStoreFloat3(&transform_.position_, vTankPos);


    //カメラのポジション tankに追従するようになってる
    Camera::SetTarget(transform_.position_);

    XMVECTOR vCam = { 0, 3, -5, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotY);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vTankPos + vCam);
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
