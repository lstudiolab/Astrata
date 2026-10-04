#pragma once
#include <string>
#include <vector>

namespace astrata {
struct Token {
    std::string text;
    bool punctuation = false;
};

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& text);
    static std::string normalize(const std::string& token);
};
}
