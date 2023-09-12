#if 0

#pragma once
#include<string>
#include<vector>
#include"Fbx.h"
#include"Transform.h"

using std::string;
using std::vector;

namespace Model
{
	struct ModelData
	{
		//FBX
		Fbx* pfbx_;
		//�g�����X�t�H�[��
		Transform Transform_;
		//�t�@�C����
		string mFileName_;
	};

	//���f�������[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃��f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//���[���h�s���ݒ�
	//�����FhModel	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int hModel, Transform& transform);

	//�`��
	//�����FhModel	�`�悵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int hModel);

	void Release();

	void RayCast(int hModel, RayCastData& rayData);
}

#else

#pragma once
#include <string>
#include <vector>
#include "Transform.h"
#include "Fbx.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;

	};

	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	void Release();
	void RayCast(int hModel, RayCastData& rayData);
};

#endif

