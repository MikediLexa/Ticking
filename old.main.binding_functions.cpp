#include <functional>
#include <iostream>
#include <string>

class MyClass
{
  public:
	static void FuncC() {}

	static bool FuncD(int, float) { return true; }

	void NonStaticFunc() {}

	bool NonStaticFuncParams(int x, float y) { return true; }
};

class Player
{
  public:
	std::string GetName() { return Name; }

	void SetName(std::string NewName) { Name = NewName; }

	auto GetRenamer() { return std::bind_front(&Player::SetName, this); }

	std::string Name;
};

void FuncA() {}

bool FuncB(int, float) { return true; }

int Add(int x, int y, int z) { return x + y + z; };

void Logger(auto GetString)
{
	std::cout << "\n\n\nThe Player Name by Logger is: " << GetString();
};

int main()
{
	// free functions
	void (*PtrA)(){FuncA};
	bool (*PtrB)(int, float){FuncB};

	// Static Functions like free Functions
	void (*PtrC)(){MyClass::FuncC};
	bool (*PtrD)(int, float){MyClass::FuncD};

	// Non-Static Functions
	void (MyClass::*PtrE)() = &MyClass::NonStaticFunc;

	bool (MyClass::*PtrF)(int, float) = &MyClass::NonStaticFuncParams;

	// include <functional>
	std::function<void(MyClass&)>{&MyClass::NonStaticFunc};
	std::function<bool(MyClass&, int, float)>{&MyClass::NonStaticFuncParams};

	std::function<void()> PtrTry{MyClass::FuncC};

	// Binding and Partial Application

	auto PartialA{std::bind_front(Add, 1)};
	auto PartialB{std::bind(PartialA, 2, 3)};
	std::cout << "\n\n\nDoing partial Applications by a simple "
				 "Add-Function\nThe Result is: "
			  << PartialB();

	Player PlayerOne{"Anna"};
	auto BoundFunction{std::bind_front(&Player::GetName, &PlayerOne)};

	PlayerOne.Name = "John";
	Logger(BoundFunction);

	Player PlayerTwo;
	auto RenamePlayerTwo{PlayerTwo.GetRenamer()};

	RenamePlayerTwo("Anna");
	std::cout << "\n\nName of PlayerTwo is: " << PlayerTwo.GetName();
}
