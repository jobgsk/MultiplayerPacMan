
#include <thread>

#include "SceneLevel.h"
#include "../factories/ObjectsFactory.h"
#include "../factories/MapParser.h"
#include "../models/Enemy.h"
#include "../models/Player.h"

void SceneLevel::init()
{
	if (inited)
		return;

	ParseMap("media/map1.txt");
	ObjectsFactory * fact = ObjectsFactory::instance();

	player = fact->get_player();

	GraphPath graph2;
	std::vector<GraphNode*> nodes = fact->get_nodes();
	for (int i = 0; i < nodes.size(); i++)
	{
		graph2.add_node(nodes[i]);
	}
	graph2.create_edges("media/road1.txt");

	std::vector<GameObject*> enemies = fact->get_enemies();
	for (int i = 0; i < enemies.size(); i++)
	{
		// copy graphs objects
		((EnemyModel *)enemies[i])->set_agent(graph2.get_nodes());
	}


	/*std::map<int, GraphNode*> nodes2;
	nodes2 = graph2.get_nodes();
	GraphNode *start2 = nodes2.find(31)->second;
	start2->set_weight(0);
	start2->create_graf();

	GraphNode *end2 = nodes2.find(24)->second;
	graph2.show_path(end2, start2);
	*/

	camera = new Camera(player, 25);
	//camera->set_behind();
	camera->set_ontop();

	info1 = new TextRender("Score: ", 100, 550);
	info2 = new TextRender("", 350, 550);
	
	set_init();
	lstatus = LevelStatus::PLAY;
};

void SceneLevel::display()
{
	Vector3<float> pos = camera->m_target->get_pos();
	Vector3<float> dir = camera->m_target->get_dir();

	GLfloat position[] = { pos.x, pos.y, pos.z, 1.0f };
	GLfloat direction[] = { dir.x, dir.y, dir.z, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0f);

	std::vector<GameObject*> glist = ObjectsFactory::instance()->get_game_objects();
	for (int i = 0; i < glist.size(); i++)
	{
		glist[i]->render();
	}

	std::stringstream sstm1;
	std::stringstream sstm2;

	sstm1 << info1->m_init_text;
	sstm1 << ((PlayerModel*)player)->score;
	info1->m_render_text = sstm1.str();
	info1->render();

	if (player->state == GameObject::ObjectState::DESTROYED ||
		((PlayerModel*)player)->score == ObjectsFactory::instance()->num_coints())
	{
		sstm2 << "Game Over";
		info2->m_render_text = sstm2.str();
		info2->render();
	}
	
};

void SceneLevel::update(float duration)
{
	if (lstatus != LevelStatus::PLAY)
		return;

	if (player->state == GameObject::ObjectState::DESTROYED ||
		((PlayerModel*)player)->score == ObjectsFactory::instance()->num_coints())
		return;

	std::vector<std::thread *> trs;
	std::vector<GameObject*> object_list = ObjectsFactory::instance()->get_game_objects();
	
	for (int i = 0; i < object_list.size(); i++)
	{
		if (dynamic_cast<EnemyModel*>(object_list[i]))
		{
			//std::thread t1(actor->update, duration);
			std::thread * t1 = new std::thread(&EnemyModel::update, ((EnemyModel*)object_list[i]), duration);
			trs.push_back(t1);
			continue;
		}
			
		object_list[i]->update(duration);
	}

	//waiting for threads
	for (int i = 0; i < trs.size(); i++)
		trs[i]->join();
	
	camera->update();
};

void SceneLevel::keyboard(cubro::ButtonControlls button)
{
	if (button == cubro::ButtonControlls::MOVE_UP)
	{
		((PlayerModel*)player)->move(Vector3<float>(0, 0.0, -1.0), 0.25);
		return;
	}

	if (button == cubro::ButtonControlls::MOVE_DOWN)
	{
		((PlayerModel*)player)->move(Vector3<float>(0, 0.0, 1.0), 0.25);
		return;
	}

	if (button == cubro::ButtonControlls::MOVE_LEFT)
	{
		((PlayerModel*)player)->move(Vector3<float>(-1.0, 0.0, 0.0), 0.25);
		return;
	}

	if (button == cubro::ButtonControlls::MOVE_RIGHT)
	{
		((PlayerModel*)player)->move(Vector3<float>(1.0, 0.0, 0.0), 0.25);
		return;
	}

	if (button == cubro::ButtonControlls::SHOW_MAP)
	{
		camera->set_ontop();
		return;
	}
	
	if (button == cubro::ButtonControlls::SHOW_GAME)
	{
		camera->set_behind();
		return;
	}
};