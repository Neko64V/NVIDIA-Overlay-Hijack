#pragma once
#include "../GameSDK/GameSDK.h"

struct Bone {
	Vector3 position;
	uint64_t address[2];
};

struct AllBones {
	Bone bone[32]{};
};

class CEntity
{
public:
    uintptr_t address;
	uintptr_t m_pCSPlayerPawn;
	uintptr_t m_pGameSceneNode;
	uintptr_t m_pCameraServices;
	uintptr_t m_pCollision;
	uintptr_t m_pClippingWeapon;

	// Player
	Vector3 m_vecAbsVelocity;
	Vector3 m_vOldOrigin;

	int m_iTeamNum;
	int m_lifeState;
	int m_iHealth;
	int m_iMaxHealth;
	int m_ArmorValue;
	uintptr_t m_pBoneArray;
	char pName[32];
	char pWeaponName[32];

    // Functions
	bool Update();
	bool UpdateStatic(const uintptr_t& entitylist);
	bool IsDead();

	Vector3 vecMin();
	Vector3 vecMax();

	uint32_t GetFlag();
	std::vector<Vector3> GetBoneList();
};