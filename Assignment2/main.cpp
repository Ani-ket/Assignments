#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>

// Function to update a file by replacing text matching the pattern
void updateFile(const std::string& filePath, const std::string& pattern, const std::string& replacement) {
    std::ifstream fin(filePath);
    if (!fin) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    std::ofstream fout(filePath + ".tmp");
    if (!fout) {
        std::cerr << "Error: Unable to create temporary file" << std::endl;
        fin.close();
        return;
    }

    std::string line;
    std::regex regexPattern(pattern);
    while (std::getline(fin, line)) {
        fout << std::regex_replace(line, regexPattern, replacement) << std::endl;
    }

    fin.close();
    fout.close();

    // Replace original file with updated temporary file
    std::remove(filePath.c_str());
    std::rename((filePath + ".tmp").c_str(), filePath.c_str());
}

// Function to update the build number in the SConstruct file
void updateSconstruct(const std::string& sourcePath, const std::string& buildNum) {
    std::string sconstructPath = sourcePath + "/develop/global/src/SConstruct";
    updateFile(sconstructPath, R"(point=\d+)", "point=" + buildNum);
}

// Function to update the build number in the VERSION file
void updateVersion(const std::string& sourcePath, const std::string& buildNum) {
    std::string versionPath = sourcePath + "/develop/global/src/VERSION";
    updateFile(versionPath, R"(ADLMSDK_VERSION_POINT=\d+)", "ADLMSDK_VERSION_POINT=" + buildNum);
}

int main() {
    // Fetch environment variables
    const char* buildNum = std::getenv("BuildNum");
    const char* sourcePath = std::getenv("SourcePath");

    // Check if both environment variables are provided
    if (!buildNum || !sourcePath) {
        std::cout << "Environment variables 'BuildNum' and 'SourcePath' are required." << std::endl;

        // Prompt the user for input
        std::cout << "Enter the build number: ";
        std::string buildNumInput;
        std::getline(std::cin, buildNumInput);
        if (!buildNumInput.empty()) {
            buildNum = buildNumInput.c_str();
        }

        std::cout << "Enter the source path: ";
        std::string sourcePathInput;
        std::getline(std::cin, sourcePathInput);
        if (!sourcePathInput.empty()) {
            sourcePath = sourcePathInput.c_str();
        }

        // Check again if both variables are provided
        if (!buildNum || !sourcePath) {
            std::cerr << "Error: Build number and source path are required." << std::endl;
            return 1;
        }
    }

    try {
        updateSconstruct(sourcePath, buildNum);
        updateVersion(sourcePath, buildNum);
        std::cout << "Version numbers updated successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
