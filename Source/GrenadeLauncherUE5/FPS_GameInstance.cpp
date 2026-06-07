// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_GameInstance.h"

void UFPS_GameInstance::SetOriginalWeaponValues()
{

	

	AWeapons::originalWeaponInfo.damage = savedWeaponInfo.damage;
	AWeapons::originalWeaponInfo.reloadTime = savedWeaponInfo.reloadSpeedRate;
	AWeapons::originalWeaponInfo.ammo = savedWeaponInfo.ammo;
	AWeapons::originalWeaponInfo.fireRate = savedWeaponInfo.fireRate;



}