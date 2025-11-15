#pragma once
class BackGround :public IGameObject
{
public:
	BackGround();
	~BackGround();


	//描画関数
	void Render(RenderContext& rc);

	//モデルレンダー
	ModelRender m_modelRender;//初期リス
	PhysicsStaticObject m_physicsStaticObject;//初期リス
	Vector3 m_positon;
	
	
	
};

