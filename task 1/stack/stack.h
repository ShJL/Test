//-----------------------------------------------------------------------------
//! @file stack.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a stack class
//!
//!
//! @version 3.0
//!
//! @author ShJ
//! @date   27.02.2017
//-----------------------------------------------------------------------------
#pragma once
#ifndef STK_STACK_H
#define STK_STACK_H

#include <stdexcept>
//#define NDEBUG
#include <cassert>
#include <fstream>
#include <ctime>
#include <algorithm>

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
    //-----------------------------------------------------------------------------
    template<typename Tp = int>
    class stack_t {
    public:

        using value_type       = Tp;          //!< Element type
        using const_value_type = const Tp;    //!< Const element type
        using size_type        = std::size_t; //!< Size type

        //-----------------------------------------------------------------------------
        //! Default constructor
        //-----------------------------------------------------------------------------
        stack_t() :
            top_     (0u),
            capacity_(0u),
            data_    (nullptr)
        { }

        //-----------------------------------------------------------------------------
        //! Constructor
        //! Reserve memory to n elements
        //! @param n The number of elements for which memory is allocated
        //-----------------------------------------------------------------------------
        explicit stack_t(const size_type n);

        //-----------------------------------------------------------------------------
        //! The copy constructor
        //! @param stack The copy source
        //-----------------------------------------------------------------------------
        stack_t(const stack_t& stack);

        //-----------------------------------------------------------------------------
        //! The assignment operator
        //! @param stack The source of the assignment
        //! @return Reference to the calling object
        //-----------------------------------------------------------------------------
        stack_t& operator=(const stack_t& stack);

        //-----------------------------------------------------------------------------
        //! Destructor
        //! Removes allocated memory
        //-----------------------------------------------------------------------------
        ~stack_t() {
            delete[] data_;
        }

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
        //! @throw std::bad_alloc When the memory is not allocated
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
        //! Capacity
        //! @return Capacity of the stack
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            return capacity_;
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
        //! Reserve a memory
        //! @param n The number of elements for which memory is allocated
        //! @return True if memory allocated, otherwise false
        //-----------------------------------------------------------------------------
        bool reserve(const size_type n);

    private:

        //-----------------------------------------------------------------------------
        //! Constant for mark the empty fields
        //-----------------------------------------------------------------------------
        const_value_type FREE_POISON_ = value_type();

        //-----------------------------------------------------------------------------
        //! Constant memory increase
        //-----------------------------------------------------------------------------
        const size_type MEMORY_MULTIPLIER_ = 2u;

        size_type  top_;      //!< Pointer on the top item of the stack
        size_type  capacity_; //!< Capacity of the stack
        value_type *data_;    //!< Stack base on dynamic array

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


    template<typename Tp>
    stack_t<Tp>::stack_t(const size_type n) :
        top_     (0u),
        capacity_(n) {

        if (capacity_) {
            try {
                data_ = new value_type[capacity_];
            }
            catch (std::bad_alloc) {
                data_ = nullptr;
                capacity_ = 0;
                return;
            }

            std::fill(data_, data_ + capacity_, FREE_POISON_);
        }
        else {
            data_ = nullptr;
            capacity_ = 0;
        }
    }

    template<typename Tp>
    stack_t<Tp>::stack_t(const stack_t<Tp>& stack) :
        top_     (stack.top_),
        capacity_(stack.top_) {

        if (capacity_) {
            try {
                data_ = new value_type[capacity_];
            }
            catch (std::bad_alloc) {
                data_ = nullptr;
                top_ = capacity_ = 0;
                return;
            }

            std::copy(stack.data_, stack.data_ + stack.top_, data_);
            std::fill(stack.data_ + stack.top_, stack.data_ + stack.capacity_, FREE_POISON_);
        }
        else {
            data_ = nullptr;
            top_ = capacity_ = 0;
        }
    }

    template<typename Tp>
    stack_t<Tp>& stack_t<Tp>::operator=(const stack_t& stack) {
        stack_t<value_type> tmp_stack(stack);

        std::swap(tmp_stack.data_, data_);
        capacity_ = tmp_stack.capacity_;
        top_ = tmp_stack.top_;

        return *this;
    }

    template<typename Tp>
    Tp stack_t<Tp>::top() const {
        ASSERT_VALID();

        if (!top_) {
            throw std::out_of_range("*Error: Stack is empty*");
        }

        return data_[top_ - 1];
    }

    template<typename Tp>
    void stack_t<Tp>::push(const_value_type& x) {
        ASSERT_VALID();

        try {
            if (top_ >= capacity_ && !reserve(capacity_ + 1)) {
                throw std::bad_alloc();
            }
        }
        catch (...) {
            throw;
        }

        data_[top_++] = x;

        ASSERT_VALID();
    }

    template<typename Tp>
    void stack_t<Tp>::pop() {
        ASSERT_VALID();

        if (!top_) {
            throw std::out_of_range("*Error: Stack is empty*");
        }
        data_[--top_] = FREE_POISON_;

        ASSERT_VALID();
    }

    template<typename Tp>
    bool stack_t<Tp>::reserve(const size_type n) {
        if (n <= capacity_) {
            return false;
        }

        size_type new_capacity = std::max(capacity_, 1u);
        while (new_capacity < n) {
            new_capacity *= MEMORY_MULTIPLIER_;
        }

        value_type *tmp_buffer = nullptr;
        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            return false;
        }

        std::copy(data_, data_ + top_, tmp_buffer);
        std::fill(tmp_buffer + top_, tmp_buffer + new_capacity, FREE_POISON_);

        delete[] data_;
        data_ = tmp_buffer;
        tmp_buffer = nullptr;
        capacity_ = new_capacity;

        ASSERT_VALID();

        return true;
    }

    template<typename Tp>
    bool stack_t<Tp>::is_valid() const {
        if (data_ != nullptr) {
            if (top_ <= capacity_) {
                for (size_type i = top_; i < capacity_; ++i) {
                    if (data_[i] != FREE_POISON_) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        return !(top_ || capacity_);
    }

    template<typename Tp>
    void stack_t<Tp>::dump(const char* function_name) const {
        std::ofstream fout("__stack_dump.txt", std::ios_base::app);

        if (fout.is_open()) {
            const time_t time_info = time(nullptr);

            fout << "******************\n"
                    "Class stack_t:\n"
                    "time: "         << ctime(&time_info) <<
                    "function: "     << function_name     << "\n"
                    "satus: "        << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tcapacity: "   << capacity_         << "\n"
                    "\ttop: "        << top_              << "\n\n";

            for (size_type i = 0; i < capacity_; ++i) {
                fout << (i < top_ ? "\t* [" : "\t  [") << i << "]"
                     << " = " << data_[i]
                     << (i >= top_ && data_[i] != FREE_POISON_ ? "  //ERROR!\n" : "\n");
            }

            fout << "}\n";

            fout.close();
        }
    }

}

#endif // STK_STACK_H
