#ifndef OBJECTS_FACTORY_H_
#define OBJECTS_FACTORY_H_

#include <vector>
#include "../GameObject.h"
#include "../Camera.h"
#include "../behaviors/GraphPath.h"

class ObjectsFactory {
private:
	std::vector<GameObject*> m_game_objects;

	std::vector<GameObject*> m_enemies;
	std::vector<GameObject*> m_coints;
	std::vector<GameObject*> m_obstacles;

	std::vector<GraphNode*> m_nodes;
	
	GameObject * m_player;
	Camera * m_camera;

	static ObjectsFactory *m_instance;
	ObjectsFactory() { };

public:
	static ObjectsFactory *instance()
	{
		if (!m_instance)
			m_instance = new ObjectsFactory();
		return m_instance;
	}

	std::vector<GameObject*> get_game_objects()
	{
		return m_game_objects;
	};

	int num_game_objects()
	{
		return m_game_objects.size();
	};

	/*
		graph nodes
	*/
	void add_node(GraphNode * node)
	{
		m_nodes.push_back(node);
	};

	GraphNode * get_node(int id)
	{
		for (int i = 0; i < m_nodes.size(); i++)
			if (m_nodes[i]->get_id() == id)
				return m_nodes[i];
		return NULL;
	};

	std::vector<GraphNode*> get_nodes()
	{
		return m_nodes;
	};

	int num_nodes()
	{
		return m_nodes.size();
	};
	
	/*
		enemies
	*/
	void add_enemy(GameObject * enemy)
	{
		m_enemies.push_back(enemy);
		m_game_objects.push_back(enemy);
	};

	GameObject * get_enemy(int id)
	{
		for (int i = 0; i < m_enemies.size(); i++)
			if (m_enemies[i]->m_id == id)
				return m_enemies[i];
		return NULL;
	};

	std::vector<GameObject*> get_enemies()
	{
		return m_enemies;
	};

	int num_enemies()
	{
		return m_enemies.size();
	};

	/*
		victims
	*/
	void add_coint(GameObject * coint)
	{
		m_coints.push_back(coint);
		m_game_objects.push_back(coint);
	};

	GameObject * get_coint(int id)
	{
		for (int i = 0; i < m_coints.size(); i++)
			if (m_coints[i]->m_id == id)
				return m_coints[i];
		return NULL;
	};

	std::vector<GameObject*> get_coints()
	{
		return m_coints;
	};

	int num_coints()
	{
		return m_coints.size();
	};

	/*
		obstacles
	*/
	void add_obstacle(GameObject * obstacle)
	{
		m_obstacles.push_back(obstacle);
		m_game_objects.push_back(obstacle);
	};

	GameObject * get_obstacle(int id)
	{
		for (int i = 0; i < m_obstacles.size(); i++)
			if (m_obstacles[i]->m_id == id)
				return m_obstacles[i];
		return NULL;
	};

	std::vector<GameObject*> get_obstacles()
	{
		return m_obstacles;
	};

	int num_obstacles()
	{
		return m_obstacles.size();
	};

	/*
		camera
	*/
	void add_camera(Camera * camera)
	{
		m_camera = camera;
	};

	Camera * get_camera()
	{
		return m_camera;
	};

	/*
		player
	*/
	void add_player(GameObject * player)
	{
		m_player = player;
		m_game_objects.push_back(player);
	};

	GameObject * get_player()
	{
		return m_player;
	};

};
#endif /* OBJECTS_FACTORY_H_ */