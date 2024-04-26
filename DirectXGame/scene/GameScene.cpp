#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelBlock_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//  3Dモデルの生成
	modelBlock_ = Model::CreateFromOBJ("cube");

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;

	// ブロック一個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更する
	// 列数を設定
	worldTransformBlocks_.resize(kNumBlockHorizontal);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		// 一列の要素数を設定
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * i;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * j;
		}
	}

	// ビュープロジェクション初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {

	//// ブロックの更新
	// for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {

	//	// 平行移動
	//	Matrix4x4 result{
	//	    1.0f, 0.0f, 0.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f, 0.0f,
	//		0.0f, 0.0f, 1.0f, 0.0f,
	//		worldTransformBlock->translation_.x,
	//		worldTransformBlock->translation_.y,
	//		worldTransformBlock->translation_.z,
	//	    1.0f};

	//	// アフィン変換行列の作成
	//	worldTransformBlock->matWorld_ = result;

	//	    // 定数バッファの転送する
	//	   worldTransformBlock->TransferMatrix();
	//}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlock, viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
