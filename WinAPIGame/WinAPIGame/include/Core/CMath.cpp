#include "CMath.h"

float CMath::Distance(const POSITION& tPos1, const POSITION& tPos2)
{
	float dx, dy;
	dx = tPos1.x - tPos2.x;
	dy = tPos1.y - tPos2.y;

	return sqrtf(dx * dx + dy * dy);
}
