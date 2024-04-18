#include <string>
#include <sstream>
#include <cctype> 
#include <cassert> 
 
std::string reverse_words(const std::string &str)
{
    std::istringstream iss(str); // Create an input string stream
    std::ostringstream oss;       // Create an output string stream

    std::string word;
    while (iss >> word) {         // Read each word from the input stream
        std::string reversed_word;
        for (char c : word) {
            if (std::isalnum(c)) { // Check if character is alphanumeric
                reversed_word = c + reversed_word; // Reverse the word
            } else {
                reversed_word += c; // Maintain punctuation and spaces
            }
        }
        oss << reversed_word << " "; // Write the reversed word to the output stream
    }

    std::string result = oss.str();
    if (!result.empty()) {
        // Remove the trailing space
        result.pop_back();
    }

    return result;
}

int main()
{
    std::string test_str = "String; 2be reversed...";
    assert(reverse_words(test_str) == "gnirtS; eb2 desrever...");
    return 0;
}
