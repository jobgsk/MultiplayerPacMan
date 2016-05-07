
#include "Tasks.h"
#include "../models/Enemy.h"
#include "../models/Player.h"


bool find_target_by_direction(GameObject * game_object, RayTrace * ray_trace)
{
	Vector3<float> origin_direct = game_object->m_body->get_direction();
	/*
		look at all directions
		to chack if the target object is directly visible
	*/
	game_object->m_body->set_direction(Vector3<float>(0, 0.0, -1.0));
	if (ray_trace->find_target())
	{
		std::cout << " found target z -1 " << std::endl;
		return true;
	}

	game_object->m_body->set_direction(Vector3<float>(0, 0.0, 1.0));
	if (ray_trace->find_target())
	{
		std::cout << " found target z 1 " << std::endl;
		return true;
	}


	game_object->m_body->set_direction(Vector3<float>(-1.0, 0.0, 0.0));
	if (ray_trace->find_target())
	{
		std::cout << " found target x -1 " << std::endl;
		return true;
	}

	game_object->m_body->set_direction(Vector3<float>(1.0, 0.0, 0.0));
	if (ray_trace->find_target())
	{
		std::cout << " found target x 1 " << std::endl;
		return true;
	}

	/*
		set direction back 
	*/
	game_object->m_body->set_direction(origin_direct);
	return false;
}

BehaviourTask * FindClosesNode::task(float duration)
{
	//gen road
	GraphNode * closes_node = path_finder->find_closest_node(m_game_object->m_body->get_position());
	GraphNode * target_node = path_finder->find_closest_node(target_object->m_body->get_position());
	path_finder->m_start_node = closes_node;
	path_finder->m_end_node = target_node;
	path_finder->create_path();

	((EnemyModel*)m_game_object)->next_node = path_finder->find_next_node();

	//std::cout << " FindClosesNode::task closes_node " << closes_node->get_id() << std::endl;
	//std::cout << " FindClosesNode::task target_node " << target_node->get_id() << std::endl;
	//std::cout << " FindClosesNode::task next_node " << ((EnemyModel*)m_game_object)->next_node->get_id() <<  std::endl;

	//change direction to translate
	Vector3<float> direction = ((EnemyModel*)m_game_object)->next_node->m_position - m_game_object->m_body->get_position();
	direction.normalize();
	m_game_object->m_body->set_direction(direction);

	return task_move_next_node;
};

BehaviourTask * FindNextNode::task(float duration)
{
	std::cout << " FindNextNode::task " << std::endl;
	/*
		generate new path if the finish
	*/
	if (path_finder->m_path_nodes.size() == 0)
	{
		GraphNode * current_node = ((EnemyModel*)m_game_object)->next_node;
		GraphNode * target_node = path_finder->find_closest_node(target_object->m_body->get_position());

		if (current_node == target_node)
			return task_move_next_node;
		
		path_finder->m_start_node = current_node;
		path_finder->m_end_node = target_node;
		path_finder->create_path();
	}

	((EnemyModel*)m_game_object)->next_node = path_finder->find_next_node();
	
	//change direction to translate
	Vector3<float> direction = ((EnemyModel*)m_game_object)->next_node->m_position - m_game_object->m_body->get_position();
	direction.normalize();
	m_game_object->m_body->set_direction(direction);

	return task_move_next_node;
};

BehaviourTask * MoveToNextNode::task(float duration)
{
	//if (find_target_by_direction(m_game_object, ray_trace))
	//	return task_move_to_target;

	/*
		if the bot has reached the graph's node
	*/
	if (cubro::SphereAndSphere(m_game_object->m_body->get_position(), m_game_object->m_body->get_half_size().x/10,
		((EnemyModel*)m_game_object)->next_node->m_position, ((EnemyModel*)m_game_object)->next_node->m_radius))
	{
		return task_find_next_node;
	}
		
	/*
		continue moving
	*/
	m_game_object->m_body->add_translation(0.05);
	/*
		check collision with player
	*/
	if (cubro::SphereAndSphere(m_game_object->m_body->get_position(), m_game_object->m_body->get_half_size().x,
		target_object->m_body->get_position(), target_object->m_body->get_half_size().x))
	{
		((PlayerModel*)target_object)->destroy();
	}
	return this;
};

BehaviourTask * MoveToTarget::task(float duration)
{
	/*
		generate new path 
		if the target is not visible
	*/
	if (!ray_trace->find_target())
	{
		return task_find_closes_node;
	}

	/*
		continue moving
	*/
	m_game_object->m_body->add_translation(0.05);
	
	/*
		check collision with player
	*/
	if (cubro::SphereAndSphere(m_game_object->m_body->get_position(), m_game_object->m_body->get_half_size().x,
		target_object->m_body->get_position(), target_object->m_body->get_half_size().x))
	{
		((PlayerModel*)target_object)->destroy();
	}
	return this;
};

