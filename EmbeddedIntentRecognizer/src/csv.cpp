#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "csvrow.h"
#include "csv.h"

namespace
{
    std::istream& operator>>(std::istream& str, cin::CSVRow& data)
    {
        //data.readRow(str);
        std::string word;
        std::vector<int> vData;
        data.readRow(str, word, vData);
        data.setWord(word);
        data.setData(vData);
        return str;
    }
    /**
    * Remove CRLF
    */
    std::string& removeCrLf(std::string &input) {        
        std::string output;
        output.reserve(input.length());

        std::copy_if(input.begin(), input.end(),
                std::back_inserter(output),
                [] (char c) { return c != '\r' && c != '\n'; });
        input.assign(output.begin(), output.end());
        return input;
    }
}

cin::CsvFileParser::CsvFileParser(const std::filesystem::path& path)
: m_path {path}
{
    
}
void cin::CsvFileParser::LoadCsvFile()
{
    std::string sPath { m_path.u8string() };
    std::ifstream csvFile (sPath.c_str());
    int nRow = 0;
    CSVRow row;
    if (csvFile.is_open() == false) {
        throw cin::CsvFileParser::CsvError("Cannot open file");
    }
    std::string header;
    std::getline(csvFile, header);
    GetEncodedIntentData(header);  
    nRow++;
    while (csvFile >> row)
    {        
        if (nRow == 0) {
            nRow++;
            continue;
        }
        m_intentData[row.m_word] = row.m_data;
    }
    
}
void cin::CsvFileParser::GetEncodedIntentData(std::string& header)
{
    std::vector<std::string> vIntentStr;
    std::vector<std::vector<int>> vEncodedIntent;
    GetEncodedIntentDataImpl(header,vIntentStr, vEncodedIntent);
    m_vIntentStr = vIntentStr;
    m_vEncodedIntent = vEncodedIntent;

}
void cin::CsvFileParser::GetEncodedIntentDataImpl(std::string& header, std::vector<std::string> &vIntentStr, std::vector<std::vector<int>> &vEncodedIntent)
{
    std::istringstream ss(header);
    std::string token;
    
    int col = 0;
    while (ss.good()) {
        std::getline(ss, token, ',');
        if (col > 0) {           
           vIntentStr.push_back(removeCrLf(token));               
        }
        col++;
    }
    col = vIntentStr.size();
    
    for (int i = 0; i < vIntentStr.size(); i++) {
        std::vector<int> vEnc (col,0);
        vEnc[i] = 1;        
        vEncodedIntent.push_back(vEnc);
        vEnc.clear();
    }
   
    return;

}
size_t cin::CsvFileParser::FindIntentData(std::vector<int>& vData, std::string& str) const
{        
    auto iter = m_intentData.find(str);
    if (iter != m_intentData.end()) {        
        vData = iter->second;
        return vData.size();
    }
    return 0;
    
}
std::string cin::CsvFileParser::GetIntentFromKeyWords(std::string keyword) 
{
    std::vector<int> vData;
    std::string intentStr{""};
   
   
    if (m_intentData.find(keyword) != m_intentData.end()) {
        vData.assign(m_intentData[keyword].begin(), m_intentData[keyword].end());       
    } else {
        return intentStr;
    }
    for (int i = 0; i < m_vEncodedIntent.size(); i++ ) {
      
        if (m_vEncodedIntent[i] == vData) {           
            if (i != 0) {
                intentStr = m_vIntentStr[i];
            }
            else {
                intentStr = keyword;
            }
            return intentStr;
        }
    }
    return intentStr;

}