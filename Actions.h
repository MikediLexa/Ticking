#pragma once
#include <functional>
#include <iostream>

void Heal() { std::cout << "Healing ... \n"; }

void Attack() { std::cout << "Attack ... \n"; }

void RunAway() { std::cout << "Running away ... \n"; }

bool canHeal() { return false; }

bool canAttack() { return false; }

bool GetAttackDamage() { return 100; }

std::function<void()> SuggestAction(int& Utility)
{
	if (canHeal()) {
		Utility = 150;
		return Heal;
	} else if (canAttack()) {
		Utility = GetAttackDamage();
		return Attack;

	} else {
		Utility = 25;
		return RunAway;
	}
}