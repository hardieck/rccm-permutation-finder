//
// Created by hardieck on 9/27/19.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H



#include <vector>
#include <set>
#include <string>
#include "config_rccm.h"
#include <algorithm>

class evaluate_result : public base_obj
{
public:
	evaluate_result();
	void set_distribution(std::string input);
	std::vector<double> distribution;

	enum enum_eval_type {BEST_DISTRIBUTION, WORST_DISTRIBUTION, MIN_GAB} eval_type;

	double evaluate(std::set<int> input);

	float match;
	config_rccm result;

	std::vector<config_rccm> result_by_coeff_number;

	void print_best_result(bool show_coeff = true, bool show_all_= false);

	double calculate_distribution_match(std::vector<int> &input);

	template <class T>
	std::vector<double> norm_distribution(const std::vector<T> &input) const
	{
		double max = *std::max_element(input.begin(),input.end());
		std::vector<double> r(input.size());
		for(int i=0; i< input.size();++i)
		{
			if(i==0)
			{
				r[i] = 0.000001;
			}
			else
			{
				r[i]=(((double)input[i])/max);
			}
		}
		return r;
	}

	double Kullback_Leibler_Divergenz(std::vector<double> &P_i, std::vector<double> &R_i);
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_RESULT_H
