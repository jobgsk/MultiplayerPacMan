#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera  {


public:
	Vector3<float> m_position;
	Vector3<float> m_direction;

	float m_distance;
	GameObject *m_target;

	enum CameraPosition
	{
		BEHIND,
		ONTOP,
		INFRONT
	};
	CameraPosition m_camera_position;

	Camera(GameObject *target, float distance)
	{
		m_distance = distance;
		m_target = target;

	};

	//TODO: instead of calling set_behind every time, 
	//remove update, create methods getPosition, getDirection
	//calculate position and direction depend of m_camera_position
	void update()
	{
		if (m_camera_position == CameraPosition::BEHIND)
			set_behind();
	};
		
	void set_behind()
	{
		Vector3<float> t_position = m_target->get_pos();
		Vector3<float> t_direct = m_target->get_dir();
		t_direct.invert();
		
		
		Vector3<float> behind_position = (t_direct * m_distance) + t_position;
		m_position = Vector3<float>(behind_position.x, behind_position.y, behind_position.z);
		m_direction = Vector3<float>(t_position.x, t_position.y, t_position.z);

		m_camera_position = CameraPosition::BEHIND;
	};

	void set_ontop()
	{
		std::cout << " set_ontop " << std::endl;
		m_position = Vector3<float>(0.01, m_distance, 0.01);
		m_direction = Vector3<float>(0.0, 1.0, 0.0);
		m_camera_position = CameraPosition::ONTOP;
	};
	
	void set_infront()
	{
		std::cout << " set_infront " << std::endl;
		m_position = Vector3<float>(0.0, 0.0, 5.0);
		m_direction = Vector3<float>(0.0, 0.0, 0.0);
		m_camera_position = CameraPosition::INFRONT;
	};

};

#endif /* CAMERA_H_ */