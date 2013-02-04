#ifndef ViewVO_h__
#define ViewVO_h__
#include <vector>
struct LevelUpVO
{
	int curLevel;
	int nextLevel;
	int curAttack;
	int nextAttack;
	int curDefense;
	int nextDefense;
	int curLife;
	int nextLife;
	int itemID;
	LevelUpVO():curLevel(5),nextLevel(6),curAttack(500),nextAttack(500),
		curDefense(500),nextDefense(500),curLife(500),nextLife(500),itemID(0)
	{

	}
};

#endif // ViewVO_h__
