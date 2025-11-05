#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include"Enemy1.h"
#include"nature/SkyCube.h"
#include"graphics/RenderingEngine.h"

Game::Game()
{
	
}


Game::~Game()
{

}


bool Game::Start()
{

	//これはm_enemyをm_enemy自身の値で初期化しようとしている
	/*{
		m_enemy[0],
		m_enemy[1],
		m_enemy[2],
	};*/

	for (int i = 0; i < 3; i++)
	{
		m_enemy[i] = NewGO<Enemy1>(0, "enemy1");
	}


	m_enemy[0]->m_position = { 0.0f,0.0f,300.0f };
	m_enemy[1]->m_position = { 50.0f,0.0f,300.0f };
	m_enemy[2]->m_position = { -50.0f,0.0f,300.0f };

	InitSky();
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_player = NewGO<Player>(0, "player");
	return true;
}

void Game::Update()
{

}

void Game::InitSky()
{
	DeleteGO(m_skycube);
	m_skycube = NewGO<SkyCube>(0, "skycube");
	m_skycube->SetLuminance(1.0f);//明るさ設定
	m_skycube->SetType((EnSkyCubeType)m_SkyCubeType);//スカイキューブのタイプ設定
	g_renderingEngine->SetAmbientByIBLTexture(m_skycube->GetTextureFilePath(), 1.0f);
	//環境光の計算のためのIBLテクスチャをセット
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

//void Game::Render(RenderContext& rc)
//{
//	m_modelRender.Draw(rc);
//}
