#ifndef WALL_MODEL_H_
#define WALL_MODEL_H_


#include "../GameObject.h"
#include "../factories/Textures.h"

class WallModel : public GameObject {
public:
	WallModel(int i, Vector3<float> pos) : GameObject()
	{
		m_id = i;
		cubro::PhysicsBody* b = new cubro::PhysicsBody(
			pos,
			Vector3<float>(1.0, 0.0, 0.0),
			Vector3<float>(0.0, 0.0, 0.0),
			Vector3<float>(0.5, 0.1, 0.5));
		b->commit();
		m_body = b;

		GLuint texture = TexturesFactory::getW1();
		Render* r = new BoxRender(texture, b->get_half_size());
		m_render = r;
	}

	void update(float duration)
	{
		// collision detection and efect to the collided objects 

		//m_body->update(duration);
		m_body->commit();
	}
};

#endif /* WALL_MODEL_H_ */


