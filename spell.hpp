//
//  spell.hpp
//  dsf
//
//  Created by Ruler on 14-8-10.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef dsf_spell_hpp
#define dsf_spell_hpp

#include <fstream>
#include "wordslib.hpp"
#include "cache.hpp"
#include "caculate.h"
#include "node.hpp"

#include <cstdlib>
#include <set>
#include <queue>



class SpellCorrect{
private:
    WordsLib lib_;
    Cache cache_;
    uint32_t pv_;           //编辑距离超过这个值直接抛弃
    int topnumber_;         //推荐几个
    
    std::set<std::string> answer_set_;       //为了下面得correct在无结果时能顺利返回，还有别的方法吗？？
    void correct(const std::string & query);

    
public:
    SpellCorrect(const std::string & filepath)
    :pv_(1), lib_(filepath), topnumber_(10) {}
    
    void set_pv(uint32_t num){ pv_ = num;}
    
    void begin_query(){
        std::string temp_string;
        while (std::cin >> temp_string) {
            correct(temp_string);
            for (auto & item : answer_set_ ){
                std::cout << item << std::endl;
            }
        }
    }
    
    
};


//这函数复杂得不行，需要重构！！
inline void SpellCorrect::correct(const std::string & query)
{
    std::priority_queue<Node> que_;                 //放在里面方便每次清空
    answer_set_.clear();
    
    auto it_cache = cache_.get_cache().find(query);      //这段我不造怎么写到cache里面，查不到返回啥？
    if (it_cache != cache_.get_cache().end())
        answer_set_ = it_cache->second;
    
    for (auto it = query.begin(); it != query.end(); ++it) {
        if (!isalpha(*it))
            continue;
        for (auto & element: lib_.get_index(*it)){
            if (labs(element.first.length() - query.length()) > pv_+1)  //长度差比最大编辑距离还大，抛弃
                continue;
            memset(memo, 0, sizeof(memo));
            long dis = min_destance(element.first.c_str(),
                                    element.first.length()-1,
                                    query.c_str(),
                                    query.length()-1);
            if (dis > pv_)
                continue;
            Node temp_node(element.first,
                           dis,
                           element.second);
            que_.push(temp_node);
        }
    }
    
    if (que_.size() == 0){      //防止无结果
        answer_set_.insert("no answer!!!");
        return;                      //本来要return一个set，怎么搞？
    }
    
    
    size_t min = topnumber_ < que_.size() ? topnumber_ : que_.size(); //防止que里面元素不够多
    for (int i = 0 ;i < min; ++i){
        cache_.add_to_cache(query, que_.top().str_);
        que_.pop();
    }
    
    it_cache = cache_.get_cache().find(query);
    answer_set_.insert(it_cache->second.begin(), it_cache->second.end());  //怎么用set对set复制？
}


#endif
