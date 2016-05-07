#include "PathFinder.h"

GraphNode * PathFinder::find_closest_node(Vector3<float> current_position)
{
	node_it_type node_it = m_nodes_map.begin();
	GraphNode *closest_node = node_it->second;

	for (; node_it != m_nodes_map.end(); node_it++)
	{
		if (closest_node == node_it->second)
		{
			continue;
		}

		float prev_distance = (closest_node->m_position - current_position).magnitude();
		float curr_distance = (node_it->second->m_position - current_position).magnitude();
		if (curr_distance < prev_distance)
		{
			closest_node = node_it->second;
		}
	}
	return closest_node;
};

GraphNode * PathFinder::find_random_node()
{
	int size = m_nodes_map.size();
	int index = rand() % size + 1;
	//std::cout << " >>>>" << index << " " << size << std::endl;
	return m_nodes_map[index];
};

GraphNode * PathFinder::find_next_node()
{
	int size = m_path_nodes.size();
	GraphNode * next = m_path_nodes[(size - 1)];
	m_path_nodes.pop_back();
	return next;
};

void PathFinder::create_path()
{
	if (m_start_node == NULL)
		return;
	m_graph.clean_graf();
	m_start_node->set_weight(0);
	m_start_node->create_graf();

	// debug
	m_graph.show_path(m_end_node, m_start_node);

	m_path_nodes.clear();

	std::vector<GraphNode *>::iterator it;
	while (m_end_node != m_start_node) {
		//it = m_path_nodes.begin();
		//m_path_nodes.insert(it, m_end_node);
		m_path_nodes.push_back(m_end_node);

		GraphEdge * road = m_end_node->get_main_edge();
		m_end_node = road->get_node(m_end_node);
	}
	m_path_nodes.push_back(m_start_node);
};
