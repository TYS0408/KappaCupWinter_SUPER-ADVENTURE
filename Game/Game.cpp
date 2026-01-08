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
#include"Display_Bone.h"
#include"GoalPole.h"
#include"sound/SoundSource.h"


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
		{-800.0f, 500.0f, 0.0f},
		{-720.0f, 500.0f, 0.0f},
		{-640.0f, 500.0f, 0.0f}
	};


	const int bonePos = 6;
	//骨の座標
	Vector3 m_BonePos[bonePos] =
	{
		{-850.0f,-400.0f,0.0f},
		{-750.0f,-400.0f,0.0f},
		{-650.0f,-400.0f,0.0f},
		{-550.0f,-400.0f,0.0f},
		{-450.0f,-400.0f,0.0f},
		{-350.0f,-400.0f, 0.0f} ,
	};

	Vector3 m_BlackBonePos[bonePos] =
	{
		{-850.0f,-400.0f,0.0f},
		{-750.0f,-400.0f,0.0f},
		{-650.0f,-400.0f,0.0f},
		{-550.0f,-400.0f,0.0f},
		{-450.0f,-400.0f,0.0f},
		{-350.0f,-400.0f,0.0f},
	};


}



Game::~Game()
{
	if (m_player->m_HP <= 0 || m_LimitTime <= 0)
	{
		//DeleteGO(m_gameCamera);
		//m_gameCamera = nullptr;

		///*DeleteGO(m_player);
		//m_player = nullptr;*/

		DeleteGO(m_timerImage);
		m_timerImage = nullptr;

	}
	//背景を削除
	if (m_backGround != nullptr)
	{

		DeleteGO(m_backGround);
		m_backGround = nullptr;
	}
	//プレイヤーを削除
	if (m_player != nullptr)
	{

		DeleteGO(m_player);
		m_player = nullptr;
	}

	

	if (gameBGM != nullptr)
	{
		DeleteGO(gameBGM);
		gameBGM = nullptr;
    }
	

	if (m_goalpole)
	{
		DeleteGO(m_goalpole);
		m_goalpole = nullptr;
	}
	//ゲームカメラを削除
	if (m_gameCamera != nullptr)
	{

		DeleteGO(m_gameCamera);
		m_gameCamera = nullptr;
	}


	//これは C++ では配列名 = 配列の先頭アドレス
	//しかし nullptr と比較しても絶対に true にも false にもならない
	//つまり 常に true 扱い
	//if (m_enemy != nullptr)  // ← 配列なので絶対に nullptr にならない！
	//これは 無意味。


	

	//エネミー１を削除
	for (int i = 0; i < 6; i++)
	{
		if (m_enemy[i] != nullptr)
		{
			DeleteGO(m_enemy[i]);
			m_enemy[i] = nullptr;
		}
	}

	//エネミー２を削除

	for (int j = 0; j < 6; j++)
	{
		if (m_enemy2[j] != nullptr)
		{
			DeleteGO(m_enemy2[j]);
			m_enemy2[j] = nullptr;
		}

	}

	

	if (m_appearStage != nullptr)
	{
		DeleteGO(m_appearStage);
		m_appearStage = nullptr;
	}

	for (auto h : m_bones)
	{
		if (h)
		{
			DeleteGO(h);
		}
	}
	//std::vector<Bone_Obj> m_bones;* の//中身をすべて消して,「空の配列」に戻すための処理
	m_bones.clear();
	
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
	
	//ゲームのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(0, "Assets/BGM・SE/GameBGM.wav");

	//BGMの再生
	gameBGM = NewGO<SoundSource>(0,"soundsource");
	gameBGM->Init(0);
	gameBGM->Play(true);


	
	m_gameClear = FindGO<GameClear>("gameclear");

	m_goalpole = FindGO<GoalPole>("goalpole");

	//HPのUIをfor文で追加
	for (int i = 0; i < 3; i++)
	{

		m_RedHeartRender[i].Init("Assets/Sprite/Heart.dds", 100.0f, 100.0f);
		m_BlackHeartRender[i].Init("Assets/Sprite/BlackHeart3.dds", 100.0f, 100.0f);

	}


	//骨のUIをfor文で追加
	for (int i = 0; i < 6; i++)
	{
		m_BoneRender[i].Init("Assets/Sprite/Bone.dds", 300.0f, 300.0f);
		m_BlackBoneRender[i].Init("Assets/Sprite/BlackBone.dds", 300.0f, 300.0f);
	}
	

	InitSky();

	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0, "backGround");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_timerImage = NewGO<TimerImage>(0, "timerimage");

	//m_goalpole = NewGO<GoalPole>(0, "goalpole");
	//これはm_enemyをm_enemy自身の値で初期化しようとしている
	/*{
		m_enemy[0],
		m_enemy[1],
		m_enemy[2],
	};*/
	//エネミー１をfor文で追加
	for (int i = 0; i < 6; i++)
	{
		m_enemy[i] = NewGO<Enemy1>(0, "enemy1");
	}

	//エネミーの初期位置を設定する
	m_enemy[0]->SetPosition(Vector3(0.0f, 0.0f, 500.0f));
	m_enemy[1]->SetPosition(Vector3(200.0f, 0.0f, 400.0f));
	m_enemy[2]->SetPosition(Vector3(-200.0f, 0.0f, 200.0f));
	m_enemy[3]->SetPosition(Vector3(-500.0f, 550.0f, 2000.0f));
	m_enemy[4]->SetPosition(Vector3(-900.0f, 550.0f, 2000.0f));
	m_enemy[5]->SetPosition(Vector3(700.0f, 550.0f, 2000.0f));


	//エネミー２をfor文で追加

	for (int j = 0; j < 6; j++)
	{
		m_enemy2[j] = NewGO<Enemy2>(0, "enemy2");
	}
	//エネミー２の初期座標を設定
	m_enemy2[0]->SetPosition(Vector3(0.0f, 330.0f, 1000.0f));
	m_enemy2[1]->SetPosition(Vector3(200.0f, 330.0f, 1000.0f));
	m_enemy2[2]->SetPosition(Vector3(-200.0f, 330.0f, 1000.0f));
	m_enemy2[3]->SetPosition(Vector3(-700.0f, 550.0f, 2000.0f));
	m_enemy2[4]->SetPosition(Vector3(500.0f, 550.0f, 2000.0f));
	m_enemy2[5]->SetPosition(Vector3(900.0f, 550.0f, 2000.0f));

	m_displayBone = nullptr;
	return true;
}


void Game::Update()
{
	TimerDraw();
	
	if (!m_isEnd)
	{
		HPDraw();
	}
	

	//BoneDraw();
	//後で検索
	for (int i = 0; i < m_bones.size(); )
	{
		Display_Bone* bone = m_bones[i];

		// 死んだ骨は削除
		if (bone == nullptr || bone->IsDead())
		{
			DeleteGO(bone);
			m_bones.erase(m_bones.begin() + i);
			//ここでcontinueすることで下の処理を飛ばしている
			continue;
		}

		 //生きている骨だけ更新
		bone->Update();
		i++;
	}


	
	//キルカウントが3以上ならステージを出現させる
	if (m_killCount >= 3 && m_appearStage == nullptr)
	{
		m_appearStage = NewGO<AppearStage>(0, "appearstage");
	}

	if (m_killCount >= 12 && m_goalpole == nullptr)
	{
		m_goalpole = NewGO<GoalPole>(0, "goalpole");
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



	for (int i = 0; i < 6; i++)
	{
		m_BoneRender[i].SetPosition(m_BonePos[i]);
		m_BoneRender[i].Update();
	}

	for (int i = 0; i < 6; i++)
	{
		m_BlackBoneRender[i].SetPosition(m_BlackBonePos[i]);
		m_BlackBoneRender[i].Update();
	}


	//HPが0になったらゲームオーバーにする
	if (m_player->m_HP <= 0||m_LimitTime<=0)
	{
		if (m_gameOver == nullptr)
		{
			// BGM停止
			if (gameBGM)
			{
				gameBGM->Stop();
			}
			m_gameOver = NewGO<GameOver>(0, "gameover");
		}
		m_isEnd = true;
		return;
	}





	/*if (m_goalpole && m_goalpole->m_isGoal)
	{
		if (m_gameClear == nullptr)
		{
			m_gameClear = NewGO<GameClear>(0, "gameclear");
		}

		DeleteGO(m_goalpole);
		m_goalpole = nullptr;

		m_isEnd = true;
		return;
	}*/
		
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

	/*if (m_LimitTime <= 0.0f)
	{
		m_gameOver = NewGO<GameOver>(0, "gameover");
		m_isEnd = true;

	}*/
}



void Game::HPDraw()
{
	hpFontRender.SetText(L"HP");
	//座標
	hpFontRender.SetPosition({ -950.0f,540.0f,0.0f });
	//文字の大きさ
	hpFontRender.SetScale(2.0f);
	//文字の色
	hpFontRender.SetColor(g_vec4White);
}


void Game::OnGoal()
{
	if (m_goalpole && m_goalpole->m_isGoal)
	{
		if (m_gameClear == nullptr)
		{
			m_gameClear = NewGO<GameClear>(0, "gameclear");
			DeleteGO(m_goalpole);
			m_goalpole = nullptr;

			// BGM停止
			if (gameBGM)
			{
				gameBGM->Stop();
			}
		}
	}
	m_isEnd = true;
}



//「敵が倒れた位置に骨を生成して、後でまとめて管理できるようにする処理」
void Game::OnDeleteBone(const Vector3& pos)//←このposは骨を生成する位置
{
	/*m_deathCount -= g_gameTime->GetFrameDeltaTime();

	if (m_deathCount <= 0.0f)
	{*/
		Display_Bone* bone = NewGO<Display_Bone>(0, "display_bone");

		//敵を倒した場所に骨を生成する
		bone->SetPosition(pos);

		//生成した骨オブジェクト bone を 骨のリスト m_bones に追加、これにより後でまとめて削除したり、管理したりすることができる。
		m_bones.push_back(bone);
	//}

	
}


void Game::UnregisterEnemy1(Enemy1* enemy)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_enemy[i] == enemy)
		{

			m_enemy[i] = nullptr;
			return;
	     }

	}

}


void Game::UnregisterEnemy2(Enemy2* enemy2)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_enemy2[i] == enemy2)
		{
			m_enemy2[i] = nullptr;
			return;
		}
	}
}


//後で検索
 std::vector<IGameObject*>Game::GetEnemylist()
{
	std::vector<IGameObject*>list;

	for (int i = 0; i < 6; i++)
	{
		if (m_enemy[i] && !m_enemy[i]->IsDead)
		{
			list.push_back(m_enemy[i]);
		}
	}



	for (int i = 0; i < 6; i++)
	{
		if (m_enemy2[i] && !m_enemy2[i]->IsDead)
		{
			list.push_back(m_enemy2[i]);
		}
	}
	return list;
}



void Game::OnGetBone()
{
	//取得した骨の数を増やす
	m_haveBoneCount++;
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

	hpFontRender.Draw(rc);

	//boneFontRender.Draw(rc);

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

	int m_BoneCount = m_haveBoneCount;

	for (int i = 0; i < 6; i++)
	{
		if (i < m_BoneCount)
		{
			//所持している骨だけ描画
			m_BoneRender[i].Draw(rc);
		}

		else
		{
			//持っていないところは黒い骨
			m_BlackBoneRender[i].Draw(rc);
		}
	}
	

	
}