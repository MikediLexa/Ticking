#include <iostream>

void Process(int Number, void (*EvenCallback)() = nullptr)
{
	std::cout << "\nProcessing " << Number;
	if (EvenCallback && Number % 2 == 0) {
		EvenCallback();
	}
}

void LogEven() { std::cout << " - that number is even"; }

int main()
{
	Process(4, LogEven);
	Process(5, LogEven);
	Process(6);
}