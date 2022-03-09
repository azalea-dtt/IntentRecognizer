#pragma once

#include <filesystem>
#include <memory>
#include <vector>
#include "csv.h"
namespace cin 
{
    class CSVRow {
    public:
        /**
         * Return true if the input string of a column in csv file contains only digits.
         *
         * @return true or false.
         */
        bool is_digits(const std::string& str);
        /**
         * Read the input row.
         *
         * Read the first column in the row into m_word and the remaining columns to m_data 
         * m_data contains the information of intent in a sentence, using one-hot encoding techniques
         * @param str input stream.  
         * @param word keyword in the sentence
         * @param data encoded intent       
         * @return void.
         */
        
        void readRow(std::istream& str, std::string &word, std::vector<int> &data);
        /**
         * set word.         
         * @return void.
         */
        void setWord(std::string word) { m_word = word; }
         /**
         * set encoded intent vector (use one-hot encoding technique)
         * @return void.
         */
        void setData(std::vector<int> vData) { m_data = vData; }
    private:
        std::string         m_line;
        std::vector<int>    m_data;
        std::string         m_word;

        friend class CsvFileParser;
    }; 

}