#pragma once
#include "Engine/GameObject.h"

class Fbx;

class Enemy :public GameObject
{
private:
	Fbx* pFbx;
	int hModel_;
	public:
		//コンストラクタ
		Enemy(GameObject * parent);

		//初期化
		void Initialize() override;

		//更新
		void Update() override;

		//描画
		void Draw() override;

		//開放
		void Release() override;
};
