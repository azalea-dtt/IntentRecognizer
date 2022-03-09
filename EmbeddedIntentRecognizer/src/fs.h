#pragma once
#include <vector>
#include <filesystem>

namespace cin
{
    using Paths = std::vector<std::filesystem::path>;

    /**
     * Enumerate csv files located in @p path.
     *
     * The intent_data.csv defines the keywords and the intent classes
     * We can define different intent data files for different domains
     * @param path Path denoting a directory.
     * @return A vector of file paths.
     */
    Paths get_valid_csv_files(const std::filesystem::path& path);
    
}