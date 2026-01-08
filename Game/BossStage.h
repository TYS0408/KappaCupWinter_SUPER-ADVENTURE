#pragma once
#include"sound/SoundEngine.h"
class Player;
class Enemy3;
class GameCamera;
class BossGameOver;
class Game;
class BossStage : public IGameObject
{
  public:
	  BossStage();
	  ~BossStage();


	  bool Start();

	  void Update();


	  void HPDraw();

	  void TimerDraw();

	  void OnGameClear();

	  void Render(RenderContext& rc);

	  void RequestRestart();

	  bool m_isClear = false;

private:
	ModelRender m_modelRender;

	FontRender  m_playerPosFontRender;

	FontRender timerFontRender;//時間表示

	FontRender hpFontRender;//HP表示


	SpriteRender m_RedHeartRender[3];//赤いハート

	SpriteRender m_BlackHeartRender[3];//黒いハート

	float m_LimitTime = 90.0f;//残り時間

	Enemy3* m_enemy3 = nullptr;

	Player* m_player = nullptr;

	SoundSource* bgm = nullptr;

	GameCamera* m_gameCamera = nullptr;//ゲームカメラ

	Game* m_game = nullptr;

	BossGameOver* m_bossgameover = nullptr;

	Vector3 m_position;

	PhysicsStaticObject m_physicsStaticObject;
};

