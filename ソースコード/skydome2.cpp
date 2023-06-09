//=================================================================================================
//
// スカイドーム2処理 [skydome2.cpp]
//
//=================================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "model.h"
#include "skydome2.h"

#include "camera2.h"

void SkyDome2::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\skydome\\skydome003.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(500.0f, 500.0f, 500.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}

void SkyDome2::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SkyDome2::Update()
{
	Scene* scene = Manager::GetScene();
	Camera2* camera = scene->GetGameObject<Camera2>(LAYER_CAMERA);

	// ポジション取得
	D3DXVECTOR3 cameraPosition = camera->GetPosition();

	m_Position.x = cameraPosition.x;
	m_Position.z = cameraPosition.z;

}

void SkyDome2::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}