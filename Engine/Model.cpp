#include"Model.h"
#include"Direct3D.h"
namespace Model
{
	//モデルのポインタをぶち込んでいくベクタ
	vector<ModelData*>_datas;

	int Load(std::string fileName)
	{
		//ファイル名のモデルを読み込んで、同じモデル名のものがあったらそのモデル番号(配列のインデックス-1)を返す関数
		//同じ名前のモデルがなかったら、モデルを読み込んで、ベクタに追加

		ModelData* pData = new ModelData;
		pData->mFileName_ = fileName;
		pData->pfbx_ = nullptr;

		//ファイルネームが同じだったら読まない
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
		//モデル番号は_datasのインデックス
		_datas[hModel]->Transform_ = transform;
	}
	void Draw(int hModel)
	{
		//モデル番号は、_datasのインデックス
		_datas[hModel]->pfbx_->Draw(_datas[hModel]->Transform_);
	}
	void Release()
	{
		bool isRefferd = false; //参照されているか
		for (int i= 0; i<_datas.size();i++)
		{
			for (int j = i + 1; j < _datas.size(); j++)
			{
				if (_datas[i]->pfbx_ == _datas[i]->pfbx_)
				{
					isRefferd = true;
					break;
				}
			}
			if (isRefferd == false)
			{
				SAFE_DELETE(_datas[i]->pfbx_);
			}
			SAFE_DELETE(_datas[i]);
		}
		_datas.clear();
		
	}
	void RayCast(int hModel, RayCastData& rayData)
	{
		//⓪モデルのトランスフォームをカリキュレーション
		_datas[hModel]->Transform_.Calclation();
		//①ワールド行列の逆行列
		XMMATRIX wInv = XMMatrixInverse(nullptr, _datas[hModel]->Transform_.GetWorldMatrix());
		//②レイの通過点を求める(モデル空間でのレイの方向ベクトルを求める)
		XMVECTOR vpass{ rayData.start.x + rayData.dir.x ,
					    rayData.start.y + rayData.dir.y ,
					    rayData.start.z + rayData.dir.z ,
					    rayData.start.w + rayData.dir.w };
		//③rayData.startをモデル空間に変換(①を掛ける)
		XMVECTOR vstart = XMLoadFloat4(&rayData.start);
		vstart = XMVector3TransformCoord(vstart, wInv); //transforncoordはw要素を無視してくれるらしい
		//④(視点から方向ベクトルをちょい伸ばした先)通過点(②)に①を掛ける
		vpass = XMVector3TransformCoord(vpass, wInv);
		//⑤raydata.dirを③から④に向かうベクトルにする(引数)
		vpass = vpass - vstart;
		XMStoreFloat4(&rayData.dir, vpass);
		//指定したモデル番号のFBXにレイキャスト!
		_datas[hModel]->pfbx_->RayCast(rayData);
	}
}