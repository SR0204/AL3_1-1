#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {

	//自キャラの生成
	player_ = new Player();

	//自キャラの初期化
	player_->Initialize(model, textureHandle,viewProjection);

	//NULLポインタチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}



void Player::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}

void Player::Draw() {

	//3Dモデル
	model_->Draw(worldTransform_,viewProjection_,textureHandle_ );


}
