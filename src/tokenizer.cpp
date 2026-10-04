#include "tokenizer.hpp"
#include <cctype>

namespace astrata {
std::string Tokenizer::normalize(const std::string& token) {
    std::string out;
    for (unsigned char c : token) out += static_cast<char>(std::tolower(c));
    return out;
}

std::vector<Token> Tokenizer::tokenize(const std::string& text) {
    std::vector<Token> result;
    std::string word;
    auto flush = [&] {
        if (!word.empty()) {
            result.push_back({normalize(word), false});
            word.clear();
        }
    };

    for (size_t i = 0; i < text.size();) {
        unsigned char c = static_cast<unsigned char>(text[i]);
        if (std::isspace(c)) { flush(); ++i; continue; }

        // Keep UTF-8 bytes together as part of a token. This intentionally
        // avoids corrupting non-ASCII languages; future Unicode segmentation
        // can replace this routine without changing the model API.
        if (c >= 128) {
            flush();
            size_t start = i++;
            while (i < text.size() &&
                   (static_cast<unsigned char>(text[i]) >= 128 ||
                    std::isalnum(static_cast<unsigned char>(text[i])))) ++i;
            result.push_back({text.substr(start, i - start), false});
            continue;
        }

        if (std::isalnum(c) || c == '_' || c == '\'') {
            word += static_cast<char>(c);
            ++i;
            continue;
        }

        flush();
        result.push_back({std::string(1, static_cast<char>(c)), true});
        ++i;
    }
    flush();
    return result;
}
}
