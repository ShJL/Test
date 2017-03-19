//-----------------------------------------------------------------------------
//! @file exceptions.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Set of the exceptions
//!
//!
//! @version 1.0
//!
//! @author ShJ
//! @date   04.03.2017
//-----------------------------------------------------------------------------
#ifndef ATOM_EXCEPTIONS_H
#define ATOM_EXCEPTIONS_H 1

#include <string>

//-----------------------------------------------------------------------------
//! @def _FUNCTION_
//! @brief Function name for GNU or MVSC
//-----------------------------------------------------------------------------
#ifdef __GNUC__
    #define _FUNCTION_ __PRETTY_FUNCTION__
#elif _MSC_VER
    #define _FUNCTION_ __FUNCSIG__
#endif

//-----------------------------------------------------------------------------
//! @def FUNC_AND_LINE
//! @brief Replace macro function name and line numbers to substitute into the function
//-----------------------------------------------------------------------------
#ifdef __GNUC__
    #define FUNC_AND_LINE _FUNCTION_, __LINE__
#endif

//-----------------------------------------------------------------------------
//! @namespace atom
//! @brief Common namespace
//-----------------------------------------------------------------------------
namespace atom {

    //-----------------------------------------------------------------------------
    //! @class error
    //! @brief Abstract class which is template for all exceptions
    //! @details Have three members: function_, line_, message_
    //! @details which discribe place where was generate exception and give message about it
    //-----------------------------------------------------------------------------
    class error {
    public:

        using const_string_type = const std::string; //!< Const string type

        //-----------------------------------------------------------------------------
        //! @breif Constructor
        //! @param func Name of the function which generate exception
        //! @param line Number of the line
        //! @param msg Additional messange about error
        //-----------------------------------------------------------------------------
        error(const_string_type& func = "",
              const int          line = 0,
              const_string_type& msg  = "") :
            line_    (line),
            function_(func),
            message_ (msg) {
        }

        //-----------------------------------------------------------------------------
        //! @breif Return name caused function
        //! @retunr const std::string - name function
        //-----------------------------------------------------------------------------
        const_string_type func() const {
            return function_;
        }

        //-----------------------------------------------------------------------------
        //! @breif Return number line where was exception
        //! @return number of the line
        //-----------------------------------------------------------------------------
        int line() const {
            return line_;
        }

        //-----------------------------------------------------------------------------
        //! @breif Message about error
        //! @return const std::string - message
        //-----------------------------------------------------------------------------
        const_string_type what() const {
            return message_;
        }

        //-----------------------------------------------------------------------------
        //! @breif Pure virtual destructor
        //! @details With the aim of abstraction of the class
        //-----------------------------------------------------------------------------
        virtual ~error() = 0;

    private:

        const int         line_;     //!< Number of the line
        const_string_type function_; //!< Name of the function which generate exception
        const_string_type message_;  //!< Additional messange about error
    };

    error::~error() {
    }

    //-----------------------------------------------------------------------------
    //! @class badAlloc
    //! @brief Exception about problems with allocate of the memory
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class badAlloc: public error {
    public:

        badAlloc(const_string_type& func = "",
                 const int          line = 0,
                 const_string_type& msg  = "") :
            error(func, line, msg) {
        }
    };

    //-----------------------------------------------------------------------------
    //! @class outOfRange
    //! @brief Exception about problems connected with borders
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class outOfRange: public error {
    public:

        outOfRange(const_string_type& func = "",
                   const int          line = 0,
                   const_string_type& msg  = "") :
            error(func, line, msg) {
        }
    };

    //-----------------------------------------------------------------------------
    //! @class invalidArgument
    //! @brief Exception about problems with arguments in functions
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class invalidArgument: public error {
    public:

        invalidArgument(const_string_type& func = "",
                        const int          line = 0,
                        const_string_type& msg  = "") :
            error(func, line, msg) {
        }
    };

    //-----------------------------------------------------------------------------
    //! @class invalidObject
    //! @brief Exception about problems with object different classes
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class invalidObject: public error {
    public:

        invalidObject(const_string_type& func = "",
                      const int          line = 0,
                      const_string_type& msg  = "") :
            error(func, line, msg) {
        }
    };

    //-----------------------------------------------------------------------------
    //! @class otherError
    //! @brief Undefine here exceptions
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class otherError: public error {
    public:

        otherError(const_string_type& func = "",
                   const int          line = 0,
                   const_string_type& msg  = "") :
            error(func, line, msg) {
        }
    };

}

#endif // ATOM_EXCEPTIONS_H
