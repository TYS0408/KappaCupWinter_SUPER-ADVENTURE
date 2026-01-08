#pragma once
class GameOver;
class Game;
class GoalPole;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();

	bool Start();

	void Move();

	void Rotation();


	void Render(RenderContext& rc);

	void ManageState();

	void PlayAnimation();

	//void ResetStatus();

	void ThrowBone();//取得した骨を投げる処理
	const Vector3& GetPos()
	{
		return m_position;
	}
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	//後で検索
	Vector3 m_forward = Vector3::AxisZ;

	Vector3 m_moveSpeed;
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	int m_HP = 3;//プレイヤーの体力

	static constexpr int Max_HP = 3;
	Vector3 m_position;//座標

	bool InvincibleJuge = false;//無敵か無敵じゃないかのフラグ

	bool Shot = false;//発射フラグ
	
	float InvincibleTime = 3.0f;//無敵時間

	//ノックバック処理
	bool m_isKnockBack = false;
	float m_knockBackTime = 0.0f;
private:
	//メンバ関数
	ModelRender m_modelRender;

	
	Vector3 m_respawn;//リスポーン

	Quaternion m_rot;//回転処理

	CharacterController m_characterController;//当たり判定

	GameOver* m_gameover = nullptr;

	Game* m_game = nullptr;

	GoalPole* m_goalPole = nullptr;

	bool IsDead = false;//死亡フラグ

	int m_playerState = 0;//プレイヤーステート
	

	//点滅用
	float m_blinkTimer = 0.0f;
	float m_blinkInterval = 0.1f;//点滅間隔
	bool m_isVisible = true;

	

	//アニメーション
	enum EnPlayAnimation
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];

};

