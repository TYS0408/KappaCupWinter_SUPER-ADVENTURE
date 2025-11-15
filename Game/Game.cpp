#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include"Enemy1.h"
#include"Title.h"
#include"GameClear.h"
#include"GameOver.h"
#include"nature/SkyCube.h"
#include"graphics/RenderingEngine.h"

namespace
{
	const int hpPos = 3;

	//赤いハートの座標
	Vector3 m_RedHealthPos[hpPos] =
	{
		{-400.0f, 250.0f, 0.0f,},
		{-300.0f, 250.0f, 0.0f},
	    {-200.0f,250.0f,0.0f,}
	};
	//黒いハートの座標
	Vector3 m_BlackHealthPos[hpPos] =
	{
		{-400.0f, 250.0f, 0.0f,},
		{-300.0f, 250.0f, 0.0f},
		{-200.0f,250.0f,0.0f,}
	};

}
Game::Game()
{
	
}


Game::~Game()
{
	//背景を削除
	DeleteGO(m_backGround);
	//プレイヤーを削除
	DeleteGO(m_player);
	//ゲームカメラを削除
	DeleteGO(m_gameCamera);
	
	//エネミーを削除
	DeleteGO(m_enemy[0]);
	DeleteGO(m_enemy[1]);
	DeleteGO(m_enemy[2]);
	
	

}


bool Game::Start()
{
	
	//HPのUIをfor文で追加
	for (int i = 0; i < 3; i++)
	{

		m_RedHeartRender[i].Init("Assets/Sprite/Heart.dds", 200.0f, 200.0f);
		m_BlackHeartRender[i].Init("Assets/Sprite/BlackHeart3.dds", 200.0f, 200.0f);

	}
	

	InitSky();

	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0, "backGround");
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	
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

	//エネミーの初期位置を設定する
	m_enemy[0]->SetPosition(Vector3(0.0f, 0.0f, 500.0f));
	m_enemy[1]->SetPosition(Vector3(200.0f, 0.0f, 400.0f));
	m_enemy[2]->SetPosition(Vector3(-200.0f, 0.0f, 200.0f));
		

	return true;
}

void Game::Update()
{
	TimerDraw();

	for (int i = 0; i < 3; i++)
	{
		m_RedHeartRender[i].SetPosition(m_RedHealthPos[i]);

		m_RedHeartRender[i].Update();
	}

	

	for (int i = 0; i < 3; i++)
	{
		m_BlackHeartRender[i].SetPosition(m_BlackHealthPos[i]);
	
		m_BlackHeartRender[i].Update();
	}


	
	
		
	
}

void Game::TimerDraw()
{

	//残り時間のテキスト
	int minute = (int)m_LimitTime / 60;
	int seconds = (int)m_LimitTime % 60;
	m_LimitTime -= g_gameTime->GetFrameDeltaTime();
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"残り時間:%02d:%02d", minute, seconds);

	timerFontRender.SetText(timerText);
	//座標
	
	timerFontRender.SetPosition({ -300.0f,540.0f,0.0f });
	//文字の大きさ
	timerFontRender.SetScale(1.5f);
	//文字の色
	timerFontRender.SetColor(g_vec4White);

	if (m_LimitTime <= 0.0f)
	{
		m_gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);



	}

	
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

void Game::Render(RenderContext& rc)
{
	timerFontRender.Draw(rc);
    int m_Health = m_player->m_HP;


	
	for (int i = 0; i < 3; i++)
	{
		//(例)/*m_Health = 2 のとき
			//i = 0 → 赤
			//i = 1 → 赤
			//i = 2 → 黒
		//i = 0　→ 0 < 2　→赤ハートを出す
		// i = 1→ 1 <  2　→赤ハートを出す 
		//i = 2 →2 < 2 →false→黒ハートを出す
		if (i < m_Health)
		{
			m_RedHeartRender[i].Draw(rc);
		}

		else
		{
			m_BlackHeartRender[i].Draw(rc);
		}
	}

	if (m_Health <= 0)
	{
		m_gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}
}
