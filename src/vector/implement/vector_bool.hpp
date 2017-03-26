#ifndef ATOM_VECTOR_BOOL_HPP
#define ATOM_VECTOR_BOOL_HPP 1

#include <fstream>
#include <memory.h>
#include "bool/bool_space.h"
#include "exceptions.h"
#include "debug_tools.h"
#include <iostream>

namespace atom {

    void vector_t<bool>::shrink_alloc(const size_type n_bit) {
        const size_type new_capacity = bit_to_block(n_bit);
        const size_type new_size     = std::min(n_bit, size_);

        bit_container_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new bit_container_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw atom::badAlloc(FULL_COORDINATES_FFL);
        }

        copy_bits(tmp_buffer, data_, new_size, BIT_BLOCK_SIZE);

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = block_to_bit(new_capacity);
        size_     = new_size;

#ifndef ATOM_NDEBUG
        fill_n_bit(size_, capacity_ - size_, POISON<bool>::value);
#endif

        ATOM_ASSERT_VALID(this);
    }

    vector_t<bool>::vector_t(const vector_t& that) :
        size_         (0),
        capacity_     (0),
        data_         (nullptr),
        status_valid_ (1) {

#ifndef ATOM_NDEBUG
        try {
#endif
            shrink_alloc(that.size_);
#ifndef ATOM_NDEBUG
        }
        catch (...) {
            status_valid_ = 0;
            throw;
        }
#endif

        copy_bits(data_, that.data_, that.size_, BIT_BLOCK_SIZE);

        size_ = that.size_;

        ATOM_ASSERT_VALID(this);
    }

    void vector_t<bool>::resize(const size_type n, const bool value) {
        ATOM_ASSERT_VALID(this);

        const size_type new_size = n;

        shrink_alloc(new_size);

        if (new_size > size_) {
            fill_n_bit(size_, new_size - size_, value);
        }
		
        size_ = new_size;

        ATOM_ASSERT_VALID(this);
    }

    void vector_t<bool>::alloc(const size_type n) {
        ATOM_ASSERT_VALID(this);

        if (n <= capacity_) {
            return;
        }

        size_type new_capacity = std::max(bit_to_block(capacity_), static_cast<size_type>(1));

        size_type need_capacity = bit_to_block(n);
        while (new_capacity < need_capacity) {
            new_capacity *= MEMORY_MULTIPLIER_;
        }

        shrink_alloc(block_to_bit(new_capacity));

        ATOM_ASSERT_VALID(this);
    }

    void vector_t<bool>::fill_n_bit(const size_type begin,
                                    const size_type n,
                                    const bool      value) {

        ATOM_ASSERT_VALID(this);

        ATOM_OUT_OF_RANGE(begin + n > capacity_);

        size_type       it  = begin;
        const size_type end = begin + n;

        while (it % BIT_BLOCK_SIZE && it != end) {
            set_bit(it, value);
            ++it;
        }
        while (it + BIT_BLOCK_SIZE <= end) {
            data_[n_block(it)] = value ? ~0 : 0;
            it += BIT_BLOCK_SIZE;
        }
        for (; it < end; ++it) {
            set_bit(it, value);
        }

        ATOM_ASSERT_VALID(this);
    }

    bool vector_t<bool>::erase(const size_type pos) {
        ATOM_ASSERT_VALID(this);

        if (pos >= size_) {
            return false;
        }

        size_type it = pos;
        --size_;

        while (it % BIT_BLOCK_SIZE && it != size_) {
            set_bit(it, get_bit(it + 1));
            ++it;
        }
        while (it + BIT_BLOCK_SIZE <= size_) {
            data_[n_block(it)] >>= 1;
            it += BIT_BLOCK_SIZE;
        }
        for (; it < size_; ++it) {
            set_bit(it, get_bit(it + 1));
        }

#ifndef ATOM_NDEBUG
        set_bit(size_, POISON<bool>::value);
#endif
        ATOM_ASSERT_VALID(this);
        return true;
    }


    vector_t<bool>::size_type
    vector_t<bool>::count() const {
        ATOM_ASSERT_VALID(this);

        size_type result       = 0;
        size_type count_blocks = size_ / BIT_BLOCK_SIZE;

        for (size_type i = 0; i < count_blocks; ++i) {
            bit_container_type copy_block = data_[i];
            while (copy_block) {
                result += last_bit(copy_block);
                copy_block >>= 1;
            }
        }
        if (data_) {
            bit_container_type copy_block = data_[count_blocks];
            for (size_type i = block_to_bit(count_blocks); i < size_; ++i) {
                result += last_bit(copy_block);
                copy_block >>= 1;
            }
        }

        return result;
    }

    void vector_t<bool>::invert() {
        ATOM_ASSERT_VALID(this);

        const size_type count_blocks = size_ / BIT_BLOCK_SIZE;

        for (size_type i = 0; i < count_blocks; ++i) {
            data_[i] = ~data_[i];
        }

        const size_type remain_bits      = size_ % BIT_BLOCK_SIZE;
        const size_type first_remaim_bit = block_to_bit(count_blocks);

        for (size_type i = 0; i < remain_bits; ++i) {
            flip(first_remaim_bit + i);
        }

        ATOM_ASSERT_VALID(this);
    }

    void vector_t<bool>::dump(const char* file,
                              const char* function_name,
                              int         line_number,
                              const char* output_file) const {

        std::ofstream fout(output_file, std::ios_base::app);

        ATOM_BAD_STREAM(!fout.is_open());

        fout << "-------------------\n"
                "Class vector_t:\n"
                "time: "           << __TIME__      << "\n"
                "file: "           << file          << "\n"
                "function: "       << function_name << "\n"
                "line: "           << line_number   << "\n"
                "status: "         << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
        fout << "\tsize: "         << size_         << "\n"
                "\tcapacity: "     << capacity_     << "\n"
                "\tfield_status: " << (status_valid_ ? "ok\n\n" : "fail\n\n");

#ifndef ATOM_NWRITE
        try {
            for (size_type i = 0; i < size_; ++i) {
                fout << "\t* [" << i << "] =  " << get_bit_dump_version(i) << "\n";
            }
            for (size_type i = size_; i < capacity_; ++i) {
                fout << "\t  [" << i << "] =  " << get_bit_dump_version(i)
                     << (get_bit_dump_version(i) != POISON<bool>::value ? "\t//ERROR!\n" : "\n");
            }
        }
        catch (...) {
            fout << "ERROR with output\n";
        }
#endif
        fout << "}\n"
                "-------------------\n";

        fout.close();
    }

}

#endif // ATOM_VECTOR_BOOL_HPP
