#ifndef     PMERGEME_HPP
# define    PMERGEME_HPP

#include <vector>
#include <deque>
#include <set>

class PmergeMe
{
private:
      std::vector<int> _main_chain;//큰값들
      std::vector<int> _pend_chain;//작은값들
      std::vector<std::pair<int, int> > _pairs;//쌍저장
      std::vector<int> _jacobsthal_sequence;
      std::vector<int>  _odd_num;//홀수
      std::deque<int> _jacobsthal_sequence_deq;

      
      std::deque<int> _main_chain_deq;
      std::deque<int> _pend_chain_deq;
      std::deque<std::pair<int, int> > _pairs_deq;
      std::deque<int> _odd_num_deq;
public:
      PmergeMe();
      ~PmergeMe();
      PmergeMe(const PmergeMe& other);
      PmergeMe& operator=(const PmergeMe& other);
      void make_chain(int argc, char **argv);
      void _sort_big_values();
      int jacobsthal_sequence();
      void insert_small_values();
      void insert_odd_element();  // 홀수 원소 삽입 함수 추가
      //vector 버전 함수
      void  make_chain_vector(int argc, char **argv);
      void  sort_big_values_vector();
      void  insert_small_values_vector();

      //deque 버전 함수
      void  make_chain_deque(int argc, char **argv);
      void  sort_big_values_deque();
      void  insert_small_values_deque();
      int   jacobsthal_sequence_deque();
      void  insert_odd_element_deque();

      void  clear_vector_members();
      void  clear_deque_members();
      
      // 디버깅용 함수들
      void  print_pairs() const;
      void  print_chains() const;
      void  print_jacobsthal() const;
      void  print_pairs_deq() const;
      void  print_chains_deq() const;
      void  print_jacobsthal_deq() const;

      void  end_print(int argc, char** argv);
      int   check_dup(int argc, char** argv);
      const std::vector<int>& get_main_chain() const;
      const std::deque<int>& get_main_chain_deque() const;
      long long   _time_vector;//시간
      long long   _time_deque;//시간

};
std::vector<int> Fordjohnson_Sort(std::vector<int> input);
std::vector<int> handleBaseCase(std::vector<int> input);
std::vector<int> sortLargerValues();

void  createPairs(const std::vector<int>& input);

#endif