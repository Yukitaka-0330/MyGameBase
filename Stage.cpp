#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++)
        hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < ZSIZE; z++)
            table_[x][z] = 0;
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
        "BoxBrick.fbx",
        "BoxDefault.fbx",
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
        for (int z = 0; z < XSIZE; z++)
            table_[x][z] = x % 5;

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
            int tzpe = table_[w][z];
            BlockTrans.position_.x = w;
            BlockTrans.position_.z = z;
            Model::SetTransform(table_[w][z], BlockTrans);
            Model::Draw(table_[w][z]);

        }
    }
        
}

//開放
void Stage::Release()
{
}
