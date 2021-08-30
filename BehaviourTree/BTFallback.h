#pragma once

#include "BTNode.h"

class BTFallback : public BTNode
{
public:

	BTFallback(std::string name) : m_Name(name)
	{

	}


	~BTFallback()
	{
		for (auto& kid : m_Children)
		{
			// Delete nodes
			kid.second->~BTNode();
		}

		m_Name.clear();
	}

	BTNodeResult tick() override
	{
		for (auto& kid : m_Children)
		{
			BTNodeResult result = kid.second->tick();

			if (result == BTNodeResult::RUNNING)
			{
				return BTNodeResult::RUNNING;
			}
			else if (result == BTNodeResult::SUCCESS)
			{
				return BTNodeResult::SUCCESS;
			}
		}

		return BTNodeResult::FAILURE;
	}


	BTNode* parent() override
	{
		return m_Parent;
	}


	void setParent(BTNode* node) override
	{
		m_Parent = node;
	}


	BTNode* child(std::string name) override
	{
		for (auto& kid : m_Children)
		{
			if (strcmp(name.c_str(), kid.second->name().c_str()) == 0)
			{
				return kid.second;
			}
		}

		return nullptr;
	}

	std::map<int, BTNode*>  children() override
	{
		return m_Children;
	}


	void addChild(BTNode* node) override
	{
		m_Children.try_emplace(m_NextNodeIndex, node);

		m_NextNodeIndex++;

		node->setParent(this);
	}


	void removeChild(std::string name) override
	{
		int location = 0;

		for (auto& kid : m_Children)
		{
			if (strcmp(kid.second->name().c_str(), name.c_str()) == 0)
			{
				m_Children.erase(location);
				m_NextNodeIndex--;
				return;
			}

			location++;
		}
	}


	std::string name() override
	{
		return m_Name;
	}


private:

	BTNode* m_Parent = nullptr;

	/*
	* The first number indicates the positional value of the node,
	* where 0 means this node is executed first and n-1 is the last node.
	*/
	std::map<int, BTNode*> m_Children;
	int m_NextNodeIndex = 0;

	std::string m_Name;
};