#include "Actions.h"
#include "Player.h"

#include <functional>
#include <iostream>

void Process(int Number, void (*EvenCallback)() = nullptr)
{
	std::cout << "\nProcessing " << Number;
	if (EvenCallback && Number % 2 == 0) {
		EvenCallback();
	}
}

void LogEven() { std::cout << " - that number is even"; }

void FunctionA() {};

bool FunctionB(int x) { return true; }

bool FunctionC(int x, float y) { return true; }

void OnDefeat() { std::cout << "Game Over"; }

int main()
{
	Process(4, LogEven);
	Process(5, LogEven);
	Process(6);

	auto PtrA{FunctionA}; // With "auto" I can ignore the Pointerdeclaration
						  // witch "(*PtrA)()..."
	bool (*PtrB)(int){FunctionB}; // with the return-type I need to write the
								  // full form of the function pointer
	std::function<bool(int, float)> PtrC{FunctionC};

	std::function PtrD{FunctionC};

	std::cout << "\n\n\n\n\n // asynchronous callbacks output: \n\n";
	// Playing with asynchronous callbacks
	Player PlayerOne{100, OnDefeat}; // Player 1 init mit 100 Leben und
									 // CallbackFunktion bei defeat
	PlayerOne.TakeDamage(101);

	std::cout << "\n\n\n\n\n // returning functions: \n\n";

	int Utility;
	auto Action{SuggestAction(Utility)};

	if (Utility >= 100) {
		Action();
	} else {
		std::cout << "Utility (" << Utility
				  << ") is too low - taking no action";
	}
}