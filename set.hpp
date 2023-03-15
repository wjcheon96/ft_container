#ifndef SET_HPP
#define SET_HPP

#include "RBtree.hpp"
#include "utils.hpp"
#include <memory>

namespace ft {
    template < typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> > 
    class set {
        public:
            typedef T                           key_type;
            typedef T                           value_type;
            typedef Compare                     key_compare;
            typedef Compare                     value_compare;
            typedef Alloc                       allocator_type;
            typedef size_t                      size_type;
            typedef ptrdiff_t                   difference_type;

            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;

            typedef typename ft::RBtree_iterator<value_type>            iterator;
            typedef typename ft::RBtree_const_iterator<value_type>      const_iterator;
            typedef ft::reverse_iterator<iterator>                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        
        private:
            key_compare														_comp;
            allocator_type													_alloc;
            ft::RBtree<value_type, value_compare, allocator_type>           _tree;
        public:
            explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
            : _comp(comp), _alloc(alloc), _tree(value_compare(_comp), _alloc) {}
            template <class InputIterator>
            set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            : _comp(comp), _alloc(alloc), _tree(value_compare(_comp), _alloc) {
                insert(first, last);
            }
            set (const set& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}
		    ~set() {}
            set& operator=(const set& x) {
                if (this == &x)
                    return *this;
                _tree = x._tree;
                return *this;
		    } 
            iterator begin() {return _tree.begin();}
            const_iterator begin() const {return _tree.begin();}

            iterator end() {return _tree.end();}
            const_iterator end() const {return _tree.end();}

            reverse_iterator rbegin() {return _tree.rbegin();}
            const_reverse_iterator rbegin() const {return _tree.rbegin();}

            reverse_iterator rend() {return _tree.rend();}
            const_reverse_iterator rend() const {return _tree.rbegin();}

            bool empty() const {return _tree.empty();}
            size_type size() const {return _tree.size();}
            size_type max_size() const {return _tree.max_size();}
 
            key_type& operator[](const key_type& k){
                return (*((this->insert(ft::make_pair(k, key_type()))).first)).second;
            }

            pair<iterator, bool> insert(const value_type& val){
                return _tree.insert(val);
            }
            iterator insert(iterator position, const value_type& val){
                (void) position;
                return _tree.insert(val).first;
            }
            template<typename InputIterator>
            void insert(InputIterator first, InputIterator last){
                _tree.insert(first, last);
            }

            void erase(iterator position){
                _tree.erase(position);
            }
            size_type erase(const value_type& val){
                return _tree.erase(val);
            }
            void erase(iterator first, iterator last){
                _tree.erase(first, last);
            }
            void swap(set& x){
                _tree.swap(x._tree);
            }
            void clear(){
                _tree.clear();
            }
            key_compare key_comp() const{
                return _comp;
            }
            value_compare value_comp() const{
                return _comp;
            }

            iterator find(const value_type& val) const {
                return _tree.find(val);
            }
            size_type count(const value_type& val) const {
                return _tree.count(val);
            }
        
            iterator lower_bound(const value_type& val) const {
                    iterator it1 = this->begin();
                    iterator it2 = this->end();
                    while (it1 != it2) {
                        if (_comp(*it1, val) == false)
                            break;
                        ++it1;
                    }
                    return it1;
            }

            iterator upper_bound(const value_type& val) const {
                    iterator it1 = this->begin();
                    iterator it2 = this->end();
                    while (it1 != it2) {
                        if (_comp(val, *it1) == true)
                            break;
                        ++it1;
                    }
                    return it1;
            }
        
            pair<iterator, iterator> equal_range(const value_type& val) const{
                return ft::make_pair(lower_bound(val), upper_bound(val));
            }
            allocator_type get_allocator() const{
                return allocator_type();
            }

    };
    template <class T, class Compare, class Alloc>
	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) {
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>
	bool operator==(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		if (x.size() != y.size())
			return false;
		return ft::equal(x.begin(), x.end(), y.begin());
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(x == y);
	}

	template <class T, class Compare, class Alloc>
	bool operator<(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(y < x);
	}

	template <class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return y < x;
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(const set<T, Compare, Alloc>& x, const set<T, Compare, Alloc>& y) {
		return !(x < y);
	}
}

#endif