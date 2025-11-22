#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include"Enemy1.h"
#include"Title.h"
#include"GameClear.h"
#include"GameOver.h"
#include"Enemy2.h"
#include"AppearStage.h"
#include"nature/SkyCube.h"
#include"TimerImage.h"
#include"graphics/RenderingEngine.h"

namespace
{
	const int hpPos = 3;

	//赤いハートの座標
	Vector3 m_RedHealthPos[hpPos] =
	{
		{-800.0f, 500.0f, 0.0f,},
		{-720.0f, 500.0f, 0.0f},
	    {-640.0f, 500.0f, 0.0f,}
	};
	//黒いハートの座標
	Vector3 m_BlackHealthPos[hpPos] =
	{
		{-800.0f, 500.0f, 0.0f,},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f,}
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
	
	if (m_enemy[0] != nullptr)
	{
		//エネミーを削除
		DeleteGO(m_enemy[0]);
		m_enemy[0] = nullptr;
	}
	
	if (m_enemy[1] != nullptr)
	{
		DeleteGO(m_enemy[1]);
		m_enemy[1] = nullptr;
	}
	
	if (m_enemy[2] != nullptr)
	{
		DeleteGO(m_enemy[2]);
		m_enemy[2] = nullptr;
	}

	if (m_enemy2 != nullptr)
	{
		//エネミー２のモデル削除
		DeleteGO(m_enemy2);
		m_enemy2 = nullptr;
	}
	
	if (m_timerImage != nullptr)
	{
		DeleteGO(m_timerImage);
		m_timerImage = nullptr;
    }

	if (m_appearStage != nullptr)
	{
		DeleteGO(m_appearStage);
		m_appearStage = nullptr;
	}
	
;
	

}


bool Game::Start()
{
	////ポイントライトを作成
	//auto* pointLight = g_sceneLight->NewPointLight();
	//pointLight->SetPosition(Vector3(5.0f, 55.0f, 0.0f));
	//pointLight->SetColor(0.1f, 0.1f, 10.0f);
	//pointLight->SetRange(100.0f);
	//pointLight->SetAffectPowParam(1.0f);
	//pointLight->Update();



	

	//HPのUIをfor文で追加
	for (int i = 0; i < 3; i++)
	{

		m_RedHeartRender[i].Init("Assets/Sprite/Heart.dds", 100.0f, 100.0f);
		m_BlackHeartRender[i].Init("Assets/Sprite/BlackHeart3.dds", 100.0f, 100.0f);

	}
	

	InitSky();

	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0, "backGround");
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_enemy2 = NewGO<Enemy2>(0, "enemy2");

	m_timerImage = NewGO<TimerImage>(0, "timerimage");

	//m_appearStage = NewGO<AppearStage>(0, "appearstage");
	

	//m_timerImage = NewGO<TimerImage>(0, "timerimage");
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


	if (m_killCount >= 3 && m_appearStage ==nullptr)
	{
		//m_appearStage = FindGO<AppearStage>("appearstage");
	    m_appearStage = NewGO<AppearStage>(0, "appearstage");
	}

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
	int seconds = (int)m_LimitTime;
	m_LimitTime -= g_gameTime->GetFrameDeltaTime();
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"%03d", seconds);

	timerFontRender.SetText(timerText);
	//座標
	timerFontRender.SetPosition({ 800.0f,530.0f,0.0f });
	//文字の大きさ
	timerFontRender.SetScale(2.0f);
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
