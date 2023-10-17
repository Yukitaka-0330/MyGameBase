#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::fstream;
using std::stringstream;
using std::string;


//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++)
        hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < ZSIZE; z++)
            SetBlockHeight(x, z, 0);

    
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelname[] =
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
        hModel_[i] = Model::Load(fname_base + modelname[i]);
        assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++)
    {
        for (int x = 0; x < XSIZE; x++)
        {
            SetBlock(x, z, DEFAULT);
        }
    }
}

//更新
void Stage::Update()
{

    if (!Input::IsMouseButtonDown(0))
        return;
    
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);

    float distance = FLT_MAX;
    int posX = -1;
    int posZ = -1;

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


    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++) 
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                RayCastData data{};
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[0], trans);

                Model::RayCast(hModel_[0], data);

                if (data.hit)
                {
                    if (distance > data.dist)
                    {
                        distance = data.dist;
                        posX = x ;
                        posZ = z ;
                    }
                   
                    break;
                }

            }
        }
    }

    switch (mode_)
    {
      case 0: //RADIO_UP
          table_[posX][posZ].height++;
         break;

     case 1://RADIO_DOWN
         if (!(table_[posX][posZ].height < 1))
             table_[posX][posZ].height--;
         break;

     case 2://RADIO_CHANGE
         SetBlock(posX, posZ, (BLOCKTYPE)select_);
         break;

     case 3: //ALL_Delete
         for (int x = 0; x < XSIZE; x++)
         {
             for (int z = 0; z < ZSIZE; z++)
             {
                 SetBlockHeight(x, z, 0);
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
            for (int y = 0; y < table_[x][z].height + 1; y++) 
            {

                BlockTrans.position_.x = x;
                BlockTrans.position_.z = z;
                BlockTrans.position_.y = y;
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

//バイナリファイルvar
void Stage::Save()
{
    char fileName[MAX_PATH] = "SaveData.map";
    string buffer;
    stringstream oss;


    //「ファイルを保存」　ダイアログの設定
    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = TEXT("map");
    }

    //ファイルに保存
    if (GetSaveFileName(&ofn))
    {
        fstream outputFile(fileName, std::ios::binary | std::ios::out);

        for (int x = 0; x < XSIZE; x++)
        {
            for (int z = 0; z < ZSIZE; z++)
            {
                outputFile.write((char*)&table_[x][z], sizeof(BLOCKHEIGHT));
            }
        }
        outputFile.close();
    }
}

//バイナリファイルvar
void Stage::Load()
{
    char fileName[MAX_PATH] = "SaveData.map";
    string buffer;
    stringstream oss;

    //「ファイルを保存」　ダイアログの設定
    OPENFILENAME ofn; 
    {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_FILEMUSTEXIST;
        ofn.lpstrDefExt = TEXT("map");
        ofn.lpstrDefExt;
    }

    //ファイルを開く
    if (GetOpenFileName(&ofn))
    {
        fstream inputFile(fileName, std::ios::binary | std::ios::in);

        for (int x = 0; x < XSIZE; x++)
        {
            for (int z = 0; z < ZSIZE; z++)
            {
                inputFile.read((char*)&table_[x][z], sizeof(BLOCKHEIGHT));
            }
        }
        inputFile.close();
    }
}


BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"デフォルト"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"レンガ"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"草"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"砂"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"水"));

        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        return TRUE;

    case WM_COMMAND:
        select_=SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0,0);

        if (IsDlgButtonChecked(hDlg, IDC_RADIO_UP))
        {
            mode_ = 0;
        }

        if (IsDlgButtonChecked(hDlg, IDC_RADIO_DOWN))
        {
            mode_ = 1;
        }

        if (IsDlgButtonChecked(hDlg, IDC_RADIO_CHANGE))
        {
            mode_ = 2;
        } 

        if (LOWORD(wp) == IDC_RADIO_ALLDELETE)
        {
            mode_ = 3;
        }

    }
    return FALSE;
}

//Save(文字列var(完成))

/*void Stage::Save()
{
    char fileName[MAX_PATH] = "SaveData.map";

    //「ファイルを保存」　ダイアログの設定
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")
        TEXT("すべてのファイル(*.*)\0*.*\0\0");
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "map";

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;


    //セーブのルーチン
    HANDLE hFile;        //ファイルのハンドル
    hFile = CreateFile(
        fileName,                 //ファイル名
        GENERIC_WRITE,           //アクセスモード（書き込み用）
        0,                      //共有（なし）
        NULL,                   //セキュリティ属性（継承しない）
        CREATE_ALWAYS,           //作成方法
        FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
        NULL);                  //拡張属性（なし）

    //std::string Stagedata = std::to_string(XSIZE) + "," + std::to_string(ZSIZE) + "\n"; // ステージのサイズを追加
    std::string Stagedata;

    for (int z = 0; z < ZSIZE; z++)
    {
        for (int x = 0; x < XSIZE; x++)
        {
            // ブロックの高さと種類を文字列に変換してコンマで区切って連結
            Stagedata += std::to_string(table_[x][z].height) + "," + std::to_string(table_[x][z].blocks);

            // XSIZE - 1 のときはコンマを追加
            if (x < XSIZE - 1)
                Stagedata += ",";
        }

        // ZSIZE - 1 のときは改行文字を追加
        if (z < ZSIZE - 1)
            Stagedata += "\n";
    }

    DWORD bytes = 0;
    WriteFile(
        hFile,      //ファイルハンドル
        Stagedata.c_str(),  //保存したい文字列
        (DWORD)strlen(Stagedata.c_str()),         //保存する文字列
        &bytes,     //保存したいサイズ
        NULL
    );
    CloseHandle(hFile);

}*/


//Load(文字列var(まだ))
/*
  void Stage::Load()
{
    char fileName[MAX_PATH] = "SaveData.map";

    //「ファイルを開く」　ダイアログの設定
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")
        TEXT("すべてのファイル(*.*)\0*.*\0\0");
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "map";

    //「ファイルを開く」ダイアログ
    BOOL selFile;
    selFile = GetOpenFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;


    HANDLE hFile;        //ファイルのハンドル
    hFile = CreateFile(
        fileName,                 //ファイル名
        GENERIC_READ,           //アクセスモード（読み込み専用）
        0,                      //共有（なし）
        NULL,                   //セキュリティ属性（継承しない）
        OPEN_EXISTING,           //作成方法
        FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
        NULL);                  //拡張属性（なし）


    //ファイルのサイズを取得
    DWORD fileSize = GetFileSize(hFile, NULL);

    //ファイルのサイズ分メモリを確保
    char* data;
    data = new char[fileSize];

    DWORD dwBytes = 0; //読み込み位置

    ReadFile(
        hFile,     //ファイルハンドル
        data,      //データを入れる変数
        fileSize,  //読み込むサイズ
        &dwBytes,  //読み込んだサイズ
        NULL);     //オーバーラップド構造体（今回は使わない）
    CloseHandle(hFile);

    int* iArray = new int[fileSize];

    //データを整数に変換して読み込み
    char* value = strtok(data, ","); //コンマ区切りになってるから
    int index = 0;

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < ZSIZE; z++)
        {
            iArray[index] = atoi(value);
        }
}

*/
