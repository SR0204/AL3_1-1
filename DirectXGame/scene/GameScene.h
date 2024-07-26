#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<vector>
#include"DebugCamera.h"
#include"Skydome.h"
#include "Player.h"
#include"MapChipField.h"
#include"CameraController.h"
#include"Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void GenerateBlocks();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	/// ゲームシーン用
	uint32_t textureHandle_ = 0;

	// 3Dモデルの生成
	Model* model_ = nullptr;


	// 自キャラ
	Player* player_ = nullptr;

	// 3Dモデルデータ
	Model* modelBlock_ = nullptr;

	//天球
	Skydome* skyDome_ = nullptr;

	//天球モデルデータ
	Model* modelSkydome_ = nullptr;

	Model* modelPlayer_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//マップチップフィールド
	MapChipField* mapChipFiled_;

	//カメラビュープロジェクション
	ViewProjection* CameraViewProjection_;

	//カメラコントローラー
	CameraController* CameraController_;

	//敵
	Enemy* enemy_ = nullptr;
};
