#include "Player.h"
#include "MathUtilityFortext.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	// Nullポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position; // 初期配置

	worldTransform_.translation_.x = 5;
	worldTransform_.translation_.y = 5;

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {
	// 行列を更新して定数バッファに転送
	worldTransform_.UpdateMatrix();

	// 移動入力
	// 左右移動
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			// 左移動中の右入力
			if (velocity_.x < 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAcceleration);
			}
			acceleration.x += kAcceleration;
			// 左右状態切り替え
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;

				turnFirstRotationY_ = worldTransform_.translation_.y;
				turnTimer_ = kTimeTurn;
			}

		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 右移動中の左入力
			if (velocity_.x > 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAcceleration);
			}

			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;

				turnFirstRotationY_ = worldTransform_.translation_.y;
				turnTimer_ = kTimeTurn;

			}

			acceleration.x -= kAcceleration;
		}

		// 加速/減速
		velocity_ += acceleration;

	} else {
		// 非入力時は移動減衰をかける（kAccelerationは速度減衰率）
		velocity_.x *= (1.0f - kAttenuation);
	}

	// 旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1 / 60.0f;

		// 左右の自キャラ角度テーブル(左右の向き状態に合わせて、適切な角度に回転する処理
		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,
		    std::numbers::pi_v<float> * 3.0f / 2.0f,
		};

		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);

	}


	// 最大速度制限
	velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	// 移動
	worldTransform_.translation_ += velocity_;

	// 行列計算
	worldTransform_.UpdateMatrix();
}
/// <summary>
/// 描画処理
/// </summary>
void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
