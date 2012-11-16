#pragma once

class Map
{
	vector<MapNode*> targets; //list of prizes in the game
	MapNode **Nodes;
	int X;
	int Z;

	void cleanupNodes();
	void initializeNodes(int x,int z);

public:
	Map(void);
	~Map(void);

	void createMap(Point minCoords, 
					Point maxCoords, 
					Obstacle item, 
					Gift *gifts, 
					int numGifts, 
					bool (*collisionFunc)(Obstacle&)
					);
	MapNode* getNode(Point currentLocation);
	MapNode* getNode(int indexX,int indexY, int indexZ);
	void setState(Point location, enum nodeState newState);
	void printState();
	vector<MapNode*> getTargets();
	int getX();
	int getZ();
};
