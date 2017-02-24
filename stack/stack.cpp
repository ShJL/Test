//-----------------------------------------------------------------------------
//! @file stack.cpp
//! Implementation of functional of the stack class
//!
//! See files:
//!  - stack.h
//!  - stack.cpp
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   2017
//-----------------------------------------------------------------------------
#include "stack.h"
#include <fstream>
#include <ctime>


namespace stk {

    template<typename Tp, std::size_t stack_size>
    void stack_t<Tp, stack_size>::push(const_value_type& x) {
        ASSERT_VALID();

        if (top_ >= stack_size) {
            throw std::out_of_range("*Error: Stack is full*");
        }
        data_[top_++] = x;

        ASSERT_VALID();
    }

    template<typename Tp, std::size_t stack_size>
    void stack_t<Tp, stack_size>::pop() {
        ASSERT_VALID();

        if (!top_) {
            throw std::out_of_range("*Error: Stack is empty*");
        }
        data_[top_--] = FREE_POISON_;

        ASSERT_VALID();
    }

    template<typename Tp, std::size_t stack_size>
    bool stack_t<Tp, stack_size>::is_valid() const {

        if (top_ <= stack_size) {
            for (size_type i = top_; i < stack_size; ++i) {
                if (data_[i] != FREE_POISON_) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    template<typename Tp, std::size_t stack_size>
    void stack_t<Tp, stack_size>::dump() const {

        std::ofstream fout("__stack_dump.txt", std::ios_base::out | std::ios_base::app);

        if (fout.is_open()) {

            fout << "\nClass stack_t:\n"
                    "time: "         << ctime(time(nullptr)) << "\n"
                    "satus: "        << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tstack_size: " << stack_size           << "\n"
                    "\ttop: "        << top_                 << "\n";

            for (size_type i = 0; i < stack_size; ++i) {
                fout << (i < top_ ? "\t* [" : "\t  [") << i << "]"
                     << " = " << data_[i]
                     << (i >= top_ && data_[i] != FREE_POISON_ ? "  //ERROR!\n" : "\n");
            }

        }
    }
}


