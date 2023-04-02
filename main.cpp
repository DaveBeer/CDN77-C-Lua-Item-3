#include <cstdlib>
#include <iostream>
#include <string>
#include "RefererValidator.h"

void TestValidator(RefererValidator const& rv, std::string const& r)
{
    auto const valid = rv.IsValid(r);
    std::cout << "Record " << r << " is " << (valid ? "valid" : "invalid") << std::endl;
}

int main()
{
    auto const configRecords = {
        "host1.www.example.com",
        "host2.*.example.com",
        "*.example.com",
        "www.example.*"
    };

    auto const testRecords = {
        "host1.www.example.com",
        "host2.www.example.com",
        "example.com",
        "host2.*.example.com",
        "some.example.com",
        "www.example.org",
        "some.example.org"
    };

    std::cout << "Initial configuration:\n";
    RefererValidator rv;

    for (auto const& r : configRecords)
    {
        std::cout << r << std::endl;
        rv.AddRecord(r);
    }

    std::cout << std::endl;

    for (auto const& r : testRecords)
    {
        TestValidator(rv, r);
    }

    return EXIT_SUCCESS;
}
