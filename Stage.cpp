#if 0

#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), select_(0)
{
    for (int i = 0; i < MODEL_NUM; i++)
        hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            SetBlockType(x, z, DEFAULT);
            //table_[x][z].height = 1;
        }
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelName[] =
    {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string  fname_base = "Assets/"; 

    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++)
    {
        hModel_[i] = Model::Load(fname_base + modelName[i]);
        assert(hModel_[i] >= 0);
    }

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            SetBlockType(x, z, DEFAULT);
            SetBlockHeight(x, z, 1); //1足さないと1ブロック表示されくなるから注意
        }
            
    }
        
    /*SetBlockHeight(7, 7, 3);*/
}

//更新
void Stage::Update()
{
    if ( !Input::IsMouseButtonDown(0))
    {
        return;
    }

    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //0ffsetx,yは 0
    //minZ = 0 max Z = 1;

    XMMATRIX vp =
    {
        w ,0 ,0 ,0,
        0,-h ,0 ,0,
        0, 0, 1, 0,
        w, h, 0, 1,
    };

    //ビューポート
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //ビュー変換
    XMMATRIX inView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::F3GetMousePosition();
    mousePosFront.z = 0.0;
    XMFLOAT3 mousePosBack = Input::F3GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@ mouseposFrontをベクトルに変換
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //�A �@にinvVP,invPrj,invViewをかける
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * inView);
    //�B mousePosBackをベクトルに変換
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //�C �BにinvVP,invPrj,invViewを掛ける
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * inView);

        for (int x = 0; x < 15; x++)
        {
            for (int z = 0; z < 15; z++)
            {
                for (int y = 0; y < table_[x][z].height + 1; y++)
                {
                    //�D �Aから�Cに向かってレイを打つ(とりあえずモデル番号は)hModel[0])
                    RayCastData data;
                    XMStoreFloat4(&data.start, vMouseFront);
                    XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                    Transform trans;
                    trans.position_.x = x;
                    trans.position_.y = y;
                    trans.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);
                    Model::RayCast(hModel_[0], data);

                    //�E レイが当たったらブレークポイントで止める
                    if (data.hit)
                    {
                        break;
                    }
                }
            }
        }
    
}

//描画
void Stage::Draw()
{
    Transform BlockTrans;//Transfrom型の変数
    //Transform型 -> 位置,向き,大きさを扱う型
    for (int w = 0; w < XSIZE; w++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
           /* Model::SetTransform(table_[w][z].blocks, BlockTrans);
            Model::Draw(table_[w][z].blocks);*/

            for (int y = 0; y < table_[w][z].height ; y++)
            {
                BlockTrans.position_.x = w;
                BlockTrans.position_.z = z;
                BlockTrans.position_.y = y;
                Model::SetTransform(table_[w][z].blocks, BlockTrans);
                Model::Draw(table_[w][z].blocks);
            }
        }
    }
        
}

//開放
void Stage::Release()
{
}

void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].blocks = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}

//偽のダイアログプロシージャ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        //ダイアログができたとき
    case WM_INITDIALOG:
        // GetDlgItem(hDlg, IDC_RADIO_UP);
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //コンボボックスの初期値
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"草");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"砂");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);

        return TRUE;

    case WM_COMMAND:
        select_ = SendMessage(GetDlgItem(hDlg, IDD_DIALOG1), CB_GETCURSEL, 0,0);
    }
    return FALSE;
}

#else

#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
#include "Engine/Direct3D.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            /* table_[i][f];
             table_[i][f].height = 1;*/
            SetBlockHeight(x, z, 0);
        }
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string  fname_base = "Assets/";
    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, DEFAULT);
        }
    }
}

//更新
void Stage::Update()
{

    if (!Input::IsMouseButtonDown(0)) {
        return;
    }
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);

    XMMATRIX vp =
    {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);

    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);

    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);

    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);


    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            for (int y = 0; y < table_[x][z].height + 1; y++) {
                RayCastData data{};
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                if (data.hit) {
                   table_[x][z].height++;
                    break;
                }

            }
        }
    }

}

//描画
void Stage::Draw()
{
    Transform BlockTrans;//Transform型の変数
    //Transform型 -> 位置,向き,大きさを扱う型



    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {


            for (int y = 0; y < table_[x][z].height + 1; y++) {

                BlockTrans.position_.x = x;
                BlockTrans.position_.z = z;
                BlockTrans.position_ = { (float)x,(float)y,(float)z };
                Model::SetTransform(table_[x][z].blocks, BlockTrans);
                Model::Draw(table_[x][z].blocks);

            }
        }
    }
}


//開放
void Stage::Release()
{

}

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].blocks = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}


BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"default");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"Brick");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"Grass");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"sand");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"water");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        return TRUE;


    }
    return FALSE;
}

#endif