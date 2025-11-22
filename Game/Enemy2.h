#pragma once
class Enemy2:  public IGameObject
{
public:
	Enemy2();
	~Enemy2();

	bool Start();

	void Update();

	void Move();//敵の移動処理

	void Render(RenderContext& rc);

private:
	ModelRender m_modelRender;//エネミー２のモデル(スケルトン)

	SphereCollider m_sphereColider;
	Vector3 m_position;//スケルトンのポジション


};

