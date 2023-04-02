#include "RefererValidator.h"
#include <vector>

// static helpers forward declarations

static std::vector<std::string> GetSubdomains(std::string const &record);

// class RefererValidator

RefererValidator::RefererValidator()
{
    root = std::make_unique<TreeNode>();
}

void RefererValidator::AddRecord(std::string const &record)
{
    auto const& sd = GetSubdomains(record);
    auto* cur = root.get();

    for (int i = sd.size() - 1; i >= 0; --i)
    {
        auto const isWildcard = (i == sd.size() - 1 || i == 0) && sd[i] == "*";
        auto& child = (isWildcard) ? cur->wildcard : cur->domainNames[sd[i]];

        if (child == nullptr)
        {
            child = std::make_unique<TreeNode>();
        }
        
        cur = child.get();
    }

    cur->isTerminal = true;
}

bool RefererValidator::IsValid(std::string const &record) const
{
    auto const& sd = GetSubdomains(record);
    auto* cur = root.get();

    for (auto sdit = sd.crbegin(); sdit != sd.crend(); ++sdit)
    {
        auto const& hashmap = cur->domainNames;
        auto const& hmit = hashmap.find(*sdit);
        auto const& child = (hmit != hashmap.end()) ? hmit->second : cur->wildcard;

        if (child == nullptr) // even wildcard is nullptr
        {
            return false;
        }

        cur = child.get();
    }

    return cur->isTerminal;
}

// static helpers impl

static std::vector<std::string> GetSubdomains(std::string const &record)
{
    std::vector<std::string> result = {""};

    for (char const c : record)
    {
        if (c == '.')
        {
            result.emplace_back();
        }
        else
        {
            result.back().push_back(c);
        }
    }

    return result;
}
