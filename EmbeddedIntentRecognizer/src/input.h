#pragma once
#include <string>

namespace cin 
{
    class InputSentence {
    public:
        /**
         * Input sentence error
         */
        class InputSentenceError : public std::runtime_error {
        public:
            /**
             * Construct error message
             *
             * @param msg Error message.
             */
            InputSentenceError(const char *msg) : std::runtime_error{msg} {}
        };
        /**
         * Construct a new InputSentence to analyse intent.
         *
         * @p str input string
         */
        InputSentence (std::string input);
        /**
         * Get intent keywords.
         */
        std::vector<std::string> getKeywords() { return m_words;}
    private:
        /**
         * Analyse InputSentence to get intent keywords.
         */
        void extractKeywords();
    //private:
        std::string m_inputStr;
        std::vector<std::string> m_words;      
    };
}
