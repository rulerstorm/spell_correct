//
//  wordslib.hpp
//  dsf
//
//  Created by Ruler on 14-8-9.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef dsf_wordslib_hpp
#define dsf_wordslib_hpp

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <map>


class WordsLib
{
private:
    std::map<std::string, uint32_t> words_;
    std::ifstream file_;
    std::map<std::string, uint32_t> index_[26];
    
    void input_words_();
    void map_to_index_();
    void trim_(std::string & word);
    void add_to_index_(const std::pair<std::string, uint32_t> & word);
    
public:
    WordsLib(const std::string & filepath){
        file_.open(filepath.c_str());
        input_words_();
        map_to_index_();
        file_.close();
    }
    
    const std::map<std::string, uint32_t> & get_map(){
        return words_;
    }
    const std::map<std::string, uint32_t> & get_index(char ch){
        return index_[ch-97];
    }
    
//    void debug(char ch){
//        for (auto & item : index_[ch - 97]){
//            std::cout << item.first << " " << item.second << std::endl;
//        }
//    }
};



inline void WordsLib::input_words_()
{
    std::string temp_word;
    
    while(file_ >> temp_word){
        trim_(temp_word);
        if (temp_word.length() == 0) continue;
        ++words_[temp_word];
    }
}

inline void WordsLib::trim_(std::string & word)
{
    for (auto it = word.begin(); it != word.end(); ++it){
        if (isupper(*it))
            *it += 32;
        if (!isalpha(*it))
            it = word.erase(it) - 1;    //对于迭代器的失效一定要重视！
    }
}



inline void WordsLib::add_to_index_(const std::pair<std::string, uint32_t> & word)
{
    for (auto it = word.first.begin(); it != word.first.end(); ++it){
        index_[*it - 97].insert(word);
    }
}


inline void WordsLib::map_to_index_()
{
    for (auto & word : words_){
        add_to_index_(word);
    }
}

#endif
