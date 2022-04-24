
#include "engine/io/serialize.hpp"

#include <iostream>
#include <cassert>


int main() {
    struct Bla {
        int a;
        char b;
        double d;
    };


    Bla bla_var = {.a = 1234, .b = 'X', .d = 1234.1234};

    bool success = Serialize::save_object<Bla>("Bla.bin", bla_var);

    if (success) {
        std::cout << "saved successfully" << std::endl;
    } else {
        std::cout << "couldn't save object" << std::endl;
    }
    assert(success);

    std::optional<Bla> opt_bla_var = Serialize::read_object<Bla>("Bla.bin");

    if (opt_bla_var.has_value()) {
        std::cout << "Bla read from file: \n" <<
                  "\t.a= " << opt_bla_var->a << std::endl <<
                  "\t.b= " << opt_bla_var->b << std::endl <<
                  "\t.d= " << opt_bla_var->d << std::endl;
    } else {
        std::cout << "Optional Bla value read from \"Bla.bin\" has no value!" << std::endl;
    }

    assert(opt_bla_var.has_value());
}