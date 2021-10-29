#include "table.h"

std::vector<std::string> Table::get_schema() {
    return this->schema;
}

std::string Table::get_name() {
    return this->name;
}

Table::Table() {

}

Table::Table(const std::string& name, const std::vector<std::string>& schema) {
    this->name = name;
    this->schema = schema;
    unsigned int N = 0;
    for (int i = 0; i < schema.size(); i++) {
        std::cout << schema[i] << std::endl;
        if (schema[i] == "int") {
            this->offset_vec.push_back(sizeof(int));
            N += sizeof(int);
        } else if (schema[i].find("varchar" == 0)) {
            std::string str = schema[i].substr(8, schema[i].size());
            this->offset_vec.push_back(sizeof(char)*std::stoi(str));
            N += sizeof(char) * std::stoi(str);
        }
    }

    record_idx = 0;
    page_idx = 0;

    this->RECORD_SIZE = N;
}

void Table::insert(const std::vector<std::string>& args) {
    assert(args.size() == schema.size() + 1);
    unsigned int offset = 0;
    char row[RECORD_SIZE];
    for (int i = 0; i < schema.size(); i++) {
        if (schema[i] == "int") {
            int val = std::stoi(args[i+1]);
            std::memcpy(row+offset, &val, offset_vec[i]); 
        } else if (schema[i].find("varchar" == 0)) {
            const char* str = args[i+1].c_str();
            std::memcpy(row+offset, str, offset_vec[i]);
        }
        offset += offset_vec[i];
    }
    if ((record_idx + 1) * RECORD_SIZE > MAX_PAGE_BYTES) {
        record_idx = 0;
        page_idx++;
    }
    if (page_idx >= MAX_PAGE_NUM) return;
    std::memcpy(pages[page_idx]+(record_idx*RECORD_SIZE), row, RECORD_SIZE);
    record_idx++;
}

std::string Table::select(const std::vector<std::string>& args) {
    std::string out = "";
    for (int i = 0; i <= page_idx; i++) {
        unsigned int max_record_idx;
        if (i < page_idx) {
            max_record_idx = (MAX_PAGE_BYTES / RECORD_SIZE) + 1;
        } else {
            max_record_idx = record_idx;
        }
        for (int j = 0; j < max_record_idx; j++) {
            unsigned int offset = j*RECORD_SIZE;
            for (int k = 0; k < schema.size(); k++) {
                if (schema[k] == "int") {
                    int* val;
                    std::memcpy(val,pages[i]+offset,offset_vec[k]); 
                    out += std::to_string(*val);
                } else if (schema[k].find("varchar" == 0)) {
                    char byte_str[offset_vec[k]+1];
                    std::memcpy(byte_str,pages[i]+offset,offset_vec[k]);
                    byte_str[offset_vec[k]] = 0;
                    out += std::string(byte_str);
                }
                out += " ";
                offset += offset_vec[k];
            }
            out += "\n";
        }
    }
    return out;
}




