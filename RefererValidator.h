#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class RefererValidator
{
public:

    RefererValidator();

    void AddRecord(std::string const& record);

    bool IsValid(std::string const& record) const;

private:

    struct TreeNode
    {
        std::unordered_map<std::string, std::unique_ptr<TreeNode>> domainNames;
        std::unique_ptr<TreeNode> wildcard;
        bool isTerminal = false;
    };

    std::unique_ptr<TreeNode> root;
};
