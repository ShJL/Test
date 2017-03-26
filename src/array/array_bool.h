//-----------------------------------------------------------------------------
//! @file array_bool.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Specialized class array for bool
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   21.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_ARRAY_BOOL_H
#define ATOM_ARRAY_BOOL_H 1

#include "bool/bool_space.h"
#include "exceptions.h"
#include "debug_tools.h"
#include "bool/va_bool_ref.h"
#include "bool/va_bool_iterator.h"
#include <algorithm>


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class array_t
    //! @details Specialized for bool type
    //-----------------------------------------------------------------------------
    template<const std::size_t max_size_>
    class array_t<bool, max_size_> {
    public:

        using value_type = bool;
        using pointer    = bit_container_type*;
        using size_type  = std::size_t;             //!< Size type

        using reference = va_reference<array_t<bool, max_size_> >;
        using iterator  = va_bool_iterator<array_t<bool, max_size_> >;

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //! @details When switched debug fill all elements of the POISON
        //-----------------------------------------------------------------------------
        array_t() noexcept :
            size_        (0),
            status_valid_(1) {

#ifndef ATOM_NDEBUG
            fill_n_bit(0, max_size_, POISON<value_type>::value);
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
                const bool      value = false) :
            size_        (0),
            status_valid_(1) {

            if (n > max_size_) {
                status_valid_ = 0;
                throw atom::badAlloc(FULL_COORDINATES_FFL);
            }

            size_ = n;
            fill_n_bit(0, size_, value);

#ifndef ATOM_NDEBUG
            fill_n_bit(size_, max_size_ - size_, POISON<value_type>::value);
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
        //! @brief Default destructor
        //! @details Macro ATOM_NDEBUG for debug mode
        //-----------------------------------------------------------------------------
        ~array_t() {
#ifndef ATOM_NDEBUG
            fill_n_bit(0, size_, POISON<value_type>::value);
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
            array_t<bool, max_size_> tmp_array(that);
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
        //! @brief Iterator
        //! @return Iterator on the begin of the array
        //-----------------------------------------------------------------------------
        iterator begin() {
            ATOM_OUT_OF_RANGE(!size_);
            return iterator(data_, 0);
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the end of the array
        //-----------------------------------------------------------------------------
        iterator end() {
            ATOM_OUT_OF_RANGE(!size_);
            return iterator(data_ + size_ / BIT_BLOCK_SIZE, size_ % BIT_BLOCK_SIZE);
        }

        //-----------------------------------------------------------------------------
        //! @brief First element
        //! @throws The same exceptions as the get_bit
        //! @return First bit
        //-----------------------------------------------------------------------------
        bool front() const {
            ATOM_ASSERT_VALID(this);
            ATOM_OUT_OF_RANGE(!size_);
            return get_bit(0);
        }

        //-----------------------------------------------------------------------------
        //! @brief Last element
        //! @throws The same exceptions as the get_bit
        //! @retrurn Last bit
        //-----------------------------------------------------------------------------
        bool back() const {
            ATOM_ASSERT_VALID(this);
            ATOM_OUT_OF_RANGE(!size_);
            return get_bit(size_ - 1);
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the array
        //! @param pos Number of the element
        //! @throw The same exceptions as the get_bit
        //! @return Nth item of the array
        //-----------------------------------------------------------------------------
        bool operator[](const size_type pos) const {
            ATOM_ASSERT_VALID(this);

            ATOM_OUT_OF_RANGE(pos >= size_);
            return get_bit(pos);
        }

        reference operator[](const size_type pos) {
            ATOM_ASSERT_VALID(this);

            ATOM_OUT_OF_RANGE(pos >= size_);
            return reference(data_ + n_block(pos), pos_in_block(pos));
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new item in back of the array
        //! @param x new element which will be added in array
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @throw atom::badAlloc When currently size equalent max_size of the array
        //-----------------------------------------------------------------------------
        void push_back(const bool x) {
            ATOM_ASSERT_VALID(this);

            ATOM_BAD_ALLOC(size_ >= max_size_);
            ++size_;
            set_bit(size_ - 1, x);

            ATOM_ASSERT_VALID(this);
        }

        bool erase(const size_type pos);

        //-----------------------------------------------------------------------------
        //! @brief Clear the array
        //-----------------------------------------------------------------------------
        void clear() noexcept {
#ifndef ATOM_NDEBUG
            fill_n_bit(0, size_, POISON<value_type>::value);
#endif
            size_ = 0;
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
                fill_n_bit(size_, n - size_, POISON<value_type>::value);
#endif
                size_ = n;
                return true;
            }

            return false;
        }

        size_type count() const;

        void set(const size_type pos) {
            ATOM_ASSERT_VALID(this);

            ATOM_OUT_OF_RANGE(pos >= size_);
            set_bit(pos, true);

            ATOM_ASSERT_VALID(this);
        }

        void reset(const size_type pos) {
            ATOM_OUT_OF_RANGE(pos >= size_);
            set_bit(pos, false);
        }

        void flip(const size_type pos) {
            ATOM_ASSERT_VALID(this);
            ATOM_OUT_OF_RANGE(pos >= size_);

            data_[n_block(pos)] ^= (ONE << pos_in_block(pos));

            ATOM_ASSERT_VALID(this);
        }

        void invert();

        //-----------------------------------------------------------------------------
        //! @brief Checks the array on the void
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @return True if array is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const {
            ATOM_ASSERT_VALID(this);
            return !size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @return capacity of the array
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            ATOM_ASSERT_VALID(this);
            return max_size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Size
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when array is not valid
        //! @return Count bits in the array
        //-----------------------------------------------------------------------------
        size_type size() const {
            ATOM_ASSERT_VALID(this);
            return size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Swap two array
        //! @param rhs other array to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(array_t& rhs) noexcept {
            std::swap_ranges(data_, data_ + bit_to_block(max_size_), rhs.data_);
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

        size_type          size_;
        bit_container_type data_[div_ceil(max_size_, BIT_BLOCK_SIZE)];

        unsigned char status_valid_: 1; //!< Status of the array

        void set_bit(const size_type pos, const bool value) {
            ATOM_ASSERT_VALID(this);

            if (value) {
                data_[n_block(pos)] |= ONE << pos_in_block(pos);
            }
            else {
                data_[n_block(pos)] &= ~(ONE << pos_in_block(pos));
            }

            ATOM_ASSERT_VALID(this);
        }

        bool get_bit(const size_type pos) const {
            ATOM_ASSERT_VALID(this);
            return get_n_bit(data_[n_block(pos)], pos_in_block(pos));
        }

        bool get_bit_dump_version(const size_type pos) const {
            ATOM_OUT_OF_RANGE(pos >= max_size_);
            return get_n_bit(data_[pos / BIT_BLOCK_SIZE], pos % BIT_BLOCK_SIZE);
        }

        size_type n_block(const size_type pos) const {
            ATOM_OUT_OF_RANGE(pos >= max_size_);
            return pos / BIT_BLOCK_SIZE;
        }

        size_type pos_in_block(const size_type pos) const {
            ATOM_OUT_OF_RANGE(pos >= max_size_);
            return pos % BIT_BLOCK_SIZE;
        }

        size_type block_to_bit(const size_type count_blocks) const noexcept {
            return count_blocks * BIT_BLOCK_SIZE;
        }

        size_type bit_to_block(const size_type count_bits) const {
            return div_ceil(count_bits, BIT_BLOCK_SIZE);
        }

        void fill_n_bit(const size_type begin,
                        const size_type n,
                        const bool      value);

        void dump(const char* file,
                  const char* function_name,
                  int         line_number,
                  const char* output_file = "__array_bool_dump.txt") const;
    };

}

#include "implement/array_bool.hpp"

#endif // ATOM_ARRAY_BOOL_H
