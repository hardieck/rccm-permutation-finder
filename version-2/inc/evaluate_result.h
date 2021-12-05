//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H



#include <vector>
#include <set>
#include <string>
#include "rccm.h"
#include <algorithm>


//TODO: make results mergable... so that only parts of search space can be done seperatly (for Example in multiple threads) to fuse them together again
// make a result class to handle...
class evaluate_result : public base_obj
{
public:
	evaluate_result();
	void set_distribution(std::string inputs);
	std::vector<double> distribution;

	enum enum_eval_type {BEST_DISTRIBUTION, WORST_DISTRIBUTION, MIN_GAB} eval_type; // TODO make seperate Classes...

	double evaluate(std::set<int> inputs);

	//float match;
	//rccm result;

	//std::vector<rccm> result_by_coeff_number;

	void print_best_result(bool show_coeff = true, bool show_all_= false);

	double calculate_distribution_match(std::vector<int> &inputs);

	template <class T>
	std::vector<double> norm_distribution(const std::vector<T> &inputs) const
	{
		double max = *std::max_element(inputs.begin(),inputs.end());
		std::vector<double> r(inputs.size());
		for(int i=0; i< inputs.size();++i)
		{
			if(i==0)
			{
				r[i] = 0.000001;
			}
			else
			{
				r[i]=(((double)inputs[i])/max);
			}
		}
		return r;
	}

	double Kullback_Leibler_Divergenz(std::vector<double> &P_i, std::vector<double> &R_i);
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H
