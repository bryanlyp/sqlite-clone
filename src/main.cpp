#include "repl.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    // create repl :)
    Repl repl;
    while (repl.is_expecting_new_input()) {
        repl.print_prompt();
        repl.read_input();
        repl.execute();
        repl.print_output();
    }
    return 0;
}
