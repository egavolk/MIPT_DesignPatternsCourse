#pragma once
#include "Field.h"
#include "Component.h"

enum KindOfUnits { PLANT = 0, PET = 1 };
enum ComponentType { UNIT = 0, SQUAD = 1, ARMY = 2 };
enum DecoratorType { NON = 0, ORDER = 1, ECONOMY = 2 };

class ClassDialog
{
public:
	KindOfUnits ChooseKindOfUnits()
	{
		color.SetColor(RED);
		printf("What kind of units do you want to use in fight?\n");
		color.SetColor(WHITE);
		printf("Plants: 0\nPets: 1\nPlease, enter the number\n");
		int x;
		scanf("%d", &x);
		system("cls");
		return KindOfUnits(x);
	}

	bool IsSecondTaskDemostration()
	{
		color.SetColor(RED);
		printf("Choose variant of demonstration\n");
		color.SetColor(WHITE);
		printf("First task demonstration: 1\nSecond task demonstration: 2\nEnter the number: ");
		int x;
		scanf("%d", &x);
		system("cls");
		return x == 2;
	}

	void CreateUnit(int &x, int &y, UnitsTypes &type, LevelOfUnits &level)
	{
		color.SetColor(RED);
		printf("Choose unit to use. Format to enter is: 'X Y Type Level' without brakets.\n");
		printf("X and Y are coordinates in zero-numeration\nTypes are\nShoot: 0\nWall: 1\nEnergyGenerator: 2\nHit: 3\nMine: 4\nLevel from 0 to 3\n");
		scanf("%d%d%d%d", &x, &y, &type, &level);
		color.SetColor(WHITE);
	}

	void CreateUnitComponent(UnitsTypes &type, LevelOfUnits &level)
	{
		color.SetColor(RED);
		printf("Choose unit to use. Format to enter is: 'Type Level' without brakets.\n");
		printf("Types are\nShoot: 0\nWall: 1\nEnergyGenerator: 2\nHit: 3\nMine: 4\nLevel from 0 to 3\n");
		scanf("%d%d", &type, &level);
		color.SetColor(WHITE);
	}

	void CreateSquadComponent(std::vector < UnitsTypes > &types, std::vector < LevelOfUnits > &levels)
	{
		color.SetColor(RED);
		printf("Choose units to use in squad. Choose Number of units: ");
		int n;
		scanf("%d", &n);
		printf("Print n lines for units. Format to enter is : 'Type Level' without brakets.\n");
		printf("Types are\nShoot: 0\nWall: 1\nEnergyGenerator: 2\nHit: 3\nMine: 4\nLevel from 0 to 3\n");
		for (int i = 0; i < n; ++i)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			types.push_back(UnitsTypes(a));
			levels.push_back(LevelOfUnits(b));
		}
		color.SetColor(WHITE);
	}

	void CreateArmyComponent(int &n)
	{
		color.SetColor(RED);
		printf("Choose squads to use in army. Choose Number of squads: ");
		scanf("%d", &n);
		color.SetColor(WHITE);
	}

	ComponentType ChooseComponentType()
	{
		printf("Choose, what do you want to create?\nUnit: 0\nSquad: 1\nArmy: 2\n");
		int x;
		scanf("%d", &x);
		return ComponentType(x);
	}

	DecoratorType ChooseDecoratorType()
	{
		printf("Choose, what decorator do you want to use?\nNon: 0\nOrder: 1\nEconomy: 2\n");
		int x;
		scanf("%d", &x);
		return DecoratorType(x);
	}

	void GetOrder(std::vector < DecoratorType > &order)
	{
		printf("How many objects do you want to use? ");
		int n;
		scanf("%d", &n);
		printf("Print order of units\nShoot: 0\nWall: 1\nEnergyGenerator: 2\nHit: 3\nMine: 4\n");
		for (int i = 0; i < n; ++i)
		{
			int x;
			scanf("%d", &x);
			order.push_back(DecoratorType(x));
		}
	}

private:
	ClassConsoleColor color;
};

class ClassGame
{
public:
	void Run()
	{
		KindOfUnits factoryType = dialog.ChooseKindOfUnits();
		if (dialog.IsSecondTaskDemostration())
			SecondTaskDemonstration(factoryType);
		else
			FirstTaskDemonstration(factoryType);
	}

	void FirstTaskDemonstration(KindOfUnits factoryType)
	{
		while (true)
		{
			system("cls");
			field.printField();
			int x, y;
			UnitsTypes unitType;
			LevelOfUnits level;
			dialog.CreateUnit(x, y, unitType, level);
			if (!field[x][y])
			{
				field[x][y] = CreateUnit(unitType, level, factoryType);
			}
		}
	}

	void SecondTaskDemonstration(KindOfUnits factoryType)
	{
		ComponentType componentType = dialog.ChooseComponentType();
		AbstractClassComponent* component;
		if (componentType == UNIT)
		{
			component = CreateUnitComponent(factoryType);
		}
		if (componentType == SQUAD)
		{
			component = CreateSquadComponent(factoryType);
		}
		if (componentType == ARMY)
		{
			component = CreateArmyComponent(factoryType);
		}
		DecoratorType decoratorType = dialog.ChooseDecoratorType();
		AbstractClassComponent* decComponent = component;
		if (decoratorType == ECONOMY)
		{
			decComponent = new EconomyDecorator(component);
		}
		if (decoratorType == ORDER)
		{
			std::vector < DecoratorType > order;
			dialog.GetOrder(order);
			for (int i = 0; i < order.size(); ++i)
			{
				decComponent = NewConcreteUnitDecorator(order[i], decComponent, component);
			}
		}
		AdapterComponentToUnit *adaptDecComponent = new AdapterComponentToUnit(decComponent);
		adaptDecComponent->Action();
	}
private:
	ClassDialog dialog;
	ClassField field = *ClassField::GetInstance();

	AbstractClassComponent* NewConcreteUnitDecorator(DecoratorType type, AbstractClassComponent* decComponent, AbstractClassComponent* component)
	{
		if (type == SHOOT)
			return new ConcreteUnitDecorator < SHOOT >(decComponent, component);
		if (type == WALL)
			return new ConcreteUnitDecorator < WALL >(decComponent, component);
		if (type == ENERGY_GENERATOR)
			return new ConcreteUnitDecorator < ENERGY_GENERATOR >(decComponent, component);
		if (type == HIT)
			return new ConcreteUnitDecorator < HIT >(decComponent, component);
		if (type == MINE)
			return new ConcreteUnitDecorator < MINE >(decComponent, component);
	}

	AbstractClassComponent* CreateUnitComponent(KindOfUnits factoryType)
	{
		UnitsTypes unitType;
		LevelOfUnits level;
		dialog.CreateUnitComponent(unitType, level);
		return new Leaf(CreateUnit(unitType, level, factoryType));
	}

	AbstractClassComponent* CreateSquadComponent(KindOfUnits factoryType)
	{
		std::vector < UnitsTypes > types;
		std::vector < LevelOfUnits > levels;
		dialog.CreateSquadComponent(types, levels);
		std::vector < AbstractClassComponent* > components;
		for (int i = 0; i < types.size(); ++i)
			components.push_back(new Leaf(CreateUnit(types[i], levels[i], factoryType)));
		return new Composite(components);
	}

	AbstractClassComponent* CreateArmyComponent(KindOfUnits factoryType)
	{
		int n;
		dialog.CreateArmyComponent(n);
		std::vector < AbstractClassComponent* > components;
		for (int i = 0; i < n; ++i)
			components.push_back(CreateSquadComponent(factoryType));
		return new Composite(components);
	}

	AbstractClassUnit* CreateUnit(UnitsTypes type, LevelOfUnits level, KindOfUnits factoryType)
	{
		ClassPlantFactory plantFactory;
		ClassPetFactory petFactory;
		if (factoryType == PET)
			return CreateUnit(type, level, petFactory);
		if (factoryType == PLANT)
			return CreateUnit(type, level, plantFactory);
	}

	AbstractClassUnit* CreateUnit(UnitsTypes type, LevelOfUnits level, AbstractFactory &factory)
	{
		if (type == SHOOT)
			return factory.CreateShoot(level);
		if (type == WALL)
			return factory.CreateWall(level);
		if (type == ENERGY_GENERATOR)
			return factory.CreateEnergyGenerator(level);
		if (type == HIT)
			return factory.CreateHit(level);
		if (type == MINE)
			return factory.CreateMine(level);
	}
};