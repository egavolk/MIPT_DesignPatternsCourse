#pragma once

enum LevelOfUnits { LOW = 0, MEDIUM = 1, HIGH = 2, SUPER = 3 };
enum UnitsTypes { SHOOT = 0, WALL = 1, ENERGY_GENERATOR = 2, HIT = 3, MINE = 4, COMPOSITE = 5 };

class AbstractClassProperties
{
private:
	bool isTypicalLevel_;
	LevelOfUnits level_;
	UnitsTypes type_;
public:
	AbstractClassProperties()
		: isTypicalLevel_(false)
	{

	}

	AbstractClassProperties(UnitsTypes type)
		: isTypicalLevel_(false)
		, type_(type)
	{

	}

	AbstractClassProperties(LevelOfUnits level, UnitsTypes type)
		: level_(level)
		, isTypicalLevel_(true)
		, type_(type)
	{

	}

	bool IsTypicalLevel()
	{
		return isTypicalLevel_;
	}

	LevelOfUnits GetLevel()
	{
		return level_;
	}

	UnitsTypes GetType()
	{
		return type_;
	}
};

class ShootProperties
	:public AbstractClassProperties
{
public:
	ShootProperties(LevelOfUnits level = LOW)
		: AbstractClassProperties(level, SHOOT)
		, power_(GetPowerDependingOnLevel_(level))
		, interval_(GetIntervalDependingOnLevel_(level))
		, speedOfBullet_(GetSpeedOfBulletDependingOnLevel_(level))
	{

	}

	ShootProperties(unsigned power, unsigned interval, unsigned speedOfBullet)
		: AbstractClassProperties(SHOOT)
		, power_(power)
		, interval_(interval)
		, speedOfBullet_(speedOfBullet)
	{

	}

	const unsigned GetPower()
	{
		return power_;
	}

	const unsigned GetInterval()
	{
		return interval_;
	}

	const unsigned GetSpeedOfBullet()
	{
		return speedOfBullet_;
	}

private:
	unsigned power_, interval_, speedOfBullet_;
	static const unsigned BASIC_POWER_ = 10;
	static const unsigned BASIC_INTERVAL_ = 1000;
	static const unsigned BASIC_SPEED_OF_BULLET_ = 50;

	unsigned GetPowerDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_POWER_ + 10 * level;
	}

	unsigned GetIntervalDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_INTERVAL_ - 200 * level;
	}

	unsigned GetSpeedOfBulletDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_SPEED_OF_BULLET_ + 50 * level;
	}
};

class WallProperties
	:public AbstractClassProperties
{
public:
	WallProperties(LevelOfUnits level = LOW)
		: AbstractClassProperties(level, WALL)
		, defense_(GetDefenseDependingOnLevel_(level))
	{

	}

	WallProperties(unsigned defense)
		: AbstractClassProperties(WALL)
		, defense_(defense)
	{

	}

	const unsigned GetDefense()
	{
		return defense_;
	}

private:
	unsigned defense_;
	static const unsigned BASIC_DEFENSE_ = 100;

	unsigned GetDefenseDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_DEFENSE_ + 50 * level;
	}
};

class EnergyGeneratorProperties
	:public AbstractClassProperties
{
public:
	EnergyGeneratorProperties(LevelOfUnits level = LOW)
		: AbstractClassProperties(level, ENERGY_GENERATOR)
		, energy_(GetEnergyDependingOnLevel_(level))
		, interval_(GetIntervalDependingOnLevel_(level))
	{

	}

	EnergyGeneratorProperties(unsigned energy, unsigned interval)
		: AbstractClassProperties(ENERGY_GENERATOR)
		, energy_(energy)
		, interval_(interval)
	{

	}

	const unsigned GetEnergy()
	{
		return energy_;
	}

	const unsigned GetInterval()
	{
		return interval_;
	}

private:
	unsigned energy_, interval_;
	static const unsigned BASIC_ENERGY_ = 100;
	static const unsigned BASIC_INTERVAL_ = 5000;

	unsigned GetEnergyDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_ENERGY_ + 40 * level;
	}

	unsigned GetIntervalDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_INTERVAL_ - 500 * level;
	}
};

class HitProperties
	:public AbstractClassProperties
{
public:
	HitProperties(LevelOfUnits level = LOW)
		: AbstractClassProperties(level, HIT)
		, power_(GetPowerDependingOnLevel_(level))
		, interval_(GetIntervalDependingOnLevel_(level))
		, distance_(GetDistanceDependingOnLevel_(level))
	{

	}

	HitProperties(unsigned power, unsigned interval, unsigned distance)
		: AbstractClassProperties(HIT)
		, power_(power)
		, interval_(interval)
		, distance_(distance)
	{

	}

	const unsigned GetPower()
	{
		return power_;
	}

	const unsigned GetInterval()
	{
		return interval_;
	}

	const unsigned GetDistance()
	{
		return distance_;
	}

private:
	unsigned power_, interval_, distance_;
	static const unsigned BASIC_POWER_ = 10;
	static const unsigned BASIC_INTERVAL_ = 1000;
	static const unsigned BASIC_DISTANCE_ = 5;

	unsigned GetPowerDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_POWER_ + 10 * level;
	}

	unsigned GetIntervalDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_INTERVAL_ - 200 * level;
	}

	unsigned GetDistanceDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_DISTANCE_ + 2 * level;
	}
};

class MineProperties
	:public AbstractClassProperties
{
public:
	MineProperties(LevelOfUnits level = LOW)
		:AbstractClassProperties(level, MINE)
	{

	}
};

class CompositeProperties
	: public AbstractClassProperties
{
public:
	CompositeProperties(LevelOfUnits level = LOW)
		: AbstractClassProperties(level, COMPOSITE)
		, power_(GetPowerDependingOnLevel_(level))
		, interval_(GetIntervalDependingOnLevel_(level))
		, distance_(GetDistanceDependingOnLevel_(level))
		, defense_(GetDefenseDependingOnLevel_(level))
		, energy_(GetEnergyDependingOnLevel_(level))
	{

	}

	CompositeProperties(unsigned power, unsigned interval, unsigned distance, unsigned defense, unsigned energy)
		: AbstractClassProperties(HIT)
		, power_(power)
		, interval_(interval)
		, distance_(distance)
		, defense_(defense)
		, energy_(energy)
	{

	}

	const unsigned GetDefense()
	{
		return defense_;
	}

	const unsigned GetEnergy()
	{
		return energy_;
	}

	const unsigned GetPower()
	{
		return power_;
	}

	const unsigned GetInterval()
	{
		return interval_;
	}

	const unsigned GetDistance()
	{
		return distance_;
	}

private:
	unsigned power_, interval_, distance_, defense_, energy_;
	static const unsigned BASIC_POWER_ = 10;
	static const unsigned BASIC_INTERVAL_ = 1000;
	static const unsigned BASIC_DISTANCE_ = 5;
	static const unsigned BASIC_DEFENSE_ = 100;
	static const unsigned BASIC_ENERGY_ = 100;

	unsigned GetDefenseDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_DEFENSE_ + 50 * level;
	}

	unsigned GetPowerDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_POWER_ + 10 * level;
	}

	unsigned GetIntervalDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_INTERVAL_ - 200 * level;
	}

	unsigned GetDistanceDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_DISTANCE_ + 2 * level;
	}

	unsigned GetEnergyDependingOnLevel_(LevelOfUnits level)
	{
		return BASIC_ENERGY_ + 40 * level;
	}
};
