#if 0

#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

//�R���X�g���N�^
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
            //table_[x][z].height = 1;
        }
    }
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
        "BoxDefault.fbx",
        "BoxBrick.fbx",
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
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            SetBlockType(x, z, DEFAULT);
            SetBlockHeight(x, z, 1); //1�����Ȃ���1�u���b�N�\�����ꂭ�Ȃ邩�璍��
        }
            
    }
        
    /*SetBlockHeight(7, 7, 3);*/
}

//�X�V
void Stage::Update()
{
    if ( !Input::IsMouseButtonDown(0))
    {
        return;
    }

    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);
    //0ffsetx,y�� 0
    //minZ = 0 max Z = 1;

    XMMATRIX vp =
    {
        w ,0 ,0 ,0,
        0,-h ,0 ,0,
        0, 0, 1, 0,
        w, h, 0, 1,
    };

    //�r���[�|�[�g
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    //�r���[�ϊ�
    XMMATRIX inView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    XMFLOAT3 mousePosFront = Input::F3GetMousePosition();
    mousePosFront.z = 0.0;
    XMFLOAT3 mousePosBack = Input::F3GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@ mouseposFront���x�N�g���ɕϊ�
    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    //�A �@��invVP,invPrj,invView��������
    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * inView);
    //�B mousePosBack���x�N�g���ɕϊ�
    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    //�C �B��invVP,invPrj,invView���|����
    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * inView);

        for (int x = 0; x < 15; x++)
        {
            for (int z = 0; z < 15; z++)
            {
                for (int y = 0; y < table_[x][z].height + 1; y++)
                {
                    //�D �A����C�Ɍ������ă��C��ł�(�Ƃ肠�������f���ԍ���)hModel[0])
                    RayCastData data;
                    XMStoreFloat4(&data.start, vMouseFront);
                    XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                    Transform trans;
                    trans.position_.x = x;
                    trans.position_.y = y;
                    trans.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);
                    Model::RayCast(hModel_[0], data);

                    //�E ���C������������u���[�N�|�C���g�Ŏ~�߂�
                    if (data.hit)
                    {
                        break;
                    }
                }
            }
        }
    
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

//�J��
void Stage::Release()
{
}

void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].blocks = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}

//�U�̃_�C�A���O�v���V�[�W��
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        //�_�C�A���O���ł����Ƃ�
    case WM_INITDIALOG:
        // GetDlgItem(hDlg, IDC_RADIO_UP);
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //�R���{�{�b�N�X�̏����l
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�����K");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);

        return TRUE;

    case WM_COMMAND:
        select_ = SendMessage(GetDlgItem(hDlg, IDD_DIALOG1), CB_GETCURSEL, 0,0);
    }
    return FALSE;
}

#else

#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include <iostream>


//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++)
        hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++)
        for (int z = 0; z < ZSIZE; z++)
            SetBlockHeight(x, z, 0);

    
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
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
    //���f���f�[�^�̃��[�h
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

//�X�V
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


    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++) 
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
    }

}

//�`��
void Stage::Draw()
{
    Transform BlockTrans;//Transform�^�̕ϐ�
    //Transform�^ -> �ʒu,����,�傫���������^
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


//�J��
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

void Stage::Save()
{
    char fileName[MAX_PATH] = "SaveData.map";

    //�u�t�@�C����ۑ��v�@�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "map";

    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //�L�����Z�������璆�f
    if (selFile == FALSE) return;


    //�Z�[�u�̃��[�`��
    HANDLE hFile;        //�t�@�C���̃n���h��
    hFile = CreateFile(
        fileName,                 //�t�@�C����
        GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
        0,                      //���L�i�Ȃ��j
        NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
        CREATE_ALWAYS,           //�쐬���@
        FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
        NULL);                  //�g�������i�Ȃ��j

    std::string Stagedata = std::to_string(XSIZE) + "," + std::to_string(ZSIZE) + "\n"; // �X�e�[�W�̃T�C�Y��ǉ�

    for (int z = 0; z < ZSIZE; z++)
    {
        for (int x = 0; x < XSIZE; x++)
        {
            // �u���b�N�̍����Ǝ�ނ𕶎���ɕϊ����ăR���}�ŋ�؂��ĘA��
            Stagedata += std::to_string(table_[x][z].height) + "," + std::to_string(table_[x][z].blocks);

            if (x < XSIZE - 1)
            {
                Stagedata += ","; // XSIZE - 1 �̂Ƃ��̓R���}��ǉ�
            }
        }

        if (z < ZSIZE - 1)
        {
            Stagedata += "\n"; // ZSIZE - 1 �̂Ƃ��͉��s������ǉ�
        }
    }

    DWORD bytes = 0;
    WriteFile(
        hFile,      //�t�@�C���n���h��
        Stagedata.c_str(),  //�ۑ�������������
        (DWORD)strlen(Stagedata.c_str()),         //�ۑ����镶����
        &bytes,     //�ۑ��������T�C�Y
        NULL
    );
    CloseHandle(hFile);

}

void Stage::Road()
{
    char fileName[MAX_PATH] = "SaveData.map";

    //�u�t�@�C�����J���v�@�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "map";

    //�u�t�@�C�����J���v�_�C�A���O
    BOOL selFile;
    selFile = GetOpenFileName(&ofn);

    //�L�����Z�������璆�f
    if (selFile == FALSE) return;


    HANDLE hFile;        //�t�@�C���̃n���h��
    hFile = CreateFile(
        fileName,                 //�t�@�C����
        GENERIC_READ,           //�A�N�Z�X���[�h�i�ǂݍ��ݐ�p�j
        0,                      //���L�i�Ȃ��j
        NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
        OPEN_EXISTING,           //�쐬���@
        FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
        NULL);                  //�g�������i�Ȃ��j


    //�t�@�C���̃T�C�Y���擾
    DWORD fileSize = GetFileSize(hFile, NULL);

    //�t�@�C���̃T�C�Y�����������m��
    char* data;
    data = new char[fileSize];

    DWORD dwBytes = 0; //�ǂݍ��݈ʒu

    ReadFile(
        hFile,     //�t�@�C���n���h��
        data,      //�f�[�^������ϐ�
        fileSize,  //�ǂݍ��ރT�C�Y
        &dwBytes,  //�ǂݍ��񂾃T�C�Y
        NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

    CloseHandle(hFile);

    for (int x = 0; x < XSIZE; x++)
        for (int x = 0; x < ZSIZE; x++)
        {

        }


}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�����K"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��"));
        (SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��"));

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
    }
    return FALSE;
}

#endif