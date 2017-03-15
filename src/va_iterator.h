#ifndef ATOM_VA_ITERATOR_H
#define ATOM_VA_ITERATOR_H

#include "exceptions.h"
#include "debug_tools.h"
#include <iterator>


namespace atom {

    template<typename Tp>
    class va_iterator
            : public std::iterator<std::random_access_iterator_tag, Tp> {
    public:

        using value_type       = Tp;
        using const_value_type = const Tp;

        va_iterator() noexcept
            : current_(nullptr) {
        }

        explicit va_iterator(value_type* x) noexcept
            : current_(x) {
        }

        va_iterator(const va_iterator& other) noexcept
            : current_(other.current_) {
        }

        ~va_iterator() noexcept {
            current_ = nullptr;
        }

        va_iterator& operator=(const va_iterator& other) noexcept {
            current_ = other.current_;
        }

        value_type operator*() const {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            return *current_;
        }

        value_type* operator->() const noexcept {
            return current_;
        }

        const va_iterator& operator++() {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            ++current_;
            return *this;
        }

        const va_iterator operator++(int) {
            va_iterator old_value = *this;
            ++current_;
            return old_value;
        }

        va_iterator& operator--() {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            --current_;
            return *this;
        }

        va_iterator operator--(int) {
            value_type old_value(*this);
            --current_;
            return old_value;
        }

        va_iterator& operator+=(const int index) {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            current_ += index;
            return *this;
        }

        va_iterator& operator-=(const int index) {
            if (!current_) {
                throw atom::otherError(FUNC_AND_LINE, "Is null");
            }

            current_ -= index;
            return *this;
        }

        void swap(va_iterator& other) noexcept {
            //value_type* tmp = current_;
            //current_ = other.current_;
            //other.current_ = tmp;
            //
            //std::swap<value_type*>(current_, other.current_);
            //
            std::swap(current_, other.current_);
        }

        template<typename Tp>
        friend bool operator!=(const va_iterator<Tp>& lhs,
                               const va_iterator<Tp>& rhs);

        template<typename Tp>
        friend bool operator==(const va_iterator<Tp>& lhs,
                               const va_iterator<Tp>& rhs);

        template<typename Tp>
        friend va_iterator<Tp> operator-(const va_iterator<Tp>& lhs,
                                         const int index);

        template<typename Tp>
        friend va_iterator<Tp> operator+(const va_iterator<Tp>& lhs,
                                         const int index);

    private:

        value_type* current_;
    };


    template<typename Tp>
    bool operator!=(const va_iterator<Tp>& lhs,
                    const va_iterator<Tp>& rhs) {

        return lhs.current_ != rhs.current_;
    }

    template<typename Tp>
    bool operator==(const va_iterator<Tp>& lhs,
                    const va_iterator<Tp>& rhs) {

        return lhs.current_ == rhs.current_;
    }

    template<typename Tp>
    va_iterator<Tp>& operator-(const va_iterator<Tp>& lhs,
                               const int index) {

        if (!lhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Is null");
        }

        return va_iterator(lhs.current_ - index);
    }

    template<typename Tp>
    va_iterator<Tp>& operator+(const va_iterator<Tp>& lhs,
                               const int index) {

        if (!lhs.current_) {
            throw atom::otherError(FUNC_AND_LINE, "Is null");
        }

        return va_iterator(lhs.current_ + index);
    }

}
#endif //ATOM_VA_ITERATOR_H
