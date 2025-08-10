#ifndef     RPN_CPP
# define    RPN_CPP

#include <stack>
#include <string>

class RPN
{
private:
      std::stack<int> stack_;
public:
      RPN(/* args */);
      ~RPN();
      RPN(const RPN& other);
      RPN& operator=(const RPN& other);
};

int   ft_RPN(char *str, int &flag);




#endif