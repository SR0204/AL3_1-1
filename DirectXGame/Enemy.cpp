#include "Enemy.h"
#include <numbers>
#include "MathUtilityForText.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position; // 初期配置

	worldTransform_.translation_.x = 1;
	worldTransform_.translation_.y = 1;

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
