#include"Model.h"

namespace Model
{
	int Load(std::string fileName)
	{
		//�t�@�C�����̃��f����ǂݍ���ŁA�������f�����̂��̂��������炻�̃��f���ԍ�(�z��̃C���f�b�N�X-1)��Ԃ��֐�
		//�������O�̃��f�����Ȃ�������A���f����ǂݍ���ŁA�x�N�^�ɒǉ�

		ModelData* pData = new ModelData;
		pData->mFileName_ = fileName;
		pData->pfbx_ = nullptr;

		//�t�@�C���l�[����������������ǂ܂Ȃ�
		for (auto& e : _datas)
		{
			if (e->mFileName_ == fileName)
			{
				pData->pfbx_ = e->pfbx_;
				break;
			}
		}

		if (pData->pfbx_ == nullptr)
		{
			pData->pfbx_ = new Fbx;
			pData->pfbx_->Load(fileName);	
		}

		_datas.push_back(pData);
		return(_datas.size() - 1);
	}
	void SetTransform(int hModel, Transform& transform)
	{
		//���f���ԍ���_datas�̃C���f�b�N�X
		_datas[hModel]->Transform_ = transform;
	}
	void Draw(int hModel)
	{
		//���f���ԍ��́A_datas�̃C���f�b�N�X
		_datas[hModel]->pfbx_->Draw(_datas[hModel]->Transform_);
	}
}