#include <iostream>
#include <stack>
#include "RPN.hpp"

int   main(int argc, char **argv)
{
      if (argc != 2) {
            std::cout<<"check argv"<<std::endl;
            return (0);
      }
      int   flag = 0;
      int result = ft_RPN(argv[1], flag);
      if (flag == 0)
            std::cout << result<< std::endl;
      else
            std::cout <<"Error"<<std::endl;
      return (0);
}