#ifndef ENEMY_ANIMATION_H_
#define ENEMY_ANIMATION_H_

#include "../factories/Textures.h"
#include "../graphics/render.h"
#include "../GameObject.h"

class EnemyAnimation {
public:
	Render * r_right1; //1
	Render * r_down1; //2
	Render * r_left1; // 3
	Render * r_up1; //4

	Render * r_right2;
	Render * r_down2;
	Render * r_left2;
	Render * r_up2;

	int step;
	float frame_duration;

	GameObject * model;
	Render * m_render;

	EnemyAnimation(GameObject * m)
	{
		step = 1;
		model = m;
		Vector3<float> half_size = model->m_body->get_half_size();

		r_right1 = new BoxRender(TexturesFactory::getE(m->m_id, 1, 1), half_size);
		r_down1 = new BoxRender(TexturesFactory::getE(m->m_id, 2, 1), half_size);
		r_left1 = new BoxRender(TexturesFactory::getE(m->m_id, 3, 1), half_size);
		r_up1 = new BoxRender(TexturesFactory::getE(m->m_id, 4, 1), half_size);

		r_right2 = new BoxRender(TexturesFactory::getE(m->m_id, 1, 2), half_size);
		r_down2 = new BoxRender(TexturesFactory::getE(m->m_id, 2, 2), half_size);
		r_left2 = new BoxRender(TexturesFactory::getE(m->m_id, 3, 2), half_size);
		r_up2 = new BoxRender(TexturesFactory::getE(m->m_id, 4, 2), half_size);

		model->set_render(r_right1);
	};

	void update(float duration)
	{
		frame_duration += duration;
		if (frame_duration < 0.1)
			return;

		Vector3<float> direction = model->get_dir();
		//std::cout << " animation direction " 
		//	<< direction.x << " "
		//	<< direction.y << " " 
		//	<< direction.z << " " 
		//	<< std::endl;
		direction.x = round(direction.x);
		direction.y = round(direction.y);
		direction.z = round(direction.z);

		if (direction == Vector3<float>(0, 0, 1))
			if (step == 1)
				model->set_render(r_right1);
			else
				model->set_render(r_right2);
		else if (direction == Vector3<float>(0, 0, -1))
			if (step == 1)
				model->set_render(r_left1);
			else
				model->set_render(r_left2);
		else if (direction == Vector3<float>(1, 0, 0))
			if (step == 1)
				model->set_render(r_up1);
			else
				model->set_render(r_up2);
		else if (direction == Vector3<float>(-1, 0, 0))
			if (step == 1)
				model->set_render(r_down1);
			else
				model->set_render(r_down2);

		step = (step == 1) ? 2 : 1;
		frame_duration = 0;
	};

};

#endif /* ENEMY_ANIMATION_H_ */
