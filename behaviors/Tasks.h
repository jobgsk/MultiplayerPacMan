#ifndef BEHAVIOUR_TASKS_H_
#define BEHAVIOUR_TASKS_H_

#include "RayTrace.h"
#include "PathFinder.h"
#include "../GameObject.h"

class BehaviourTask {
public:
	GameObject * m_game_object;
	BehaviourTask(GameObject * game_object)
	{
		m_game_object = game_object;
	}
	virtual BehaviourTask * task(float duration) = 0;
};

class FindClosesNode : public BehaviourTask {
public:
	BehaviourTask * task_move_next_node;

	PathFinder * path_finder;
	GameObject * target_object;
	
	FindClosesNode(GameObject* game_object, GameObject * target, PathFinder * path)
		: BehaviourTask(game_object)
	{
		path_finder = path;
		target_object = target;
	};
	
	virtual BehaviourTask * task(float duration);
};
/*
execute then we on the path to the graph node
*/
class MoveToNextNode : public BehaviourTask {
public:
	BehaviourTask * task_move_to_target;
	BehaviourTask * task_find_next_node;
	BehaviourTask * task_move_next_node;

	GameObject * target_object;
	RayTrace * ray_trace;

	MoveToNextNode(GameObject * game_object, GameObject * target, RayTrace * rt) : 
		BehaviourTask(game_object)
	{ 
		target_object = target;
		ray_trace = rt;
	};

	virtual BehaviourTask * task(float duration);
};

/*
execute then we on the path to  target
*/
class MoveToTarget : public BehaviourTask {
public:
	BehaviourTask * task_find_closes_node;

	RayTrace * ray_trace;
	GameObject * target_object;

	MoveToTarget(GameObject * game_object, GameObject * target, RayTrace * rt) : 
		BehaviourTask(game_object)
	{
		target_object = target;
		ray_trace = rt;
	};

	virtual BehaviourTask * task(float duration);
};

/*
	execute then we on the graph node
*/
class FindNextNode : public BehaviourTask {
public:
	BehaviourTask * task_move_next_node;

	PathFinder * path_finder;
	GameObject * target_object;

	FindNextNode(GameObject * game_object, GameObject * target, PathFinder * path) :
		BehaviourTask(game_object)
	{
		path_finder = path;
		target_object = target;
	};

	virtual BehaviourTask * task(float duration);
};


/*class FindTargetDirection : public BehaviourTask {
public:

	FindTargetDirection(GameObject * game_object) : 
		BehaviourTask(game_object) 
	{
	};

	virtual BehaviourTask * task(float duration);
};
*/

#endif /* BEHAVIOUR_TASKS_H_ */
