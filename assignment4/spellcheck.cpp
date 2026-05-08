#include "spellcheck.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <vector>

// 前向声明 find_all（实现在 utils.cpp 中）
template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
    // Step 1: 找到所有空白字符的迭代器
    // 使用 ::isspace 或者静态转换来避免重载歧义
    auto is_whitespace = [](unsigned char c) { return std::isspace(c); };
    
    std::vector<std::string::iterator> whitespaceIters;
    whitespaceIters = find_all(source.begin(), source.end(), is_whitespace);
    
    // Step 2: 使用 transform 生成 Token
    Corpus tokens;
    
    // 确保有足够的迭代器来形成对
    if (whitespaceIters.size() >= 2) {
        std::transform(whitespaceIters.begin(), 
                       whitespaceIters.end() - 1,  // 第一个范围
                       whitespaceIters.begin() + 1, // 第二个范围
                       std::inserter(tokens, tokens.end()),
                       [&source](auto it1, auto it2) {
                           return Token(source, it1, it2);
                       });
    }
    
    // Step 3: 移除空的 Token
    std::erase_if(tokens, [](const Token& token) {
        return token.content.empty();
    });
    
    return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    namespace rv = std::ranges::views;
    
    // 创建视图管道
    auto result_view = source 
        // 只保留拼写错误的词
        | rv::filter([&dictionary](const Token& token) {
            return !dictionary.contains(token.content);
        })
        // 转换为 Misspelling
        | rv::transform([&dictionary](const Token& token) {
            // 找出所有编辑距离为1的字典词
            auto suggestions = dictionary 
                | rv::filter([&token](const std::string& word) {
                    return levenshtein(token.content, word) == 1;
                });
            
            // 实例化 suggestions set
            std::set<std::string> suggestion_set(suggestions.begin(), suggestions.end());
            return Misspelling{token, suggestion_set};
        })
        // 过滤掉没有建议词的
        | rv::filter([](const Misspelling& m) {
            return !m.suggestions.empty();
        });
    
    // 返回结果
    return std::set<Misspelling>(result_view.begin(), result_view.end());
}

/* Helper methods are included from utils.cpp */
#include "utils.cpp"