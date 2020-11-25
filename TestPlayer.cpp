/*---------------------------------------------------------

	[DirectX11.cpp]
	Author : 出合翔太

----------------------------------------------------------*/
#include "TestPlayer.h"
#include "InputDevice.h"
#include "AnimationModel.h"
#include "Engine.h"

namespace
{
	auto & s_dx = Wrapper::DirectX11::Instance();
}

void TestPlayer::Init()
{
	/*m_Model = new AnimationModel();
	m_Model->Load(Wrapper::DirectX11::Instance(), "asset\\model\\Akai_Idle.fbx");
	m_Model->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");*/
	m_AnimFrame = 0;
	m_BlendRate = 0.0f;

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
}

void TestPlayer::Uninit()
{
	/*m_Model->Unload();
	delete m_Model;*/
}

void TestPlayer::Update()
{
	m_AnimFrame++;
	m_BlendRate -= 0.03f;

	D3DXVECTOR3 Forward = GetForward();

	Engine::ObjectPool::SkeletalMeshUpdate(s_dx, Prefabs::SkeletalMesh::ModelID::Akai, "Idle", "Run", m_BlendRate, m_AnimFrame);

	if (KeyBoard::IsPress(DIK_W))
	{
		m_BlendRate += 0.06f;
		m_Position.x -= Forward.x * 0.1f;
		m_Position.z -= Forward.z * 0.1f;
	}
	if (KeyBoard::IsPress(DIK_S))
	{
		m_BlendRate += 0.06f;
		m_Position.x += Forward.x * 0.1f;
		m_Position.z += Forward.z * 0.1f;
	}

	if (KeyBoard::IsPress(DIK_A))
		m_Rotation.y -= 0.03f;
	if (KeyBoard::IsPress(DIK_D))
		m_Rotation.y += 0.03f;


	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;

	////メッシュフィールド高さ取得
	//CField* meshField = CManager::GetScene()->GetGameObject<CField>(LAYER_3D);
	//m_Position.y = meshField->GetHeight(m_Position);
}

void TestPlayer::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	s_dx.SetWorldMatrix(&world);
	Engine::ObjectPool::SkeletalMeshDraw(s_dx,Prefabs::SkeletalMesh::ModelID::Akai);
	
}
