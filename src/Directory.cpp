#include "Directory.h"
#include "Flags.h"
#include <cstddef>
#include <iomanip>
#include <stdexcept>
namespace seneca {
    Directory::Directory(const std::string& name) {
        if (name.empty())
            throw std::invalid_argument("Directory name cannot be empty.");
        if (name.back() != '/')
            m_name = name + "/";
        else
            m_name = name;
        // Default parent path for a newly created directory is root.
        m_parent_path = "/";
    };

    Directory::~Directory() {
        // Deallocate each resource stored in the directory.
        for (auto res : m_contents) {
            delete res;
        }
        m_contents.clear();
    }

    void Directory::update_parent_path(const std::string& new_parent_path) {
        m_parent_path = new_parent_path;

        std::string fullPath = path();
        for (auto res : m_contents) {
            res->update_parent_path(fullPath);
        };
    };

    NodeType Directory::type() const {
        return NodeType::DIR;
    };

    std::string Directory::path() const {
        if (!m_parent_path.empty() && m_parent_path.back() == '/') 
            return m_parent_path + m_name;
        else
            return m_parent_path + '/' + m_name;
    };

    std::string Directory::name() const {
        return m_name;
    };

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    };

    size_t Directory::size() const {
        size_t total = 0u;
        for (auto res : m_contents) {
            total += res->size();   
        };
        return total;
    };

    Directory& Directory::operator+=(Resource* res) {
        for (auto existing : m_contents) {
            if (existing->name() == res->name()) throw std::invalid_argument("Resource with name '" + existing->name() + "already exists.");
        };

        res->update_parent_path(m_parent_path);
        m_contents.push_back(res);
        return *this;
    };

    Resource* Directory::find(const std::string& target, const std::vector<OpFlags>& flags) {
        bool recursive = (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end());  

            for (auto res : m_contents) {
                if (res->name() == target) return res;

                if (recursive && res->type() == NodeType::DIR) {
                    Directory* subdir = dynamic_cast<Directory*>(res);
                    if (subdir) {
                        Resource* found = subdir->find(target, flags);
                        if (found != nullptr) return found; 
                    };
                }; 
            };
        return nullptr;
    };

    void Directory::remove(const std::string& target, const std::vector<OpFlags>& flags) {
        bool recursive = (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end());  

        for (auto it = m_contents.begin(); it != m_contents.end(); ++it) {
            if ((*it)->name() == target) {
                 if ((*it)->type() == NodeType::DIR && !recursive) {
                     throw std::invalid_argument(target + " is a directory.");
                 };
                 delete (*it);
                 m_contents.erase(it);
                 return;
            };
        };
        throw std::string(target + "does not exist in " + m_name);
    };

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
        // Print the total size of the directory.
        os << "Total size: " << size() << " bytes\n";
        for (auto res : m_contents) {
            // Print the type indicator.
            if (res->type() == NodeType::DIR)
                os << "D | ";
            else
                os << "F | ";
            // Print the resource name left-aligned in a field of 15 characters.
            os << std::left << std::setw(15) << res->name() << " | ";
            // Check if the LONG flag is requested.
            bool longFormat = (std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end());
            if (longFormat) {
                if (res->type() == NodeType::DIR) {
                    // For directories, print count (right-aligned, width 2) and size (right-aligned, width 10) with " bytes"
                    os << std::right << std::setw(2) << res->count() << " | " 
                       << std::right << std::setw(10) << res->size() << " bytes |";
                } else {
                    // For files, print an empty count field and the file size.
                    os << "   | " << std::right << std::setw(10) << res->size() << " bytes |";
                }
            }
            os << "\n";
        }
    };
}
