#include "Skydome.h"

//コンストラクタ
Skydome::Skydome() {}

//デストラクタ
Skydome::~Skydome() {

delete modelSkydome_;
}

void Skydome::Initialize() {

	//3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
}

void Skydome::Update() {}

void Skydome::Draw() {}
