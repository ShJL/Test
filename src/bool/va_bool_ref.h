#ifndef ATOM_VA_BOOL_REF_H
#define ATOM_VA_BOOL_REF_H

#include "bool_space.h"
#include "debug_tools.h"
#include "exceptions.h"


namespace atom {

    template<class Tp>
    class va_reference {
    public:

        using size_type = typename Tp::size_type;
        using pointer   = typename Tp::pointer;

        va_reference() = delete;

        va_reference(pointer ptr,
                  const size_type pos) :
            current_ (ptr),
            position_(pos) {
        }

        ~va_reference() {
#ifndef ATOM_NDEBUG
            current_ = nullptr;
            position_ = POISON<size_type>::value;
#endif
        }

        const va_reference& operator=(const bool x) {
            set_bit(x);
            return *this;
        }

        const va_reference& operator=(const va_reference& that) {
            if (this != &that) {
                set_bit(that);
            }
            return *this;
        }

        operator bool() const {
            ATOM_OTHER_ERROR(!current_, "Is null");

            return get_n_bit(*current_, position_);
        }

    private:

        pointer   current_;
        size_type position_;

        void set_bit(bool value) {
            if (value) {
                *current_ |= ONE << position_;
            }
            else {
                *current_ &= ~(ONE << position_);
            }
        }

    };

}

#endif // ATOM_VA_BOOL_REF_H
