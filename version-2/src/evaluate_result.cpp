////
//// Created by hardieck on 9/27/19.
////
//
//#include "../inc/evaluate_result.h"
//#include <math.h>
//#include <algorithm>
//#include <iostream>
//
//
//evaluate_result::evaluate_result()
//{
//	this->distribution.clear();
//	result_by_coeff_number.clear();
//	eval_type = BEST_DISTRIBUTION;
//	match = -1;
//
//}
//
//void evaluate_result::print_best_result(bool show_coeff, bool show_all_)
//{
//
//}
//
//double evaluate_result::evaluate(std::set<int> input)
//{
//	switch(this->eval_type)
//	{
//		case BEST_DISTRIBUTION:
//		{
//			std::vector<int> input_vec;
//			input_vec.assign(input.begin(), input.end());
//			return calculate_distribution_match(input_vec);
//			break;
//		}
//		case WORST_DISTRIBUTION:
//		{
//			std::vector<int> input_vec;
//			input_vec.assign(input.begin(), input.end());
//			return 1-calculate_distribution_match(input_vec);
//			break;
//		}
//		case MIN_GAB:
//		{
//			return 0;
//			break;
//		}
//
//		default: std::cout << "!!!ERROR FROM: evaluate_result::evalueate: Evaluation Type is not suportet!" << std::endl; exit(-1);
//
//	}
//	return -1;
//}
//
//void evaluate_result::set_distribution(std::string input)
//{
//	// do needed stuff....
//}
//
//double evaluate_result::calculate_distribution_match(std::vector<int> &input)
//{
//	std::vector<double> norm_set = this->norm_distribution(input);
//	this->Kullback_Leibler_Divergenz(norm_set,this->distribution);
//	return 0;
//	return 0;
//}
//
//double evaluate_result::Kullback_Leibler_Divergenz(std::vector<double> &P_i, std::vector<double> &R_i)
//{
//	std::vector<double> R = norm_distribution(R_i);
//	std::vector<double> P = norm_distribution(P_i);
//
//
//	double result=0;
//	if(P.size() != R.size())
//	{
//		std::cout << "ERROR: in Kullback_Leibler_Divergenz: P Must have size of Q!" << std::endl;
//		std::cout << "size of Q: " << R.size() << std::endl;
//		std::cout << "size of P: " << P.size() << std::endl;
//		exit(-1);
//	}
//
//	for(int i=0; i< R.size(); ++i)
//	{
//		double p= P[i];
//		double r= R[i];
//
//		result = result+(p*log10(p/r));
//	}
//
//	return result;
//
//}
//
//
