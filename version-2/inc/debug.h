//
// Created by hardieck on 12/7/20.
//

#ifndef ADDNET_PERMUTATOR_V2_DEBUG_H
#define ADDNET_PERMUTATOR_V2_DEBUG_H

#endif //ADDNET_PERMUTATOR_V2_DEBUG_H


extern int global_verbose;

#define IF_VERBOSE(verbose) if(global_verbose >= verbose) for(int i=0; i < verbose; i++) cout << "  "; if(global_verbose >= verbose)