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
	//void Render(RenderContext& rc);
private:
	//“G‚Ì”z—ñ
	//‘S‚Änullptr‚Å‰Šú‰»‚µ‚Ä‚¢‚é
	Enemy1* m_enemy[3] = {};

	ModelRender m_modelRender;

	Player* m_player;

	Enemy1* m_enemy1;

	BackGround* m_backGround;

	GameCamera* m_gameCamera;

	Vector3 m_pos;

	SkyCube* m_skycube;

	int m_SkyCubeType = enSkyCubeType_DayToon;
	
};

