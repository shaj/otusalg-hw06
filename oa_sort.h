
#pragma once

#include <vector>
#include <iterator>


namespace otusalg
{


/**
   Сортировка вставкой на С
 */
template <typename T>
int insertion_sort(std::vector<T> &v)
{
	T x;
	int j;
	for(int i=1; i<v.size(); i++)
	{
		x = v[i];
		j = i - 1;
		while((j >= 0) && (v[j] > x))
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = x;
	}
	return 0;
}

/**
 Сортировка вставкой на С++
 */
template <typename RandomAccessIterator, typename Compare>
void ins_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	for(RandomAccessIterator i = first + 1; i != last; ++i)
		for(RandomAccessIterator j=i; ((j-first) >= 1) && comp(*j, *(j-1)); --j)
			std::swap(*j, *(j-1));
}


// Отсюда
// https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D0%A8%D0%B5%D0%BB%D0%BB%D0%B0#%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F_%D0%BD%D0%B0_C++
template< typename RandomAccessIterator, typename Compare >
void shell_sort( RandomAccessIterator first, RandomAccessIterator last, Compare comp )
{
	for( typename std::iterator_traits< RandomAccessIterator >::difference_type d = ( last - first ) / 2; d != 0; d /= 2 )
		for( RandomAccessIterator i = first + d; i != last; ++i )
			for( RandomAccessIterator j = i; j - first >= d && comp( *j, *( j - d ) ); j -= d )
				std::swap( *j, *( j - d ) );
}


/**
 Сортировка Шелла на С
 */
template <typename T>
int shell_sort_c(std::vector<T> &v)
{
	for(int d=(v.size()/2); d!=0; d /= 2)
		for(int i=d; i < v.size(); i++)
			for(int j=i; j >= d && (v[j] < v[j-d]); j -= d)
				std::swap(v[j], v[j-d]);
}


/**
 Сортировка Шелла на С без вычисления размера промежутка.
 Количество и значения промежутков должны быть вычислены заранее
 в зависимости от размера массива данных
 */
template <typename T>
int shell_sort_ck(std::vector<T> &v, const std::vector<int> &steps)
{
	for(int d: steps)
		for(int i=d; i < v.size(); i++)
			for(int j=i; j >= d && (v[j] < v[j-d]); j -= d)
				std::swap(v[j], v[j-d]);
}




} // namespace otusalg

