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

// get full path (gfp)
std::filesystem::path ResourcePath::gfp(const std::string &relative_path) const {
    return get_full_path(convert_to_filesystem_path(relative_path));
}

// get full path string (gfps)
std::string ResourcePath::gfps(const std::string &relative_path) const {
    return gfp(relative_path).string();
}

std::filesystem::path ResourcePath::convert_to_filesystem_path(const std::string &path) {
#if defined(_WIN32) || defined(_WIN64)
	auto fp = std::filesystem::path(path);
	fp.make_preferred();
    return fp;
#else
    // For non-Windows systems, just convert to filesystem path directly
    return std::filesystem::path(path);
#endif
}
