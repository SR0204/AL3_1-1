#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {

	// NULLポインタチェック
	assert(model);

	// 引数
	model_ = model;
	textureHandle_ = textureHandle;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.translation_.x = 2;
	worldTransform_.translation_.y = 2;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {

	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}