#pragma once
#include <vector>
#include "Properties.h"

class AbstractClassUnit
{
public:
	AbstractClassUnit() {}

	AbstractClassUnit(char *s)
	{
		for (int i = 0; i < strlen(s); ++i)
			picture_[0][i] = s[i];
	}

	AbstractClassUnit(char *s, AbstractClassProperties properties)
	{
		PrintLineInPicture_(0, s, -1);
		if (properties.IsTypicalLevel())
			PrintLineInPicture_(1, "level", properties.GetLevel());
		else
			PrintLineInPicture_(1, "non typical", -1);
	}

	~AbstractClassUnit() {}

	static const size_t GetWidth()
	{
		return WIDTH_;
	}

	static const size_t GetHeight()
	{
		return HEIGHT_;
	}

	static const size_t GetNumberOfUnits()
	{
		return NUMBER_OF_UNITS_;
	}

	const std::vector < char >& operator[](unsigned index)
	{
		return picture_[index];
	}

	void printLine(unsigned index)
	{
		for (int i = 0; i < WIDTH_; ++i)
			printf("%c", picture_[index][i]);
	}

	UnitsTypes GetType()
	{
		return properties_.GetType();
	}

	virtual void Action() = 0;

protected:
	AbstractClassProperties properties_;
	static const size_t WIDTH_ = 13;
	static const size_t HEIGHT_ = 6;
	static const size_t NUMBER_OF_UNITS_ = 5;
	std::vector < std::vector < char > > picture_ = std::vector < std::vector < char > >(HEIGHT_, std::vector < char >(WIDTH_));

	void FillLine_(unsigned index, char* s)
	{
		for (int i = 0; i < strlen(s); ++i)
			picture_[index][i] = s[i];
	}

	void PrintLineInPicture_(unsigned index, char *start, int x)
	{
		if (x == -1)
		{
			FillLine_(index, start);
			return;
		}
		char s[WIDTH_ + 1];
		sprintf(s, "%s=%d", start, x);
		FillLine_(index, s);
	}
};

class ClassShoot :
	public AbstractClassUnit
{
public:
	ClassShoot(char *s, ShootProperties properties)
		:AbstractClassUnit(s, properties)
	{
		properties_ = properties;
		PrintLineInPicture_(2, "power", properties.GetPower());
		PrintLineInPicture_(3, "interval", properties.GetInterval());
		PrintLineInPicture_(4, "spped", properties.GetSpeedOfBullet());
	}

	void Action()
	{
		printf("I am shooter. I am shooting\n");
	}
};

class ClassWall :
	public AbstractClassUnit
{
public:
	ClassWall(char *s, WallProperties properties)
		:AbstractClassUnit(s, properties)
	{
		properties_ = properties;
		PrintLineInPicture_(2, "defense", properties.GetDefense());
	}

	void Action()
	{
		printf("I am wall. I am defensing\n");
	}
};

class ClassEnergyGenerator :
	public AbstractClassUnit
{
public:
	ClassEnergyGenerator(char *s, EnergyGeneratorProperties properties)
		:AbstractClassUnit(s, properties)
	{
		properties_ = properties;
		PrintLineInPicture_(2, "energy", properties.GetEnergy());
		PrintLineInPicture_(3, "interval", properties.GetInterval());
	}

	void Action()
	{
		printf("I am energy generator. I am generating energy\n");
	}
};

class ClassHit :
	public AbstractClassUnit
{
public:
	ClassHit(char *s, HitProperties properties)
		:AbstractClassUnit(s, properties)
	{
		properties_ = properties;
		PrintLineInPicture_(2, "power", properties.GetPower());
		PrintLineInPicture_(3, "interval", properties.GetInterval());
		PrintLineInPicture_(4, "distance", properties.GetDistance());
	}

	void Action()
	{
		printf("I am hit. I am hitting\n");
	}
};

class ClassMine :
	public AbstractClassUnit
{
public:
	ClassMine(char *s, MineProperties properties)
		:AbstractClassUnit(s, properties)
	{
		properties_ = properties;
	}

	void Action()
	{
		printf("I am mine. I am making BOOOOM\n");
	}
};