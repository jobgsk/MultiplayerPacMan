#ifndef PATH_FINDER_H_
#define PATH_FINDER_H_

#include <vector>
#include <map>
#include <iostream>

#include "../physics/Vector3.h"
#include "GraphPath.h"

typedef std::map<int, GraphNode*>::iterator node_it_type;
class PathFinder
{

	std::map<int, GraphNode*> m_nodes_map;

public:
	GraphPath m_graph;

	GraphNode * m_start_node;
	GraphNode * m_end_node;
	std::vector<GraphNode*> m_path_nodes;
	PathFinder(){};
	PathFinder(GraphPath graph)
	{
		m_graph = graph;
		m_nodes_map = m_graph.get_nodes();
	};

	GraphNode * find_closest_node(Vector3<float> current_position);
	GraphNode * find_random_node();
	GraphNode * find_next_node();
	void create_path();
};

#endif /* PATH_FINDER_H_ */
