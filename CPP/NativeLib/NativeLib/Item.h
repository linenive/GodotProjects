#pragma once
#include <string>
#include "Common.h"

class Item  {

private:
	string name;
	string type;
	int id;

public:
	string GetName() { return name; }
	void SetName(string name) { this->name = name; }

	string GetType() { return type; }
	void SetType(string type) { this->type = type; }

	int GetID() { return id; }
	void SetID(int _id) { id = _id; }

	Item() {}
	Item(string name, string type) : name(name), type(type) {}
};