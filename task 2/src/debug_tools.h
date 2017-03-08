//-----------------------------------------------------------------------------
//! @file debug_tools.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Macros and other tools for debug
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   06.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_DEBUG_TOOLS_H
#define ATOM_DEBUG_TOOLS_H 1

#include "exceptions.h"
#include <cassert>

//-----------------------------------------------------------------------------
//! @def ATOM_ASSERT_VALID() Macro to test object integrity
//! @details Takes a pointer to an object that have functions: is_valid() and dump()
//! @details ATOM_ASSERT_VALID() us if do not exist macro ATOM_NDEBUG, otherwise { }
//! @throw atom::invalidObject Object is not valid
//-----------------------------------------------------------------------------
#ifndef ATOM_NDEBUG
#define ATOM_ASSERT_VALID(p_elem) {\
    if (!((p_elem)->is_valid())) {\
        (p_elem)->dump(FUNC_AND_LINE);\
        assert(!"Object is good");\
        throw atom::invalidObject(FUNC_AND_LINE, __FILE__);\
    }\
}
#else
#define ATOM_ASSERT_VALID(elem) { }
#endif

//-----------------------------------------------------------------------------
//! @struct POISON
//! @tparam Tp The type of data used
//! @brief Poison constant for any elements
//-----------------------------------------------------------------------------
template<typename Tp>
struct POISON {
    static const Tp value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for short elements
//-----------------------------------------------------------------------------
template<>
struct POISON<short> {
    static const short value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for unsigned short elements
//-----------------------------------------------------------------------------
template<>
struct POISON<unsigned short> {
    static const unsigned short value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for int elements
//-----------------------------------------------------------------------------
template<>
struct POISON<int> {
    static const int value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for unsigned int elements
//-----------------------------------------------------------------------------
template<>
struct POISON<unsigned int> {
    static const unsigned int value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for float elements
//-----------------------------------------------------------------------------
template<>
struct POISON<float> {
    static const float value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for double elements
//-----------------------------------------------------------------------------
template<>
struct POISON<double> {
    static const double value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for char elements
//-----------------------------------------------------------------------------
template<>
struct POISON<char> {
    static const char value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for unsigned char elements
//-----------------------------------------------------------------------------
template<>
struct POISON<unsigned char> {
    static const unsigned char value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for long long elements
//-----------------------------------------------------------------------------
template<>
struct POISON<long long> {
    static const long long value;
};

//-----------------------------------------------------------------------------
//! @struct POISON
//! @brief Poison constant for unsigned long long elements
//-----------------------------------------------------------------------------
template<>
struct POISON<unsigned long long> {
    static const unsigned long long value;
};

//-----------------------------------------------------------------------------
//! @brief List of all poisons
//! @{
template<typename Tp>
const Tp                 POISON<Tp>::value                 = Tp();
const short              POISON<short>::value              = -121;
const unsigned short     POISON<unsigned short>::value     = 121;
const int                POISON<int>::value                = -8631004;
const unsigned int       POISON<unsigned int>::value       = 8631004u;
const float              POISON<float>::value              = -722004.5482f;
const double             POISON<double>::value             = 2588511426E-7;
const char               POISON<char>::value               = static_cast<char>(-12);
const unsigned char      POISON<unsigned char>::value      = static_cast<unsigned char>(12);
const long long          POISON<long long>::value          = -147520069954LL;
const unsigned long long POISON<unsigned long long>::value = 147520069954ULL;
//! @}
//------------------------------------------------------------------------------

#endif // ATOM_DEBUG_TOOLS_H
