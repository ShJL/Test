//-----------------------------------------------------------------------------
//! @file stack.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a stack class
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
#pragma once
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
//#define NDEBUG
#include <cassert>

//-----------------------------------------------------------------------------
//! @namespace stk
//! There the stack class describes
//-----------------------------------------------------------------------------
namespace stk {

//-----------------------------------------------------------------------------
//! @def ASSERT_VALID()
//! Macro to test object integrity
//! @throw std::exception Stack is not valid
//-----------------------------------------------------------------------------
#define ASSERT_VALID() {\
    if (!is_valid()) {\
        dump();\
        assert(!"Stack is good");\
        throw std::exception();\
    }\
}

    //-----------------------------------------------------------------------------
    //! @class stack_t
    //! @tparam Tp the type of the value in the stack
    //! @tparam stack_size the capacity of the stack (the default value is 10)
    //-----------------------------------------------------------------------------
    template<typename Tp, std::size_t stack_size = 10>
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

            for (const_value_type item : data_) {
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
        //! @return the top item from the stack
        //-----------------------------------------------------------------------------
        value_type top() const {
            ASSERT_VALID();
            return data_[top_];
        }

        //-----------------------------------------------------------------------------
        //! Delete the item from the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @throw std::out_of_range When stack is empty
        //-----------------------------------------------------------------------------
        void pop();

        //-----------------------------------------------------------------------------
        //! Append new item in the stack
        //! @throw std::exception From ASSERT_VALID() when stack is not valid
        //! @throw std::out_of_range When the stack is full
        //-----------------------------------------------------------------------------
        void push(const_value_type& x);

        //-----------------------------------------------------------------------------
        //! Currently size of the stack
        //! @return Count of the item in the stack
        //-----------------------------------------------------------------------------
        size_type size() const {
            return top_;
        }

        //-----------------------------------------------------------------------------
        //! Checks the emptiness of the stack
        //! @return true if stack is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const {
            return !top_;
        }

        //! @private
    private:

        //-----------------------------------------------------------------------------
        //! Constant for mark the empty fields
        //-----------------------------------------------------------------------------
        const_value_type FREE_POISON_ = static_cast<const_value_type>(0);

        value_type data_[stack_size]; //!< Stack base on array
        size_type  top_; //!< Pointer on the top item of the stack

        //-----------------------------------------------------------------------------
        //! Silent verifier
        //! @return True if stack is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const;

        //-----------------------------------------------------------------------------
        //! Dumper
        //! Create file "__stack_dump.txt" where is information about stack's status
        //-----------------------------------------------------------------------------
        void dump() const;

    };

}

#endif // STACK_H
