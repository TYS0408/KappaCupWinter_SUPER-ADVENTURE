#pragma once
class Player;
class Game;
using namespace nsK2EngineLow;
class Enemy2 : public IGameObject
{
public:
	Enemy2() ;
	~Enemy2();

	bool Start();

	void Update();

	void Move();//敵の移動処理

	void Tracking();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& pos);

	void Rotation();//回転の関数

	void SearchPlayer();//プレイヤーを見つけたかどうかの関数

	void Damege(Player* player);//ダメージを受ける関数

	//void DropBone();//骨を落とす処理

	void Dead();//死んだときの処理

	void ManageState();//ステート管理関数

	void Enemy2Animation();//アニメーション関数

	void OnHitBone2();//骨に当たると死ぬ処理

	

	Vector3 GetBodyPos2();

	Vector3 m_position;//スケルトンのポジション

	bool IsDead = false;//死んだか死んでないかのフラグ
	const Vector3& GetPos()
	{
		return m_position;
	}

	Game* m_game = nullptr;


private:
	ModelRender m_modelRender;//エネミー２のモデル(スケルトン)

	

	//SphereCollider m_sphereColider;

	BoxCollider m_BoxCollider;

	CharacterController m_characterController;

	int m_enemy2State = 0;//エネミーのステート

	bool isCreateBone = false;//骨を生成するフラグ

	bool DeathAnimation = false;//死んだときにすぐアニメーションが流れないようにするためのフラグ

	bool IsSearchPlayer = false;//プレイヤーを見つけたか、見つけてないかのフラグ


	Vector3 m_BoxColliderScale = Vector3(100.0f, 100.0f, 100.0f);

	Vector3 m_forward;//前方向

	Vector3 m_moveSpeed;//移動速度

	Vector3 m_HeadScale = Vector3(50.0f, 50.0f, 50.0f);



	//Vector3 m_BodyScale = Vector3(100.0f, 100.0f, 100.0f);

	Quaternion m_rotation;//回転

	Player* m_player = nullptr;

	//Bone_Obj* m_boneObj = nullptr;

	Enemy2* m_enemy2 = nullptr;

	

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

