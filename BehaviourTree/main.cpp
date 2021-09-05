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
		.add<StoreValueNode>("StoreValueNode")
		.end()
		.end()
		.build();


	tree->findNode("StoreValueNode")->setBlackboard(blackboard);


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


BehaviorTree* create_basic_test_tree()
{
	BTFactory* factory = new BTFactory("TestTree");

	BehaviorTree* tree = factory->add<BTSequence>("Root")
									.add<BTFallback>("FirstChild")
										.end()
									.add<BTTimer>("ThirdChild", BTTimer::Granularity::Seconds, BTTimer::Policy::Greater, 3.0)
										.end()
									.add<BTSequence>("SecondChild")
										.add<BTSequence>("Sequence")
											.add<BTFallback>("Fallback")
												.add<BTParallel>("Parallel", BTParallel::Policy::Require_All, BTParallel::Policy::Require_One)
													.add<BTAction>("FirstAction")
														.end()
													.add<BTAction>("SecondAction")
														.end()
													.add<BTAction>("ThirdAction")
														.end()
													.add<StoreValueNode>("StoreValueAction")
								.build();


	BTBlackboard* blackboard = new BTBlackboard("Main Testing Blackboard");
	tree->findNode("StoreValueAction")->setBlackboard(blackboard);


	delete factory;
	return tree;
}


BehaviorTree* create_basic_timer_tree()
{
	BTFactory* factory = new BTFactory("Timer Tree");

	BehaviorTree* tree = factory->add<BTTimer>("Timer", BTTimer::Granularity::Seconds, BTTimer::Policy::Greater, 1.5)
		.end()
		.build();

	delete factory;
	return tree;
}



void third_testing_run()
{
	BehaviorTree* t = create_basic_timer_tree();
	while (t->update() != BTNodeResult::SUCCESS)
	{

	}


	BehaviorTree* t1 = create_basic_timer_tree();
	while (t1->update() != BTNodeResult::SUCCESS)
	{

	}

	delete t;
	delete t1;
}



void fourth_testing_run()
{
	BehaviorTree* tree = create_basic_test_tree();
	BTFactory::exportBehaviorTree(tree);
	delete tree;
}


int main()
{
	// Define some tree with basic and blackboard.
	testing_run();
	
	// Define some tree with custom node type
	sec_testing_run();

	// Define a number of trees created on the fly with a predefined function
	third_testing_run();

	// Create a tree and export to xml
	fourth_testing_run();


	_CrtCheckMemory();
	_CrtDumpMemoryLeaks();

	return 0;
}