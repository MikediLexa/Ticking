#include "Monster.h"

#include <iostream>

void Act(Monster& Enemy)
{
	int Utility;
	auto Action{Enemy.SuggestAction(Utility)};

	if (Utility >= 20) {
		Action();

	} else {
		std::cout << "Utility (" << Utility
				  << ") is too low - taking no action\n";
	}
}

int main()
{
	Monster Enemy;
	Act(Enemy);
}