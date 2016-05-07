#include "RayTrace.h"

bool RayTrace::collide(GameObject* o, float angle_can_see)
{
	float grad_angle_betwen = cubro::get_angle_between(
		m_go->m_body->get_position(), m_go->m_body->get_direction(), o->m_body->get_position());
	if (grad_angle_betwen < angle_can_see)
		return true;
	return false;
};

bool RayTrace::overlap(GameObject* target, GameObject* obstacle)
{
	Vector3<float> target_position = target->m_body->get_position();
	Vector3<float> obstacle_position = obstacle->m_body->get_position();
	Vector3<float> current_position = m_go->m_body->get_position();

	float target_distance = (target_position - current_position).magnitude();
	float obstacle_distace = (obstacle_position - current_position).magnitude();

	if (obstacle_distace < target_distance)
		return true;
	return false;
};

bool RayTrace::find_target()
{
	if (!collide(m_target, m_angle_can_see))
		return false;

	for (int i = 0; i < m_obstacles.size(); i++)
	{
		if (!collide(m_obstacles[i], m_angle_can_see))
			continue;

		if (overlap(m_target, m_obstacles[i]))
			return false;
	}
	return true;
};