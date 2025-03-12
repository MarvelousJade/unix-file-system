#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include <string>

namespace seneca {

class Filesystem {
    Directory* m_root;
    Directory* m_current;

    // Helper: trim leading and trailing spaces from a string
    std::string trim(const std::string& str);

    // Helper: split a string by a given delimiter
    std::vector<std::string> split(const std::string& s, char delimiter);
public:
    explicit Filesystem(const std::string& filename, const std::string& rootname = ""); 
    // Delete copy operations
    Filesystem(const Filesystem&) = delete;
    Filesystem& operator=(const Filesystem&) = delete;

    // Allow move operations
    Filesystem(Filesystem&&) = default;
    Filesystem& operator=(Filesystem&&) = default;

    Filesystem& operator+=(Resource* res);

    Directory* change_directory(const std::string& dirname = "");

    Directory* get_current_directory() const;

    ~Filesystem();
};

}

#endif
