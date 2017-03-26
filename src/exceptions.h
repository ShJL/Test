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
#include <stdexcept>

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
//! @def FULL_COORDINATES_FFL
//! @brief Replace macro function name and line numbers to substitute into the function
//-----------------------------------------------------------------------------
#ifdef __GNUC__
    #define FULL_COORDINATES_FFL __FILE__, _FUNCTION_, __LINE__
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
    class error : public std::exception {
    public:

        using const_string_type = const std::string; //!< Const string type
        using exception         = std::exception;    //!< Rename std::exception

        //-----------------------------------------------------------------------------
        //! @breif Constructor
        //! @param func Name of the function which generate exception
        //! @param line Number of the line
        //! @param msg Additional messange about error
        //-----------------------------------------------------------------------------
        error(const_string_type& file   = "",
              const_string_type& func   = "",
              const int          line   = 0,
              const_string_type& msg    = "",
              error*             parent = nullptr) :
            line_    (line),
            function_(func),
            filename_(file),
            message_ (msg),
            parent_  (parent){
        }

        //-----------------------------------------------------------------------------
        //! @breif Clone object
        //! @return Pointer on clone object
        //-----------------------------------------------------------------------------
        virtual error* clone() const = 0;

        //-----------------------------------------------------------------------------
        //! @breif Return name of the file
        //! @retunr const std::string - name file
        //-----------------------------------------------------------------------------
        const_string_type& file() const {
            return filename_;
        }

        //-----------------------------------------------------------------------------
        //! @breif Return name caused function
        //! @retunr const std::string - name function
        //-----------------------------------------------------------------------------
        const_string_type& func() const {
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
        //! @breif Preventive exception
        //! @return Reference on the preventive exception
        //-----------------------------------------------------------------------------
        error& parent() const {
            return *parent_;
        }

        //-----------------------------------------------------------------------------
        //! @breif Message about error
        //! @return const char* - message
        //-----------------------------------------------------------------------------
        const char* what() const noexcept override {
            return message_.data();
        }

        //-----------------------------------------------------------------------------
        //! @breif Virtual destructor
        //-----------------------------------------------------------------------------
        virtual ~error() {
            delete parent_;
        }

    private:

        const int         line_;     //!< Number of the line
        const_string_type function_; //!< Name of the function which generated exception
        const_string_type filename_; //!< Name of the file where generated exception
        const_string_type message_;  //!< Additional messange about error
        error*            parent_;   //!< Pointer on the preventive exception
    };

    //-----------------------------------------------------------------------------
    //! @class badAlloc
    //! @brief Exception about problems with allocate of the memory
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class badAlloc: public error {
    public:

        badAlloc(const_string_type& file   = "",
                 const_string_type& func   = "",
                 const int          line   = 0,
                 const_string_type& msg    = "",
                 error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        badAlloc* clone() const final {
            return new badAlloc(*this);
        }
    };

    //-----------------------------------------------------------------------------
    //! @class outOfRange
    //! @brief Exception about problems connected with borders
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class outOfRange: public error {
    public:

        outOfRange(const_string_type& file   = "",
                   const_string_type& func   = "",
                   const int          line   = 0,
                   const_string_type& msg    = "",
                   error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        outOfRange* clone() const final {
            return new outOfRange(*this);
        }
    };

    //-----------------------------------------------------------------------------
    //! @class invalidArgument
    //! @brief Exception about problems with arguments in functions
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class invalidArgument: public error {
    public:

        invalidArgument(const_string_type& file   = "",
                        const_string_type& func   = "",
                        const int          line   = 0,
                        const_string_type& msg    = "",
                        error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        invalidArgument* clone() const final {
            return new invalidArgument(*this);
        }
    };

    //-----------------------------------------------------------------------------
    //! @class invalidObject
    //! @brief Exception about problems with object different classes
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class invalidObject: public error {
    public:

        invalidObject(const_string_type& file   = "",
                      const_string_type& func   = "",
                      const int          line   = 0,
                      const_string_type& msg    = "",
                      error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        invalidObject* clone() const final {
            return new invalidObject(*this);
        }
    };

    //-----------------------------------------------------------------------------
    //! @class badStream
    //! @brief Problem with stream
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class badStream: public error {
    public:

        badStream(const_string_type& file   = "",
                  const_string_type& func   = "",
                  const int          line   = 0,
                  const_string_type& msg    = "",
                  error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        badStream* clone() const final {
            return new badStream(*this);
        }
    };

    //-----------------------------------------------------------------------------
    //! @class otherError
    //! @brief Undefine here exceptions
    //! @details Derived from class error
    //-----------------------------------------------------------------------------
    class otherError: public error {
    public:

        otherError(const_string_type& file   = "",
                   const_string_type& func   = "",
                   const int          line   = 0,
                   const_string_type& msg    = "",
                   error*             parent = nullptr) :
            error(file, func, line, msg, parent) {
        }

        otherError* clone() const final {
            return new otherError(*this);
        }
    };

}

#define ATOM_OUT_OF_RANGE(condition) {\
    if ((condition)) {\
        throw atom::outOfRange(FULL_COORDINATES_FFL);\
    }\
}

#define ATOM_BAD_ALLOC(condition) {\
    if ((condition)) {\
        throw atom::badAlloc(FULL_COORDINATES_FFL);\
    }\
}

#define ATOM_INVALID_ARGUMENT(condition) {\
    if ((condition)) {\
        throw atom::invalidArgument(FULL_COORDINATES_FFL);\
    }\
}

#define ATOM_INVALID_OBJECT(condition) {\
    if ((condition)) {\
        throw atom::invalidObject(FULL_COORDINATES_FFL);\
    }\
}

#define ATOM_BAD_STREAM(condition) {\
    if ((condition)) {\
        throw atom::badStream(FULL_COORDINATES_FFL);\
    }\
}

#define ATOM_OTHER_ERROR(condition, mesg) {\
    if ((condition)) {\
        throw atom::otherError(FULL_COORDINATES_FFL, (mesg));\
    }\
}

#endif // ATOM_EXCEPTIONS_H
