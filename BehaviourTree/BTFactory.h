#pragma once

#include "BTNodes.h"
#include "BehaviorTree.h"


class BTFactory
{
public:
	BTFactory(const std::string& tree_name) : m_Tree(new BehaviorTree(tree_name)) {}


	~BTFactory()
	{
		last_parent = 0;
		m_Tree = 0;
		memset(&has_root, 0, sizeof(has_root));
	}

	/*
	* Add a node as child to the current worked on node.
	* The Arguments must match the required arguments for the constructor.
	*/
	template < typename NodeType, class... Args >
	BTFactory& add(const std::string& node_name, Args... args)
	{
		using namespace std;

		NodeType* node = new NodeType(node_name, args...);

		if (has_root == false)
		{
			m_Tree->setRoot(node);
			has_root = true;
			last_parent = node;
		}
		else
		{
			last_parent->addChild(node);
		}

		return *this;
	}


	/*
	* End Adding children to current Node and fallback to its parent.
	*/
	BTFactory& end()
	{
		if (last_parent->parent())
		{
			last_parent = last_parent->parent();
		}

		return *this;
	}


	/*
	* Return the complete builded tree.
	*/
	BehaviorTree* build()
	{
		return m_Tree;
	}


private:

	BTNode* last_parent = nullptr;
	BehaviorTree* m_Tree = nullptr;

	bool has_root = false;
};