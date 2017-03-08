//-----------------------------------------------------------------------------
//! @file vector.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a vector class
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   04.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_VECTOR_H
#define ATOM_VECTOR_H 1

#include "exceptions.h"
#include "debug_tools.h"


//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class vector_t
    //! @tparam Tp The type of the value in the vector
    //-----------------------------------------------------------------------------
    template<typename Tp>
    class vector_t {
    public:       

        using value_type       = Tp;          //!< Element type
        using const_value_type = const Tp;    //!< Const element type
        using size_type        = std::size_t; //!< Size type

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        vector_t() noexcept :
            status_   (true),
            size_     (0),
            capacity_ (0),
            data_     (nullptr)  {
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @details Constructor which resize memory to n elements and initialize them
        //! @param n The number of elements for which memory is allocated
        //! @param value (default value_type()) initializer for n elements
        //! @throws The same exceptions as the function resize()
        //-----------------------------------------------------------------------------
        vector_t(const size_type n,
                 const value_type& value = value_type()) :
            status_  (true),
            size_    (0),
            capacity_(0),
            data_    (nullptr) {

            try {
                resize(n, value);
            }
            catch (...) {
                status_ = false;
                throw;
            }
        }

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @details Deep copy
        //! @details Specialized types: short, int, long long, char (also with unsigned), float, double
        //! @details These types use memcpy() and memset()
        //! @param that The copy source
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        vector_t(const vector_t& that);

        //-----------------------------------------------------------------------------
        //! @brief The move constructor
        //! @param that The move source
        //-----------------------------------------------------------------------------
        vector_t(vector_t&& that) noexcept {
            swap(that);
        }

        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //! @details Macro ATOM_NDEBUG for debug mode
        //-----------------------------------------------------------------------------
        ~vector_t() {
            delete[] data_;
            data_   = nullptr;
            status_ = false;

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
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the vector
        //! @param n Number of the element
        //! @throws The same exceptions as the operator[] returns const reference
        //! @return Reference on the nth item of the vector
        //-----------------------------------------------------------------------------
        value_type& operator[](const size_type n) {
            return const_cast<value_type&>(static_cast<const vector_t*>(this)->operator[](n));
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the vector
        //! @param n Number of the element
        //! @throw atom::outOfRange When n is bigger or equal than size of the vector
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @return Const reference on the nth item of the vector
        //-----------------------------------------------------------------------------
        const_value_type& operator[](const size_type n) const {
            ATOM_ASSERT_VALID(this);

            if (n >= size_) {
                throw atom::outOfRange(FUNC_AND_LINE);
            }

            return data_[n];
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new item in back of the vector
        //! @details Can increase the capacity
        //! @param x new element which will be added in vector
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void push_back(const_value_type x) {
            ATOM_ASSERT_VALID(this);

            alloc(size_ + 1);

            data_[size_++] = x;

            ATOM_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Remove nth element
        //! @details Do not change the capacity
        //! @details Macro ATOM_NDEBUG for debug mode
        //! @param position number of the item in the vector
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
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
        //! @brief Clear the vector
        //-----------------------------------------------------------------------------
        void clear() noexcept {
            delete[] data_;
            data_     = nullptr;
            size_     = 0;
            capacity_ = 0;
        }

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
        //! @details Specialized types: short, int, long long, char (also with unsigned), float, double
        //! @details These types use memcpy() and memset()
        //! @param n The number of elements for which memory is allocated
        //! @param value (default value_type()) initializer for n elements
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        void resize(const size_type n,
                    const value_type& value = value_type());

        //-----------------------------------------------------------------------------
        //! @brief Checks the vector on the void
        //! @return True if vector is empty, otherwise false
        //-----------------------------------------------------------------------------
        bool empty() const noexcept {
            return !size_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Capacity
        //! @return capacity of the vector
        //-----------------------------------------------------------------------------
        size_type capacity() const noexcept {
            return capacity_;
        }

        //-----------------------------------------------------------------------------
        //! @brief Size
        //! @return size of the vector
        //-----------------------------------------------------------------------------
        size_type size() const noexcept {
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
            std::swap(status_, rhs.status_);
        }

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if vector is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept {
            return status_ &&
                    (data_ != nullptr ?
                        size_ <= capacity_ : !capacity_ && !size_);
        }

    private:

        const size_type MEMORY_MULTIPLIER_ = 2; //!< Constant memory increase

        bool status_; //!< Status of the vector

        size_type  size_;     //!< Size of the vector
        size_type  capacity_; //!< Capacity of the vector
        value_type *data_;    //!< A pointer to an vector

        //-----------------------------------------------------------------------------
        //! @brief Create new block of the memory
        //! @details Can increase the capacity
        //! @param n new capacity
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        void alloc(const size_type n);

        //-----------------------------------------------------------------------------
        //! @brief Create new block of the memory
        //! @details Can change capacity and size, when undefine ATOM_NDEBUG fill all elements which are behind position size_
        //! @details Specialized types: short, int, long long, char (also with unsigned), float, double
        //! @details These types use memcpy() and memset()
        //! @param n New capacity
        //! @throw atom::badAlloc When not enough of the memory
        //! @throw atom::invalidObject From ATOM_ASSERT_VALID() when vector is not valid
        //-----------------------------------------------------------------------------
        void shrink_alloc(const size_type n);

        //-----------------------------------------------------------------------------
        //! @brief Dumper
        //! @details Create file "__vector_dump.txt" where is information about vector's status
        //! @details Macro ATOM_NWRITE prohibit function dump() print elements (for example when value_type has not operator<<)
        //! @param function_name Name of function which call this method
        //! @param line_number Number of line which call this method
        //-----------------------------------------------------------------------------
        void dump(const char* function_name,
                  int         line_number) const;
    };

}

//! @brief Implementation methods of the class vector_t
#include "implement/vector.hpp"

#endif // ATOM_VECTOR_H
