#ifndef REPL_H
#define REPL_H

#include <string>

class Repl {
    private:
        std::string input_buffer;
        std::string output_buffer;
        bool expecting_new_input;
    public:
        Repl();
        void print_prompt();
        void read_input();
        void execute();
        std::string get_input_buffer();
        bool is_expecting_new_input();
        void print_output();
};

#endif
