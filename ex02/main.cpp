#include <iostream>
#include "PmergeMe.hpp"
#include <sys/time.h>
#include <vector>
#include <cstdlib>

int main(int argc, char **argv)
{
    PmergeMe pmergeme;// 입력 파싱 및 검증

    struct timeval start_time, end_time;
    long long time_diff;

        if (argc < 2) {
            std::cerr<<"Error"<<std::endl;
            return (-1);
    }

    if (pmergeme.check_dup(argc, argv) != 0) {
        std::cerr<<"argument dup"<<std::endl;
        return (-1);
    }
    
    std::vector<int> original_data;
    for (int i = 1; i < argc; i++)
        original_data.push_back(std::atoi(argv[i]));
    std::cout<<"before :";
    for (size_t i = 0; i <original_data.size(); i++)
        std::cout<<original_data[i]<<" ";
    std::cout<<std::endl;
    
    pmergeme.clear_vector_members();
    gettimeofday(&start_time, NULL);
    pmergeme.make_chain_vector(argc, argv);
    // std::cout<<"debug checkkkk"<<std::endl;
    // pmergeme.print_pairs();
    pmergeme.sort_big_values_vector();
    // std::cout<<"debug checkkkk"<<std::endl;
    // pmergeme.print_chains();
    pmergeme.jacobsthal_sequence();
    pmergeme.insert_small_values();
    // std::cout<<"debug checkkkk"<<std::endl;
    // pmergeme.print_chains();
    pmergeme.insert_odd_element();
    gettimeofday(&end_time, NULL);
    time_diff = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    pmergeme._time_vector = time_diff;
    std::cout<<"After [vector] : ";
    for (size_t i = 0; i < pmergeme.get_main_chain().size(); ++i)
        std::cout<<pmergeme.get_main_chain()[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"------vector 작업 끝, deque 시작-------"<<std::endl;
    pmergeme.clear_deque_members();
    gettimeofday(&start_time, NULL);
    pmergeme.make_chain_deque(argc, argv);
    pmergeme.sort_big_values_deque();
    pmergeme.jacobsthal_sequence_deque();
    pmergeme.insert_small_values_deque();
    pmergeme.insert_odd_element_deque();
    gettimeofday(&end_time, NULL);
    time_diff = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    pmergeme._time_deque = time_diff;
    std::cout<<"After [deque] : ";
    for (size_t i = 0; i <pmergeme.get_main_chain_deque().size(); ++i)
        std::cout<<pmergeme.get_main_chain_deque()[i]<<" ";
    std::cout<<std::endl;

    std::cout<<"--------deque 끝"<<std::endl;
    pmergeme.end_print(argc, argv);
    
    return (0);
}

/*

전체 요약 프로세스 (코딩 흐름)
pair 묶기 및 작은값-큰값 식별/저장

큰값 리스트 정렬 (재귀적으로 repeat)

pend_chain을 Jacobsthal 순서로 블록 단위 역순 분할 → 해당 구간별로 반복:

각 작은 값을 짝의 큰값 앞 공간에서만 이진탐색 후 main_chain에 삽입

홀수 원소는 마지막에 main_chain 전체에서 이진탐색 삽입

*/