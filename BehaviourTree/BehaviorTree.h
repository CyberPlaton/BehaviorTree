#pragma once

#include "BTNodes.h"
#include "BTBlackboard.h"
#include "Any.h"

class BehaviorTree
{
public:
	BehaviorTree(std::string name) : m_Name(name) {}

	~BehaviorTree()
	{
		// Delete root
		delete m_Root;
		m_Root = 0;
	}

	BTNodeResult update()
	{
		return m_Root->tick();
	}

	void setRoot(BTNode* node)
	{
		m_Root = node;
	}


private:

	BTNode* m_CurrentlyExecuting = nullptr;

	BTNode* m_Root = nullptr;

	std::string m_Name;

};
