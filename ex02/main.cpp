#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    PmergeMe pmergeme;// 입력 파싱 및 검증
        if (argc < 2)
            return (1);

    //pair 묶기 및 작은값-큰값 식별/저장하기
    pmergeme.make_chain(argc, argv);

    //큰값 리스트 정렬
    pmergeme._sort_big_values();
    //pend_chain을 Jacobsthal 순서로 블록 단위 역순 분할 → 해당 구간별로 반복:
    pmergeme.jacobsthal_sequence();
    //각 작은 값을 짝의 큰값 앞 공간에서만 이진탐색 후 main_chain에 삽입
    pmergeme.insert_small_values();
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