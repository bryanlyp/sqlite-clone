#include "repl.h"

Repl::Repl() {
    this->input_buffer = "";
    this->output_buffer = "";
    this->is_expecting_new_input = true;
}

void Repl::print_prompt() {
    std::cout << "db > " << std::flush;
}
void Repl::read_input() {
    std::getline(std::cin, this->input_buffer);
}
void Repl::execute() {
    //char meta_command_indicator = ".";
    try {
        if (this->input_buffer[0] == '.') {
            this->do_meta_command();
        } else {
            this->parse_command();
        }
    } catch (const UnrecognizedCommandException &exception) {
        std::cerr << exception.what() << std::endl;
    }
}
void Repl::do_meta_command() {
    if (this->input_buffer == ".exit") {
        this->is_expecting_new_input = false;
    } else {
        throw UnrecognizedCommandException("Unrecognized meta command \"" + this->input_buffer + "\"");
    }
}

std::vector<std::string> Repl::tokenize(const std::string str) {
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void Repl::parse_command() {
    std::vector<std::string> args = tokenize(this->input_buffer);
    if (args[0] == "select") {
        this->output_buffer = table.select(args);
    } else if (args[0] == "insert") {
        this->table.insert(args);
    } else if (args[0] == "create") {
        this->table = Table(args[2], tokenize("int varchar(32) varchar(256)"));
    } else {
        throw UnrecognizedCommandException("Unrecognized command \"" + this->input_buffer + "\"");
    }
}

std::string Repl::get_input_buffer() {
    return this->input_buffer;
}

void Repl::print_output() {
    std::cout << this->output_buffer << std::endl;
    this->output_buffer = "";
}

void Repl::init() {
    while (this->is_expecting_new_input) {
        this->print_prompt();
        this->read_input();
        this->execute();
        this->print_output();
    }
}

UnrecognizedCommandException::UnrecognizedCommandException(const std::string &error) : std::runtime_error(error.c_str()) {

}
