#ifndef MODEL_BEHAVE_H_
#define MODEL_BEHAVE_H_

#include "Tasks.h"
#include "RayTrace.h"

class ModelBehave {
public:
	
	BehaviourTask * behaviour_task;
	GameObject * current_object;

	ModelBehave(GameObject* obj)
	{
		current_object = current_object;
	};
	virtual void update(float duration) = 0;
	virtual void begin_task() = 0;

};

class EnemyBehave : public ModelBehave {
public:
	MoveToNextNode * move_to_next;
	FindClosesNode * find_closes;
	MoveToTarget * move_to_target;
	FindNextNode * find_next_node;

	RayTrace * ray_trace;
	PathFinder * path_finder;

	EnemyBehave(GameObject* current_object, GraphPath graph);
	void update(float duration)
	{
		behaviour_task = behaviour_task->task(duration);
	};
	void begin_task();

};
#endif /* MODEL_BEHAVE_H_ */
