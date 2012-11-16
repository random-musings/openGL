#include "stdafx.h"


PathNode::PathNode(void):	hCost(0),
							gCost(0),
							securityRating(0)
{}

PathNode::PathNode(	float newHCost,
				float newGCost,
				float newSecurityRating,
				MapNode newMapNode):
			hCost(newHCost),
			gCost(newGCost),
			securityRating(newSecurityRating),
			MapNode(newMapNode)
{}

PathNode::~PathNode(void)
{}

float PathNode::getHCost()
{
	return hCost;
}

float PathNode::getGCost()
{
	return gCost;
}

void PathNode::setHCost(float newHCost)
{
	hCost = newHCost;
}

void PathNode::setGCost(float newGCost)
{
	gCost = newGCost;
}

float PathNode::getMovementCost()
{
	return hCost+gCost - securityRating;
}



