
#pragma once

#include <vector>
#include <iterator>
#include <thread>
#include <functional>

#include "oa_sort.h"


namespace otusalg
{

static const auto merge_min = 4000U;

template <typename T, typename Compare>
void merge_sort(std::vector<T> &v, Compare comp)
{
	// std::cout << "Vector size is " << v.size() << std::endl;
	if(v.size() < merge_min)
	{
		insertion_sort(v, comp);
		return;
	}

	auto li = v.begin();
	auto ri = v.begin();
	std::advance(ri, v.size()/2);
	auto mid = ri;

	std::vector<T> nv1(li, ri);
	std::vector<T> nv2(ri, v.end());
	merge_sort(nv1, comp);
	merge_sort(nv2, comp);

	li = nv1.begin();
	ri = nv2.begin();
	for(auto i = v.begin(); i != v.end(); i++)
	{
		if(comp(*li, *ri))
		{ // В массив записываем li
			if(li != nv1.end())
			{
				*i = *li;
				li++;
			}
			else
			{
				*i = *ri;
				ri++;
			}
		}
		else
		{ // В массив записываем ri
			if(ri != nv2.end())
			{
				*i = *ri;
				ri++;
			}
			else
			{
				*i = *li;
				li++;
			}
		}
	}

}




template <typename T, typename Compare>
void merge_sort_mt(std::vector<T> &v, Compare comp)
{
	// std::cout << "Vector size is " << v.size() << std::endl;
	if(v.size() < merge_min)
	{
		insertion_sort(v, comp);
		return;
	}

	auto li = v.begin();
	auto ri = v.begin();
	std::advance(ri, v.size()/2);
	auto mid = ri;

	std::vector<T> nv1(li, ri);
	std::vector<T> nv2(ri, v.end());
	
	std::thread t1(merge_sort_mt<T, Compare>, std::ref(nv1), comp);
	std::thread t2(merge_sort_mt<T, Compare>, std::ref(nv2), comp);

	t1.join();
	t2.join();

	li = nv1.begin();
	ri = nv2.begin();
	for(auto i = v.begin(); i != v.end(); i++)
	{
		if(comp(*li, *ri))
		{ // В массив записываем li
			if(li != nv1.end())
			{
				*i = *li;
				li++;
			}
			else
			{
				*i = *ri;
				ri++;
			}
		}
		else
		{ // В массив записываем ri
			if(ri != nv2.end())
			{
				*i = *ri;
				ri++;
			}
			else
			{
				*i = *li;
				li++;
			}
		}
	}

}




// template< typename Iter, typename Compare >
// void merge_sort_it( Iter first, Iter last, Compare comp )
// {

// 	auto d = (last - first);
// 	std::cout << "Vector size is " << d << std::endl;
// 	if(d < merge_min)
// 	{
// 		ins_sort(first, last, comp);
// 		return;
// 	}

// 	std::vector<typename std::iterator_traits<Iter>::value_type> v(d);
// 	std::copy(first, last, std::back_inserter(v));

// 	auto mid = v.size() / 2;
// 	// std::thread t1(test_thread, v, 0, 5);
// 	// std::thread t2(test_thread, v, 6, 10);
// 	// t1.join();
// 	// t2.join();

// 	auto li = v.begin();
// 	auto ri = v.begin();
// 	std::advance(ri, mid);

// 	merge_sort(li, ri, comp);
// 	merge_sort(ri, v.end(), comp);

// 	for(auto i = first; i != last; i++)
// 	{
// 		if(*li > *ri)
// 		{
// 			if(ri != v.end())
// 			{
// 				*i = *ri;
// 				ri++;
// 			}
// 			else
// 			{
// 				*i = *li;
// 				li++;
// 			}
// 		}
// 		else
// 		{
// 			if(li != v.begin() + mid)
// 			{
// 				*i = *li;
// 				li++;
// 			}
// 			else
// 			{
// 				*i = *ri;
// 				ri++;
// 			}
// 		}
// 	}

// }


} // namespace otusalg

