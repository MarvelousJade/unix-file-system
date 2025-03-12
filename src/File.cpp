#include "File.h"
#include "Flags.h"
#include <cstring>
#include "Resource.h"

namespace seneca {
    File::File(const std::string& name, const std::string& contents) : m_contents(contents) {
        m_name = name;
    };

    void File::update_parent_path(const std::string& new_parent_path) {
        m_parent_path = new_parent_path;
    };

    seneca::NodeType File::type() const {
        return seneca::NodeType::FILE;
    };

    std::string File::path() const {
        if (!m_parent_path.empty() && m_parent_path.back() == '/') 
            return m_parent_path + m_name;
        else 
            return m_parent_path + '/' + m_name;
    };

    std::string File::name() const {
        return m_name;
    };

    int File::count() const {
        return -1;
    };

    size_t File::size() const {
        return m_contents.size();
    };
}
