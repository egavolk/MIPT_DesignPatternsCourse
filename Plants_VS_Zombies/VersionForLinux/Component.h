#pragma once
#include <typeinfo>
#include "Units.h"

class AbstractClassComponent
{
public:
	virtual void Action(UnitsTypes type) {}

	virtual void Action() = 0;
};

class Composite :
	public AbstractClassComponent
{
public:
	Composite(std::vector < AbstractClassComponent* > components)
		: children_(components)
	{

	}

	void Action(UnitsTypes type)
	{
		for (int i = 0; i < children_.size(); ++i)
			children_[i]->Action(type);
	}

	void Action()
	{
		for (int i = 0; i < children_.size(); ++i)
			children_[i]->Action();
	}

private:
	std::vector < AbstractClassComponent* > children_;
};

class Leaf :
	public AbstractClassComponent
{
public:
	Leaf(AbstractClassUnit* unit)
		: unit_(unit)
	{

	}

	void Action(UnitsTypes type)
	{
		if (type == unit_->GetType())
			unit_->Action();
	}

	void Action()
	{
		unit_->Action();
	}
private:
	AbstractClassUnit* unit_;
};

class BaseDecorator
	: public AbstractClassComponent
{
public:
	BaseDecorator(AbstractClassComponent* wrappee)
		: wrappee_(wrappee)
	{

	}

	virtual void Action()
	{
		wrappee_->Action();
	}

protected:
	AbstractClassComponent* wrappee_;
};

template < UnitsTypes type >
	class ConcreteUnitDecorator
		: public BaseDecorator
{
public:
	ConcreteUnitDecorator(AbstractClassComponent* wrappee, AbstractClassComponent* component)
		: BaseDecorator(wrappee)
		, component_(component)
	{

	}

	void Action()
	{
		if (wrappee_ != component_)
			wrappee_->Action();
		component_->Action(type);
	}
private:
	AbstractClassComponent* component_;
};

class EconomyDecorator
	: public BaseDecorator
{
public:
	EconomyDecorator(AbstractClassComponent* wrappee)
		: BaseDecorator(wrappee)
	{

	}

	void Action()
	{
		wrappee_->Action();
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("!!!BUT NOW WE HAVE A REST AND WE ARE DEVELOPING\n\n");
	}
};

class AdapterComponentToUnit
	: public AbstractClassUnit
{
public:
	AdapterComponentToUnit(AbstractClassComponent* component, AbstractClassProperties& properties)
		: component_(component)
		, AbstractClassUnit("Composite", properties)
	{

	}

	AdapterComponentToUnit(AbstractClassComponent* component)
		: component_(component)
	{

	}

	void Action()
	{
		component_->Action();
	}
private:
	AbstractClassComponent * component_;
};