
#include "MapParser.h"
#include "../models/Coint.h"
#include "../models/Enemy.h"
#include "../models/Player.h"
#include "../models/Wall.h"
#include "../factories/ObjectsFactory.h"

bool ParseWall(const char *ch, float px, float pz)
{
	if (*ch != 'x')
		return false;

	Vector3<float> pos = Vector3<float>(px, 0, pz);
	int num = ObjectsFactory::instance()->num_obstacles();

	WallModel* wall = new WallModel(num, pos);
	ObjectsFactory::instance()->add_obstacle(wall);
	return true;
};

bool ParseCoint(const char *ch, float px, float pz)
{
	Vector3<float> pos = Vector3<float>(px, 0, pz);
	int num = ObjectsFactory::instance()->num_coints();

	CointModel* coint = new CointModel(num, pos);
	ObjectsFactory::instance()->add_coint(coint);
	return true;
};

bool ParsePlayer(const char *ch, float px, float pz)
{
	if (*ch != 'p')
		return false;

	Vector3<float> pos = Vector3<float>(px, 0, pz);
	
	PlayerModel* player = new PlayerModel(pos);
	ObjectsFactory::instance()->add_player(player);
	return true;
};

bool ParseEnemy(const char *ch, float px, float pz, int num)
{
	if (*ch != 'e')
		return false;

	Vector3<float> pos = Vector3<float>(px, 0, pz);
	//int num = ObjectsFactory::instance()->num_enemies();

	EnemyModel* enemy = new EnemyModel(num, pos);
	ObjectsFactory::instance()->add_enemy(enemy);
	return true;
};

bool ParseNode(const char *ch, float px, float pz, int num)
{
	if (*ch != 'n')
		return false;

	//std::cout << " node " << num << " " << px << " " << pz << std::endl;

	Vector3<float> pos = Vector3<float>(px, 0, pz);
	float radius = 0.1;
	//int num = ObjectsFactory::instance()->num_nodes();

	GraphNode * node = new GraphNode(num, pos, radius);
	ObjectsFactory::instance()->add_node(node);
	return true;
};

void ParseMap(string filename)
{
	string input;
	ifstream inFile;

	inFile.open(filename, fstream::in);
	if (!inFile)
	{
		cout << "Cannot open map file!" << endl;
	}

	int x = 0, z = 0, x_delta = 8, z_delta = 8;
	while (getline(inFile, input)) // Loops through file line-by-line until the eof() is reached.
	{
		//cout << "Read line: " << input << endl;
		// get first char
		const char *ch = input.c_str();

		x = 0;
		while (*ch != '|')
		{
			const char *ch1 = ch; ch++;
			const char *ch2 = ch; ch++;
			const char *ch3 = ch; ch++;

			int num = 0;
			if (*ch2 != ' ')
			{
				num = *ch2 - '0';
				if (*ch3 != ' ')
				{
					int n2 = *ch3 - '0';
					num = num * 10 + n2;
				}
			}
				

			float px = (x - x_delta);
			float pz = (z - z_delta);

			if (*ch1 == 'x')
			{
				ParseWall(ch1, px, pz);
			}

			else if (*ch1 == 'p')
			{
				ParsePlayer(ch1, px, pz);
			}

			else if (*ch1 == 'e')
			{
				ParseEnemy(ch1, px, pz, num);
			}

			else if (*ch1 == 'n')
			{
				ParseNode(ch1, px, pz, num);
				ParseCoint(ch1, px, pz);
			}

			else
			{
				ParseCoint(ch1, px, pz);
			}

			x++;
		}

		z++;
	}
	inFile.close();
};
