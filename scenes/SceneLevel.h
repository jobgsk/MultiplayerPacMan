#ifndef SCENELEVEL_H_
#define SCENELEVEL_H_	

#include <iostream>
#include <deque>

#include "Scene.h"


class SceneLevel : public Scene
{
private:
	GameObject* player;
	TextRender * info1;
	TextRender * info2;

public:
	enum LevelStatus
	{
		PLAY,
		WIN,
		LOSE,
		PAUSE
	};
	LevelStatus lstatus;

	SceneLevel(SceneType level)
		:Scene(level)
	{	

	};
	~SceneLevel()
	{
		Scene::~Scene();
	};
	void init();

	void display();
	void update(float duration);
	void keyboard(cubro::ButtonControlls button);

	LevelStatus getLstatus() 
	{ 
		return lstatus; 
	};
};

#endif /* SCENELEVEL_H_ */