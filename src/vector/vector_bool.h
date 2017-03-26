//-----------------------------------------------------------------------------
//! @file vector_bool.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Specialized class vector for bool
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   20.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_VECTOR_BOOL_H
#define ATOM_VECTOR_BOOL_H 1

#include "bool/bool_space.h"
#include "exceptions.h"
#include "debug_tools.h"
#include "bool/va_bool_iterator.h"
#include "bool/va_bool_ref.h"
#include <cmath>


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class vector_t
    //! @details Specialized for bool type
    //-----------------------------------------------------------------------------
    template<>
    class vector_t<bool> {
    public:

        using value_type = bool;
        using pointer    = bit_container_type*;
        using size_type  = std::size_t;             //!< Size type

        using reference = va_reference<vector_t<bool> >;
        using iterator  = va_bool_iterator<vector_t<bool> >;

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        vector_t() noexcept :
            size_        (0),
            capacity_    (0),
            data_        (nullptr),
            status_valid_(1) {
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @details Constructor which resize memory to n elements and initialize them
        //! @param n The number of elements for which memory is allocated
        //! @param value initializer for n elements
        //! @throws The same exceptions as the function resize()
        //-----------------------------------------------------------------------------
        vector_t(const size_type n,
                 const bool value = false) :
            size_        (0),
            capacity_    (0),
            data_        (nullptr),
            status_valid_(1) {

#ifndef ATOM_NDEBUG
            try {
#endif
                resize(n, value);
#ifndef ATOM_NDEBUG
            }
            catch (...) {
                status_valid_ = 0;
                throw;
            }
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @details Deep copy
        //! @param that The copy source
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        vector_t(const vector_t& that);

        //-----------------------------------------------------------------------------
        //! @brief The move constructor
        //! @param that The move source
        //-----------------------------------------------------------------------------
        vector_t(vector_t&& that) noexcept :
            size_        (0),
            capacity_    (0),
            data_        (nullptr),
            status_valid_(1)  {

            swap(that);
        }

        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //! @details Macro ATOM_NDEBUG for debug mode
        //-----------------------------------------------------------------------------
        ~vector_t() {
            delete[] data_;
            data_ = nullptr;
            status_valid_ = 0;

#ifndef ATOM_NDEBUG
            size_     = POISON<size_type>::value;
            capacity_ = POISON<size_type>::value;
#endif
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @details Use copy and move idiom
        //! @param that The source of the assignment
        //! @throws The same exceptions as the vector_t(const vector_t&)
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const vector_t& operator=(const vector_t& that) {
            vector_t tmp_vector(that);
            swap(tmp_vector);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The move assignment operator
        //! @param that The move source
        //! @return Reference to the calling object
        //-----------------------------------------------------------------------------
        vector_t& operator=(vector_t&& that) {
            if (this != &that) {
                swap(that);
            }
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the begin of the vector
        //-----------------------------------------------------------------------------
        iterator begin() {
            ATOM_OUT_OF_RANGE(!size_);
            return iterator(data_, 0);
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the end of the vector
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
        //! @details Checks n for occurrence in the interval of bounds of the vector
        //! @param pos Number of the element
        //! @throw The same exceptions as the get_bit
        //! @return Nth item of the vector
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
        //! @brief Push new item in back of the vector
        //! @details Can increase the capacity
        //! @param x new element which will be added in vector
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void push_back(const bool x) {
            ATOM_ASSERT_VALID(this);

            alloc(size_ + 1);
            ++size_;
            set_bit(size_ - 1, x);

            ATOM_ASSERT_VALID(this);
        }

        bool erase(const size_type pos);

        //-----------------------------------------------------------------------------
        //! @brief Clear the vector
        //-----------------------------------------------------------------------------
        void clear() noexcept {
            delete[] data_;
            data_     = nullptr;
            size_     = 0;
            capacity_ = 0;
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
        //! @brief Reserve new memory
        //! @details Do not shrink the capacity
        //! @param n new capacity
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void reserve(const size_type n) {
            ATOM_ASSERT_VALID(this);

            alloc(n);

            ATOM_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Create new block of the memory
        //! @details Can change size and capacity
        //! @param n The number of elements for which memory is allocated
        //! @param value initializer for n elements
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        void resize(const size_type n,
                    const bool value = false);

        //-----------------------------------------------------------------------------
        //! @brief Checks the vector on the void
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @return True if vector is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const {
            ATOM_ASSERT_VALID(this);
            return !size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @return capacity of the vector
        //-----------------------------------------------------------------------------
        size_type capacity() const {
            ATOM_ASSERT_VALID(this);
            return capacity_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Size
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @return Count bits in the vector
        //-----------------------------------------------------------------------------
        size_type size() const {
            ATOM_ASSERT_VALID(this);
            return size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Swap two vector
        //! @param rhs other vector to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(vector_t& rhs) noexcept {
            std::swap(data_, rhs.data_);
            std::swap(size_, rhs.size_);
            std::swap(capacity_, rhs.capacity_);
            unsigned char tmp_status = status_valid_;
            status_valid_ = rhs.status_valid_;
            rhs.status_valid_ = tmp_status;
        }

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if vector is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept {
            return this && status_valid_ &&
                    !(capacity_% BIT_BLOCK_SIZE) &&
                    (data_ ? size_ <= capacity_ : !capacity_ && !size_);
        }

    private:

        const size_type MEMORY_MULTIPLIER_ = 2; //!< Constant memory increase

        size_type           size_;
        size_type           capacity_;
        bit_container_type* data_;

        unsigned char status_valid_: 1; //!< Status of the vector

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
            ATOM_OUT_OF_RANGE(pos >= std::max(capacity_, size_));
            return get_n_bit(data_[pos / BIT_BLOCK_SIZE], pos % BIT_BLOCK_SIZE);
        }

        size_type n_block(const size_type pos) const {
            ATOM_OUT_OF_RANGE(pos >= capacity_);
            return pos / BIT_BLOCK_SIZE;
        }

        size_type pos_in_block(const size_type pos) const {
            ATOM_OUT_OF_RANGE(pos >= capacity_);
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

        void alloc(const size_type n);

        void shrink_alloc(const size_type n_bit);

        void dump(const char* file,
                  const char* function_name,
                  int         line_number,
                  const char* output_file = "__vector_bool_dump.txt") const;
    };

}

#include "implement/vector_bool.hpp"

#endif // ATOM_VECTOR_BOOL_H
