#ifndef PHYSICS_BODY_H_
#define PHYSICS_BODY_H_

#include <stdlib.h>

#include "Vector3.h"
#include "MathHelper.h"
#include "Collisions.h"

namespace cubro {
	class PhysicsBody
	{
	private:
		Vector3<float> m_half_size;

		Vector3<float> m_direction;
		Vector3<float> m_position;
		Vector3<float> m_angle;
		
		Vector3<float> prev_direction;
		Vector3<float> prev_position;
		Vector3<float> prev_angle;
		
		//Vector3<float> direction_origin;
		Matrix4<float> m_tranformation;
	public:

		PhysicsBody() :
			m_position(Vector3<float>(0, 0, 0))
			, m_direction(Vector3<float>(0, 0, 0))
			, m_angle(Vector3<float>(0, 0, 0))
			, prev_position(Vector3<float>(0, 0, 0))
			, prev_direction(Vector3<float>(0, 0, 0))
			, prev_angle(Vector3<float>(0, 0, 0))
			, m_half_size(Vector3<float>(0, 0, 0)) 
			//, direction_origin(Vector3<float>(0, 0, 1))
		{

		};

		PhysicsBody(Vector3<float> pos, Vector3<float> dir, Vector3<float> angle, Vector3<float> hsize) :
			m_position(pos)
			, m_direction(dir)
			, m_angle(angle)
			, prev_position(pos)
			, prev_direction(dir)
			, prev_angle(angle)
			, m_half_size(hsize)
			//, direction_origin(Vector3<float>(0, 0, 1))
		{

		};

		
		Vector3<float> get_half_size()
		{
			return m_half_size;
		}

		Vector3<float> get_direction()
		{
			return m_direction;
		}

		Vector3<float> get_position()
		{
			return m_position;
		}

		Matrix4<float> get_transformation()
		{
			return m_tranformation;
		}


		void add_translation(float tr)
		{
			m_position += m_direction * tr;
		};

		void set_direction(Vector3<float> dir)
		{
			m_direction = dir;
		};

		void reset()
		{
			m_position = prev_position;
			m_direction = prev_direction;
		};

		bool modified()
		{
			return (m_position != prev_position || 
				m_direction != prev_direction);
		};

		void commit()
		{
			prev_position = m_position;
			prev_direction = m_direction;

			m_tranformation.init();
			m_tranformation.translate(m_position.x, m_position.y, m_position.z);
			m_tranformation.rotate(
				cubro::grad_to_rad(m_angle.x), 
				cubro::grad_to_rad(m_angle.y), 
				cubro::grad_to_rad(m_angle.z));
		};

	};
};

#endif /* PHYSICS_BODY_H_ */
