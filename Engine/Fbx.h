#if 0

#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include<vector>

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

//#pragma comment�̂Ƃ��� MT -> MD��Md�̂ǂ������ɒ��� �ǂ����ł��������ۂ�
//�w�b�_�[�Ńw�b�_�[���C���N���[�h����̂͂���܂��낵���Ȃ�

class Texture; //�O���錾�@cpp�Ńw�b�_�[���C���N���[�h����΂悢

using namespace std;

struct RayCastData
{
	XMFLOAT4 start;
	XMFLOAT4 dir;
	bool hit;
	float dist;
};

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;
		int			isTexture;
	};
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	struct MATERIAL //�}�e���A��
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};
	

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	//vector<int>indexCount_;
	int* indexCount_;

	VERTEX* pVertices_;
	int** ppIndex_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();

	//Draw����Ă΂��֐�
	void PassDataToCB(Transform transform);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();

	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void RayCast(RayCastData& rayData);

	
};

#else

#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")


class Texture;
struct RayCastData
{
	XMFLOAT4 start;
	XMFLOAT4 dir;
	bool hit;
	float dist;
};
class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4    diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
		int    isTextured;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};



	VERTEX* pVertices_;
	int** ppIndex_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�
	int* indexCount_;
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;


	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void	RayCast(RayCastData& rayData);
};

#endif



