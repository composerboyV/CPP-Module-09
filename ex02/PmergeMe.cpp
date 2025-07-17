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
#include <vector>
#include <utility>
#include "PmergeMe.hpp"



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
            *this = other;
      return (*this);
}

void PmergeMe::make_chain(int argc, char **argv)
{
      for (int i = 1; i < argc; i +=2)
      {
            int first = std::atoi(argv[i]);
            int second = 0;
            if (i + 1 < argc)
                  second = std::atoi(argv[i + 1]);
            else {
                  _main_chain.push_back(first);
                  continue;
            }
            if (first > second) {
                  int temp = first;
                  first = second;
                  second = temp;
            }
            _pairs.push_back(std::pair<int, int>(first, second));
      }
}


void PmergeMe::_sort_big_values()
{
      for(int i = 0; i < _pairs.size(); i++) {
            _main_chain.push_back(_pairs[i].second);//큰값
            _pend_chain.push_back(_pairs[i].first);//작은값
      }
}
void PmergeMe::jacobsthal_sequence()
{}
void PmergeMe::insert_small_values()
{}