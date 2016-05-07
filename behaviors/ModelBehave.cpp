
#include "ModelBehave.h"
#include "../models/Enemy.h"
#include "../models/Wall.h"
#include "../models/Player.h"

EnemyBehave::EnemyBehave(GameObject* current_object, GraphPath graph) :
	ModelBehave(current_object)
{
	
	path_finder = new PathFinder(graph);
	ray_trace = new RayTrace(current_object, 10.0f);

	ObjectsFactory * fact = ObjectsFactory::instance();
	std::vector<GameObject*> interacts = fact->get_obstacles();
	GameObject* target = fact->get_player();

	for (int i = 0; i < interacts.size(); i++)
		ray_trace->set_obstacles(interacts[i]);

	ray_trace->set_target(target);
	
	/*
		set up behaviour tree
	*/
	move_to_next = new MoveToNextNode(current_object, target, ray_trace);
	find_closes = new FindClosesNode(current_object, target, path_finder);
	move_to_target = new MoveToTarget(current_object, target, ray_trace);
	find_next_node = new FindNextNode(current_object, target, path_finder);
	
	find_closes->task_move_next_node = move_to_next;

	move_to_next->task_move_to_target = move_to_target;
	move_to_next->task_find_next_node = find_next_node;
	move_to_next->task_move_next_node = move_to_next;

	find_next_node->task_move_next_node = move_to_next;

	move_to_target->task_find_closes_node = find_closes;

	/*
		set up init task
	*/
	begin_task();
};

void EnemyBehave::begin_task()
{
	behaviour_task = find_closes;
};
