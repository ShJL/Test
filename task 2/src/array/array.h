//-----------------------------------------------------------------------------
//! @file array.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a array class
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   05.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_ARRAY_H
#define ATOM_ARRAY_H 1

#include <algorithm>
#include "exceptions.h"
#include "debug_tools.h"


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class array_t
    //! @tparam Tp The type of the value in the array
    //! @tparam max_size_ Max capacity of the array (default is 256)
    //-----------------------------------------------------------------------------
    template<typename Tp, const std::size_t max_size_ = 256>
    class array_t {
    public:

        using value_type       = Tp;          //!< Element type
        using const_value_type = const Tp;    //!< Const element type
        using size_type        = std::size_t; //!< Size type

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //! @details When switched debug fill all elements of the POISON
        //-----------------------------------------------------------------------------
        array_t() noexcept :
            status_(true),
            size_  (0) {

#ifndef ATOM_NDEBUG
            std::fill(data_, data_ + max_size_, POISON<value_type>::value);
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @details Constructor which set size of the array and initialize them
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param n The desired size of the array
        //! @param value (default value_type()) initializer for n elements
        //! @throw atom::badAlloc If n less than max size
        //-----------------------------------------------------------------------------
        array_t(const size_type n,
                const value_type& value = value_type()) :
            status_  (true),
            size_    (0) {

            if (n > max_size_) {
                status_ = false;
                throw atom::badAlloc(FUNC_AND_LINE);
            }

            size_ = n;
            std::fill_n(data_, size_, value);

#ifndef ATOM_NDEBUG
            std::fill(data_ + size_, data_ + max_size_, POISON<value_type>::value);
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief Default copy constructor
        //-----------------------------------------------------------------------------
        array_t(const array_t& that) = default;

        //-----------------------------------------------------------------------------
        //! @brief Default destructor
        //! @details Macro ATOM_NDEBUG for debug mode
        //-----------------------------------------------------------------------------
        ~array_t() {
            status_ = false;

#ifndef ATOM_NDEBUG
            size_ = POISON<size_type>::value;
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @details Use copy and move idiom
        //! @param that The source of the assignment
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const array_t& operator=(const array_t& that) {
            array_t<value_type> tmp_array(that);
            swap(tmp_array);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the array
        //! @param n Number of the element
        //! @throw atom::outOfRange When n is bigger or equal than size of the array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @return Const reference on the nth item of the array
        //-----------------------------------------------------------------------------
        const_value_type& operator[](const size_type n) const {
            ATOM_ASSERT_VALID(this);

            if (n >= size_) {
                throw atom::outOfRange(FUNC_AND_LINE);
            }

            return data_[n];
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the array
        //! @param n Number of the element
        //! @throws The same exceptions as the operator[] returns const reference
        //! @return Reference on the nth item of the array
        //-----------------------------------------------------------------------------
        value_type& operator[](const size_type n) {
            return const_cast<value_type&>(static_cast<const array_t*>(this)->operator [](n));
        }

        //-----------------------------------------------------------------------------
        //! @brief First element
        //! @throws The same exceptions as the operator[]
        //-----------------------------------------------------------------------------
        const_value_type& front() const {
            return operator[](0);
        }

        //-----------------------------------------------------------------------------
        //! @brief Last element
        //! @throws The same exceptions as the operator[]
        //-----------------------------------------------------------------------------
        const_value_type& back() const {
            return operator[](size_ - 1);
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new item in back of the array
        //! @param x new element which will be added in array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @throw atom::badAlloc When currently size equalent max_size of the array
        //-----------------------------------------------------------------------------
        void push_back(const_value_type x) {
            ATOM_ASSERT_VALID(this);

            if (size_ >= max_size_) {
                throw atom::badAlloc(FUNC_AND_LINE);
            }

            data_[size_++] = x;

            ATOM_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Remove nth element
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param position number of the item in the array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @return True if element was delete, otherwise false
        //-----------------------------------------------------------------------------
        bool erase(const size_type position) {
            ATOM_ASSERT_VALID(this);

            if (position >= size_) {
                return false;
            }

            --size_;

            for (size_type i = position; i < size_; ++i) {
                data_[i] = data_[i + 1];
            }

#ifndef ATOM_NDEBUG
            data_[size_] = POISON<value_type>::value;
#endif
            ATOM_ASSERT_VALID(this);
            return true;
        }

        //-----------------------------------------------------------------------------
        //! @brief Checks the array on the void
        //! @return True if array is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const noexcept {
            return !size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Size
        //! @return size of the array
        //-----------------------------------------------------------------------------
        size_type size() const noexcept {
            return size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @return capacity of the array
        //-----------------------------------------------------------------------------
        size_type capacity() const noexcept {
            return max_size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Fill the array
        //! @param value The value to be assigned to all elements of the array
        //-----------------------------------------------------------------------------
        void fill(const_value_type& value) {
            std::fill_n(data_, size_, value);
        }

        //-----------------------------------------------------------------------------
        //! @brief Set new size of the array within max_size
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param n The desired size of the array
        //! @return True if n less than max_size, otherwise false
        //-----------------------------------------------------------------------------
        bool use_array(const size_type n) noexcept {
            if (n <= max_size_) {

#ifndef ATOM_NDEBUG
                std::fill(data_ + size_, data_ + n, POISON<value_type>::value);
#endif
                size_ = n;
                return true;
            }

            return false;
        }

        //-----------------------------------------------------------------------------
        //! @brief Swap two array
        //! @param rhs other array to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(array_t& rhs) {
            std::swap_ranges(data_, data_ + max_size_, rhs.data_);
            std::swap(size_, rhs.size_);
            std::swap(status_, rhs.status_);
        }

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if array is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept {
            return status_ &&
                    size_ <= max_size_;
        }

    private:

        bool status_; //!< Status of the array

        size_type  size_;            //!< Size of the array
        value_type data_[max_size_]; //!< Buffer of the array

        //-----------------------------------------------------------------------------
        //! @brief Dumper
        //! @details Create file "__array_dump.txt" where is information about array's status
        //! @details Macro ATOM_NWRITE prohibit function dump() print elements (for example when value_type has not operator<<)
        //! @param function_name Name of function which call this method
        //! @param line_number Number of line which call this method
        //-----------------------------------------------------------------------------
        void dump(const char* function_name,
                  int         line_number) const;

    };
}

#include "implement/array.hpp"

#endif // ATOM_ARRAY_H
