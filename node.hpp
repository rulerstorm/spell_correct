//
//  node.hpp
//  dsf
//
//  Created by Ruler on 14-8-10.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef dsf_node_hpp
#define dsf_node_hpp

#include <iostream>

class Node{             //为了优先级队列定义……
public:
    std::string str_;
    long dis_;
    uint32_t occur_;
    
    Node(const std::string & str,
         long dis,
         uint32_t occur)
    :str_(str), dis_(dis), occur_(occur)
    {}
    
    bool operator<(const Node & other) const{
        if (dis_ == other.dis_) {
            return occur_ < other.occur_;
        }
        return dis_ > other.dis_;
    }
    
    void debug(){
        std::cout << str_ << "  dis: " << dis_ << "  ocr: " << occur_ << std::endl;
    }
};

#endif
