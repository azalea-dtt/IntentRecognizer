#include "fs.h"

cin::Paths cin::get_valid_csv_files(const std::filesystem::path& path)
{
    cin::Paths result;

    for (const auto& entry: std::filesystem::directory_iterator{path}) {
        if (entry.is_regular_file()) {
            const auto path{entry.path()};

            if (path.has_extension() && path.extension() == ".csv") {
                result.push_back(path);
            }
        }
    }
    return result;
}