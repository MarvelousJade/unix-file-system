#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include "Flags.h"

namespace seneca {
    class File : public seneca::Resource {
        std::string m_contents;
    public:
        explicit File(const std::string& name, const std::string& contents = "");
        void update_parent_path(const std::string& new_parent_path) override;
        seneca::NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        ~File() override = default;
    };
}

#endif
