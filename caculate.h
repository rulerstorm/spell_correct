//
//  caculate.hpp
//  dsf
//
//  Created by Ruler on 14-8-10.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef dsf_caculate_hpp
#define dsf_caculate_hpp


long memo[128][128] = {0};

inline long min_destance(const char * str,
                        long index_str,              //填入最大下标
                        const char * target,
                        long index_target)
{
    if (index_target < 0)  return index_str + 1;
    if (index_str < 0) return index_target + 1;
    
    if (0 != memo[index_str][index_target]) return memo[index_str][index_target];
    
    if (str[index_str] == target[index_target])
        return min_destance(str, index_str-1, target, index_target-1);
    
    long cand1 = min_destance(str, index_str, target, index_target-1) + 1;
    long cand2 = min_destance(str, index_str-1, target, index_target) + 1;
    long cand3 = min_destance(str, index_str-1, target, index_target-1) + 1;
    
    long min = (cand1<cand2) ? (cand1<cand3 ? cand1 : cand3) :
    (cand2<cand3 ? cand2 : cand3) ;
    
    memo[index_str][index_target] = min;
    
    return min;
}

#endif
