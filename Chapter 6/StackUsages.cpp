#include <iostream>
#include <stack>
#include <string>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 0;
    }
    if (c == '*' || c == '/') {
        return 1;
    }

    return 0;
}

int evaluatePostfix(std::string expression) {
    std::stack<int> stack;
    for (int i=0; i < expression.length(); i++) {
        char c = expression.at(i);
        if (isdigit(c)) {
            stack.push(c - '0');
        } else if (isOperator(c) && !stack.empty()) {
            int operand1 = stack.top();
            stack.pop();
            int operand2 = stack.top();
            stack.pop();
            int result = 0;
            if (c == '+') {
                result = operand1 + operand2;
            } else if (c == '*') {
                result = operand1 * operand2;
            } else if (c == '/') {
                result = operand2 / operand1;
            } else {
                result = operand1 - operand2;
            }

            stack.push(result);
        }
    }
    int result = 0;
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    return result;
}

// evaluating postfix operations are easy as we've seen, the real challenge is to convert infix expression to postfix
// so that we can evaluate the postfix expression easily
// converting infix to postfix is basically similar to basic calculation problem

// assuming the given infix expression is valid one
std::string convertInfixToPostfix(std::string infixExpression) {
    /**
     * initialize a result string
     * initiliaze a stack
     * for (each chartacter in infixExpression) {
     *  if (character is operand) {
     *      add to the end of result string
     *  }
     *  if (character is an `(` ) {
     *      push onto stack
     *  }
     *  if (character is an operator and if the stack is empty) {
     *      push onto stack
     *  } else if (character is an operator and if the stack is not empty) {
     *      pop operator that has greater or equal precende than the current operator
     *      you stop either when you encounter an open bracket or lower precende or stack becomes empty
     *  }
     *  if (character is a `)`) {
     *      pop all the operators until you encounter `(` and add them to the result
     *  }
     * }
     * 
     * pop the remainings of the stack and append to the result
     */
    std::string result = "";
    std::stack<char> stack;

    for (int i=0; i < infixExpression.length(); i++) {
        char c = infixExpression.at(i);

        if (isdigit(c)) {
            result+= c;
            continue;
        }
        if (c == '(') {
            stack.push(c);
            continue;
        }
        if (isOperator(c) && stack.empty()) {
            stack.push(c);
            continue;
        }
        if (isOperator(c)) {
            while (isOperator(c) && !stack.empty() && stack.top() != '(' && precedence(c) <= precedence(stack.top()))
            {
                result += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
        if (c == ')') {
            while (stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop();
        }
    }

    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }

    return result;

}

int main() {    
    std::string infixExpression = "2*4+(4/2)";

    std::string postfix = convertInfixToPostfix(infixExpression);
    std::cout << postfix << std::endl;

    int result = evaluatePostfix(postfix);
    std::cout << result;

    return 0;
}