//-----------------------------------------------------------------------------
//! @file stack.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a stack class
//!
//!
//! @version 2.2
//!
//! @author ShJ
//! @date   25.02.2017
//-----------------------------------------------------------------------------
#pragma once
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
//#define NDEBUG
#include <cassert>
#include <fstream>
#include <ctime>

//-----------------------------------------------------------------------------
//! @namespace stk
//! @brief There the stack class describes
//-----------------------------------------------------------------------------
namespace stk {

//-----------------------------------------------------------------------------
//! @def ASSERT_VALID()
//! Macro to test object integrity
//! @throw std::exception Stack is not valid
//-----------------------------------------------------------------------------
#define ASSERT_VALID() {\
    if (!is_valid()) {\
        dump(__PRETTY_FUNCTION__);\
        assert(!"Stack is good");\
        throw std::exception();\
    }\
}

    //-----------------------------------------------------------------------------
    //! @class stack_t
    //! @tparam Tp The type of the value in the stack (the default type is int)
    //! @tparam stack_size The capacity of the stack (the default value is 10)
    //-----------------------------------------------------------------------------
    template<typename Tp = int, std::size_t stack_size = 10>
    class stack_t {
    public:

        using value_type       = Tp;          //!< Element type
        using const_value_type = const Tp;    //!< Const element type
        using size_type        = std::size_t; //!< Size type

        //-----------------------------------------------------------------------------
        //! Default constructor
        //! Fill all elements FREE_POISON_
        //-----------------------------------------------------------------------------
        stack_t() :
            top_(0) {

            for (value_type& item : data_) {
                item = FREE_POISON_;
            }
        }

        //-----------------------------------------------------------------------------
        //! Default the copy constructor
        //-----------------------------------------------------------------------------
        stack_t(const stack_t&) = default;

        //-----------------------------------------------------------------------------
        //! Default the assignment operator
        //-----------------------------------------------------------------------------
        stack_t& operator=(const stack_t&) = default;

        //-----------------------------------------------------------------------------
        //! Default destructor
        //-----------------------------------------------------------------------------
        ~stack_t() = default;

        //-----------------------------------------------------------------------------
        //! Get the item from the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @return The top item from the stack
        //-----------------------------------------------------------------------------
        value_type top() const;

        //-----------------------------------------------------------------------------
        //! Delete the item from the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @throw std::out_of_range When stack is empty
        //-----------------------------------------------------------------------------
        void pop();

        //-----------------------------------------------------------------------------
        //! Append new item in the stack
        //! @param x The element that will be added to the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @throw std::out_of_range When the stack is full
        //-----------------------------------------------------------------------------
        void push(const_value_type& x);

        //-----------------------------------------------------------------------------
        //! Currently size of the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @return Count of the item in the stack
        //-----------------------------------------------------------------------------
        size_type size() const {
            ASSERT_VALID();
            return top_;
        }

        //-----------------------------------------------------------------------------
        //! Capacity
        //! @return Capacity of the stack
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            return stack_size;
        }

        //-----------------------------------------------------------------------------
        //! Checks the emptiness of the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @return True if stack is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const {
            ASSERT_VALID();
            return !top_;
        }

        //-----------------------------------------------------------------------------
        //! Checks the stack overflow
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @return True if stack is full, otherwise false
        //-----------------------------------------------------------------------------
        bool full() const {
            ASSERT_VALID();
            return top_ == stack_size;
        }

    private:

        //-----------------------------------------------------------------------------
        //! Constant for mark the empty fields
        //-----------------------------------------------------------------------------
        const_value_type FREE_POISON_ = static_cast<const_value_type>(0);

        value_type data_[stack_size]; //!< Stack base on array
        size_type  top_;              //!< Pointer on the top item of the stack

        //-----------------------------------------------------------------------------
        //! Silent verifier
        //! @return True if stack is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const;

        //-----------------------------------------------------------------------------
        //! Dumper
        //! Create file "__stack_dump.txt" where is information about stack's status
        //! @param function_name Name of function which call this method
        //-----------------------------------------------------------------------------
        void dump(const char* function_name) const;

    };


    template<typename Tp, std::size_t stack_size>
    Tp stack_t<Tp, stack_size>::top() const {
        ASSERT_VALID();

        if (!top_) {
            throw std::out_of_range("*Error: Stack is empty*");
        }

        return data_[top_ - 1];
    }

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
        data_[--top_] = FREE_POISON_;

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
    void stack_t<Tp, stack_size>::dump(const char* function_name) const {
        std::ofstream fout("__stack_dump.txt", std::ios_base::app);

        if (fout.is_open()) {
            const time_t time_info = time(nullptr);

            fout << "******************\n"
                    "Class stack_t:\n"
                    "time: "         << ctime(&time_info) <<
                    "function: "     << function_name     << "\n"
                    "satus: "        << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tstack_size: " << stack_size        << "\n"
                    "\ttop: "        << top_              << "\n\n";

            for (size_type i = 0; i < stack_size; ++i) {
                fout << (i < top_ ? "\t* [" : "\t  [") << i << "]"
                     << " = " << data_[i]
                     << (i >= top_ && data_[i] != FREE_POISON_ ? "  //ERROR!\n" : "\n");
            }

            fout << "}\n";

            fout.close();
        }
    }

}

#endif // STACK_H
