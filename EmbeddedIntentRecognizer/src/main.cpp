#include <iostream>
#include <filesystem>
#include "csv.h"
#include "input.h"

int main()
{
    std::string file_path = std::string(DATA_PATH);
    file_path += "/intent.csv";
    try {
        std::filesystem::path p(file_path);
        //std::cout << "Data file:" <<  file_path << std::endl;

        cin::CsvFileParser csv {p};
        csv.LoadCsvFile();

        std::cout << "Enter input:";
        std::string user_input;
        getline(std::cin, user_input);

        cin::InputSentence input {user_input};
        std::vector<std::string> vKeyWords = input.getKeywords();
        
        std::cout << "Intent: Get ";     
       
        for (auto &w: vKeyWords) {
          
            std::string intent = csv.GetIntentFromKeyWords(w);            
            if (intent.length() > 0) {            
                std::cout << intent << " ";                
            }
        }

        std::cout  << std::endl;
        return EXIT_SUCCESS;
    }
    catch (const std::runtime_error& error) {
        return EXIT_FAILURE;
    }
}