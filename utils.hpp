#ifndef UTILS_HPP
#define UTILS_HPP

#include "pair.hpp"
#include "iterator_traits.hpp"

namespace ft {
    template <class T1, class T2, class Result>
	struct binary_function {
		typedef T1      first_type;
		typedef T2      second_type;
		typedef Result  result;
	};

	template <class T>
	struct less : public binary_function<T, T, bool> {
		bool operator()(const T& x, const T& y) const {
			return (x < y);
		}
	};
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> {
        typedef T type;
    };
    template<class InputIterator> 
    typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
    };
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        while (first1!=last1) {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2) {
        while (first1!=last1) {
            if (first2==last2 || *first2<*first1)
                return false;
            else if (*first1<*first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2!=last2);
    }
    struct true_integral {
		static const bool value = true;
	};

	struct false_integral {
		static const bool value = false;
	};
    template<class T>
    struct is_integral: public false_integral {};
    template<>
    struct is_integral<bool> : public true_integral {};
    template<>
    struct is_integral<char> : public true_integral {};
    template<>
    struct is_integral<unsigned char> : public true_integral {};
    template<>
    struct is_integral<wchar_t> : public true_integral {};
    template<>
    struct is_integral<short> : public true_integral {};
    template<>
    struct is_integral<unsigned short> : public true_integral {};
    template<>
    struct is_integral<int> : public true_integral {};
    template<>
    struct is_integral<unsigned int> : public true_integral {};
    template<>
    struct is_integral<long> : public true_integral {};
    template<>
    struct is_integral<unsigned long> : public true_integral {};
    template<>
    struct is_integral<long long> : public true_integral {};
    template<>
    struct is_integral<unsigned long long> : public true_integral {};
}

#endif