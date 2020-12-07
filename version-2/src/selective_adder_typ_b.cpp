//
// Created by hardieck on 10/8/19.
//

#include "../inc/selective_adder_typ_b.h"

std::set<int> selective_adder_typ_b::compute()
{
	//00  A1 +B1
	//01  A1 +B2
	//02  A1 -B1
	//03  A1 -B2
	//04 -A1 +B1
	//05 -A1 +B2
	//06 -A1 -B1
	//07 -A1 -B2
	//08  A2 +B1
	//09  A2 +B2
	//10  A2 -B1
	//11  A2 -B2
	//12 -A2 +B1
	//13 -A2 +B2
	//14 -A2 -B1
	//15 -A2 -B2

	std::set<int> result;

	for (int conf: this->convfg->get_operation_set())
	{
		std::set<int> &A1 = inputs[1];
		std::set<int> &A2 = inputs[2];
		std::set<int> &A3 = inputs[3];
		std::set<int> &B1 = inputs[4];
		std::set<int> &B2 = inputs[5];

		//00  A1 +B1
		//01  A2 +B1
		//02  A3 +B1
		//03 -A1 +B1
		//04 -A2 +B1
		//05 -A3 +B1
		//06     +B1


		output.clear();

		for (int conf:this->convfg->get_operation_set())
		{
			switch (conf)
			{
				case 0:
					for (int a:A1) { for (int b:B1) { output.insert(a + b); }}
					break;
				case 1:
					for (int a:A2) { for (int b:B1) { output.insert(a + b); }}
					break;
				case 2:
					for (int a:A3) { for (int b:B1) { output.insert(a + b); }}
					break;
				case 3:
					for (int a:A1) { for (int b:B1) { output.insert(-a + b); }}
					break;
				case 4:
					for (int a:A2) { for (int b:B1) { output.insert(-a + b); }}
					break;
				case 5:
					for (int a:A3) { for (int b:B1) { output.insert(-a + b); }}
					break;
				case 6:
					for (int b:B1) { output.insert(b); }
					break;
			}
		}
		return output;
	}
}
