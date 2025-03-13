#include "resource_path.hpp"
#include <algorithm>

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
#if defined(_WIN32) || defined(_WIN64)
    // Convert the string to a filesystem path
    std::filesystem::path fs_path(path);
    // Normalize the path and convert backslashes to forward slashes
    std::string normalized_path = fs_path.string();
    std::replace(normalized_path.begin(), normalized_path.end(), '\\', '/');
    return std::filesystem::path(normalized_path);
#else
    // For non-Windows systems, just convert to filesystem path directly
    return std::filesystem::path(path);
#endif
}
