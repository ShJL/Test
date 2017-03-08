#ifndef ATOM_STACK_HPP
#define ATOM_STACK_HPP 1

#include <fstream>


namespace atom {

    template<typename Tp, typename Container>
    void stack_t<Tp, Container>::dump(const char* function_name,
                                              int         line_number) const noexcept {

        std::ofstream fout("__stack_dump.txt", std::ios_base::app);

        if (fout.is_open()) {
            const size_type top      = data_.size();
            const size_type capacity = data_.capacity();

            fout << "-------------------\n"
                    "Class stack_t:\n"
                    "time: "         << __TIME__      <<
                    "function: "     << function_name << "\n"
                    "line: "         << line_number   << "\n"
                    "satus: "        << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
            fout << "\tcapacity: "   << capacity      << "\n"
                    "\ttop: "        << top           << "\n\n";

#ifndef ATOM_NWRITE
            const value_type poison = value_type();

            for (size_type i = 0; i < top; ++i) {
                fout << "\t* [" << i << "] =  " << data_[i] << "\n";
            }
            for (size_type i = top; i < capacity; ++i) {
                fout << "\t  [" << i << "] =  " << data_[i]
                     << (data_[i] != poison ? "  //ERROR!\n" : "\n");
            }
#endif

            fout << "}\n";

            fout.close();
        }
    }

}

#endif // ATOM_STACK_HPP
