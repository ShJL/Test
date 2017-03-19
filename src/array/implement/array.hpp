#ifndef ATOM_ARRAY_HPP
#define ATOM_ARRAY_HPP 1

#include <fstream>
#include "debug_tools.h"


namespace atom {

    template<typename Tp, std::size_t max_size_>
    void array_t<Tp, max_size_>::dump(const char* function_name,
                                      int         line_number) const {

        std::ofstream fout("__array_dump.txt", std::ios_base::app);

        if (fout.is_open()) {
            fout << "-------------------\n"
                    "Class array_t:\n"
                    "time: "           << __TIME__      << "\n"
                    "function: "       << function_name << "\n"
                    "line: "           << line_number   << "\n"
                    "status: "         << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tsize: "         << size_         << "\n"
                    "\tcapacity: "     << max_size_     << "\n"
                    "\tstatus_valid: " << (status_valid_ ? "ok\n\n" : "fail\n\n");

#ifndef ATOM_NWRITE
            for (size_type i = 0; i < size_; ++i) {
                fout << "\t* [" << i << "] =  " << data_[i] << "\n";
            }
            for (size_type i = size_; i < max_size_; ++i) {
                fout << "\t  [" << i << "] =  " << data_[i]
                     << (data_[i] != POISON<value_type>::value ? "\t//ERROR!\n" : "\n");
            }
#endif
            fout << "}\n"
                    "-------------------\n";

            fout.close();
        }
    }
}

#endif // ATOM_ARRAY_HPP
