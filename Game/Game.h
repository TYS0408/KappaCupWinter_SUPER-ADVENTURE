#pragma once
#include "Level3DRender/LevelRender.h"
class Player;
class Enemy1;
class BackGround;
class GameCamera;
class GameOver;
class Enemy2;
class AppearStage;
class TimerImage;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();

	void Update();

	void InitSky();

	void TimerDraw();//タイマーの表示

	void Render(RenderContext& rc);

	//敵を倒したときにステージを出すための変数
	int m_killCount = 0;

	bool IsCreateBone = false;//敵を倒したときに骨に切り替えるフラグ
private:
	//エネミー1の配列
	/*Vector3 m_pos[3] =
	{
		{0.0f,0.0f,400.0f,},
	   {200.0f,0.0f,400.0f},
		{-200.0f,0.0f,400.0f},
	};

	Vector3 m_pos2[3] =
	{
		{0.0f,250.0f,1000.0f},
		{200.0f,250.0f,1000.0f},
		{-200.0f,250.0f,1000.0f},
	};*/

	ModelRender m_modelRender;

	ModelRender m_BoneModelRender;//骨用のモデルレンダー

	FontRender timerFontRender;//時間表示

	SpriteRender m_RedHeartRender[3];//赤いハート

	SpriteRender m_BlackHeartRender[3];//黒いハート

	//敵の配列
	//全てnullptrで初期化している
	Enemy1* m_enemy[3] = {};

	Enemy2* m_enemy2[3] = {};

	Player* m_player = nullptr;//プレイヤー

	BackGround* m_backGround = nullptr;//バックグランド

	GameCamera* m_gameCamera = nullptr;//ゲームカメラ

	SkyCube* m_skycube = nullptr;//スカイキューブ

	Game* game = nullptr;//ゲーム

	GameOver* m_gameOver = nullptr;//ゲームオーバー

	

	AppearStage* m_appearStage = nullptr;//クリボーを三体倒すと現れるステージ

	TimerImage* m_timerImage = nullptr;
	int m_SkyCubeType = enSkyCubeType_NightToon_2;

	//float m_LimitTime = 90.0f;//残り時間
	float m_LimitTime = 30.0f;//残り時間

	//GameOverかどうかを決めるフラグ
	bool m_isEnd = false;
};

