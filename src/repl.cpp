#include "repl.h"
#include <string>
#include <iostream>

Repl::Repl() {
    this->input_buffer = "";
    this->output_buffer = "";
    this->expecting_new_input = true;
}
void Repl::print_prompt() {
    std::cout << "db > " << std::flush;
}
void Repl::read_input() {
    std::getline(std::cin, this->input_buffer);
    //std::cin >> input_buffer;
}
void Repl::execute() {
    if (this->input_buffer == ".exit") {
        this->expecting_new_input = false;
    } else {
        this->output_buffer = "Unrecognized command.";
    }
}
std::string Repl::get_input_buffer() {
    return this->input_buffer;
}
bool Repl::is_expecting_new_input() {
    return this->expecting_new_input;
}
void Repl::print_output() {
    std::cout << this->output_buffer << std::endl;
    this->output_buffer = "";
}

