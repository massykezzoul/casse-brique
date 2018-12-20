#include <iostream>
#include "../option/option.h"

int main(int argc, char const *argv[]) {
    /* Declaration du tableau d'option */
    Option_tab mes_option;
    if (argc == 1) {
        std::cout << "donné des arguments pour testé :) " << std::endl;
        exit(1);
    }
    //mes_option.print();

    std::cout << "------------" << std::endl;
    mes_option.gere_parametre(argc,argv);

    return 0;
}

/* 
Compilation : 
    g++ option-test.cpp option.cpp -Wall -pedantic -o test
 */