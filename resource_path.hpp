#ifndef RESOURCE_PATH_HPP
#define RESOURCE_PATH_HPP

#include <filesystem>
#include <string>

class ResourcePath {
  public:
    ResourcePath(bool use_install_path, const std::filesystem::path &install_path = "");
    std::filesystem::path gfp(const std::string &relative_path) const;
	std::string gfps(const std::string &relative_path) const;
    std::filesystem::path get_full_path(const std::filesystem::path &relative_path) const;
    static std::filesystem::path convert_to_filesystem_path(const std::string &path);

  private:
    bool use_install_path_;
    std::filesystem::path install_path_;
};

#endif // RESOURCE_PATH_HPP
