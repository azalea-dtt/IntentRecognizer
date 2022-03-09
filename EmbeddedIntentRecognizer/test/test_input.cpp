#include <gtest/gtest.h>
#include <fstream>   

#include "input.h"

TEST(input, InputSentenceTest) {
    
    EXPECT_THROW(cin::InputSentence(""),  std::runtime_error);
}
TEST(input, GetKeyWordsTest) {
    cin::InputSentence input("What is the weather in New York tomorrow?");
    std::vector<std::string> vExpKeywords {"What","is","the","weather","in","New York","tomorrow"};
    std::vector<std::string> vKeywords = input.getKeywords();
    for (int i = 0; i < vExpKeywords.size(); i++) {
        EXPECT_EQ(vExpKeywords[i], vKeywords[i]) << "Parsing input error at keyword idx: " << i;
    }
}
TEST(input, GetKeyWordsInDoubleQuoteTest) {
    cin::InputSentence input("What is the author of \"Atomic Habits\" book?");
    std::vector<std::string> vExpKeywords {"What","is","the","author","of","Atomic Habits","book"};
    std::vector<std::string> vKeywords = input.getKeywords();
    for (int i = 0; i < vExpKeywords.size(); i++) {
        EXPECT_EQ(vExpKeywords[i], vKeywords[i]) << "Parsing input error at keyword idx: " << i;
    }
}
TEST(input, GetKeyWordsInputStringWithSpecialCharsTest) {
    cin::InputSentence input("What is the weather in @#$$ Paris?");
    std::vector<std::string> vExpKeywords {"What","is","the","weather","in","Paris"};
    std::vector<std::string> vKeywords = input.getKeywords();
    for (int i = 0; i < vExpKeywords.size(); i++) {
        EXPECT_EQ(vExpKeywords[i], vKeywords[i]) << "Parsing input error at keyword idx: " << i;
    }
}