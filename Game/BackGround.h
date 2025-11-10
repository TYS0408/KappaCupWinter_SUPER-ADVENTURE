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
	
	
	//クリボーステージ
	ModelRender m_DemoStagemodelRender;//クリボーステージ
	PhysicsStaticObject m_DemophysicsStaticObject;//クリボーステージ
	Vector3 m_DemoPos;

	//ノコノコステージ
	ModelRender m_StagemodelRender;//ノコノコステージ
	PhysicsStaticObject m_StagephysicsStaticObject;//ノコノコステージ
	Vector3 m_StagePos;

	//クリボー＆ノコノコステージ
	ModelRender m_Stage2modelRender;
	PhysicsStaticObject m_Stage2physicsStaticObject;
	Vector3 m_Stage2Pos;

	//橋のオブジェクト
	ModelRender m_BrigemodelRender;
	PhysicsStaticObject m_BrigephysicsStaticObject;
	Vector3 m_BrigePos;
};

