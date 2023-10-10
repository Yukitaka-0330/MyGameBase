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



//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];

    struct BLOCKHEIGHT
    {
        BLOCKTYPE blocks;
        int height;

    }table_[XSIZE][ZSIZE];

    int mode_;  //0:�グ�� 1:������ 2:��ނ�ς���
    int select_;    //���

public:
    
    int rands = 0;
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

    std::string Stagedata;


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
    BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    void Save();
};

#endif