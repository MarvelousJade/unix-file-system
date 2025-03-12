#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <string>
#include <vector>

namespace seneca {
    class Directory : public Resource {
        std::vector<Resource*> m_contents;
    public:
        explicit Directory(const std::string& name);

         // Disable copy and move operations
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
        ~Directory() override;

        void update_parent_path(const std::string& new_parent_path) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        Directory& operator+=(Resource* res);
        Resource* find(const std::string& target, const std::vector<OpFlags>& flags = {});
        void remove(const std::string& target, const std::vector<OpFlags>& flags = {});
        void display(std::ostream& os, const std::vector<FormatFlags>& flags = {}) const;
    };
}

#endif

