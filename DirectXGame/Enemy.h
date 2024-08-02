#pragma once
#include"Model.h"
#include "WorldTransform.h"
class Enemy {


public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:

	//ワールドトランスフォーム(敵の座標)
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;


	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	//歩行の速さ
	static inline const float kWalkSpeed = 0.01f;

	//速度
	Vector3 velocity_ = {};

	//最初の角度（度）
	static inline const float kWalkMotionAngleStart =0.01f;

	//最後の角度(度)
	static inline const float kWalkMotionAngleEnd = 0.1f;

	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 5.0f;

	//経過時間
	float walkTimer_ = 0.0f;	
};
