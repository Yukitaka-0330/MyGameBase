#include "Stage.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++)
        hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < ZSIZE; z++)
            table_[x][z] = 0;
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
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
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < MODEL_NUM; i++)
    {
        hModel_[i] = Model::Load(fname_base + modelName[i]);
        assert(hModel_[i] >= 0);
    }

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < XSIZE; z++)
            table_[x][z] = x % 5;

}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Transform BlockTrans;//Transfrom�^�̕ϐ�
    //Transform�^ -> �ʒu,����,�傫���������^

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

//�J��
void Stage::Release()
{
}
