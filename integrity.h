#pragma once
#include <filesystem>
#include <string>
#include <vector>

// Integrity namespace encapsulating manifest integrity functions
namespace Integrity {
    inline constexpr const char kManifestFileName[] = ".sit_integrity.manifest";

    // Structure to represent an issue found during integrity check
    struct Issue {
        std::string path;
        std::string status;
        std::string detail;
    };

    // Structure to hold the results of an integrity check
    struct CheckResult {
        int total = 0;
        int ok = 0;
        int changed = 0;
        int missing = 0;
        int added = 0;
        int errors = 0;
        std::vector<Issue> issues;
    };

    // Function declarations for manifest operations
    bool createManifest(const std::filesystem::path& root, std::string* error);
    bool updateManifest(const std::filesystem::path& root, std::string* error);
    bool checkManifest(const std::filesystem::path& root, CheckResult& result, std::string* error);
}
