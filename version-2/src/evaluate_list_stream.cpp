//
// Created by hardieck on 2/1/22.
//

#include "../inc/evaluate_list_stream.h"


evaluate_list_stream::evaluate_list_stream() {
    use_metric = false;
    metric = nullptr;

    evalcnt = 1;
}

evaluate_list_stream::~evaluate_list_stream() {
}

double evaluate_list_stream::evaluate(const string &config,const std::set<int> &inputs) {
    IF_VERBOSE(5) ENTER_FUNCTION("evaluate_count::evaluate(const string &config,const std::set<int> &inputs)")

    double score = 0;	     

    if (use_metric) {
      score = metric->evaluate(config,inputs);
    }

    if (evalcnt == 1) {
      // first result, so print header before actual result
      std::cout << std::endl << "Results from metric " << metric_index << ":" << std::endl;
      std::cout << "Directly prints all found sets as they come in a streaming fashion" << std::endl;
      std::cout << "Nr\tScore\tConfig\tCoefficient Set" << std::endl;
      std::cout << "------------------------------------" << std::endl;
    }

    std::cout << evalcnt << "\t" << score << "\t" << config << "\t" << inputs << std::endl;
    evalcnt++;

    return score;
}


std::stringstream evaluate_list_stream::print_result(bool ss)
{
  std::stringstream os;
  // note that as streaming evaluation this already printed its
  // result during operation, so the only thing left to do here
  // is to print the footer
  IF_VERBOSE(5) ENTER_FUNCTION("void evaluate_count::print_result()")
  std::cout << "------------------------------------" << std::endl;
  IF_VERBOSE(5) LEAVE_FUNCTION("void evaluate_count::print_result()")
    return os;
}

