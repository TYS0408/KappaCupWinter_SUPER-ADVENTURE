#pragma once
#include "Level3DRender/LevelRender.h"

class Player;
class Enemy1;
class BackGround;
class GameCamera;
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
private:
	//敵の配列
	//全てnullptrで初期化している
	Enemy1* m_enemy[3] = {};

	ModelRender m_modelRender;

	Player* m_player;

	Enemy1* m_enemy1;

	BackGround* m_backGround;

	GameCamera* m_gameCamera;

	Vector3 m_pos;

	SkyCube* m_skycube;

	FontRender timerFontRender;

	int m_SkyCubeType = enSkyCubeType_DayToon;
	float m_LimitTime = 90.0f;//残り時間
};

