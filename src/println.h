#ifndef PRINTLN_H
#define PRINTLN_H

#include <iostream>

namespace shj {

    const char ESCAPE_SYMBOL       = '~';
    const char CHECK_SYMBOL_FIRST  = '{';
    const char CHECK_SYMBOL_SECOND = '}';

    void println(const char* line) {
        const char* str = line;
        bool is_escape  = false;

        while (*str) {
            if (is_escape || *str != ESCAPE_SYMBOL) {
                std::cout << *str;
                is_escape = false;
            }
            else {
                is_escape = true;
            }

            ++str;
        }
    }

    template<typename Tp, typename... Types>
    void println(const char* line, Tp value, Types... args) {
        const char* str = line;
        bool is_escape  = false;

        while (*str) {

            if (!is_escape) {
                if (*str == ESCAPE_SYMBOL) {
                    is_escape = true;
                    ++str;
                    continue;
                }

                if (*str == CHECK_SYMBOL_FIRST &&
                        *(str + 1) == CHECK_SYMBOL_SECOND) {

                    std::cout << value;
                    println(str + 2, args...);
                    break;
                }
            }

            std::cout << *str++;

            is_escape = false;
        }
    }
}

#endif // PRINTLN_H
