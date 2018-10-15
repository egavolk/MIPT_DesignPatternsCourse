#pragma once
#include "Units.h"

class AbstractFactory
{
public:
	virtual AbstractClassUnit* CreateShoot(LevelOfUnits level) = 0;

	virtual AbstractClassUnit* CreateWall(LevelOfUnits level) = 0;

	virtual AbstractClassUnit* CreateEnergyGenerator(LevelOfUnits level) = 0;

	virtual AbstractClassUnit* CreateHit(LevelOfUnits level) = 0;

	virtual AbstractClassUnit* CreateMine(LevelOfUnits level) = 0;
};

class ClassPlantFactory :
	public AbstractFactory
{
public:
	ClassShoot* CreateShoot(LevelOfUnits level)
	{
		ShootProperties currentProperties(level);
		return new ClassShoot("PlantShoot", currentProperties);
	}
	ClassWall* CreateWall(LevelOfUnits level)
	{
		WallProperties currentProperties(level);
		return new ClassWall("PlantWall", currentProperties);
	}
	ClassEnergyGenerator* CreateEnergyGenerator(LevelOfUnits level)
	{
		EnergyGeneratorProperties currentProperties(level);
		return new ClassEnergyGenerator("PlantEnergy", currentProperties);
	}
	ClassHit* CreateHit(LevelOfUnits level)
	{
		HitProperties currentProperties(level);
		return new ClassHit("PlantHit", currentProperties);
	}
	ClassMine* CreateMine(LevelOfUnits level)
	{
		MineProperties currentProperties(level);
		return new ClassMine("PlantMine", currentProperties);
	}
};

class ClassPetFactory :
	public AbstractFactory
{
public:
	ClassShoot* CreateShoot(LevelOfUnits level)
	{
		ShootProperties currentProperties(level);
		return new ClassShoot("PetShoot", currentProperties);
	}
	ClassWall* CreateWall(LevelOfUnits level)
	{
		WallProperties currentProperties(level);
		return new ClassWall("PetWall", currentProperties);
	}
	ClassEnergyGenerator* CreateEnergyGenerator(LevelOfUnits level)
	{
		EnergyGeneratorProperties currentProperties(level);
		return new ClassEnergyGenerator("PetEnergy", currentProperties);
	}
	ClassHit* CreateHit(LevelOfUnits level)
	{
		HitProperties currentProperties(level);
		return new ClassHit("PetHit", currentProperties);
	}
	ClassMine* CreateMine(LevelOfUnits level)
	{
		MineProperties currentProperties(level);
		return new ClassMine("PetMine", currentProperties);
	}
};