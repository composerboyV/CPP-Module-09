/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 06:34:32 by junkwak           #+#    #+#             */
/*   Updated: 2025-07-15 06:34:32 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include "PmergeMe.hpp"
#include <algorithm>
#include <cstdlib>
#include <iomanip>

PmergeMe::PmergeMe(/* args */)
{
}

PmergeMe::~PmergeMe()
{
}


PmergeMe::PmergeMe(const PmergeMe& other)
{
      *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
      if (this != &other)
      {
            _main_chain = other._main_chain;
            _pend_chain = other._pend_chain;
            _pairs = other._pairs;
            _jacobsthal_sequence = other._jacobsthal_sequence;
            _odd_num = other._odd_num;
            _main_chain_deq = other._main_chain_deq;
            _pend_chain_deq = other._pend_chain_deq;
            _pairs_deq = other._pairs_deq;
            _odd_num_deq = other._odd_num_deq;
            _jacobsthal_sequence_deq = other._jacobsthal_sequence_deq;
      }
      return (*this);
}

int   PmergeMe::check_dup(int argc, char** argv)
{
    std::set<int> arg_set;
    int test;
    for (int i = 1; i < argc; i++) {
        std::stringstream ss(argv[i]);
        ss >> test;
        int value = test;
        std::pair<std::set<int>::iterator, bool> result = arg_set.insert(value);
        if (!result.second)
            return (1);
    }
    return (0);    
}

void    PmergeMe::make_chain(int argc, char **argv)
{
    // 홀수 원소가 있는지 확인 (실제 숫자 개수가 홀수인지)
    int total_numbers = argc - 1;  // argv[0]은 프로그램명 제외
    bool has_odd = (total_numbers % 2 == 1);
    
    // 홀수 원소가 있으면 마지막 원소를 따로 보관
    if (has_odd) {
        _odd_num.push_back(std::atoi(argv[argc - 1]));
        std::cout << "홀수 원소: " << _odd_num[0] << std::endl;
    }
    
    // 페어 생성 (홀수 원소 제외하고)
    int pair_count = total_numbers / 2;
    for (int i = 0; i < pair_count; i++) {
        int first = std::atoi(argv[1 + i * 2]);
        int second = std::atoi(argv[1 + i * 2 + 1]);
        
        // 작은값을 first, 큰값을 second로 정렬
        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }
        _pairs.push_back(std::pair<int, int>(first, second));
    }
}

// 큰값(second)을 기준으로 정렬하는 비교 함수 객체
struct ComparePairs {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        return a.second < b.second;
    }
};

void PmergeMe::_sort_big_values()
{
    std::sort(_pairs.begin(), _pairs.end(), ComparePairs());
    
    _main_chain.clear();
    _pend_chain.clear();
    for(size_t i = 0; i < _pairs.size(); i++) {
        _main_chain.push_back(_pairs[i].second);  // 큰값
        _pend_chain.push_back(_pairs[i].first);   // 작은값
    }
}
std::vector<int> handleBaseCase(std::vector<int> input)
{
      if (input.size() == 0 || input.size() == 1)
            return (input);
      if (input.size() == 2)
      {
            if (input[0] > input[1])
                  std::swap(input[0], input[1]);
      }
      return (input);
}
int   PmergeMe::jacobsthal_sequence()
{//Jn =Jn−1 + 2Jn−2
 
      _jacobsthal_sequence.clear();
      int   n = _pend_chain.size();

      std::vector<int> jacob_nums;
      int j1 = 1, j2 = 1;
      while (j2 < n) {
            jacob_nums.push_back(j2);
            int tmp = j2;
            j2 = j2 + 2 * j1;
            j1 = tmp;
      }
      int   last = 0;
      for (size_t i = 1; i < jacob_nums.size(); ++i) {
            int limit = jacob_nums[i];
            for (int j = limit - 1; j >= last; --j)
            if (j < n)
                  _jacobsthal_sequence.push_back(j);
            last = limit;
      }
      for (int j = n - 1; j >= last; --j)
            _jacobsthal_sequence.push_back(j);
      return n; 
}

int   PmergeMe::jacobsthal_sequence_deque()
{//Jn =Jn−1 + 2Jn−2
 
      _jacobsthal_sequence_deq.clear();
      int   n = _pend_chain_deq.size();

      std::deque<int> jacob_nums;
      int j1 = 1, j2 = 1;
      while (j2 < n) {
            jacob_nums.push_back(j2);
            int tmp = j2;
            j2 = j2 + 2 * j1;
            j1 = tmp;
      }
      int   last = 0;
      for (size_t i = 1; i < jacob_nums.size(); ++i) {
            int limit = jacob_nums[i];
            for (int j = limit - 1; j >= last; --j)
            if (j < n)
                  _jacobsthal_sequence_deq.push_back(j);
            last = limit;
      }
      for (int j = n - 1; j >= last; --j)
            _jacobsthal_sequence_deq.push_back(j);
      return n; 
}

int  Binary_Search(std::vector<int> input, int target, int right)
{
      int left = 0;
      while (left <= right)
      {
            int mid = (left + right) / 2;
            if (input[mid] == target)
                  return (mid);
            else if (input[mid] < target)
                  left = mid + 1;
            else
                  right = mid - 1;
      }
      return (left);
}

int  Binary_Search_deque(std::deque<int> input, int target, int right)
{
      int left = 0;
      while (left <= right)
      {
            int mid = (left + right) / 2;
            if (input[mid] == target)
                  return (mid);
            else if (input[mid] < target)
                  left = mid + 1;
            else
                  right = mid - 1;
      }
      return (left);
}

void PmergeMe::insert_small_values()
{
    for (size_t i = 0; i < _pend_chain.size(); i++)  // int → size_t로 변경
    {
        // int k = _jacobsthal_sequence[i]; // 사용하지 않는 변수 제거
        int small = _pend_chain[i];
        int big = _pairs[i].second;
        //big 값의 위치 설정(오른쪽큰값을 제한범위로)
        std::vector<int>::iterator it_big = std::find(_main_chain.begin(), _main_chain.end(), big);
        //짝이었던 big 위치까지 binary_search찾기
        int index = Binary_Search(_main_chain, small, std::distance(_main_chain.begin(),it_big));
        //해당범위 small값 삽입
        _main_chain.insert(_main_chain.begin() + index, small);//진행중
    }
}

void PmergeMe::insert_odd_element()
{
    if (!_odd_num.empty()) {
        int odd_value = _odd_num[0];
        std::cout << "홀수 원소 " << odd_value << "를 전체 main_chain에서 이진탐색으로 삽입" << std::endl;
        
        // 전체 main_chain에서 이진탐색으로 적절한 위치 찾기
        int index = Binary_Search(_main_chain, odd_value, _main_chain.size() - 1);
        _main_chain.insert(_main_chain.begin() + index, odd_value);
        
        std::cout << "홀수 원소 삽입 완료" << std::endl;
    }
}

std::vector<int> Fordjohnson_Sort(std::vector<int> input)  // intput → input 수정
{
    return handleBaseCase(input);  // 임시로 베이스케이스만 반환
}

std::vector<int>  sortLargerValues()
{
    return std::vector<int>();  // 빈 벡터 반환
}

void  createPairs(const std::vector<int>& /*input*/)  // 파라미터 주석 처리
{
    // - 연속된 두 원소씩 비교
// - 큰값을 second, 작은값을 first로 pair 생성
// - _pairs에 저장
// - 홀수 원소가 있으면 _odd_element에 저장
    
}


void  PmergeMe::make_chain_vector(int argc, char **argv)
{
        // 홀수 원소가 있는지 확인 (실제 숫자 개수가 홀수인지)
    int total_numbers = argc - 1;  // argv[0]은 프로그램명 제외
    bool has_odd = (total_numbers % 2 == 1);
    
    // 홀수 원소가 있으면 마지막 원소를 따로 보관
    if (has_odd) {
        _odd_num.push_back(std::atoi(argv[argc - 1]));
        std::cout << "홀수 원소: " << _odd_num[0] << std::endl;
    }
    
    // 페어 생성 (홀수 원소 제외하고)
    int pair_count = total_numbers / 2;
    for (int i = 0; i < pair_count; i++) {
        int first = std::atoi(argv[1 + i * 2]);
        int second = std::atoi(argv[1 + i * 2 + 1]);
        
        // 작은값을 first, 큰값을 second로 정렬
        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }
        _pairs.push_back(std::pair<int, int>(first, second));
    }
}

void  PmergeMe::sort_big_values_vector()
{
        std::sort(_pairs.begin(), _pairs.end(), ComparePairs());
    
    _main_chain.clear();
    _pend_chain.clear();
    for(size_t i = 0; i < _pairs.size(); i++) {
        _main_chain.push_back(_pairs[i].second);  // 큰값
        _pend_chain.push_back(_pairs[i].first);   // 작은값
    }
}
void  PmergeMe::insert_small_values_vector()
{
    for (size_t i = 0; i < _pend_chain.size(); i++)  // int → size_t로 변경
    {
        // int k = _jacobsthal_sequence[i]; // 사용하지 않는 변수 제거
        int small = _pend_chain[i];
        int big = _pairs[i].second;
        //big 값의 위치 설정(오른쪽큰값을 제한범위로)
        std::vector<int>::iterator it_big = std::find(_main_chain.begin(), _main_chain.end(), big);
        //짝이었던 big 위치까지 binary_search찾기
        int index = Binary_Search(_main_chain, small, std::distance(_main_chain.begin(),it_big));
        //해당범위 small값 삽입
        _main_chain.insert(_main_chain.begin() + index, small);//진행중
    }
/*
    if (!_odd_num.empty()) {
        int odd_value = _odd_num[0];
        std::cout << "홀수 원소 " << odd_value << "를 전체 main_chain에서 이진탐색으로 삽입" << std::endl;
        
        // 전체 main_chain에서 이진탐색으로 적절한 위치 찾기
        int index = Binary_Search(_main_chain, odd_value, _main_chain.size() - 1);
        _main_chain.insert(_main_chain.begin() + index, odd_value);
        
        std::cout << "홀수 원소 삽입 완료" << std::endl;
    }
*/
}


//deque 함수들
void  PmergeMe::make_chain_deque(int argc, char **argv)
{
        // 홀수 원소가 있는지 확인 (실제 숫자 개수가 홀수인지)
    int total_numbers = argc - 1;  // argv[0]은 프로그램명 제외
    bool has_odd = (total_numbers % 2 == 1);
    
    // 홀수 원소가 있으면 마지막 원소를 따로 보관
    if (has_odd) {
        _odd_num_deq.push_back(std::atoi(argv[argc - 1]));
        std::cout << "홀수 원소 (deque): " << _odd_num_deq[0] << std::endl;
    }
    
    // 페어 생성 (홀수 원소 제외하고)
    int pair_count = total_numbers / 2;
    for (int i = 0; i < pair_count; i++) {
        int first = std::atoi(argv[1 + i * 2]);
        int second = std::atoi(argv[1 + i * 2 + 1]);
        
        // 작은값을 first, 큰값을 second로 정렬
        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }
        _pairs_deq.push_back(std::pair<int, int>(first, second));
    }
}
void  PmergeMe::sort_big_values_deque()
{
    std::sort(_pairs_deq.begin(), _pairs_deq.end(), ComparePairs());
    
    _main_chain_deq.clear();
    _pend_chain_deq.clear();
    for(size_t i = 0; i < _pairs_deq.size(); i++) {
        _main_chain_deq.push_back(_pairs_deq[i].second);  // 큰값
        _pend_chain_deq.push_back(_pairs_deq[i].first);   // 작은값
    }
}
void  PmergeMe::insert_small_values_deque()
{
    for (size_t i = 0; i < _pend_chain_deq.size(); i++)  // int → size_t로 변경
    {
        // int k = _jacobsthal_sequence_deq[i]; // 사용하지 않는 변수 제거
        int small = _pend_chain_deq[i];
        int big = _pairs_deq[i].second;
        //big 값의 위치 설정(오른쪽큰값을 제한범위로)
        std::deque<int>::iterator it_big = std::find(_main_chain_deq.begin(), _main_chain_deq.end(), big);
        //짝이었던 big 위치까지 binary_search찾기
        int index = Binary_Search_deque(_main_chain_deq, small, std::distance(_main_chain_deq.begin(),it_big));
        //해당범위 small값 삽입
        _main_chain_deq.insert(_main_chain_deq.begin() + index, small);//진행중
    }
}

void PmergeMe::insert_odd_element_deque()
{
    if (!_odd_num_deq.empty()) {
        int odd_value = _odd_num_deq[0];
        std::cout << "홀수 원소 " << odd_value << "를 전체 main_chain_deq에서 이진탐색으로 삽입" << std::endl;
        
        // 전체 main_chain_deq에서 이진탐색으로 적절한 위치 찾기
        int index = Binary_Search_deque(_main_chain_deq, odd_value, _main_chain_deq.size() - 1);
        _main_chain_deq.insert(_main_chain_deq.begin() + index, odd_value);
        
        std::cout << "홀수 원소 삽입 완료 (deque)" << std::endl;
    }
}

void PmergeMe::clear_vector_members()
{
    _main_chain.clear();
    _pend_chain.clear();
    _pairs.clear();
    _jacobsthal_sequence.clear();
    _odd_num.clear();
}

void PmergeMe::clear_deque_members()
{
    _main_chain_deq.clear();
    _pend_chain_deq.clear();
    _pairs_deq.clear();
    _jacobsthal_sequence_deq.clear();
    _odd_num_deq.clear();
}

// 디버깅용 함수들 구현
void PmergeMe::print_pairs() const
{
    std::cout << "Pairs: ";
    for (size_t i = 0; i < _pairs.size(); i++) {
        std::cout << "(" << _pairs[i].first << "," << _pairs[i].second << ") ";
    }

    std::cout << std::endl;
}

void PmergeMe::print_chains() const
{
    std::cout << "Main chain (큰값들): ";
    for (size_t i = 0; i < _main_chain.size(); i++) {
        std::cout << _main_chain[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Pend chain (작은값들): ";
    for (size_t i = 0; i < _pend_chain.size(); i++) {
        std::cout << _pend_chain[i] << " ";
    }
    std::cout << std::endl;    
}

void PmergeMe::print_jacobsthal() const
{
    std::cout << "Jacobsthal sequence: ";
    for (size_t i = 0; i < _jacobsthal_sequence.size(); i++) {
        std::cout << _jacobsthal_sequence[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_pairs_deq() const
{
    std::cout << "Pairs (deque): ";
    for (size_t i = 0; i < _pairs_deq.size(); i++) {
        std::cout << "(" << _pairs_deq[i].first << "," << _pairs_deq[i].second << ") ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_chains_deq() const
{
    std::cout << "Main chain (큰값들, deque): ";
    for (size_t i = 0; i < _main_chain_deq.size(); i++) {
        std::cout << _main_chain_deq[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Pend chain (작은값들, deque): ";
    for (size_t i = 0; i < _pend_chain_deq.size(); i++) {
        std::cout << _pend_chain_deq[i] << " ";
    }
    std::cout << std::endl;    
}

void PmergeMe::print_jacobsthal_deq() const
{
    std::cout << "Jacobsthal sequence (deque): ";
    for (size_t i = 0; i < _jacobsthal_sequence_deq.size(); i++) {
        std::cout << _jacobsthal_sequence_deq[i] << " ";
    }
    std::cout << std::endl;
}

void    PmergeMe::end_print(int argc, char ** argv)
{
    std::cout<<"Before : ";
    for (int i = 1; i < argc; i++)
        std::cout<<argv[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"After : ";
    for (size_t i = 0; i < _main_chain.size(); i++)
        std::cout<<_main_chain[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Time to process a range of "<<_main_chain.size()<<" elements with std::vector : " \
    <<std::fixed<<std::setprecision(7)<<(double)_time_vector / 1000000.0 <<" us"<<std::endl;
    std::cout<<"Time to process a range of "<<_main_chain_deq.size()<<" elements with std::deque : " \
    <<std::fixed<<std::setprecision(7)<<(double)_time_deque / 1000000.0<<" us"<<std::endl;
}

const std::vector<int>& PmergeMe::get_main_chain() const 
{
    return _main_chain;
}
const std::deque<int>& PmergeMe::get_main_chain_deque() const
{
    return _main_chain_deq;
}