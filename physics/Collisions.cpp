#include "Collisions.h"

bool cubro::BoxAndBox(Vector3<float> current_position, Vector3<float> current_half_size,
	Vector3<float> target_position, Vector3<float> target_half_size)
{
	float distance_between_x = fabs(current_position.x - target_position.x);
	float distance_between_y = fabs(current_position.y - target_position.y);
	float distance_between_z = fabs(current_position.z - target_position.z);

	float half_size_summ_x = current_half_size.x + target_half_size.x;
	float half_size_summ_y = current_half_size.y + target_half_size.y;
	float half_size_summ_z = current_half_size.z + target_half_size.z;

	if (distance_between_x > half_size_summ_x) return false;
	if (distance_between_y > half_size_summ_y) return false;
	if (distance_between_z > half_size_summ_z) return false;

	return true;
};

bool cubro::SphereAndSphere(Vector3<float> current_position, float current_radius,
	Vector3<float> target_position, float target_radius)
{
	float distance_between_x = fabs(current_position.x - target_position.x);
	float distance_between_y = fabs(current_position.y - target_position.y);
	float distance_between_z = fabs(current_position.z - target_position.z);

	float radius_summ = current_radius + target_radius;

	if (distance_between_x > radius_summ) return false;
	if (distance_between_y > radius_summ) return false;
	if (distance_between_z > radius_summ) return false;

	return true;
};
