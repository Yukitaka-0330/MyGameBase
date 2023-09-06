#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"

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
            table_[x][z].height = 1;
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
    float w = (float)(Direct3D::scrWidth/2.0f);
    float h = (float)(Direct3D::scrHeight/2.0f);
    //0ffsetx,yは 0
    //minZ = 0 max Z = 1;

    XMMATRIX vp =
    {
        w ,0 ,0 ,0,
        0,-h ,0 ,0,
        0, 0, 1, 0,
        w, h, 0, 1,
    };

    ////ビューポート
    //XMMATRIX invVP = ;
    ////プロジェクション変換
    //XMMATRIX invProj = ;
    ////ビュー変換
    //XMMATRIX inView = ;

    //XMFLOAT3 mousePosFront = マウスポジゲット;
    //mousePosFront.z = 0.0;
    //XMFLOAT3 mousePosBack = 如妙如妙;
    //mousePosBack.z = 1.0f;

    //① mouseposFrontをベクトルに変換
    //② ①にinvVP,invPrj,invViewをかける
    //③ mousePosBackをベクトルに変換
    //④ ③にinvVP,invPrj,invViewを掛ける
    //⑤ ②から④に向かってレイを打つ(とりあえずモデル番号は)hModel[0])
    //⑥ レイが当たったらブレークポイントで止める
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