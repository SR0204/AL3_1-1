#include "Player.h"
#include <cassert>
#include<numbers>
#include<algorithm>


void Player::Initialize(Model* model,ViewProjection* viewProjection, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	// 引数
	model_ = model;
	//textureHandle_ = textureHandle;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.translation_.x = 2;
	worldTransform_.translation_.y = 2;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}



void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

	//移動入力
	//左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
	
		//左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

			acceleration.x += kAcceleration;

		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

			acceleration.x -= kAcceleration;
		} //else {
		//非入力時は移動減衰をかける
		/*	velocity_.x *= (1.0f - kAcceleration);
		}*/



		//加速・減速
		velocity_ += acceleration;

		//最大速度制限
		//velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	}


	//移動
	worldTransform_.translation_ += velocity_;

	//行列計算
	worldTransform_.UpdateMatrix();

}

void Player::Draw() {

	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}