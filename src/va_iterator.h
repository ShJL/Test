//-----------------------------------------------------------------------------
//! @file va_iterator.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a iterator for array and vector
//!
//!
//! @version 1.1
//!
//! @author ShJ
//! @date   18.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_VA_ITERATOR_H
#define ATOM_VA_ITERATOR_H 1

#include "exceptions.h"
#include "debug_tools.h"
#include <iterator>

//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class va_iterator
    //! @details Inheritance from std::iterator
    //! @details Iterator's category is std::bidirectional_iterator_tag
    //! @tparam Tp The type of the value in the iterator
    //-----------------------------------------------------------------------------
    template<typename Tp>
    class va_iterator
            : public std::iterator<std::bidirectional_iterator_tag, Tp> {
    public:

        using iterator_base   = std::iterator<std::bidirectional_iterator_tag, Tp>; //!< Class with declaretion of the types
        using value_type      = typename iterator_base::value_type;		    //!< Element type
        using reference       = typename iterator_base::reference;		    //!< Reference type
        using pointer         = typename iterator_base::pointer;		    //!< Pointer type
        using difference_type = typename iterator_base::difference_type;	    //!< Type difference between two iterator

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        va_iterator() noexcept
            : current_(nullptr) {
        }

        //-----------------------------------------------------------------------------
        //! @brief Constructor 
        //! @param x Pointer on the item
        //! @details Initialisere of the iterator
        //-----------------------------------------------------------------------------
        explicit va_iterator(pointer x) noexcept
            : current_(x) {
        }

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @param other The copy source
        //-----------------------------------------------------------------------------
        va_iterator(const va_iterator& other) noexcept
            : current_(other.current_) {
        }
        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //-----------------------------------------------------------------------------
        ~va_iterator() noexcept {
            current_ = nullptr;
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        const va_iterator& operator=(const va_iterator& other) noexcept {
			if (this != &other) {
				current_ = other.current_;
			}
			return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The dereferencing operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return value of the element
        //-----------------------------------------------------------------------------
        value_type operator*() const {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            return *current_;
        }

        //-----------------------------------------------------------------------------
        //! @brief The dereferencing operator
        //! @return Pointer on the element
        //-----------------------------------------------------------------------------
        pointer operator->() const noexcept {
            return current_;
        }

        //-----------------------------------------------------------------------------
        //! @brief The prefix increment operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return Reference on the calling object
        //-----------------------------------------------------------------------------
        va_iterator& operator++() {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            ++current_;
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The postfix increment operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return old iterator before increment
        //-----------------------------------------------------------------------------
        const va_iterator operator++(int) {
			if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }
			
            va_iterator old_value = *this;
            ++current_;
            return old_value;
        }

        //-----------------------------------------------------------------------------
        //! @brief The prefix decrement operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return Reference on the calling object
        //-----------------------------------------------------------------------------
        va_iterator& operator--() {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            --current_;
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The postfix decrement operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return old iterator before increment
        //-----------------------------------------------------------------------------
        const va_iterator operator--(int) {
			if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }
			
            value_type old_value(*this);
            --current_;
            return old_value;
        }

        //-----------------------------------------------------------------------------
        //! @brief The increase with assignment operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return Constant reference on the calling object
        //-----------------------------------------------------------------------------
        const va_iterator& operator+=(const int index) {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            current_ += index;
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The decrease with assignment operator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return Constant reference on the calling object
        //-----------------------------------------------------------------------------
        const va_iterator& operator-=(const int index) {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            current_ -= index;
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Swap two iterator
        //! @param other Iterator to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(va_iterator& other) noexcept {
            value_type* tmp = current_;
            current_ = other.current_;
            other.current_ = tmp;
        }

        //-----------------------------------------------------------------------------
        //! @brief The inequality operator
        //! @tparam T Type data in the iterator
        //! @param lhs Iterator which is left from operator
        //! @param rhs Iterator which is right from operator
        //! @return True if iterators are not equal, otherwise false
        //-----------------------------------------------------------------------------
        template<typename T>
        friend bool operator!=(const va_iterator<T>& lhs,
                               const va_iterator<T>& rhs);

        //-----------------------------------------------------------------------------
        //! @brief The equality operator
        //! @tparam T Type data in the iterator
        //! @param lhs Iterator which is left from operator
        //! @param rhs Iterator which is right from operator
        //! @return True if iterators are equal, otherwise false
        //-----------------------------------------------------------------------------
        template<typename T>
        friend bool operator==(const va_iterator<T>& lhs,
                               const va_iterator<T>& rhs);

        //-----------------------------------------------------------------------------
        //! @brief The minus operator
        //! @tparam T Type data in the iterator
        //! @param lhs The iterator is the beginning of the reference
        //! @param index The amount and direction of shift of the iterator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return 
        //-----------------------------------------------------------------------------
        template<typename T>
        friend va_iterator<T> operator-(const va_iterator<T>& lhs,
                                        const int index);

        //-----------------------------------------------------------------------------
        //! @brief The plus operator
        //! @tparam T Type data in the iterator
        //! @param lhs The iterator is the beginning of the reference
        //! @param index The amount and direction of shift of the iterator
        //! @throw atom::otherError If iterator has nullptr pointer
        //! @return 
        //-----------------------------------------------------------------------------
        template<typename T>
        friend va_iterator<T> operator+(const va_iterator<T>& lhs,
               							const int index);

        //-----------------------------------------------------------------------------
        //! @brief The difference between two iterators operator
        //! @tparam T Type data in the iterator
        //! @param lhs Iterator which is left from operator
        //! @param rhs Iterator which is right from operator
        //! @throw atom::otherError If iterators have nullptr pointer
        //! @return Difference between iterators
        //-----------------------------------------------------------------------------
        template<typename T>
        friend difference_type operator-(const va_iterator<T>& lhs,
                                         const va_iterator<T>& rhs);

    private:

        pointer current_; //!< Pointer on the item
    };


    template<typename T>
    bool operator!=(const va_iterator<T>& lhs,
                    const va_iterator<T>& rhs) {

        return lhs.current_ != rhs.current_;
    }

    template<typename T>
    bool operator==(const va_iterator<T>& lhs,
                    const va_iterator<T>& rhs) {

        return lhs.current_ == rhs.current_;
    }

    template<typename T>
    va_iterator<T>& operator-(const va_iterator<T>& lhs,
                              const int index) {

        if (!lhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Is null");
        }

        return va_iterator<T>(lhs.current_ - index);
    }

    template<typename T>
    va_iterator<T>& operator+(const va_iterator<T>& lhs,
                              const int index) {

        if (!lhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Is null");
        }

        return va_iterator<T>(lhs.current_ + index);
    }

    template<typename T>
    typename va_iterator<T>::difference_type
    operator-(const va_iterator<T>& lhs,
              const va_iterator<T>& rhs) {

        if (!lhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Lhs is null");
        }
        if (!rhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Rhs is null");
        }

        return lhs.current_ - rhs.current_;
    }

}

#endif //ATOM_VA_ITERATOR_H
