#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <sstream>
#include <iostream>

class Table {
    private:
        std::string name;
        std::vector<std::string> schema;
        //std::vector<int> column_sizes;
        
        static const unsigned int MAX_PAGE_NUM = 100;
        static const unsigned int MAX_PAGE_BYTES = 4096;
        std::vector<unsigned int> offset_vec;
        
        unsigned int RECORD_SIZE;
        unsigned int page_idx;
        unsigned int record_idx;

        char pages[MAX_PAGE_NUM][MAX_PAGE_BYTES];
        //char* serialize(const std::vector<std::string>& args);
    public:
        Table(const std::string& name, const std::vector<std::string>& schema);
        Table();
        void insert(const std::vector<std::string>& args);
        std::string select(const std::vector<std::string>& args);
        std::vector<std::string> get_schema();
        std::string get_name();
};


#endif
