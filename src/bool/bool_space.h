#ifndef ATOM_BOOL_SPACE_H
#define ATOM_BOOL_SPACE_H

#include <cmath>


namespace atom {

    using bit_container_type = unsigned long long;

    const std::size_t        BIT_IN_BYTE    = 8;
    constexpr std::size_t    BIT_BLOCK_SIZE = sizeof(bit_container_type) * BIT_IN_BYTE;
    const bit_container_type ONE            = 1;


    inline constexpr std::size_t div_ceil(const std::size_t dividend,
                                          const std::size_t divider) {

        return std::ceil(static_cast<double>(dividend) / divider);
    }

    template<typename Tp>
    inline bool last_bit(const Tp x) {
        return x & 1;
    }

    template<typename Tp>
    inline bool get_n_bit(const Tp x,
                          const std::size_t n) {

        return last_bit(x >> n);
    }

    template<typename Tp>
    void copy_bits(Tp* dst,
                   Tp* src,
                   const std::size_t size,
                   const std::size_t bit_block_size = sizeof(Tp) * BIT_IN_BYTE) {

        const std::size_t count_full_blocks = size / bit_block_size;

        memcpy(dst, src, count_full_blocks * sizeof(Tp));

        const std::size_t end = size % bit_block_size;

        for (std::size_t i = 0; i < end; ++i) {
            if (get_n_bit(src[count_full_blocks], i)) {
                dst[count_full_blocks] |= static_cast<Tp>(1) << i;
            }
            else {
                dst[count_full_blocks] &= ~(static_cast<Tp>(1) << i);
            }
        }
    }

}

#endif // ATOM_BOOL_SPACE_H
