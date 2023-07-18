#pragma once
#include "GameObject.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理

//ゲームシーンを列挙
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
};

class SceneManager :
    public GameObject
{
private:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
public:

	//コンストラクタ
	SceneManager(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//シーンを切り替え
	void ChangeScene(SCENE_ID _next);
};

