#pragma once
#include <map>

struct sUnique
{
	int unique;
	sUnique();
	void save()const;
	void load();
};


class cIndexCounter
{
public:
	static cIndexCounter* getInstance();

	int getValue(int add);

	void setValue(int value);
protected:
	cIndexCounter();

private:
	int _value;
};


template<class T>
class cUnique
{
protected:
	void insert(T* e)
	{
		e->unique = cIndexCounter::getInstance()->getValue(1);
		_table.insert(std::make_pair(e->unique, e));
	}

	T* get(int unique)
	{
		const auto& it = _table.find(unique);
		if (it == _table.end())
		{
			return nullptr;
		}
		return it->second;
	}

	bool remove(int unique)
	{
		const auto& it = _table.find(unique);
		if (it == _table.end())
		{
			return false;
		}
		delete it->second;
		_table.erase(it);
		return true;
	}
	std::map<int, T*> _table;
};