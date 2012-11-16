#pragma once

 class PathController
{
	Map *currMap;
	Enemy *character;
	vector<MapNode*> visited; //last 10 visited nodes
	vector<PathNode*> path; //the future path

	MapNode* currNPCLocation;
	int currTarget;
	int currPath;
	int maxPath;

	Point makeUnitVector(Point newPt);
	void deleteVisited();
	void deletePath();
	bool nodeAlreadyVisited(MapNode *node);
	bool nodeIsAvailable(MapNode *node);
	void setPathNodes(MapNode* target);

	public:
	PathController(void);
	PathController(	Map *newMap,
					Enemy *newCharacter
					);
	~PathController(void);
	
	void setTarget(int newCurrTarget);
	void setNextTarget();
	void setPath();
	Point adjustVelocity(Point pt1, Point pt2,float speed);
	void advancePath();
	void advanceCharacter();

 };
