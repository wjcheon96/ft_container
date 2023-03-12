#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft
{
    template<class T, class Alloc = std::allocator<T> > class vector {
        public:
            typedef T                                                           value_type;
            typedef Alloc                                                       allocator_type;
            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;
            typedef typename ft::random_access_iterator<value_type*>                   iterator;
            typedef typename ft::random_access_iterator<const value_type*>             const_iterator;
            typedef typename ft::reverse_iterator<iterator>                         reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>                   const_reverse_iterator; 
            typedef typename allocator_type::difference_type                    difference_type;
            typedef typename allocator_type::size_type                          size_type;
            explicit vector (const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _begin = _alloc.allocate(0);
                _end = _begin;
                _capacity = _begin;
            }
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _begin(NULL), _end(NULL), _capacity(NULL), _alloc(alloc) {
                _begin = _alloc.allocate(n);
                _end = _begin;
                _capacity = _begin + n;
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_end, val);
                    _end++;
                }
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) 
            : _begin(NULL), _end(NULL), _capacity(NULL), _alloc(alloc) {
                size_type n = ft::distance(first, last);
                _begin = _alloc.allocate(n);
                _end = _begin;
                _capacity = _end + n;
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_end, *first);
                    _end++;
                    first++;
                }
            }
            vector (const vector& x) : _begin(NULL), _end(NULL), _capacity(NULL) {
                _alloc = x._alloc;
                assign(x.begin(), x.end());
            }
            size_type size() const {
                return (_end - _begin);
            }
            ~vector() {
                clear();
                _alloc.deallocate(_begin, capacity());
            }
            vector& operator=(const vector& x) {
                _alloc = x._alloc;
                assign(x.begin(), x.end());
                return (*this);
            }
            iterator begin() {
                return (_begin);
            }
            const_iterator begin() const {
                return (_begin);
            }
            iterator end() {
                return (_end);
            }
            const_iterator end() const {
                return (_end);
            }
			reverse_iterator rbegin() {
                return reverse_iterator(_end);
            }
			const_reverse_iterator rbegin() const {
                return const_reverse_iterator(_end);
            }
			reverse_iterator rend() {
                return reverse_iterator(_begin);
            }
			const_reverse_iterator rend() const {
                return const_reverse_iterator(_begin);
            }
            size_type max_size() const {
                return (_alloc.max_size());
            }
            void resize (size_type n, value_type val = value_type()) {
                if (n > size()) {
                    if (n > capacity())
						reserve(n);
					for (size_type i = size(); i < n; i++) {
						_alloc.construct(_end, val);
						_end++;
					}
                } 
                else if (n < size()) {
					for (size_type i = size(); i > n; i--) {
						_alloc.destroy(_end);
						_end--;
					}
				}
            }
            size_type capacity() const {
                return (_capacity - _begin);
            }
            bool empty() const {
                return (_end == _begin);
            }
            void reserve (size_type n) {
                if (capacity() < n) {
                    pointer tmp;
                    tmp = _alloc.allocate(n);
                    size_type _size = size();
                    for (size_type i = 0; i < size(); i++) {    
                        _alloc.construct(&tmp[i], _begin[i]);
                    }
                    clear();
                    _alloc.deallocate(_begin, _size);
                    _begin = tmp;
                    _end = _begin + _size;
                    _capacity = _begin + n;
                }
            }
            reference operator[] (size_type n) {
                return (_begin[n]);
            }
            const_reference operator[] (size_type n) const {
                return (_begin[n]);
            }
            reference at (size_type n) {
                if (n >= size())
                    throw std::out_of_range("out of range");
                return (_begin[n]);
            }
            const_reference at (size_type n) const {
                if (n > size())
                    throw ("out of range");
                return (_begin[n]);
            }
            reference front() {
                return (*_begin);
            }
            const_reference front() const {
                return (*_begin);
            }
            reference back() {
                return (*(_end - 1));
            }
            const_reference back() const {
                return (*(_end - 1));
            }
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
                size_type n = ft::distance(first, last);
                if (n > capacity())
                    reserve(n);
                clear();
                for (size_type i = 0; i < n; i++) {
                    if (i < size())
                        _begin[i] = *first;
                    else {
                        _alloc.construct(_end, *first);
                        _end++;
                    }
                    first++;
                }
            }
            void assign (size_type n, const value_type& val) {
                if (n > capacity())
                    reserve(n);
                clear();
                for (size_type i = 0; i < n; i++) {
                    if (i < size())
                        _begin[i] = val;
                    else {
                        _alloc.construct(_end, val);
                        _end++;
                    }
                }
            }
            void push_back(const value_type& val) {
                if (size() == 0)
                    reserve(1);
                if (size() == capacity())
                    reserve(size() * 2);
                _alloc.construct(_end, val);
                _end++;
            }
            void pop_back() {
                if (size() != 0) {
                    _alloc.destroy(_end);
                }
                _end--;
            }
            iterator insert (iterator position, const value_type& val) {
                size_type n = position - begin();
                if (size() == capacity())
                    reserve(size() * 2);
                for (size_type i = size(); i > n; i--) {
                    _begin[i] = _begin[i - 1];
                } 
                _begin[n] = val;
                _end++;
                return (begin() + n);
            }
            void insert (iterator position, size_type n, const value_type& val) {
                size_type pos = position - begin();
                if (size() + n > capacity() * 2)
                    reserve(size() + n);
                else if (size() + n > capacity())
                    reserve(capacity() * 2);
                for (size_type i = size(); i > pos; i--) {
                    _begin[i + n - 1] = _begin[i - 1];
                }
                for (size_type i = 0; i < n; i++) {
                    _begin[pos + i] = val;
                }
                _end += n;
            }
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
                size_type n = ft::distance(first, last);
				size_type pos = position - begin();
                if (size() + n > capacity() * 2)
                    reserve(size() + n);
				else if (size() + n > capacity())
					reserve(capacity() * 2);
				for (size_type i = size(); i > pos; i--) {
					_begin[i + n - 1] = _begin[i - 1];
				}
				for (size_type i = 0; i < n; i++) {
					_begin[pos + i] = *first;
					first++;
				}
				_end += n;
            }
            iterator erase (iterator position) {
                size_type n = position - begin();
                for (size_type i = n; i < size() - 1; i++) {
                    _begin[i] = _begin[i + 1];
                } 
                _alloc.destroy(_end);
                _end--;
                return (begin() + n);
            }
            iterator erase (iterator first, iterator last) {
                size_type n = first - begin();
                size_type m = last - begin();
                for (size_type i = n; i < size() - (m - n); i++) {
                    _begin[i] = _begin[i + (m - n)];
                }
                for (size_type i = 0; i < (m - n); i++) {
                    _alloc.destroy(_end);
                    _end--;
                }
                return (begin() + n);
            }
            void swap (vector& x) {
                pointer tmp_begin = _begin;
                pointer tmp_end = _end;
                pointer tmp_capacity = _capacity;
                allocator_type tmp_alloc = _alloc;

                _begin = x._begin;
                _end = x._end;
                _capacity = x._capacity;
                _alloc = x._alloc;
                x._begin = tmp_begin;
                x._end = tmp_end;
                x._capacity = tmp_capacity;
                x._alloc = tmp_alloc;
            }
            void clear() {
                erase(begin(), end());
            }
            allocator_type get_allocator() const {
                return (_alloc);
            }
        private:
            pointer     _begin;
            pointer     _end;
            pointer     _capacity;
            allocator_type   _alloc;
    };
    template <class T, class Alloc>  
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i])
                return (false);
        }
        return (true);
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(rhs < lhs));
    }
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (!(lhs < rhs));
    }
    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        x.swap(y);
    }
}
#endif