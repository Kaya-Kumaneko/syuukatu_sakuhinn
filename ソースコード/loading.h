//=================================================================================================
// 
// ローディング管理 [loading.h]
//
//=================================================================================================
#pragma once
#include "scene.h"

class Loading : public Scene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};