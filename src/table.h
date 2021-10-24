#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <sstream>
class Record {
    private:
        char* byte_array;
    public:
        Record(char* byte_array);
        //unsigned int get_id();
        Record();
};

class Table {
    private:
        std::string name;
        std::string schema;
        std::vector<int> column_sizes;
        Record* table_data;
        unsigned int num_rows;
        unsigned int capacity;
    public:
        Table(const std::string& name, const std::string& schema);
        Table();
        void insert(const std::string& args);
        void print_all(void);
        std::string get_schema();
        std::string get_name();
};


#endif
