#pragma once
#include "MathUtilityForText.h"
#include "ViewProjection.h"


class Player;

class CameraController {

public:
	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// プレイヤー追従
	Player* target_ = nullptr;

	// 追従対象とカメラの座標の差
	Vector3 targetOffset_ = {0, 0, -15.0f};
};
