#pragma once
#include"Model.h"
#include "WorldTransform.h"
class Enemy {


public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;


	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};
