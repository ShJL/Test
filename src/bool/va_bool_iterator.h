//-----------------------------------------------------------------------------
//! @file va_bool_va_bool_iterator.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a va_bool_iterator for bool array or vector
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   20.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_VA_BOOL_va_bool_iterator_H
#define ATOM_VA_BOOL_va_bool_iterator_H 1

#include "exceptions.h"
#include "debug_tools.h"
#include "bool_space.h"
#include "va_bool_ref.h"
#include <iterator>

//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    template<class Tp>
    class va_bool_iterator
            : public std::iterator<std::bidirectional_iterator_tag,
                                   bit_container_type,
                                   ptrdiff_t,
                                   typename Tp::pointer,
                                   typename Tp::reference> {
    public:

        using va_bool_iterator_base = std::iterator<std::bidirectional_iterator_tag,
                                                    bit_container_type,
                                                    ptrdiff_t,
                                                    typename Tp::pointer,
                                                    typename Tp::reference>;

        using reference       = typename va_bool_iterator_base::reference;	     //!< Reference type
        using pointer         = typename va_bool_iterator_base::pointer;	     //!< Pointer type
        using difference_type = typename va_bool_iterator_base::difference_type; //!< Type difference between two va_bool_iterator
        using size_type       = typename Tp::size_type;

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        va_bool_iterator() noexcept :
            current_(nullptr),
            offset_ (0) {
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @param x Pointer on the item
        //! @details Initialisere of the va_bool_iterator
        //-----------------------------------------------------------------------------
        va_bool_iterator(const pointer x,
                         const size_type pos) noexcept :
            current_(x),
            offset_ (pos) {
        }

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @param other The copy source
        //-----------------------------------------------------------------------------
        va_bool_iterator(const va_bool_iterator& other) noexcept :
            current_(other.current_),
            offset_ (other.offset_) {
        }
        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //-----------------------------------------------------------------------------
        ~va_bool_iterator() noexcept {
            current_ = nullptr;
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const va_bool_iterator& operator=(const va_bool_iterator& other) noexcept {
            if (this != &other) {
                current_ = other.current_;
                offset_  = other.offset_;
            }
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The dereferencing operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return Reference of the element
        //-----------------------------------------------------------------------------
        reference operator*() const {
            ATOM_OTHER_ERROR(!current_, "Is null");
            return reference(current_, offset_);
        }

        //-----------------------------------------------------------------------------
        //! @brief The prefix increment operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return Reference on the calling object
        //-----------------------------------------------------------------------------
        va_bool_iterator& operator++() {
            ATOM_OTHER_ERROR(!current_, "Is null");

            inc(1);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The postfix increment operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return old va_bool_iterator before increment
        //-----------------------------------------------------------------------------
        const va_bool_iterator operator++(int) {
            ATOM_OTHER_ERROR(!current_, "Is null");

            va_bool_iterator old_value = *this;
            inc(1);
            return old_value;
        }

        //-----------------------------------------------------------------------------
        //! @brief The prefix decrement operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return Reference on the calling object
        //-----------------------------------------------------------------------------
        va_bool_iterator& operator--() {
            ATOM_OTHER_ERROR(!current_, "Is null");

            inc(-1);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The postfix decrement operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return old va_bool_iterator before increment
        //-----------------------------------------------------------------------------
        const va_bool_iterator operator--(int) {
            ATOM_OTHER_ERROR(!current_, "Is null");

            va_bool_iterator old_value(*this);
            inc(-1);
            return old_value;
        }

        //-----------------------------------------------------------------------------
        //! @brief The increase with assignment operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return Constant reference on the calling object
        //-----------------------------------------------------------------------------
        const va_bool_iterator& operator+=(const int index) {
            ATOM_OTHER_ERROR(!current_, "Is null");

            inc(index);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The decrease with assignment operator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return Constant reference on the calling object
        //-----------------------------------------------------------------------------
        const va_bool_iterator& operator-=(const int index) {
            ATOM_OTHER_ERROR(!current_, "Is null");

            inc(-index);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Swap two va_bool_iterator
        //! @param other va_bool_iterator to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(va_bool_iterator& other) noexcept {
            std::swap(current_, other.current_);
            std::swap(offset_, other.offset_);
        }

        //-----------------------------------------------------------------------------
        //! @brief The inequality operator
        //! @param lhs va_bool_iterator which is left from operator
        //! @param rhs va_bool_iterator which is right from operator
        //! @return True if va_bool_iterators are not equal, otherwise false
        //-----------------------------------------------------------------------------
        template<class Y>
        friend bool operator!=(const va_bool_iterator<Y>& lhs,
                               const va_bool_iterator<Y>& rhs);

        //-----------------------------------------------------------------------------
        //! @brief The equality operator
        //! @param lhs va_bool_iterator which is left from operator
        //! @param rhs va_bool_iterator which is right from operator
        //! @return True if va_bool_iterators are equal, otherwise false
        //-----------------------------------------------------------------------------
        template<class Y>
        friend bool operator==(const va_bool_iterator<Y>& lhs,
                               const va_bool_iterator<Y>& rhs);

        //-----------------------------------------------------------------------------
        //! @brief The minus operator
        //! @param lhs The va_bool_iterator is the beginning of the reference
        //! @param index The amount and direction of shift of the va_bool_iterator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return
        //-----------------------------------------------------------------------------
        template<class Y>
        friend va_bool_iterator<Y> operator-(const va_bool_iterator<Y>& lhs,
                                             const int index);

        //-----------------------------------------------------------------------------
        //! @brief The plus operator
        //! @param lhs The va_bool_iterator is the beginning of the reference
        //! @param index The amount and direction of shift of the va_bool_iterator
        //! @throw atom::otherError If va_bool_iterator has nullptr pointer
        //! @return
        //-----------------------------------------------------------------------------
        template<class Y>
        friend va_bool_iterator<Y> operator+(const va_bool_iterator<Y>& lhs,
                                             const int index);

        //-----------------------------------------------------------------------------
        //! @brief The difference between two va_bool_iterators operator
        //! @param lhs va_bool_iterator which is left from operator
        //! @param rhs va_bool_iterator which is right from operator
        //! @throw atom::otherError If va_bool_iterators have nullptr pointer
        //! @return Difference between va_bool_iterators
        //-----------------------------------------------------------------------------
        template<class Y>
        friend typename va_bool_iterator<Y>::difference_type operator-(const va_bool_iterator<Y>& lhs,
                                                                       const va_bool_iterator<Y>& rhs);

    private:

        pointer   current_; //!< Pointer on the item
        size_type offset_;

        void inc(const int index) noexcept {
            int off = offset_ + index;

            if (index >= 0) {
                while (off >= static_cast<int>(BIT_BLOCK_SIZE)) {
                    ++current_;
                    off -= BIT_BLOCK_SIZE;
                }
            }
            else {
                while (off < 0) {
                    --current_;
                    off += BIT_BLOCK_SIZE;
                }
            }

            offset_ = off;
        }

    };

    template<class Y>
    bool operator!=(const va_bool_iterator<Y>& lhs,
                    const va_bool_iterator<Y>& rhs) {

        return lhs.current_ != rhs.current_ ||
                lhs.offset_ != rhs.offset_;
    }

    template<class Y>
    bool operator==(const va_bool_iterator<Y>& lhs,
                    const va_bool_iterator<Y>& rhs) {

        return lhs.current_ == rhs.current_ &&
                lhs.offset_ == lhs.offset_;
    }

    template<class Y>
    va_bool_iterator<Y> operator-(const va_bool_iterator<Y>& lhs,
                          const int index) {

        ATOM_OTHER_ERROR(!lhs.current_, "Is null");

        va_bool_iterator<Y> tmp(lhs);
        tmp.inc(-index);

        return va_bool_iterator<Y>(tmp);
    }

    template<class Y>
    va_bool_iterator<Y> operator+(const va_bool_iterator<Y>& lhs,
                          const int index) {

        ATOM_OTHER_ERROR(!lhs.current_, "Is null");

        va_bool_iterator<Y> tmp(lhs);
        tmp.inc(index);

        return va_bool_iterator<Y>(tmp);
    }

    template<class Y>
    typename va_bool_iterator<Y>::difference_type
    operator-(const va_bool_iterator<Y>& lhs,
              const va_bool_iterator<Y>& rhs) {

        ATOM_OTHER_ERROR(!lhs.current_, "Lhs is null");
        ATOM_OTHER_ERROR(!rhs.current_, "Rhs is null");

        return (lhs.current_ - rhs.current_) * BIT_BLOCK_SIZE + lhs.offset_ - rhs.offset_;
    }

}

#endif // ATOM_VA_BOOL_va_bool_iterator_H
