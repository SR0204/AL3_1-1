#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	//自キャラの生成
	player_ = new Player();

	//自キャラの初期化
	player_->Initialize();

	//NULLポインタチェック
	assert(model);
}



void Player::Update() {}

void Player::Draw() {}
