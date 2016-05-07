#ifndef IDENTIFIERS_H_
#define IDENTIFIERS_H_


namespace cubro {

	enum ModelType
	{
		PLAYER,
	};

	enum AxisType
	{
		X, Y, Z
	};

	enum ButtonControlls
	{
		NONE,
		TEST,
		SHOW_MAP,
		SHOW_GAME,
		ENTER,
		ESCAPE,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT
	};

	typedef struct MoveControlls
	{
		bool move_forvard;
		bool move_back;
		bool move_left;
		bool move_right;
		bool turn_left;
		bool turn_right;

		MoveControlls() :
			move_forvard(false),
			move_back(false),
			move_left(false),
			move_right(false),
			turn_left(false),
			turn_right(false) {}
	} MoveControlls;


	enum MenuType
	{
		EMPTY,
		PLAY,
		HELP,
		SETTINGS,
		QUIT,
	};
};

#endif /* IDENTIFIERS_H_ */