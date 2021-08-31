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

	/*
	BehaviorTree* tree = factory->add<BTSequence>("Begin sequence")
		.add<BTParallel>("Parallel Timer Execution", BTParallel::Policy::Require_All, BTParallel::Policy::Require_One)
		.add<BTTimer>("First Timer", BTTimer::Granularity::Milliseconds, BTTimer::Policy::Greater, 100.0)
		.end()
		.add<BTTimer>("Second Timer", BTTimer::Granularity::Milliseconds, BTTimer::Policy::Smaller, 200.0)
		.end()
		.end()
		.build();


	int i = 0;
	BTNodeResult result = BTNodeResult::FAILURE;
	while (tree->update() == BTNodeResult::FAILURE)
	{
		blackboard->set<int>("Time", ++i, "int");
		blackboard->set<BTNodeResult>("Timer Result", result, "bt_node_result");

		cout << "Result: ";

		switch (blackboard->getData<BTNodeResult>("Timer Result"))
		{
		case BTNodeResult::FAILURE:
			cout << "Failure" << endl;
			break;

		case BTNodeResult::SUCCESS:
			cout << "Success" << endl;
			break;

		case BTNodeResult::RUNNING:
			cout << "Running" << endl;
			break;

		case BTNodeResult::INVALID:
			cout << "Invalid" << endl;
			break;

		}

	}

	result = BTNodeResult::SUCCESS;

	blackboard->set<BTNodeResult>("Timer Result", result, "bt_node_result");

	cout << "Result: ";
	switch (blackboard->getData<BTNodeResult>("Timer Result"))
	{
	case BTNodeResult::FAILURE:
		cout << "Failure" << endl;
		break;

	case BTNodeResult::SUCCESS:
		cout << "Success" << endl;
		break;

	case BTNodeResult::RUNNING:
		cout << "Running" << endl;
		break;

	case BTNodeResult::INVALID:
		cout << "Invalid" << endl;
		break;

	}


	delete blackboard;
	delete factory;
	delete tree;
	*/

	delete factory;
	delete blackboard;
	delete tree;
}



int main()
{
	testing_run();


	_CrtCheckMemory();
	_CrtDumpMemoryLeaks();

	return 0;
}