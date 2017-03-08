#ifndef ATOM_VECTOR_HPP
#define ATOM_VECTOR_HPP 1

#include <algorithm>
#include <fstream>
#include <memory.h>
#include "exceptions.h"
#include "debug_tools.h"


namespace atom {

    template<typename Tp>
    void vector_t<Tp>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        std::copy(data_, data_ + new_size, tmp_buffer);

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<short>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<int>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<unsigned short>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<unsigned int>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<char>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<unsigned char>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<float>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<double>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<long long>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<>
    void vector_t<unsigned long long>::shrink_alloc(const size_type n) {
        const size_type new_capacity = n;
        const size_type new_size     = std::min(n, size_);

        value_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new value_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FUNC_AND_LINE);
        }

        memcpy(tmp_buffer, data_, new_size * sizeof(value_type));

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = new_capacity;
        size_     = new_size;

#ifndef ATOM_NDEBUG
        std::fill(data_ + size_, data_ + capacity_, POISON<value_type>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    template<typename Tp>
    vector_t<Tp>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        std::copy(that.data_, that.data_ + that.size_, data_);
        size_ = that.size_;
    }

    template<>
    vector_t<short>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<int>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<long long>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<unsigned short>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<unsigned int>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<unsigned long long>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<char>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<unsigned char>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<float>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<>
    vector_t<double>::vector_t(const vector_t& that) :
        status_   (true),
        size_     (0),
        capacity_ (0),
        data_     (nullptr) {

        try {
            shrink_alloc(that.size_);
        }
        catch (...) {
            status_ = false;
            throw;
        }

        memcpy(data_, that.data_, that.size_ * sizeof(value_type));
        size_ = that.size_;
    }

    template<typename Tp>
    void vector_t<Tp>::resize(const size_type n, const value_type& value) {
        ATOM_ASSERT_VALID(this);

        const size_type new_size = n;

        shrink_alloc(new_size);

        std::fill(data_ + size_, data_ + new_size, value);
        size_ = new_size;

        ATOM_ASSERT_VALID(this);
    }

    template<typename Tp>
    void vector_t<Tp>::alloc(const size_type n) {
        ATOM_ASSERT_VALID(this);

        if (n <= capacity_) {
            return;
        }

        size_type new_capacity = std::max(capacity_, static_cast<size_type>(1));

        while (new_capacity < n) {
            new_capacity *= MEMORY_MULTIPLIER_;
        }

        shrink_alloc(new_capacity);

        ATOM_ASSERT_VALID(this);
    }

    template<typename Tp>
    void vector_t<Tp>::dump(const char* function_name,
                            int         line_number) const {

        std::ofstream fout("__vector_dump.txt", std::ios_base::app);

        if (fout.is_open()) {
            fout << "-------------------\n"
                    "Class vector_t:\n"
                    "time: "         << __TIME__      << "\n"
                    "function: "     << function_name << "\n"
                    "line: "         << line_number   << "\n"
                    "status: "       << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tsize: "       << size_         << "\n"
                    "\tcapacity: "   << capacity_     << "\n\n";

#ifndef ATOM_NWRITE
            for (size_type i = 0; i < size_; ++i) {
                fout << "\t* [" << i << "] =  " << data_[i] << "\n";
            }
            for (size_type i = size_; i < capacity_; ++i) {
                fout << "\t  [" << i << "] =  " << data_[i]
                     << (data_[i] != POISON<value_type>::value ? "  //ERROR!\n" : "\n");
            }
#endif
            fout << "}\n"
                    "-------------------\n";

            fout.close();
        }
    }

}

#endif // ATOM_VECTOR_HPP
