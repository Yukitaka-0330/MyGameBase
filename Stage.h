#pragma once
#include "Engine/GameObject.h"
#include "Windows.h"

namespace {
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT, BRICK, GRASS, SAND, WATER,MAX
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
    //BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    /// <summary>
    /// ファイルのセーブ
    /// </summary>
    void Save();

    /// <summary>
    /// ファイルのロード
    /// </summary>
    void Load();

    /// <summary>
    /// 一括削除
    /// </summary>
    void Bulk_Deletion(int startX, int startZ, int endX, int endZ, int newHeight);
};