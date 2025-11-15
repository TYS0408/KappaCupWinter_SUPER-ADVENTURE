#pragma once
class Player;
class Enemy1 : public IGameObject
{
public:

	Enemy1();
	~Enemy1();
	bool Start();

	void Update();

	void Move();//敵の移動関数

	void TracKing();//追跡する関数

	void Rotation();//回転の関数

	void SearchPlayer();//プレイヤーを見つけたかどうかの関数

	void Damege(Player* player);//ダメージを受ける関数

	void Dead();//死んだときの処理

	void ManageState();//ステート管理関数

	void Enemy1Animation();//アニメーション関数

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& pos);
	/*{
		m_position = pos;
    }*/
	Vector3 m_position;//エネミーのポジション;
private:

	int m_enemy1State = 0;//エネミーのステート
		

	bool IsDead = false;//死んだか死んでないかのフラグ

	bool DeathAnimation = false;//死んだときにすぐアニメーションが流れないようにするためのフラグ

		bool m_isSearchPlayer = false;//プレイヤーを見つけたか、見つけてないかのフラグ

		ModelRender m_modelRender;//モデルレンダー

		Vector3 m_forward;//前方向

		Vector3 m_moveSpeed;//移動速度

		Vector3 m_size = Vector3(30.0f, 30.0f, 30.0f);//ゴーストオブジェクトの大きさ

		Quaternion m_rotation;//回転
		
		FontRender m_fontRender;//文字表示

		SphereCollider m_sphereCollider;//球の当たり判定

		CharacterController m_characterController;//キャラコン

		Player* m_player = nullptr;//プレイヤーポインター

		PhysicsGhostObject m_GhostObjHead;//敵を倒す用のゴーストオブジェクト
        
		PhysicsGhostObject m_GhostObjBody;//プレイヤーが触れたらダメージを与えるゴーストオブジェクト

		//アニメション再生
		enum EnPlayAnimation
		{
			enAnimationClip_Idle,
			enAnimationClip_Attack,
			enAnimationClip_Walk,
			enAnimationClip_Dead,
			enAnimationClip_Num,
		};
		AnimationClip animationClips[enAnimationClip_Num];

};

