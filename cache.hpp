//
//  cache.hpp
//  dsf
//
//  Created by Ruler on 14-8-9.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef dsf_cache_hpp
#define dsf_cache_hpp

#include <map>
#include <set>

class Cache
{
private:
    std::map<std::string, std::set<std::string> > map_;     //需要加入容量限制吗？
    
public:
    void add_to_cache(const std::string & word1, const std::string & word2){
        auto it = map_.find(word1);
        if (it != map_.end()) {
            it->second.insert(word2);
        }
        else {
            std::set<std::string> temp_set;
            temp_set.insert(word2);
            map_.insert(make_pair(word1, temp_set));
        }
    }
    
    const std::map<std::string, std::set<std::string>> & get_cache(){
        return map_;
    }
    
    void update_from_disk();
    void save_to_disk();
};




#endif
