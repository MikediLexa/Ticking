#pragma once
#include "Actions.h"

#include <functional>
#include <iostream>

class Monster
{
  public:
	std::function<void()> SuggestAction(int& Utility)
	{
		if (canHeal()) {
			Utility = 150;
			return std::bind_front(&Monster::Heal, this);
		} else if (canAttack()) {
			Utility = GetAttackDamage();
			return std::bind_front(&Monster::Attack, this);
		} else {
			Utility = 25;
			return std::bind_front(&Monster::RunAway, this);
		}
	}

	void Heal() { std::cout << "Healing...\n"; }

	void Attack() { std::cout << "Attacking...\n"; }

	void RunAway() { std::cout << "Running Away...\n"; }

  private:
	bool canHeal() { return false; }

	bool canAttack() { return false; }

	int GetAttackDamage() { return 100; }
};