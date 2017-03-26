//-----------------------------------------------------------------------------
//! @file array.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a array class
//!
//!
//! @version 1.1
//!
//! @author ShJ
//! @date   18.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_ARRAY_H
#define ATOM_ARRAY_H 1

#include "exceptions.h"
#include "debug_tools.h"
#include "va_iterator.h"
#include <initializer_list>
#include <algorithm>


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class array_t
    //! @tparam Tp The type of the value in the array
    //! @tparam max_size_ Max capacity of the array
    //-----------------------------------------------------------------------------
    template<typename Tp, const std::size_t max_size_>
    class array_t {
    public:

        friend class va_iterator<Tp>;

        using value_type       = Tp;                    //!< Element type
        using const_value_type = const Tp;              //!< Constant element type
        using reference        = Tp&;                   //!< Reference type
        using const_reference  = const Tp&;             //!< Constant reference type
        using iterator         = va_iterator<Tp>;       //!< Iterator type
        using const_iterator   = va_iterator<const Tp>; //!< Iterator type
        using size_type        = std::size_t;           //!< Size type

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //! @details When switched debug fill all elements of the POISON
        //-----------------------------------------------------------------------------
        array_t() noexcept :
            size_        (0),
            status_valid_(1) {

#ifndef ATOM_NDEBUG
            std::fill_n(data_, max_size_, POISON<value_type>::value);
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @details Constructor which set size of the array and initialize them
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param n The desired size of the array
        //! @param value initializer for n elements
        //! @throw atom::badAlloc If n less than max size
        //-----------------------------------------------------------------------------
        array_t(const size_type n,
                const_reference value) :
            size_        (0),
            status_valid_(1) {

            if (n > max_size_) {
                status_valid_ = 0;
                throw atom::badAlloc(FULL_COORDINATES_FFL);
            }

            size_ = n;
            std::fill_n(data_, size_, value);

#ifndef ATOM_NDEBUG
            std::fill(data_ + size_, data_ + max_size_, POISON<value_type>::value);
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @details Constructor which set size of the array and initialize them
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param n The desired size of the array
        //! @param value rvalue reference (default value_type()) initializer for n elements
        //! @throw atom::badAlloc If n greater than max size
        //-----------------------------------------------------------------------------
        array_t(const size_type n,
                const_value_type&& value = value_type()) :
            size_        (0),
            status_valid_(1) {

            if (n > max_size_) {
                status_valid_ = 0;
                throw atom::badAlloc(FULL_COORDINATES_FFL);
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
        //! @brief The move constructor
        //! @param that The move source
        //-----------------------------------------------------------------------------
        array_t(array_t&& that) noexcept :
            size_        (0),
            status_valid_(1) {

            swap(that);
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor with std::initializer_list
        //! @details Constructor which copy from std::initializer_list
        //! @param init List of elements
        //! @throw atom::badAlloc If n greater than max size
        //-----------------------------------------------------------------------------
        array_t(const std::initializer_list<value_type>& init) :
            size_        (0),
            status_valid_(1) {

            if (init.size() > max_size_) {
                status_valid_ = 0;
                throw atom::badAlloc(FULL_COORDINATES_FFL);
            }

            size_ = init.size();
            std::copy(init.begin(), init.end(), data_);

#ifndef ATOM_NDEBUG
            std::fill(data_ + size_, data_ + max_size_, POISON<value_type>::value);
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief Default destructor
        //! @details Macro ATOM_NDEBUG for debug mode
        //-----------------------------------------------------------------------------
        ~array_t() {
#ifndef ATOM_NDEBUG
            std::fill_n(data_, size_, POISON<value_type>::value);
            size_ = POISON<size_type>::value;
#endif
            status_valid_ = 0;
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @details Use copy and move idiom
        //! @param that The source of the assignment
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const array_t& operator=(const array_t& that) {
            array_t<value_type, max_size_> tmp_array(that);
            swap(tmp_array);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The move assignment operator
        //! @param that The move source
        //! @return Reference to the calling object
        //-----------------------------------------------------------------------------
        array_t& operator=(array_t&& that) {
            if (this != &that) {
                swap(that);
            }
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
        const_reference operator[](const size_type n) const {
            ATOM_ASSERT_VALID(this);

            ATOM_OUT_OF_RANGE(n >= size_);
            return data_[n];
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the array
        //! @param n Number of the element
        //! @throws The same exceptions as the operator[] returns const reference
        //! @return Reference on the nth item of the array
        //-----------------------------------------------------------------------------
        reference operator[](const size_type n) {
            return const_cast<reference>(static_cast<const array_t*>(this)->operator [](n));
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the begin of the array
        //-----------------------------------------------------------------------------
        iterator begin() {
            return iterator(data_);
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the end of the array
        //-----------------------------------------------------------------------------
        iterator end() {
            return iterator(data_ + size_);
        }

        //-----------------------------------------------------------------------------
        //! @brief Constant iterator
        //! @return Iterator on the begin of the array
        //-----------------------------------------------------------------------------
        const_iterator cbegin() {
            return const_iterator(data_);
        }

        //-----------------------------------------------------------------------------
        //! @brief Constant iterator
        //! @return Iterator on the end of the array
        //-----------------------------------------------------------------------------
        const_iterator cend() {
            return const_iterator(data_ + size_);
        }

        //-----------------------------------------------------------------------------
        //! @brief First element
        //! @throws The same exceptions as the operator[]
        //-----------------------------------------------------------------------------
        const_reference front() const {
            return operator[](0);
        }

        //-----------------------------------------------------------------------------
        //! @brief Last element
        //! @throws The same exceptions as the operator[]
        //-----------------------------------------------------------------------------
        const_reference back() const {
            return operator[](size_ - 1);
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new item in back of the array
        //! @param x new element which will be added in array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @throw atom::badAlloc When currently size equalent max_size of the array
        //-----------------------------------------------------------------------------
        void push_back(const_reference x) {
            ATOM_ASSERT_VALID(this);

            ATOM_BAD_ALLOC(size_ >= max_size_);
            data_[size_++] = x;

            ATOM_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new rvalue reference item in back of the array
        //! @param x new element which will be added in array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @throw atom::badAlloc When currently size equalent max_size of the array
        //-----------------------------------------------------------------------------
        void push_back(const_value_type&& x) {
            ATOM_ASSERT_VALID(this);

            ATOM_BAD_ALLOC(size_ >= max_size_);
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
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //-----------------------------------------------------------------------------
        bool empty() const {
            ATOM_ASSERT_VALID(this);
            return !size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Clear the array
        //-----------------------------------------------------------------------------
        void clear() noexcept {
#ifndef ATOM_NDEBUG
            std::fill_n(data_, size_, POISON<value_type>::value);
#endif
            size_ = 0;
        }

        //-----------------------------------------------------------------------------
        //! @brief Size
        //! @return size of the array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //-----------------------------------------------------------------------------
        size_type size() const {
            ATOM_ASSERT_VALID(this);
            return size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @return capacity of the array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            ATOM_ASSERT_VALID(this);
            return max_size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Fill the array
        //! @param value The value to be assigned to all elements of the array
        //-----------------------------------------------------------------------------
        void fill(const_reference value) {
            ATOM_ASSERT_VALID(this);
            std::fill_n(data_, size_, value);
            ATOM_ASSERT_VALID(this);
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
        void swap(array_t& rhs) noexcept {
            std::swap_ranges(data_, data_ + max_size_, rhs.data_);
            std::swap(size_, rhs.size_);
            unsigned char tmp_status = rhs.status_valid_;
            rhs.status_valid_ = status_valid_;
            status_valid_ = tmp_status;
        }

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if array is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept {
            return this &&
                    status_valid_ &&
                    size_ <= max_size_;
        }

    private:

        size_type  size_;            //!< Size of the array
        value_type data_[max_size_]; //!< Buffer of the array

        unsigned char status_valid_: 1; //!< Status of the array

        //-----------------------------------------------------------------------------
        //! @brief Dumper
        //! @details Create file "__array_dump.txt" where is information about array's status
        //! @details Macro ATOM_NWRITE prohibit function dump() print elements (for example when value_type has not operator<<)
        //! @param function_name Name of function which call this method
        //! @param line_number Number of line which call this method
        //-----------------------------------------------------------------------------
        void dump(const char* file,
                  const char* function_name,
                  int         line_number,
                  const char* output_file = "__array_dump.txt") const;

    };
}

//! @brief Implementation methods of the class vector_t
#include "implement/array.hpp"
#include "array_bool.h"

#endif // ATOM_ARRAY_H
