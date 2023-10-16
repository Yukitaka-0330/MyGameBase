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



//���������Ǘ�����N���X
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
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    //BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    /// <summary>
    /// �t�@�C���̃Z�[�u
    /// </summary>
    void Save();

    /// <summary>
    /// �t�@�C���̃��[�h
    /// </summary>
    void Load();

    /// <summary>
    /// �ꊇ�폜
    /// </summary>
    void Bulk_Deletion(int startX, int startZ, int endX, int endZ, int newHeight);
};