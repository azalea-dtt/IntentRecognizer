#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include <unordered_map>
namespace cin 
{
    class CsvFileParser {
    public:
        /**
         * Thrown if file could not be read.
         */
        class CsvError : public std::runtime_error {
        public:
            /**
             * Construct CsvError error.
             *
             * @param msg Error message.
             */
            CsvError(const char *msg) : std::runtime_error{msg} {}
        };

        
        CsvFileParser(const std::filesystem::path& path);
        /**
         * Parsing csv file and save data in intenData
         *
         * @param 
         * @return 
         */
        void LoadCsvFile();
        /**
         * Parsing csv file: get row header and encode it to recognize intent data
         *
         * @param 
         * @return 
         */
        void GetEncodedIntentData(std::string& header);
        void GetEncodedIntentDataImpl(std::string& header, std::vector<std::string> &vIntentStr, std::vector<std::vector<int>> &vEncodedIntent);
        /**
         * Get the encoded intent category of a string.
         *        
         *
         * @param data Output data vector 
         * @param str input string to find its encoded intent category.
         * @return Size of data. If the intent is not found, return 0
         */
        size_t FindIntentData(std::vector<int>& vData, std::string& str) const;
        /**
         * Get the intent string of a keyword.
         * 
         * @param keyword input string to find its intent category.
         * @return intent category string
         */
        std::string GetIntentFromKeyWords(std::string keyword) ;
    private:
        std::unordered_map <std::string, std::vector<int>> m_intentData;
        const std::filesystem::path m_path;
        std::vector<std::string> m_vIntentStr;
        std::vector<std::vector<int>> m_vEncodedIntent;
    };
}