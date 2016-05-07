#ifndef COLLISION_DETECTOR_H_
#define COLLISION_DETECTOR_H_

#include "Vector3.h"

namespace cubro {

	bool BoxAndBox(Vector3<float> current_position, Vector3<float> current_half_size,
		Vector3<float> target_position, Vector3<float> target_half_size);

	bool SphereAndSphere(Vector3<float> current_position, float current_radius,
		Vector3<float> target_position, float target_radius);
};

#endif /* COLLISION_DETECTOR_H_ */
