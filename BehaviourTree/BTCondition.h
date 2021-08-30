#pragma once

#include "BTNode.h"

class BTCondition : public BTNode
{
public:

	BTCondition(std::string name) : m_Name(name)
	{

	}

	~BTCondition()
	{
		m_Name.clear();
	}

	virtual BTNodeResult checkCondition()
	{
		return INVALID;
	}

	BTNodeResult tick() override
	{
		if (checkCondition() == BTNodeResult::SUCCESS)
		{
			return SUCCESS;
		}
		else
		{
			return FAILURE;
		}
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


	std::map<int, BTNode*>  children() override
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

	std::string name() override
	{
		return m_Name;
	}


private:


	BTNode* m_Parent = nullptr;

	std::string m_Name;
};