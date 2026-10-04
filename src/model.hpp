#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace astrata {
class LanguageModel {
public:
    explicit LanguageModel(size_t order = 4);

    void train(const std::string& text);
    void trainFile(const std::string& path);
    std::string generate(const std::string& prompt, size_t maxTokens = 80) const;

    bool save(const std::string& path) const;
    bool load(const std::string& path);

    size_t vocabularySize() const;
    uint64_t learnedTokens() const;

private:
    size_t order_;
    uint64_t learnedTokens_ = 0;
    std::unordered_map<std::string, uint64_t> vocabulary_;
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> transitions_;

    static std::string key(const std::vector<std::string>& tokens, size_t start, size_t count);
    std::string chooseNext(const std::vector<std::string>& context) const;
};
}
