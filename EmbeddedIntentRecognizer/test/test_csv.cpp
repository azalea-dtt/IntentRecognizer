#include <gtest/gtest.h>
#include <fstream>   

#include "csv.h"

TEST(csv, CsvFileErrorTest) {
    
    std::string test_path = std::string(TEST_PATH);
    test_path += "/test_csvrow_noexist.csv";
    
    std::filesystem::path p(test_path);  
    cin::CsvFileParser csv {p}; 
    EXPECT_THROW(csv.LoadCsvFile(),  std::runtime_error);
}

TEST(csv, GetEncodedIntentDataTest) {
    std::string header{"word,topic,In city,people,time,book,weather"};
    std::vector<std::string> vIntentStr;
    std::vector<std::string> vExpIntentStr {"topic","In city","people","time","book","weather"};
    std::vector<std::vector<int>> vEncodedIntent;
    std::string test_path = std::string(TEST_PATH);
    test_path += "/test_csvrow.csv";
    
    std::filesystem::path p(test_path);   

    cin::CsvFileParser csv {p};
    
    csv.GetEncodedIntentDataImpl(header,vIntentStr, vEncodedIntent);
    for (int i = 0; i < vIntentStr.size(); i++) {
        EXPECT_EQ(vExpIntentStr[i],vIntentStr[i]) << "Parsing data error at col: " << i; 
    }
    std::vector<std::vector<int>> vExpEncodedIntent {{1,0,0,0,0,0},{0,1,0,0,0,0},{0,0,1,0,0,0},{0,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,1}};

    for (int i = 0; i < vExpEncodedIntent.size(); i++) {
        for (int j = 0; j < vExpEncodedIntent[i].size(); j++) {
            EXPECT_EQ(vExpEncodedIntent[i][j],vEncodedIntent[i][j]) << "Parsing data error at idx: " << i;
        }
    }
}

TEST(csv, GetIntentFromKeywordTest) {
    std::string file_path = std::string(DATA_PATH);
    file_path += "/intent.csv";
    std::filesystem::path p(file_path);
      
    cin::CsvFileParser csv {p};
    csv.LoadCsvFile();

    EXPECT_EQ(csv.GetIntentFromKeyWords("Celine Dion"),"people");
    EXPECT_EQ(csv.GetIntentFromKeyWords("Paris"),"In city");
    EXPECT_EQ(csv.GetIntentFromKeyWords("windy"),"weather");
}