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
}

//更新
void Controller::Update()
{

    //カメラの位置をベクトル型に変換する
    XMVECTOR vCamPos = XMLoadFloat3(&transform_.position_);

    //1フレームごとの移動ベクトル 4つあるのは四次元まで対応しているからでも基本は使わない x y zの順になってる
    XMVECTOR vCamMove = { 0.0f ,0.0f ,0.1f , 0.0f };//z軸が0.1なので奥方向に進んでいく
    XMVECTOR vCamMoveX = { 0.1f ,0.0f ,0.0f , 0.0f };//x軸が0.1なので横方向に進んでいく

    //ここでtransform_.rotate_y度回転させる行列を作成
    //ここでtransform_.rotate_x度回転させる行列を作成
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //移動ベクトルを変形(戦車と同じ向きに回転)させる  ベクトルを行列に変換　行列に変換することで移動させることができるようになる
    vCamMove = XMVector3TransformCoord(vCamMove, mRotY);//ベクトルｖを行列ｍで変形

    //Wが押されていたら
    if (Input::IsKey(DIK_W))
    {
        vCamPos += vCamMove;

    }

    //Sが押されていたら
    if (Input::IsKey(DIK_S))
    {
        vCamPos -= vCamMove;

    }

    //Aが押されていたら
    if (Input::IsKey(DIK_A))
    {
        vCamPos -= vCamMoveX;
    }

    //Dが押されていたら
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
        transform_.rotate_.y -= 1.0f;     // 1°ずつ回転
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;     // 1°ずつ回転
    }

    //現在地をベクトルからいつものtransform_.position_に戻す
    XMStoreFloat3(&transform_.position_, vCamPos);
    //カメラのポジション Camに追従するようになってる
    Camera::SetTarget(transform_.position_);

    //X軸に回転
    XMVECTOR vCam = { 0, 6, -10, 0 };
    vCam = XMVector3TransformCoord(vCam, mRotX);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos + vCam);
    Camera::SetPosition(camPos);

    //Y軸に回転
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
    //    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotate);//vCamを回す
    //    Camera::SetPosition(vPos + vCam);
    //    Camera::SetTarget(XMVectorSet(transform_.position_.x, transform_.position_.y, transform_.position_.z, 0));
   
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}
