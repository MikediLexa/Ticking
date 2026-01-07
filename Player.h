// Player.h
#pragma once
#include <functional>
#include <iostream>
#include <vector>

class Player
{
  public:
	using DelegateType = std::function<void()>;

	int AddOnDamageDelegate(DelegateType Callback)
	{
		MulticastDelegate.push_back(Callback);
		return NextObserverIndex++;
	}

	void RemoveOnDamageDelegate(int Index)
	{
		std::cout << "Removing Observer at index " << Index << '\n';
		if (Index >= 0 && Index < MulticastDelegate.size()) {
			MulticastDelegate[Index] = nullptr;
		}
	}

	void TakeDamage(int Damage) { NotifyOnDamage(); }

  private:
	int NextObserverIndex{0};
	std::vector<DelegateType> MulticastDelegate;

	void NotifyOnDamage()
	{
		std::cout << "Took Damage - Notifying " << MulticastDelegate.size()
				  << " Observer(s)\n";

		for (auto& Callback : MulticastDelegate) {
			if (Callback) Callback();
		}
	}
};