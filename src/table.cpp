#include "table.h"

Record::Record(char* byte_array) {
    //this->byte_array = new char[256+32+4];
    this->byte_array = byte_array;
    //serialize
    //memcpy(this->byte_array, &id, sizeof (unsigned int));
    //memcpy((this->byte_array) + sizeof(unsigned int), &name, 32*sizeof(char));
    //memcpy((this->byte_array) + sizeof(unsigned int) + 32*sizeof(char), &id, 256*sizeof(char));

}

Record::Record() {

}
Table::Table() {
    this->capacity = 256;
    this->num_rows = 0;
    this->table_data = new Record[256];
}

Table::Table(const std::string& name, const std::string& schema) {
    this->name = name;
    this->schema = schema;
    this->capacity = 256;
    this->num_rows = 0;
    this->table_data = new Record[256];
    std::stringstream ss(this->schema);
    std::string token;
    while (ss >> token) {
        if (token == "int") {
            column_sizes.push_back(4);
        } else if (token.find("varchar")!=std::string::npos) {
            column_sizes.push_back(std::stoi(token.substr(8, token.size()-1)));
        }
    }

}

std::string Table::get_name() {
    return this->name;
}

std::string Table::get_schema() {
    return this->schema;
}

void Table::insert(const std::string& args) {
    unsigned int N = 0;
    for (auto column_size:column_sizes) {
        N += column_size;
    }
    char serialized[N];
    std::stringstream args_ss(args);
    std::stringstream schema_ss(this->schema);
    std::string arg_tkn;
    std::string schema_tkn;
    int offset = 0;
    for (auto column_size:column_sizes) {
        args_ss >> arg_tkn;
        schema_ss >> schema_tkn;
        if (schema_tkn == "int") {
            int val = std::stoi(arg_tkn);
            memcpy(serialized+offset, &val, column_size);
        } else {
            const char* char_arr = arg_tkn.c_str();
            memcpy(serialized+offset, char_arr, column_size);
        }
        offset+=column_size;
    }
    Record row(serialized);
    this->table_data[num_rows] = row;
    num_rows++;
    return;
}

void Table::print_all(void) {

}
