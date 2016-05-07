#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "Settings.h"
#include "physics/body.h"

#include "factories/Meshes.h"
#include "graphics/render.h"


class GameObject
{
public:
	
	int m_id;
	
	cubro::PhysicsBody * m_body;
	Render * m_render;

	enum ObjectState
	{
		ACTIVE,
		DESTROYED,
		CHANGED,
		WAITING
	};
	ObjectState state;

	GameObject() :
		state(ObjectState::ACTIVE)
	{

	};

	GameObject(cubro::PhysicsBody* b, Render* r, int i) :
		m_body(b), m_render(r), m_id(i), state(ObjectState::ACTIVE)
	{
	
	};

	void set_render(Render * r)
	{
		m_render = r;
	}

	virtual void update(float duration)
	{
		//m_body->update(duration);
		m_body->commit();
	}

	virtual void render()
	{
		// Get the OpenGL transformation
		GLfloat mat[16];
		Matrix4<float> tranformation = m_body->get_transformation();
		tranformation.get_mat(mat);
		m_render->render(mat);
	}

	Vector3<float> get_pos()
	{
		return m_body->get_position();
	}

	Vector3<float> get_dir()
	{
		return m_body->get_direction();
	}

};

#endif /* GAME_OBJECT_H_ */