#include <iostream>
#include <string>
#include <set>

bool isPalindrome(std::string word) {
    if (word.length() == 0) {
        return true;
    }

    if (word.at(0) == word.at(word.length() - 1)) {
        std::string substr = word.substr(1,word.length() - 2);
        return isPalindrome(word.substr(1,word.length() - 2));
    }

    return false;
}

// prefix expression
// +E1E2, if an expression starts with an operator and there are two consecutive prefix expressions exist
// it's a valid prefix expression

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}


// finds the end of the first prefix expression
int endPre(std::string expression, int first) {
    int last = expression.length() - 1;
    if (first < 0 || first > last) {
        return -1;
    }

    char c = expression.at(first);

    if (isalpha(c)) {
        return first;
    } else if (isOperator(c)) {
        int firstEnd = endPre(expression, first + 1); // end of the first valid prefix

        if (firstEnd > -1) {
            return endPre(expression, firstEnd + 1);
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

bool isPrefix(std::string expression) {
    int end = endPre(expression, 0);

    return end == expression.length() - 1 && end > 0;
}

int main() {
    std::string word = "+–/abc * + def * gh";

    std::cout << isPrefix(word) << std::endl;
    return 0;
}