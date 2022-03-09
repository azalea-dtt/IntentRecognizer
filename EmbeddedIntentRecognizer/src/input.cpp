#include <vector>
#include <iostream>

#include <string>
#include <sstream>
#include <vector>
#include <iostream> 
#include <regex> 


#include "input.h"
namespace 
{
    /**
    * Left trim whitespace
    */
    std::string& ltrim(std::string& s)
    {
        auto it = std::find_if(s.begin(), s.end(),
            [](char c) {
                return !std::isspace<char>(c, std::locale::classic());
            });
        s.erase(s.begin(), it);
        return s;
    }
    /**
    * Right trim whitespace
    */
    std::string& rtrim(std::string& s)
    {
        auto it = std::find_if(s.rbegin(), s.rend(),
            [](char c) {
                return !std::isspace<char>(c, std::locale::classic());
            });
        s.erase(it.base(), s.end());
        return s;
    }
    /**
    * Left and Right trim whitespace
    */
    std::string& trim(std::string& s) 
    {
        return ltrim(rtrim(s));
    }
    /**
    * Remove special characters in string, keep the whitespace between words
    *    
    */
    void removeSpecialChars(std::string& s)
    {
        s.erase(std::remove_if(s.begin(), s.end(),
            [](auto const& c) -> bool { return (!std::isalnum(c)&& (c != ' ') && (c != '\"')); }), s.end());
    }

    void extractRegResult(std::string& str)
    {
        size_t len = str.length();
        str = str.substr(1, len - 2);
        trim(str);
    }
    /**
    * Extract the string in double quotation marks
    *    
    */
    void extractPattern(std::string &s, std::vector<std::string> &regWords)
    {        
        std::regex regexp(R"(\"[^()]*\")");
        std::smatch m;        
        regex_search(s, m, regexp);
        
        for (unsigned i = 0; i < m.size(); ++i) {
            std::string matchStr = m.str(i);
            extractRegResult(matchStr);
            regWords.push_back(matchStr);
            
            s.erase(m.position(i)+1, m.length(i)-2);            
        }
        return ;
    }
}

cin::InputSentence::InputSentence(std::string input)
: m_inputStr {input}
{
    if (input.length() == 0) {
        throw cin::InputSentence::InputSentenceError("Input Sentence error");
    }
    extractKeywords();
}
void cin::InputSentence::extractKeywords()
{
    std::vector<std::string> regWords;
    extractPattern(m_inputStr, regWords);
    removeSpecialChars(m_inputStr);
   
    std::vector<std::string> words;
    std::stringstream ss(m_inputStr);
    std::string buf;
    std::string upperBuf = "";
    int count = 0;
    while (ss >> buf) { 
              
        if (buf == "\"\"") {
            if (upperBuf.length() > 0) {
                words.push_back(upperBuf);
                upperBuf.clear();
            }
           
            words.push_back(regWords[count]);
            count++;                 
        }
        else {            
            if (isupper(buf[0])) {
                if (upperBuf.length() > 0) {
                    upperBuf.push_back(' ');
                }
                upperBuf += buf;
            }
            else {
                if (upperBuf.length() > 0) {
                    words.push_back(upperBuf);
                    upperBuf.clear();
                }
                words.push_back(buf);
            }
        }
    }
    if (upperBuf.length() > 0)
        words.push_back(upperBuf);
    
    m_words = words;
    return; 

}