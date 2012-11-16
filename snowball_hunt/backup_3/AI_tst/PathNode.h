#pragma once

class PathNode :
	public MapNode
{
	float hCost;
	float gCost;
	float securityRating;

public:
	PathNode(void);
	PathNode(	float newHCost,
				float newGCost,
				float newSecurityRating,
				MapNode newMapNode);
	~PathNode(void);

	float getHCost();
	float getGCost();

	void setHCost(float newHCost);
	void setGCost(float newGCost);
	float getMovementCost();

};
