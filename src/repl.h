#ifndef REPL_H
#define REPL_H
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include "table.h"

class Repl {
    private:
        std::string input_buffer;
        std::string output_buffer;
        bool is_expecting_new_input;
        Table table;

        void print_prompt();
        void read_input();
        void execute();
        std::string get_input_buffer();
        void print_output();
        void do_meta_command();
        void parse_command();
        char* serialize_input();
    public:
        Repl();
        void init();
};

class UnrecognizedCommandException : public std::runtime_error {
    private:
    public:
        UnrecognizedCommandException(const std::string &error);
};

#endif
