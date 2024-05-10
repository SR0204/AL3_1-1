#pragma once

#include "GameScene.h"
#include "WorldTransform.h"

/// <summary>
/// 天球
/// </summary>
class Skydome {

public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Skydome();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Skydome();

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

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	//3Dモデル
	Model* modelSkydome_ = nullptr;
};
