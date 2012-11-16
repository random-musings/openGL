#include "stdafx.h"

MapNode::MapNode(void):
			location(0,0,0),
			maxPts(0,0,0),
			minPts(0,0,0),
			dimension(0),
			hideRating(0),
			state(EMPTY),
			nodeIndex(Point(0,0,0))
{
}

MapNode::~MapNode(void)
{
}

MapNode::MapNode(enum nodeState newState,
			Point newLocation,
			Point newMinPoints,
			Point newMaxPoints,
			float newSize,
			float newHideRating,
			Point newNodeIndex):
			location(newLocation),
			maxPts(newMaxPoints),
			minPts(newMinPoints),
			dimension(newSize),
			hideRating(newHideRating),
			state(newState),
			nodeIndex(newNodeIndex)
	{}


	bool MapNode::itemInNode(Point item)
	{
		if( item.x >minPts.x && item.x<maxPts.x &&
			item.y >minPts.y && item.y<maxPts.y &&
			item.z >minPts.y && item.z<maxPts.z)
		{return true;}
		return false;

	}

	bool MapNode::itemInNode(Obstacle item)
	{
		return itemInNode(item.getOrigin());
	}


	void MapNode::setBoundingBox(Point newMinPoints,Point newMaxPoints)
	{
		minPts = newMinPoints;
		maxPts = newMaxPoints;
	}

	void MapNode::setSize(GLfloat newSize) 
	{
		dimension = newSize;
	}

	void MapNode::setLocation(Point newPoint)
	{
		location = newPoint;
	}

	void MapNode::setHideRating(GLfloat newHideRating)
	{
		hideRating = newHideRating;
	}

	GLfloat MapNode::getSize() { return dimension;}
	Point MapNode::getLocation(){ return location;}
	GLfloat MapNode::getHideRating(){ return hideRating;}


	void MapNode::setState(enum nodeState newState)
	{
		state = newState;
	}

	enum nodeState MapNode::getState()
	{
		return state;
	}	

	Point MapNode::getNodeIndex()
	{
		return nodeIndex;
	}

