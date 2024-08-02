#include "Enemy.h"
#include "MathUtilityForText.h"
#include "cassert"
#include <numbers>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position; // 初期配置

	// worldTransform_.translation_.x = 1;
	// worldTransform_.translation_.y = 1;

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;
}

void Enemy::Update() {

	// 移動
	worldTransform_.translation_ += velocity_;

	// タイマーを加算
	walkTimer_ += 1.0f / 60.0f;

	// 回転アニメーション
	worldTransform_.rotation_.x = std::sin(2 * std::numbers::pi_v<float> * walkTimer_ / kWalkMotionTime);

	/*float param = std::sin(2 * std::numbers::pi_v<float> * walkTimer_ / kWalkMotionTime);

	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;

	worldTransform_.rotation_.x =(radian);*/

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
