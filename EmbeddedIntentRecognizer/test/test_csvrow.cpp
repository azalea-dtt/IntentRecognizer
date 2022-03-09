#include <gtest/gtest.h>
#include <fstream>   

#include "csvrow.h"

TEST(csvrow, readRowTest) {
  
    std::filebuf fb;
    std::string test_path = std::string(TEST_PATH);
    test_path += "/test_csvrow.csv";
    fb.open (test_path,std::ios::in);
    std::istream str(&fb);
    
    std::string word;
    std::vector<int> data;
    std::vector<int> exp_data {0,0,0,0,0,1};
    cin::CSVRow csvRow;
    csvRow.readRow(str, word, data);
    EXPECT_EQ("weather",word);
    for (int i = 0; i < exp_data.size(); i++) {
        EXPECT_EQ(exp_data[i],data[i]) << "Parsing data error at col: " << i; 
    }
  

}