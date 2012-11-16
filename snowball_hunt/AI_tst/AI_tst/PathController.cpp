#include "stdafx.h"

PathController::PathController(void):currMap(0),character(0)
{

}

PathController::PathController(	Map *newMap,
					Enemy *newCharacter
					):currTarget(0)
{
	character = newCharacter;
	currMap = newMap;
}

PathController::~PathController(void)
{

}


	
void PathController::setNextTarget()
{
	vector<MapNode*> targets = currMap->getTargets();
	int numTargets = targets.size();
	currTarget = (currTarget+1) % numTargets;
}


Point PathController::adjustVelocity(Point pt1, Point pt2,float speed)
{
	//calculate velocity 
	//facing angle vs angle to nextPath
	Point tmp = makeUnitVector(Point(pt2.x - pt1.x,0,pt2.z  - pt1.z));
	tmp.x = tmp.x*speed; //adjust for speed of object
	tmp.y = tmp.y*speed;
	tmp.z = tmp.z*speed;
	return tmp;
}


Point PathController::makeUnitVector(Point newPt)
{
	GLfloat magnitude = sqrt(newPt.x*newPt.x + newPt.y*newPt.y +newPt.z*newPt.z);
	return Point (newPt.x/magnitude,newPt.y/magnitude,newPt.z/magnitude);
}

void PathController::deletePath()
{
	vector<PathNode*>::iterator pIter;
	pIter= path.begin();
	while(pIter != path.end())
		delete *pIter;
	path.clear();
}

void PathController::setPath()
{
	deleteVisited();
	deletePath();
	setNextTarget(); //set the target
	setPathNodes(currMap->getTargets()[currTarget]);
}

void PathController::advancePath()
{
	
	if(!path.empty())
		path.erase(path.begin()); 		

	if(path.empty())
		setPath();

	//reset the facing angle &velocity of object
	if (!path.empty())
		character->setVelocity(adjustVelocity(character->getOrigin(),path[0]->getLocation(),character->getSpeed() ));
}



void PathController::advanceCharacter()
{
	npcAction oldState= character->getCurrentState();
	character->UpdateCurrentState();


	switch(character->getCurrentState())
	{
		case IDLE:
		case CARRY_SNOWBALL:
			if(path.empty()) //if current path has not been set
				setPath();
			if( path[0]->itemInNode(character->getOrigin()) )//check to see if character in the node of the next 
			{
				visited.push_back(path[0]);
				advancePath();
			}else
			{ //set velocity to reach the next node
				character->setVelocity(adjustVelocity(character->getOrigin(),path[0]->getLocation(),character->getSpeed()));
			}
			character->setOrigin(character->getOrigin()+ character->getVelocity());
			break;
		case RUN_FOR_LIFE:
			//if previous state !=RUN_FOR_LIFE... set  new path
			//oldState
			advancePath();
			break;
		//default do nothing as these states require the character to do nothing
	}//end of switch
}//end of advanceCharacter


void PathController::setPathNodes(MapNode* target)
{
	//get node that current object resides in 
	//check all nodes around object
	//find node closest distanct to object that has a security rating
	//add to path target 
	//increment path count
	//repeat until nodeindex==targetindex point
	MapNode *nextNode=0;
	MapNode *currNode =currMap->getNode(character->getOrigin());
	Point nodeIndex = currNode->getNodeIndex();
	int Gcost =0;
	int Hcost =0;
	int securityRating=0;
	int currCost=-1;
	int currSecurityRating=0;
	int currHCost=0;
	int currGCost=0;

	while(nodeIndex!=target->getNodeIndex())
	{
		int minX=nodeIndex.x-1<0?0:nodeIndex.x-1;
		int maxX=nodeIndex.x+1>currMap->getX()?currMap->getX():nodeIndex.x+1;
		for(int i =minX;i<=maxX;i++)
		{
			int minZ=nodeIndex.z-1<0?0:nodeIndex.z-1;
			int maxZ=nodeIndex.z+1>currMap->getZ()?currMap->getZ():nodeIndex.z+1;
			for(int j = minZ;j<=maxZ;j++)
			{	
				MapNode *adjNode = currMap->getNode(i,0,j);
				if (nodeIsAvailable(adjNode))
				{
					if(adjNode->getNodeIndex()!=nodeIndex) //if not the square we occupy
					{							
						//get the distance to final destination;
						Hcost = target==adjNode ?0:(    abs( (target->getNodeIndex().x-i)) + abs((target->getNodeIndex().z-j)) )*10;
						if(i==nodeIndex.x || j==nodeIndex.z)
							Gcost = 10;
						else
							Gcost = 14;

						securityRating= 0;//CalcSecurityRating();
						
						if(currCost==-1 ||  (Gcost+Hcost+securityRating)<currCost )
						{
							nextNode = adjNode;
							currHCost = Hcost;
							currGCost = Gcost;
							currSecurityRating;
							currCost = Gcost+Hcost+securityRating;
						}
					}
				}//end of if nodeIsAvailable
			}//end of for Z
		}//end of for X
		if(nextNode!=0)
		{
			currCost =-1;
			PathNode *newPath = new PathNode(currHCost,currGCost, currSecurityRating,*nextNode);
			path.push_back(newPath);
			nodeIndex = nextNode->getNodeIndex();//re-assess the next node
			nextNode=0;
		}else
		{
			return; //prevent infinite loop if no nodes available
		}
	}//end of while

}//end of function


///
//verify that this node has not been visited
//that there are no objects on this node
bool PathController::nodeIsAvailable(MapNode *node)
{
	if (node==0)
		return false;

	vector<PathNode*>::iterator pIter = path.begin();
	while(pIter!=path.end())
	{
		if((*pIter)->getNodeIndex() == node->getNodeIndex())
			return false;
		pIter++;
	}
	switch( node->getState())
	{
	case EMPTY:
	case GIFT:
		return true;
	}

	return false;
}

bool PathController::nodeAlreadyVisited(MapNode *node)
{
	return false;
}

void PathController::deleteVisited()
{
	visited.clear();
}