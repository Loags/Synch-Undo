#pragma once
#include <string>

class Interactable
{
public:
	enum class InteractableType { Item, PickUp };
	static std::string InteractableToString(const InteractableType interactable) {
		switch (interactable) {
		case InteractableType::Item:
			return "Item";
		case InteractableType::PickUp:
			return "PickUp";
		}
		return {};
	}

protected:
	~Interactable() = default;
	InteractableType interactableType = InteractableType::Item;

public:
	virtual void Interact() = 0;
	InteractableType GetInteractableType() const { return interactableType; }
};

