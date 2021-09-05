#pragma once

#include "BTAction.h"
#include "BTBlackboard.h"

class StoreValueNode : public BTAction
{
public:
	StoreValueNode(std::string name) :
		BTAction(name)
	{
	}

	~StoreValueNode()
	{
		delete blackboard;
		blackboard = 0;
		store_string_value.clear();
		store_double_value = 0;
	}

	void exportToXML(tinyxml2::XMLElement* elem) override final
	{
		if (blackboard)
		{
			elem->SetAttribute("blackboard", true);
		}
		else
		{
			elem->SetAttribute("blackboard", false);
		}
	}

	bool hasBlackboard() override
	{
		return true;
	}

	void setBlackboard(BTBlackboard* b) override
	{
		blackboard = b;
	}

	BTBlackboard* getBlackboard() override
	{
		return blackboard;
	}

	BTNodeResult command() override
	{
		int i = rand() % 10;

		store_double_value = sin(i) * i;

		store_string_value = "Numeric Value: " + std::to_string(store_double_value);
	

		blackboard->set<double>("Numeric", store_double_value, "double");
		blackboard->set<std::string>("String", store_string_value, "string");

		return BTNodeResult::SUCCESS;
	}


	std::string type() override
	{
		return "StoreValueNode";
	}

	BTBlackboard* blackboard = 0;
	
	std::string store_string_value = "";
	double store_double_value = 0.0;
};