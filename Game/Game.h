#pragma once
#include "Level3DRender/LevelRender.h"
#include"Display_Bone.h"
#include"sound/SoundSource.h"
class Player;
class Enemy1;
class BackGround;
class GameCamera;
class GameOver;
class Enemy2;
class AppearStage;
class TimerImage;
class Display_Bone;
class GoalPole;
class GameClear;
class Game : public IGameObject
{
public:

	
	Game() {};
	~Game();
	bool Start();

	void Update();

	void InitSky();

	void TimerDraw();//タイマーの表示

	void HPDraw();//HP表示

	//void ResetGameStatus();

void OnGoal();//ゴール通知

	void UnregisterEnemy1(Enemy1* enemy1);
	void UnregisterEnemy2(Enemy2* enemy2);
	void Render(RenderContext& rc);

	
//敵が骨に切り替わる処理
	void OnDeleteBone(const Vector3 & pos);
	
	void OnGetBone();

	//敵を倒したときにステージを出すための変数
	int m_killCount = 0;

	int m_haveBoneCount = 0;//所持している骨の数

	float m_deathCount = 2.0;//敵を倒したときに骨を秒数

	bool IsCreateBone = false;//ノコノコを倒した時に骨に切り替えるフラグ

	bool IsDelete = false;//削除処理
	
	bool isGameClear = false;

	float m_LimitTime = 60.0f;//残り時間
	//static constexpr float LIMIIT_TIME_MAX = 90.0f;
	//float m_LimitTime = 30.0f;//残り時間

	std::vector<IGameObject* >GetEnemylist() ;//骨に当たることができるオブジェクト

private:

	//後で検索しておく
	std::vector<Display_Bone*>m_bones;//単数から複数へ(骨の管理用)

	

	ModelRender m_modelRender;//モデルレンダー

	FontRender timerFontRender;//時間表示

	FontRender hpFontRender;//HP表示

	FontRender boneFontRender;//骨の表示

	SpriteRender m_RedHeartRender[3];//赤いハート

	SpriteRender m_BlackHeartRender[3];//黒いハート

	SpriteRender m_BoneRender[6];//骨

	SpriteRender m_BlackBoneRender[6];//黒い骨
	

	//敵の配列
	//全てnullptrで初期化している
	Enemy1* m_enemy[6] = {};

	Enemy2* m_enemy2[6] = {};

	Player* m_player = nullptr;//プレイヤー

	BackGround* m_backGround = nullptr;//バックグランド

	GameCamera* m_gameCamera = nullptr;//ゲームカメラ

	SkyCube* m_skycube = nullptr;//スカイキューブ

	Game* game = nullptr;//ゲーム

	GameOver* m_gameOver = nullptr;//ゲームオーバー

	GameClear* m_gameClear = nullptr;

	AppearStage* m_appearStage = nullptr;//クリボーを三体倒すと現れるステージ

	TimerImage* m_timerImage = nullptr;//時計のUI

	Display_Bone* m_displayBone = nullptr;//骨を出すためのインスタンス

	GoalPole* m_goalpole = nullptr;


	SoundSource* gameBGM = nullptr;
	int m_SkyCubeType = enSkyCubeType_NightToon_2;

	

	//GameOverかどうかを決めるフラグ
	bool m_isEnd = false;
	bool isClear = false;

};
