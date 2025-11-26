#pragma once
class Player;
class Game;
class Enemy2:  public IGameObject
{
public:
	Enemy2();
	~Enemy2();

	bool Start();

	void Update();

	void Move();//敵の移動処理

	void Tracking();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& pos);

	Game* m_game = nullptr;
private:
	ModelRender m_modelRender;//エネミー２のモデル(スケルトン)

	ModelRender m_modelBoneRender;//エネミーを踏みつけた後のモデル

	//SphereCollider m_sphereColider;

	BoxCollider m_BoxCollider;

	CharacterController m_characterController;
	Vector3 m_position;//スケルトンのポジション

	void Rotation();//回転の関数

	void SearchPlayer();//プレイヤーを見つけたかどうかの関数

	void Damege(Player* player);//ダメージを受ける関数

	void Dead();//死んだときの処理

	void ManageState();//ステート管理関数

	void Enemy2Animation();//アニメーション関数


	
	/*{
		m_position = pos;
	}*/

	

	
private:

	int m_enemy1State = 0;//エネミーのステート


	bool IsDead = false;//死んだか死んでないかのフラグ

	bool DeathAnimation = false;//死んだときにすぐアニメーションが流れないようにするためのフラグ

	bool m_isSearchPlayer = false;//プレイヤーを見つけたか、見つけてないかのフラグ

	Vector3 m_BoxColliderScale = Vector3(100.0f, 100.0f, 100.0f);

	Vector3 m_forward;//前方向

	Vector3 m_moveSpeed;//移動速度

	Vector3 m_HeadScale = Vector3(50.0f, 50.0f, 50.0f);

	//Vector3 m_BodyScale = Vector3(100.0f, 100.0f, 100.0f);

	Quaternion m_rotation;//回転

	Player* m_player = nullptr;

	//頭のゴーストオブジェクト
	PhysicsGhostObject m_HeadGhostObj;

	//胴体のゴーストオブジェクト
	PhysicsGhostObject m_BodyGhostObj;

	


	enum EnPlayAnimation
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Dead,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];

};

