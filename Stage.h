#if 0

#pragma once
#include "Engine/GameObject.h"
#include "Windows.h"

namespace
{
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };

    enum BLOCKTYPE
    {
        DEFAULT,BRICK,GRASS,SAND,WATER
    };
}



//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];

    struct BLOCKHEIGHT
    {
        BLOCKTYPE blocks;
        int height;

    }table_[XSIZE][ZSIZE];

    int mode_;  //0:上げる 1:下げる 2:種類を変える
    int select_;    //種類

public:
    
    int rands = 0;
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetBlockType(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
};

#else

#pragma once
#include "Engine/GameObject.h"
#include "Windows.h"
#include <sstream>

namespace {
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT, BRICK, GRASS, SAND, WATER
    };

}



//◆◆◆を管理するクラス
class Stage : public GameObject
{

    int hModel_[MODEL_NUM];


    struct BLOCKHEIGHT {
        int blocks;
        int height;

    } table_[XSIZE][ZSIZE];
    int mode_;
    int select_;

    std::string Stagedata;


public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    void Save();
};

#endif