#ifndef ATOM_ARRAY_BOOL_HPP
#define ATOM_ARRAY_BOOL_HPP

#include <fstream>
#include "debug_tools.h"
#include "exceptions.h"
#include "bool/bool_space.h"

namespace atom {

    template<const std::size_t max_size_>
    typename array_t<bool, max_size_>::size_type
    array_t<bool, max_size_>::count() const {
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
        bit_container_type copy_block = data_[count_blocks];
        for (size_type i = block_to_bit(count_blocks); i < size_; ++i) {
            result += last_bit(copy_block);
            copy_block >>= 1;
        }

        return result;
    }

    template<const std::size_t max_size_>
    void array_t<bool, max_size_>::invert() {
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

    template<const std::size_t max_size_>
    void array_t<bool, max_size_>::fill_n_bit(const size_type begin,
                                              const size_type n,
                                              const bool      value) {

        ATOM_ASSERT_VALID(this);

        ATOM_OUT_OF_RANGE(begin + n > max_size_);

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
        while (it < end) {
            set_bit(it, value);
            ++it;
        }

        ATOM_ASSERT_VALID(this);
    }

    template<const std::size_t max_size_>
    bool array_t<bool, max_size_>::erase(const size_type pos) {
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

    template<const std::size_t max_size_>
    void array_t<bool, max_size_>::dump(const char* file,
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
                "\tcapacity: "     << max_size_     << "\n"
                "\tfield_status: " << (status_valid_ ? "ok\n\n" : "fail\n\n");

#ifndef ATOM_NWRITE
        try {
            for (size_type i = 0; i < size_; ++i) {
                fout << "\t* [" << i << "] =  " << get_bit_dump_version(i) << "\n";
            }
            for (size_type i = size_; i < max_size_; ++i) {
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

#endif // ATOM_ARRAY_BOOL_HPP
