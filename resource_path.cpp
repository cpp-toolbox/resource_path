#include "resource_path.hpp"

ResourcePath::ResourcePath(bool use_install_path, const std::filesystem::path &install_path)
    : use_install_path_(use_install_path), install_path_(install_path) {}

std::filesystem::path ResourcePath::get_full_path(const std::filesystem::path &relative_path) const {
    if (use_install_path_ && !install_path_.empty()) {
        return install_path_ / relative_path;
    }
    return relative_path;
}

std::filesystem::path ResourcePath::gfp(const std::string &relative_path) const {
    return get_full_path(convert_to_filesystem_path(relative_path));
}

std::filesystem::path ResourcePath::convert_to_filesystem_path(const std::string &path) {
#ifdef _WIN32
    std::filesystem::path fs_path(path);
    return fs_path.make_preferred();
#else
    return std::filesystem::path(path);
#endif
}
