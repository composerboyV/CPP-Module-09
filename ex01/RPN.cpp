#include "RPN.hpp"

#include <iostream>
RPN::RPN(/* args */)
{
}

RPN::~RPN()
{
}
RPN::RPN(const RPN& other)
{
      this->stack_ = other.stack_;
}

RPN& RPN::operator=(const RPN& other)
{
      if (this != &other)
            this->stack_ = other.stack_;
      return (*this);
}



int  ft_RPN(char *str, int &flag)
{
      std::stack<int> stack;
      flag = 0;
      for (int i = 0; str[i];  i++) {
            if (str[i] == ' ' || str[i] == '\t')
                  continue ;
            int temp = str[i];
            if (48 <= temp && temp <= 57) {
                  stack.push(temp - '0');
                  continue ;
            }
            else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
                  if (stack.size() == 0 && i != 0) {
                        flag = 1;
                        return (-1);
                  }
                  int b = stack.top();
                  stack.pop();
                  if (stack.size() == 0) {
                        flag = 1;
                        return (-1);
                  }
                  int a = stack.top();
                  stack.pop();
                  int   result = 0;
                  if (temp == '+')
                        result = a + b;
                  else if (temp == '-')
                        result = a - b;
                  else if (temp == '*')
                        result = a * b;
                  else if (temp == '/') {
                        if (b == 0) {
                              flag = 1;
                              std::cout<<"cause : n/0"<<std::endl;
                              return (-1);
                        }
                        result = a / b;
                  }
                  stack.push(result);
            }
            else {
                  flag = 1;
                  return (-1);
            }
      }
      if (stack.size() != 1) {
            flag = 1;
            return (-1);
      }
      return (stack.top());
}
