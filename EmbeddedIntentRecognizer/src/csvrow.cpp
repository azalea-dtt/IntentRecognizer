#include <algorithm> 
#include <iostream>
#include "csvrow.h"

bool cin::CSVRow::is_digits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}
#if 0
void cin::CSVRow::readRow(std::istream& str)
{
    std::getline(str, m_line);        
    if (m_line.find_first_of("0123456789") == std::string::npos)
        return;
    m_data.clear();
    std::istringstream ss(m_line);
    std::string token;
    
    int col = 0;
    while (std::getline(ss, token, ',')) {
        
        if (col == 0) {
            m_word = token;
            
        }
        else {
            
            if (is_digits(token.substr(0,1))) {                
                m_data.push_back(stoi(token.substr(0,1)));
            }             
        }
        col++;
    }
   
    return;
}
#endif
void cin::CSVRow::readRow(std::istream& str, std::string &word, std::vector<int> &data)
{
    std::getline(str, m_line);        
    if (m_line.find_first_of("0123456789") == std::string::npos)
        return;
    data.clear();
    std::istringstream ss(m_line);
    std::string token;
    
    int col = 0;
    while (std::getline(ss, token, ',')) {
        
        if (col == 0) {
            word = token;
            
        }
        else {
            
            if (is_digits(token.substr(0,1))) {                
                data.push_back(stoi(token.substr(0,1)));
            }             
        }
        col++;
    }
   
    return;
}