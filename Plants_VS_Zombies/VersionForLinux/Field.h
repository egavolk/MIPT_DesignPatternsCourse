#pragma once
#include "AbstractFactory.h"

enum Color { WHITE = 0, RED = 31, GREEN = 32, BLUE = 34 };

class ClassConsoleColor
{
public:
	void SetColor(Color x)
	{
		printf("\033[%dm", x);
	}
};

class ClassPath
{
private:
	std::vector < AbstractClassUnit* > path;

	void printSymbol(int n, char c, bool newLine)
	{
		for (int i = 0; i < n; ++i)
			printf("%c", c);
		if (newLine)
			printf("\n");
	}

public:
	ClassPath()
	{

	}

	ClassPath(size_t len)
	{
		path.resize(len);
	}

	void printPath()
	{
		if (path.empty())
			return;
		int h = AbstractClassUnit::GetHeight();
		int w = AbstractClassUnit::GetWidth();
		printSymbol((w + 1) * path.size() + 1, '-', true);
		for (int i = 0; i < h; ++i)
		{
			printf("|");
			for (int j = 0; j < path.size(); ++j)
			{
				if (path[j])
					path[j]->printLine(i);
				else
					printSymbol(w, ' ', false);
				printf("|");
			}
			printf("\n");
		}
		printSymbol((w + 1) * path.size() + 1, '-', true);
	}

	AbstractClassUnit* &operator[](size_t index)
	{
		return path[index];
	}
};

class ClassField
{
private:
	static ClassField* pInstance_;
	std::vector < ClassPath > field;
	static const size_t SIZE_X = 4;
	static const size_t SIZE_Y = 8;
	ClassConsoleColor color;

	ClassField()
	{
		field = std::vector < ClassPath >(SIZE_X, ClassPath(SIZE_Y));
	}

public:
	static ClassField* GetInstance()
	{
		if (!pInstance_)
			pInstance_ = new ClassField();
		return pInstance_;
	}

	void printField()
	{
		color.SetColor(GREEN);
		for (int i = 0; i < field.size(); ++i)
			field[i].printPath();
		color.SetColor(WHITE);
	}

	ClassPath &operator[](size_t index)
	{
		return field[index];
	}
};

ClassField* ClassField::pInstance_ = nullptr;
