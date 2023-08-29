#pragma once
#include "Engine/GameObject.h"

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

public:
    int hModel_[MODEL_NUM];
    int table_[XSIZE][ZSIZE];
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
};