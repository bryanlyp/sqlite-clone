#ifndef REPL_H
#define REPL_H
#include <stdexcept>
#include <string>
#include <iostream>


class Repl {
    private:
        std::string input_buffer;
        std::string output_buffer;
        bool is_expecting_new_input;

        void print_prompt();
        void read_input();
        void execute();
        std::string get_input_buffer();
        void print_output();
        void do_meta_command();
        void prepare_statement();

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
