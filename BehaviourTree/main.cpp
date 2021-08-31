/*
* AI Behavior Tree Library.
* 
* 
*/


#include "BTInterface.h"

#include <iostream>

void testing_run()
{
	using namespace std;

	BTFactory* factory = new BTFactory("Main Testing Tree");
	
	BTBlackboard* blackboard = new BTBlackboard("Main Testing Blackboard");

	BehaviorTree* tree = factory->add<BTSequence>("Begin sequence")
		.add<BTParallel>("Parallel Timer Execution", BTParallel::Policy::Require_All, BTParallel::Policy::Require_One)
		.add<BTTimer>("First Timer", BTTimer::Granularity::Milliseconds, BTTimer::Policy::Greater, 100.0)
		.end()
		.add<BTTimer>("Second Timer", BTTimer::Granularity::Milliseconds, BTTimer::Policy::Smaller, 200.0)
		.end()
		.end()
		.build();


	BTNodeResult result = BTNodeResult::FAILURE;
	int i = 0;
	while (tree->update() == BTNodeResult::FAILURE)
	{
		blackboard->set<int>("Time", ++i, "int");
		blackboard->set<BTNodeResult>("Timer Result", result, "bt_node_result");
	}

	delete factory;
	delete blackboard;
	delete tree;
}


#include "StoreValueNode.h"
void sec_testing_run()
{

	using namespace std;

	BTFactory* factory = new BTFactory("Main Testing Tree");

	BTBlackboard* blackboard = new BTBlackboard("Main Testing Blackboard");

	BehaviorTree* tree = factory->add<BTSequence>("Begin sequence")
		.add<BTParallel>("Parallel Timer Execution", BTParallel::Policy::Require_All, BTParallel::Policy::Require_One)
		.add<BTTimer>("First Timer", BTTimer::Granularity::Seconds, BTTimer::Policy::Greater, 3.0)
		.end()
		.add<BTTimer>("Second Timer", BTTimer::Granularity::Seconds, BTTimer::Policy::Smaller, 5.0)
		.end()
		.add<StoreValueNode>("StoreValueNode", blackboard)
		.end()
		.end()
		.build();


	delete factory;


	BTNodeResult result = BTNodeResult::FAILURE;
	int i = 0;
	while (tree->update() == BTNodeResult::FAILURE)
	{
		blackboard->set<int>("Time", ++i, "int");
		blackboard->set<BTNodeResult>("Timer Result", result, "bt_node_result");
	}

	delete tree;
}



int main()
{
	testing_run();
	sec_testing_run();


	_CrtCheckMemory();
	_CrtDumpMemoryLeaks();

	return 0;
}