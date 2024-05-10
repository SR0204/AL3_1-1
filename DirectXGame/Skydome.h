#pragma once

#include "WorldTransform.h"
#include "GameScene.h"

/// <summary>
/// 天球
/// </summary>
class Skydome {

public:
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
		//ワールド変換データ
	    WorldTransform worldTransform_;

		//モデル
	    Model* model_ = nullptr;
};
