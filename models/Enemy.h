#ifndef ENEMY_MODEL_H_
#define ENEMY_MODEL_H_

#include "../GameObject.h"
#include "../behaviors/ModelBehave.h"
#include "../factories/ObjectsFactory.h"
#include "../animation/Enemy.h"

class EnemyModel : public GameObject {
public:
	EnemyBehave * actor;
	GraphNode * next_node;
	float start_time;
	float delta_time;

	EnemyAnimation * m_animation;

	EnemyModel(int i, Vector3<float> pos) : GameObject()
	{
		m_id = i;
		cubro::PhysicsBody* b = new cubro::PhysicsBody(
			pos, 
			Vector3<float>(1.0, 0.0, 0.0), 
			Vector3<float>(0.0, 90.0, 0.0),
			Vector3<float>(0.4, 0.1, 0.4));
		b->commit();
		m_body = b;

		m_animation = new EnemyAnimation(this);
	};

	void set_agent(std::map<int, GraphNode*> nodes)
	{
		start_time = m_id * 2;
		delta_time = 0;
		
		GraphPath graph(nodes);
		actor = new EnemyBehave(this, graph);
	};

	
	void update(float duration)
	{
		// collision detection and efect to the collided objects 
		if (delta_time > start_time)
		{
			actor->update(duration);
			//m_body->update(duration);
			m_body->commit();
			m_animation->update(duration);
		}
		
		delta_time += duration;
	};
};

#endif /* ENEMY_MODEL_H_ */

