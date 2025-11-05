#pragma once
class Player;
class Enemy1 : public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	bool Start();

	void Update();

	void Move();

	void TracKing();

	void ManageState();

	void Enemy1Animation();

	void Render(RenderContext& rc);

	Vector3 m_position;//エネミーのポジション;
private:
	

	int m_enemy1State = 0;//エネミーのステート
		void Rotation();

		void SearchPlayer();

		bool m_isSearchPlayer = false;


		ModelRender m_modelRender;//モデルレンダー

		Vector3 m_forward;//前方向

		Vector3 m_moveSpeed;//移動速度

		Quaternion m_rotation;//回転
		
		FontRender m_fontRender;//文字表示

		SphereCollider m_sphereCollider;//球の当たり判定

		CharacterController m_characterController;//キャラコン

		Player* m_player = nullptr;//プレイヤーポインター

		//アニメション再生
		enum EnPlayAnimation
		{
			enAnimationClip_Idle,
			enAnimationClip_Walk,
			enAnimationClip_Num,
		};
		AnimationClip animationClips[enAnimationClip_Num];

};

