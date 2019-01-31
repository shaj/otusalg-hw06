
#pragma once

#include <vector>
#include <iterator>

#include "oa_sort.h"


namespace otusalg
{

template< typename RandomAccessIterator, typename Compare >
void merge_sort( RandomAccessIterator first, RandomAccessIterator last, Compare comp )
{
	auto d = (last - first);
	if(d < merge_min)
	{
		ins_sort(first, last, comp);
		break;
	}

	std::vector<typename std::iterator_traits<Iter>::value_type> v(d);
	std::copy(first, last, std::back_inserter(v));

	auto mid = v.end() / 2;
	auto t1 = std::thread(merge_sort, v.begin(), mid, comp);
	auto t2 = std::thread(merge_sort, mid + 1, v.end(), comp);

	t1.join();
	t2.join();

	for(auto i = first; i < last; i++)
	{
		if(*li > *ri)
		{
			if(ri < v.end())
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
		else
		{
			if(li < mid)
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
	}

}


} // namespace otusalg

