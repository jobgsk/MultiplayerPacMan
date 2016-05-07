#ifndef PLAYER_ANIMATION_H_
#define PLAYER_ANIMATION_H_

#include "../factories/Textures.h"
#include "../graphics/render.h"
#include "../GameObject.h"

class PlayerAnimation {
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

	GameObject * model;
	Render * m_render;

	PlayerAnimation(GameObject * m)
	{
		step = 1;
		model = m;
		Vector3<float> half_size = model->m_body->get_half_size();

		r_right1 = new BoxRender(TexturesFactory::getP(1, 1), half_size);
		r_down1 = new BoxRender(TexturesFactory::getP(2, 1), half_size);
		r_left1 = new BoxRender(TexturesFactory::getP(3, 1), half_size);
		r_up1 = new BoxRender(TexturesFactory::getP(4, 1), half_size);

		r_right2 = new BoxRender(TexturesFactory::getP(1, 2), half_size);
		r_down2 = new BoxRender(TexturesFactory::getP(2, 2), half_size);
		r_left2 = new BoxRender(TexturesFactory::getP(3, 2), half_size);
		r_up2 = new BoxRender(TexturesFactory::getP(4, 2), half_size);

		model->set_render(r_right1);
	};

	void update(float duration)
	{
		Vector3<float> direction = model->get_dir();

		if (direction == Vector3<float>(0, 0, 1))
			if (step == 1)
			{	
				model->set_render(r_down1);
			}
			else
			{
				model->set_render(r_down2);
			}		
		else if (direction == Vector3<float>(0, 0, -1))
			if (step == 1)
			{
				model->set_render(r_up1);
			}
			else
			{
				model->set_render(r_up2);
			}
		else if (direction == Vector3<float>(1, 0, 0))
			if (step == 1)
			{
				model->set_render(r_right1);
			}
			else
			{
				model->set_render(r_right2);
			}
		else if (direction == Vector3<float>(-1, 0, 0))
			if (step == 1)
			{
				model->set_render(r_left1);
			}
			else
			{
				model->set_render(r_left2);
			}

		step = (step == 1) ? 2 : 1;
	};

};

#endif /* PLAYER_ANIMATION_H_ */
