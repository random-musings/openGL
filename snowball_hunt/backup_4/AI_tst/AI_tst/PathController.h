#pragma once

 class PathController
{
	Map *currMap;
	Enemy *character;
	Vehicle *opponent;
	vector<MapNode*> visited; //last 10 visited nodes
	vector<PathNode*> path; //the future path

	MapNode* currNPCLocation;
	MapNode* currTargetNode;

	int currTarget;
	int currPath;
	int maxPath;



	Point makeUnitVector(Point newPt);
	void deleteVisited();
	void deletePath();
	bool nodeAlreadyVisited(MapNode *node);
	bool nodeIsAvailable(MapNode *node);
	void setPathNodes(MapNode* target);
	float distanceFromNode(Point node1,Point node2);
	void moveCharacter();
	void setCharacterStates();

	void findHidingPlace(); //find a closest hiding place

	public:
	PathController(void);
	PathController(	Map *newMap,
					Enemy *newCharacter,
					Vehicle *newOpponent
					);
	~PathController(void);
	
	void setTarget(int newCurrTarget);
	void setNextTarget();
	void setPath();
	Point adjustVelocity(Point pt1, Point pt2,float speed);
	void advancePath();
	void advanceCharacter();
	MapNode* ObstacleExistsBetween(Point node1,Point node2);

	void setMaxPath(int newMaxPath);
	int getMaxPath();
 };
