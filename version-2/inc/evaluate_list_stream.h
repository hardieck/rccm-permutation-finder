//
// Created by hardieck on 2/1/22.
//

#ifndef ADDNET_PERMUTATOR_V2_EVALUATE_LIST_STREAM_H
#define ADDNET_PERMUTATOR_V2_EVALUATE_LIST_STREAM_H

#include "evaluate_base.h"

class evaluate_list_stream : public evaluate_base
{
public:
    evaluate_list_stream();
    virtual ~evaluate_list_stream();

    double evaluate(const string &config,const std::set<int> &inputs) override;
    std::stringstream print_result(bool ss=false) override;

    virtual bool streaming() override {
      return true;
    }

private:
    unsigned long evalcnt;
};


#endif //ADDNET_PERMUTATOR_V2_EVALUATE_LIST_STREAM_H
