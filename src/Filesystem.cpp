#include "Filesystem.h"
#include "File.h"  // for creating File objects
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace seneca {

// Helper: trim leading and trailing spaces
std::string Filesystem::trim(const std::string& str) {
    const std::string whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

// Helper: split a string by a delimiter
std::vector<std::string> Filesystem::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        token = trim(token);
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

Filesystem::Filesystem(const std::string& filename, const std::string& rootName) {
    // If no root name is provided, default to "/"
    std::string effectiveRootName = rootName.empty() ? "/" : rootName;
    m_root = new Directory(effectiveRootName);
    m_current = m_root;

    // Open the file containing the filesystem description.
    std::ifstream file(filename);
    if (!file)
        throw std::invalid_argument("Invalid file name: " + filename);

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty())
            continue;

        // Check if the line defines a file (contains '|') or a directory.
        size_t sepPos = line.find('|');
        std::string pathStr, content;
        bool isFile = (sepPos != std::string::npos);
        if (isFile) {
            // Split into path and file contents.
            pathStr = trim(line.substr(0, sepPos));
            content = trim(line.substr(sepPos + 1));
        } else {
            pathStr = line;  // It's a directory resource
        }

        // Split the path into components using '/' as delimiter.
        std::vector<std::string> components = split(pathStr, '/');
        Directory* currDir = m_root;
        // Process all components except the last if it's a file resource.
        // For a directory resource, process all components.
        size_t limit = isFile ? components.size() - 1 : components.size();

        for (size_t i = 0; i < limit; ++i) {
            // Ensure directory names end with '/'
            std::string dirName = components[i];
            if (dirName.back() != '/')
                dirName.push_back('/');

            // Use find() to see if this subdirectory already exists.
            Resource* found = currDir->find(dirName);
            Directory* subDir = nullptr;
            if (found && found->type() == NodeType::DIR)
                subDir = dynamic_cast<Directory*>(found);
            else {
                // Not found; create a new Directory.
                subDir = new Directory(dirName);
                *currDir += subDir;
            }
            currDir = subDir;
        }

        if (isFile) {
            // For file resource, the last component is the file name.
            std::string fileName = components.back();
            // Create the file and add it to the current directory.
            Resource* newFile = new seneca::File(fileName, content);
            *currDir += newFile;
        } else {
            // For a directory resource, ensure the last component is created.
            std::string dirName = components.back();
            if (dirName.back() != '/')
                dirName.push_back('/');
            Resource* found = currDir->find(dirName);
            if (!found) {
                Directory* newDir = new Directory(dirName);
                *currDir += newDir;
            }
        }
    }
    file.close();
}

Filesystem& Filesystem::operator+=(Resource* res) {
    *m_current += res;
    return *this;
}

Directory* Filesystem::change_directory(const std::string& dirname) {
    if (dirname.empty()) {
        m_current = m_root;
        return m_current;
    }

    // Look for a resource with the specified name in the current directory.
    Resource* found = m_current->find(dirname);
    Directory* dirFound = dynamic_cast<Directory*>(found);
    if (!dirFound)
        throw std::invalid_argument("Cannot change directory! " + dirname + " not found!");
    m_current = dirFound;
    return m_current;
}

Directory* Filesystem::get_current_directory() const {
    return m_current;
}

Filesystem::~Filesystem() {
    delete m_root;
}

} 
