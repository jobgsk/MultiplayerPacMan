#ifndef PLAYER_MODEL_H_
#define PLAYER_MODEL_H_


#include "../GameObject.h"
#include "../factories/ObjectsFactory.h"
#include "Coint.h"
#include "../animation/Player.h"

class PlayerModel : public GameObject {
public:
	int score;
	PlayerAnimation * m_animation;

	PlayerModel(Vector3<float> pos) : GameObject()
	{
		m_id = 0;
		cubro::PhysicsBody* b = new cubro::PhysicsBody(
			pos,
			Vector3<float>(1.0, 0.0, 0.0),
			Vector3<float>(0.0, 90.0, 0.0),
			Vector3<float>(0.4, 0.1, 0.4));
		b->commit();
		m_body = b;

		m_animation = new PlayerAnimation(this);
		score = 0;
	};

	void destroy()
	{
		state = GameObject::ObjectState::DESTROYED;
	};

	void move(Vector3<float> dir, float tr)
	{
		m_body->set_direction(dir);
		m_body->add_translation(tr);
	}

	void update(float duration)
	{
		// collision detection and efect to the collided objects 

		std::vector<GameObject*> obstacles = ObjectsFactory::instance()->get_obstacles();
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (cubro::BoxAndBox(
				m_body->get_position(), m_body->get_half_size(),
				obstacles[i]->m_body->get_position(), obstacles[i]->m_body->get_half_size()))
			{
				m_body->reset();
			}
		}

		std::vector<GameObject*> coints = ObjectsFactory::instance()->get_coints();
		for (int i = 0; i < coints.size(); i++)
		{
			if (coints[i]->state == GameObject::ObjectState::ACTIVE && 
				cubro::BoxAndBox(m_body->get_position(), m_body->get_half_size(),
				coints[i]->m_body->get_position(), coints[i]->m_body->get_half_size()))
			{
				score++;
				((CointModel*)coints[i])->destroy();
			}
		}
		
		if (m_body->modified())
			m_animation->update(duration);
		
		//m_body->update(duration);
		m_body->commit();
	}

};

#endif /* PLAYER_MODEL_H_ */

