#include "GameScene.h"
#include "MapChipField.h"
#include "MathUtilityForText.h"
#include "Skydome.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ

	// 3Dモデルデータの解放
	delete modelBlock_;

	// 天球
	delete skyDome_;

	// デバッグカメラ
	delete debugCamera_;

	delete player_;

	delete model_;

	// マップチップフィールドの解放
	delete mapChipFiled_;

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

	// テクスチャ読み込み
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// 自キャラの生成
	player_ = new Player();

	//座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipFiled_->GetMapChipPositionByIndex(100, 100);

	// 自キャラの初期化
	player_->Initialize(modelPlayer_, &viewProjection_, playerPosition);

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 700;
	viewProjection_.Initialize();

	// マップチップフィールドの初期化
	mapChipFiled_ = new MapChipField;
	mapChipFiled_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();

	// 3Dモデルの生成
	modelBlock_ = Model::Create();

	// 天球の生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 天球
	skyDome_ = new Skydome();

	// 天球の初期化
	skyDome_->Initialize(modelSkydome_, &viewProjection_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}
void GameScene::Update() {
	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			// 平行移動
			// Matrix4x4 result{
			//    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, worldTransformBlock->translation_.x, worldTransformBlock->translation_.y, worldTransformBlock->translation_.z,
			//    1.0f};
			// 平行移動だけ代入
			// worldTransformBlock->matWorld_ = result;

			// 定数バッファに転送する
			/*worldTransformBlock->TransferMatrix();

			Matrix4x4 matWorld = MakeAffineMatrix(worldTransformBlock->scale_,
			    worldTransformBlock->rotation_, worldTransformBlock->translation_);

			worldTransformBlock->matWorld_ = matWorld;*/

			// アフィン返還と転送
			worldTransformBlock->UpdateMatrix();
		}
	}

	// 自キャラの更新
	player_->Update();

	// 天球の更新
	skyDome_->Update();

	// カメラの処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;             // デバッグカメラのビュー行列
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection; // デバッグカメラのプロジェクション行列
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // _DEBUG
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

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	// スカイドームの辨官
	skyDome_->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	player_->Draw();

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

// マップチップ生成
void GameScene::GenerateBlocks() {
	// 要素数
	const uint32_t kNumBlockVirtical = mapChipFiled_->GetNumBlockVirtical();
	const uint32_t kNumBlockHorizontal = mapChipFiled_->GetNumBlockHorizontal();

	// ブロック一個分の横幅
	// const float kBlockWidth = 2.0f;
	// const float kBlockHeight = 2.0f;

	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if (mapChipFiled_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipFiled_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}