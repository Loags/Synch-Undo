#pragma once
#include <unordered_map>

#include "Attackable.h"
#include "CharacterController.h"
#include "Movable.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class Character : public Component, public Movable, public Attackable, public CharacterController
{
private:
	Uint32 deathTime = 0;
	bool pendingRespawn = false;
	Character* lastAttackTarget;
	CommandInvoker* commandInvoker;

protected:
	const GameObject* gridObject;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	std::unordered_map<SDL_Keycode, Movable::Direction> keyMap;
	SDL_Keycode attackKey;

public:
	Character(GameObject* owner, const GameObject* gridObject, const int offSet, const CharacterStats::CharacterType characterType, const int health, const int damage, const std::string& componentName);
	~Character() override = default;
	void Update() override;
	void Move(const GameObject* gridObject, const Direction newFacingDirection) override;
	Character* Attack();
	void Attack(Attackable* target) override;
	void Die() override;
	void Respawn() override;

	const GameObject* GetGridObject() const { return gridObject; }
	const std::unordered_map<SDL_Keycode, Movable::Direction>& GetKeyMap() const { return keyMap; }
	SDL_Keycode GetAttackKey() const { return attackKey; }
	Uint32 GetDeathTime() const { return deathTime; }
	bool GetPendingRespawn() const { return pendingRespawn; }
	Character* GetLastAttackTarget() const { return lastAttackTarget; }
	CommandInvoker* GetCommandInvoker() const { return commandInvoker; }

	void SetDeathTime(Uint32 newDeathTime) { deathTime = newDeathTime; }
	void SetPendingRespawn(bool newPendingRespawn) { pendingRespawn = newPendingRespawn; }
};

