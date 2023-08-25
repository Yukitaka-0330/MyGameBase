#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/BoxDefault.fbx");
    assert(hModel_ >= 0);
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

    for (int w = 0; w < 15; w++)
    {
        for (int z = 0; z < 15; z++)
        {
            BlockTrans.position_.x = w;
            BlockTrans.position_.z = z;

            Model::SetTransform(hModel_, BlockTrans);
            Model::Draw(hModel_);

        }
    }
   
}

//開放
void Stage::Release()
{
}
