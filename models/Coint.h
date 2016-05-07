#ifndef COINT_MODEL_H_
#define COINT_MODEL_H_


#include "../GameObject.h"
#include "../factories/Textures.h"

class CointModel : public GameObject {
public:
	CointModel(int i, Vector3<float> pos) : GameObject()
	{
		m_id = i;
		cubro::PhysicsBody* b = new cubro::PhysicsBody(
			pos,
			Vector3<float>(1.0, 0.0, 0.0),
			Vector3<float>(0.0, 0.0, 0.0),
			Vector3<float>(0.1, 0.1, 0.1));
		b->commit();
		m_body = b;

		GLuint texture = TexturesFactory::getC1();
		Render* r = new BoxRender(texture, b->get_half_size());
		m_render = r;
	}

	void destroy()
	{
		state = GameObject::ObjectState::DESTROYED;
	};

	void update(float duration)
	{
		if (state == GameObject::ObjectState::DESTROYED)
			return;

		// collision detection and efect to the collided objects 

		//m_body->update(duration);
		m_body->commit();
	};

	virtual void render()
	{
		if (state == GameObject::ObjectState::DESTROYED)
			return;

		GameObject::render();
	}

};

#endif /* COINT_MODEL_H_ */
