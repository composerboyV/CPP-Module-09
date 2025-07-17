#ifndef     PMERGEME_HPP
# define    PMERGEME_HPP

class PmergeMe
{
private:
      std::vector<int> _main_chain;
      std::vector<int> _pend_chain;
      std::vector<std::pair<int, int>> _pairs;
      std::vector<int> _jacobsthal_sequence;
public:
      PmergeMe(/* args */);
      ~PmergeMe();
      PmergeMe(const PmergeMe& other);
      PmergeMe& operator=(const PmergeMe& other);
      void make_chain(int argc, char **argv);
      void _sort_big_values();
      void jacobsthal_sequence();
      void insert_small_values();
};



#endif