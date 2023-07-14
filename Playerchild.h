#pragma once
#include "Engine/GameObject.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;} //開放処理


//前方宣言
class Fbx;
//■■シーンを管理するクラス
class Playerchild : public GameObject
{
	int hModel_;//モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Playerchild(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


