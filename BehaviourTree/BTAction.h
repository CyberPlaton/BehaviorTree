#pragma once

#include "BTNode.h"

class BTAction : public BTNode
{
public:

	BTAction(std::string name) : m_Name(name)
	{

	}

	virtual ~BTAction()
	{
	}

	bool hasBlackboard() override
	{
		return false;
	}

	BTBlackboard* getBlackboard() override
	{
		return nullptr;
	}

	virtual BTNodeResult command()
	{
		return INVALID;
	}


	BTNodeResult tick() override
	{
		BTNodeResult result = command();
		return result;
	}


	BTNode* parent() override
	{
		return m_Parent;
	}


	void setParent(BTNode* node) override
	{
		m_Parent = node;
	}


	BTNode* child(std::string) override
	{
		return nullptr;
	}


	std::map<int, BTNode*> children() override
	{
		std::map<int, BTNode*> v;
		return v;
	}


	void addChild(BTNode*) override
	{
		return;
	}


	void removeChild(std::string) override
	{
		return;
	}

	void removeFirstChild() override
	{
		return;
	}

	std::string name() override
	{
		return m_Name;
	}

	void freeMemory() override
	{
		using namespace std;
		cout << "Deleting Node \"" << m_Name << "\"" << endl;

		m_Name.clear();
		m_Parent = 0;
		delete this;
	}

private:


	BTNode* m_Parent = nullptr;

	std::string m_Name;
};