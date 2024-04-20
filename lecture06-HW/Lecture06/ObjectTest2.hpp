#pragma once
#include <iostream>

using namespace std;

class ObjectTest2
{
public:
	ObjectTest2()
	{
		cout << "생성되었다" << endl;
	}
	~ObjectTest2()
	{
		cout << "소멸되었다" << endl;
	}

};

