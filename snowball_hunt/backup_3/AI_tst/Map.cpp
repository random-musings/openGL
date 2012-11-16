#include "stdafx.h"

Map::Map(void):
	Nodes(0),
	X(0),
	Z(0)
{
	targets.clear();
}

Map::~Map(void)
{
	cleanupNodes();
}


void Map::cleanupNodes()
{
	for(int i=0;i<X;i++)
	{
		delete []Nodes[i];
	}
	X=0;
	Z=0;
	targets.clear();
}

void Map::initializeNodes(int x,int z)
{ 
	if(x!=0||z!=0)
		cleanupNodes();
	X=x;
	Z=z;
	Nodes = new MapNode*[x];
	for(int i=0;i<x;i++)
		Nodes[i]=new MapNode[z];
}


void Map::createMap(Point minCoords, 
					Point maxCoords, 
					Obstacle item, 
					Gift *gifts, 
					int numGifts, 
					bool (*collisionFunc)(Obstacle&)
					)
{

	Obstacle tmp(item);
	float objectSize = item.getSpaceDimensions().x;
	Point boundingDim = Point(objectSize/2,objectSize,objectSize/2);

	int x = (maxCoords.x-minCoords.x)/objectSize;
	int z = (maxCoords.z-minCoords.z)/objectSize;

	//cleanup and initialize will both occur by calling this function
	initializeNodes(x,z);		

	Point currPoint(minCoords);
	currPoint.y= -44; //adjust for the y coords
	for(int i=0;i<x; i++)
	{
		currPoint.x = currPoint.x + objectSize;
		for(int j=0;j<z; j++)
		{
			currPoint.z = currPoint.z +=objectSize;
			Point minPoints = currPoint - boundingDim;
			Point maxPoints = currPoint + boundingDim;
			tmp.setOrigin(currPoint);
			enum nodeState newState = EMPTY;
			if((*collisionFunc)(tmp))
				newState=OBSTACLE;
			Nodes[i][j] = MapNode(		newState,
										currPoint,
										minPoints,
										maxPoints,
										objectSize,
										-1,
										Point(i,0,j));
		}
		currPoint.z = minCoords.z;
	}//end of create nodes

	//assign nodes where Gifts Exist
	for(int giftix=0;giftix<numGifts;giftix++)
	{
		setState(gifts[giftix].getOrigin(),GIFT);
		targets.push_back(getNode(gifts[giftix].getOrigin()));
	}
}


MapNode* Map::getNode(Point currentLocation)
{
	for(int i=0;i<X; i++)
	{
		for(int j=0;j<Z; j++)
		{
				if(Nodes[i][j].itemInNode(currentLocation))
				{
					return &Nodes[i][j];
				}
		}
	}
	return 0;
}


MapNode* Map::getNode(int indexX,int indexY, int indexZ)
{
	
	if(indexX>=X || indexX<0)
		return 0;
//	if(indexY>=Y || indexY<0)
//		return 0;
	if(indexZ>=Z || indexZ<0)
		return 0;

	return &Nodes[indexX][indexZ];
}

void Map::setState(Point location, enum nodeState newState)
{
	
	for(int i=0;i<X; i++)
	{
		for(int j=0;j<Z; j++)
		{
				if(Nodes[i][j].itemInNode(location))
				{
					Nodes[i][j].setState(newState);
					return;
				}
		}
	}
}


void Map::printState()
{
	for(int i=0;i<X; i++)
	{
		for(int j=0;j<Z; j++)
		{
			switch(Nodes[i][j].getState())
			{
				case OBSTACLE: cout <<"O"; break;
				case GIFT: cout<<"G"; break;
				case EMPTY: cout<<"_";break;
				case OPPONENT: cout<<"X";break;
			}
		}
		cout<<endl;
	}
}


vector<MapNode*> Map::getTargets()
{
	return targets;
}

int Map::getX()
{
	return X;
}

int Map::getZ()
{
	return Z;
}
