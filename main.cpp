#include "Player.h"

#include <functional>
#include <iostream>

void LogDamage() { std::cout << "Player has taken damage"; }

int main()
{
	Player Subject;

	int ObserverId{Subject.AddOnDamageDelegate(LogDamage)};

	Subject.TakeDamage(100);
	Subject.RemoveOnDamageDelegate(ObserverId);
	Subject.TakeDamage(100);
}