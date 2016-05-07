#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_


#include "TankExeptions.h"

#include "scenes/SceneLevel.h"

class GameManager
{
private:
	float base_time;

	std::vector<Scene*> scenes;
	Scene::SceneType current_type;
public:
	cubro::MoveControlls * moving;

	/*
	Load resourses
	*/
	GameManager()
	{
		
	}

	void init()
	{
		moving = new cubro::MoveControlls();
		SceneLevel* level1 = new SceneLevel(Scene::SceneType::LEVEL1);

		scenes.push_back(level1);
		current_type = Scene::SceneType::LEVEL1;
	}

	Scene* getScene(Scene::SceneType type)
	{
		for (int i = 0; i < scenes.size(); i++)
		{
			if (scenes[i]->getType() == type)
				return scenes[i];
		}
		return NULL;
	};

	Scene* getCurrent()
	{
		Scene* current_scene = getScene(current_type);
		if (current_scene == NULL)
			return NULL;

		return current_scene;
	};

	void initScene()
	{
		Scene* current_scene = getScene(current_type);
		if (current_scene == NULL)
			return;

		if (!current_scene->inited)
			current_scene->init();
	};

	/*
	Run Game loop
	*/
	void run()
	{
		base_time = glutGet(GLUT_ELAPSED_TIME);
		Graphics::Run();
	}
	/*
	render all objects in the scene
	*/
	void display()
	{
		Scene* current_scene = getCurrent();
		if (!current_scene->get_init())
			return;

		Camera *camera = current_scene->getCamera();
		Vector3<float> c_position = camera->m_position;
		Vector3<float> c_direction = camera->m_direction;
		Graphics::Camera(
			c_position.x, c_position.y, c_position.z,
			c_direction.x, c_direction.y, c_direction.z);

		current_scene->display();
	};
	/*
	update positions of all objects in the scene
	*/
	void update()
	{
		float time = glutGet(GLUT_ELAPSED_TIME);
		float delta = (time - base_time);

		

		//if (1000.0 / 60 > delta)
		//	return;

		// Find the duration of the last frame in seconds
		float duration = delta * 0.001f;
		if (duration <= 0.01f) return;
		else if (duration > 0.05f) duration = 0.05f;

		//std::cout << " duration " << delta << " " << delta * 0.001f << std::endl;

		initScene();
		Scene* current_scene = getCurrent();
		current_scene->update(duration);

		//std::cout << " test " << current_scene->getType() << " " 
		//	<< current_scene->getCamera()->m_position.x << std::endl;
		 
		Graphics::Redispaly();
		
		base_time = time;
	};
	/*
	handle keys events or pass them to the current scene
	*/
	void keyboard(cubro::ButtonControlls button)
	{
		try
		{
			
			Scene* current_scene = getCurrent();
			current_scene->keyboard(button);

		}
		catch (ExitException& e)
		{
			cout << e.what() << '\n';
			quit();
			return;
		}
	};

	void mouse_press(int button, int state, int x, int y)
	{

	};

	void mouse_release(int button, int state, int x, int y)
	{

	};

	void mouse_move(int x, int y)
	{

	};

	void quit()
	{
		for (int i = 0; i < scenes.size(); i++)
			delete scenes[i];
		Graphics::Exit();
		exit(0);
	}
};

#endif /* GAME_MANAGER_H_ */

