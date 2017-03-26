//-----------------------------------------------------------------------------
//! @file stack.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a stack class
//!
//!
//! @version 4.0
//!
//! @author ShJ
//! @date   05.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_STACK_H
#define ATOM_STACK_H 1

#include "vector/vector.h"
#include "exceptions.h"
#include "debug_tools.h"


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class stack_t
    //! @tparam Tp The type of the value in the stack
    //! @tparam Container the type of container which houses the stack (default is atom::vector_t)
    //! @details Container must have function: push_back(), erase(), back(), size(), swap() and capacity()
    //-----------------------------------------------------------------------------
    template<typename Tp, typename Container = atom::vector_t<Tp> >
    class stack_t {
    public:

        using value_type       = typename Container::value_type;       //!< Element type
        using const_value_type = typename Container::const_value_type; //!< Const element type
        using size_type        = typename Container::size_type;        //!< Size type
        using container_type   = Container;                            //!< Type of the container

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        stack_t() = default;

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @param that The copy source
        //-----------------------------------------------------------------------------
        stack_t(const stack_t& that) :
            data_(that.data_) {
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @details Use copy and swap idiom
        //! @param that The source of the assignment
        //! @throws The same exceptions as the stack_t(const stack_t&)
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const stack_t& operator=(const stack_t& that) {
            stack_t tmp_stack(that);
            swap(tmp_stack);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The move constructor
        //! @param that The move source
        //-----------------------------------------------------------------------------
        stack_t(stack_t&& that) noexcept {
            swap(that);
        }

        //-----------------------------------------------------------------------------
        //! @brief The move assignment operator
        //! @param that The source of the assignment
        //! @return Reference to the calling object
        //-----------------------------------------------------------------------------
        stack_t& operator=(stack_t&& that) {
            if (this != &that) {
                swap(that);
            }
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //-----------------------------------------------------------------------------
        ~stack_t() = default;

        //-----------------------------------------------------------------------------
        //! @brief Get the item from the stack
        //! @throws The same exceptions as the function back() (from container)
        //! @return The top item from the stack
        //-----------------------------------------------------------------------------
        value_type top() const {
            return data_.back();
        }

        //-----------------------------------------------------------------------------
        //! @brief Delete the item from the stack
        //! @details If stack is empty does nothing
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when stack is not valid
        //-----------------------------------------------------------------------------
        void pop() {
            ATOM_ASSERT_VALID(this);

            const size_type size = data_.size();
            if (size) {
                data_.erase(size - 1);
            }

            ATOM_ASSERT_VALID(this);
        }


        //-----------------------------------------------------------------------------
        //! @brief Append new item in the stack
        //! @param x The element that will be added to the stack
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when stack is not valid
        //! @throws The same exceptions as the function push_back() (from container)
        //-----------------------------------------------------------------------------
        void push(const_value_type& x) {
            ATOM_ASSERT_VALID(this);

            data_.push_back(x);

            ATOM_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Currently size of the stack
        //! @return Count of the item in the stack
        //-----------------------------------------------------------------------------
        size_type size() const {
            return data_.size();
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @return Capacity of the stack
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            return data_.capacity();
        }

        //-----------------------------------------------------------------------------
        //! @brief Checks the emptiness of the stack
        //! @return True if stack is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const {
            return data_.empty();
        }

        //-----------------------------------------------------------------------------
        //! @brief Clear the stack
        //-----------------------------------------------------------------------------
        void clear() const noexcept {
            data_.clear();
        }

        //-----------------------------------------------------------------------------
        //! @brief swap two stack
        //! @param rhs other stack to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(stack_t& rhs) noexcept {
            data_.swap(rhs.data_);
        }

    private:

        container_type data_; //!< Container, base of the stack

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if stack is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept {
            return data_.is_valid();
        }

        //-----------------------------------------------------------------------------
        //! @brief Dumper
        //! @details Create file "__stack_dump.txt" where is information about stack's status
        //! @details Macro ATOM_NWRITE prohibit function dump() print elements (for example when value_type has not operator<<)
        //! @param function_name Name of function which call this method
        //! @param line_number Number of the line where call this method
        //-----------------------------------------------------------------------------
        void dump(const char* file,
                  const char* function_name,
                  int         line_number,
                  const char* output = "__stack_dump.txt") const;
    };

}

//! @brief Implementation methods of the class stack_t
#include "implement/stack.hpp"

#endif // ATOM_STACK_H
