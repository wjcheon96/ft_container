#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "RBtree_iterator_traits.hpp"
#include "RBtree_node.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
    template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> > 
    class RBtree {
        private:
			typedef ft::RBtree_node<T>									node_type;
			typedef ft::RBtree_node<T>* 								NodePtr;
			typedef typename Alloc::template rebind<node_type>::other	node_alloc_type;
		public:
			typedef T													value_type;
			typedef Compare												value_compare;
			typedef Alloc												allocator_type;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef ft::RBtree_iterator<value_type>						iterator;
			typedef ft::RBtree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
        private:
			value_compare	_comp;
			allocator_type	_alloc;
			node_alloc_type	_node_alloc;
			NodePtr			_root;
            NodePtr        	_nil;
			size_type		_size;
        public:
            RBtree(value_compare const& comp, allocator_type const& alloc, node_alloc_type const& node_alloc = node_alloc_type())
            : _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _root(NULL), _nil(NULL), _size(0) {
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, node_type());
                _root = _nil;
				_nil->_color = BLACK;
            }
            RBtree(const RBtree& x) : _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(NULL), _nil(NULL), _size(x._size) {
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, node_type());
                _root = _nil;
                _nil->_color = BLACK;
                if (x._root != x._nil) {
                    copy(x._root, x._nil);
                }
                _size = x._size;
            }
            RBtree& operator=(const RBtree& x) {
				if (this == &x) {
					return *this;
				}
				clear();
				_comp = x._comp;
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, node_type());
                _root = _nil;
                _nil->_color = BLACK;
				if(x._root != x._nil) {
					copy(x._root, x._nil);
				}
				_size = x._size;
				return *this;
			}
            virtual ~RBtree() {
				clear();
			}
			iterator				begin() { return iterator(rbtree_min(_root), _nil); }
			const_iterator			begin() const { return const_iterator(rbtree_min(_root), _nil); }
			iterator				end() { return iterator(_nil, _nil); }
			const_iterator			end() const { return const_iterator(_nil, _nil); }
			reverse_iterator		rbegin() { return reverse_iterator(end(), _nil); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end(), _nil); }
			reverse_iterator		rend() { return reverse_iterator(begin(), _nil); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin(), _nil); }
        private:
            void copy(NodePtr node, NodePtr nil) {
				if (node == nil)
					return ;
				insert_value(node->_value);
				copy(node->_left, nil);
				copy(node->_right, nil);
			}
            void    right_rotate(NodePtr node) {
                NodePtr left_child = node->_left;

                node->_left = left_child->_right;
                if (left_child->_right != _nil) {
                    left_child->_right->_parent = node;
                }
                left_child->_parent = node->_parent;
                if (node->_parent == _nil) {
                    _root = left_child;
                }
                else if (node == node->_parent->_left) {
                    node->_parent->_left = left_child;
                }
                else {
                    node->_parent->_right = left_child;
                }
                left_child->_right = node;
                node->_parent = left_child;
            }
            void    left_rotate(NodePtr node) {
                NodePtr right_child = node->_right;
                node->_right = right_child->_left;

                if (right_child->_left != _nil) {
                    right_child->_left->_parent = node;
                }
                right_child->_parent = node->_parent;
                if (node->_parent == _nil) {
                    _root = right_child;
                }
                else if (node == node->_parent->_left) {
                    node->_parent->_left = right_child;
                }
                else {
                    node->_parent->_right = right_child;
                }
                right_child->_left = node;
                node->_parent = right_child;
            }
            void    delete_tree(NodePtr node) {
                if (node != _nil) {
                    delete_tree(node->_left);
                    delete_tree(node->_right);
                    _node_alloc.destroy(node);
				    _node_alloc.deallocate(node, 1);
                }
            }
        public:
            bool empty() const {
				return (size() == 0);
			}

			size_type size() const {
				return _size;
			}

			size_type max_size() const {
				return (_node_alloc.max_size());
			}
//---------------------------------insert-----------------------------------
            pair<iterator, bool> insert_value(const value_type& val) {
                NodePtr node = _node_alloc.allocate(1);
				_node_alloc.construct(node, node_type(val));

                NodePtr y = _nil;
                NodePtr x = _root;
                while (x != _nil) {
                    y = x;
                    if (_comp(node->_value, x->_value)) {
                        x = x->_left;
                    }
                    else if (_comp(x->_value, node->_value)) {
                        x = x->_right;
                    }
                    else {
                        _node_alloc.destroy(node);
    					_node_alloc.deallocate(node, 1);
                        return (ft::make_pair(iterator(x, _nil), false));
                    }
                }
                _size++;
                node->_parent = y;
                if (y == _nil) {
                    _root = node;
                }
                else if (node->_value < y->_value) {
                    y->_left = node;
                }
                else
                    y->_right = node;
                node->_left = _nil;
                node->_right = _nil;
                node->_color = RED;
                bool ret = insert_fixup(node);
                return (ft::make_pair(iterator(node, _nil), ret));
            }

            bool    insert_fixup(NodePtr z) {
                while (z->_parent->_color == RED) {
                    if (z->_parent == z->_parent->_parent->_left) {
                        NodePtr y = z->_parent->_parent->_right;
                        if (y->_color == RED) {
                            z->_parent->_color = BLACK;
                            y->_color = BLACK;
                            z->_parent->_parent->_color = RED;
                            z = z->_parent->_parent;
                        }
                        else {
                            if (z == z->_parent->_right) {
                                z = z->_parent;
                                left_rotate(z);
                            }
                            z->_parent->_color = BLACK;
                            z->_parent->_parent->_color = RED;
                            right_rotate(z->_parent->_parent);
                        }
                    }
                    else {
                        NodePtr y = z->_parent->_parent->_left;
                        if (y->_color == RED) {
                            z->_parent->_color = BLACK;
                            y->_color = BLACK;
                            z->_parent->_parent->_color = RED;
                            z = z->_parent->_parent;
                        }
                        else {
                            if (z == z->_parent->_left) {
                                z = z->_parent;
                                right_rotate(z);
                            }
                            z->_parent->_color = BLACK;
                            z->_parent->_parent->_color = RED;
                            left_rotate(z->_parent->_parent);
                        }
                    }
                }
                _root->_color = BLACK;
                return (true);
            }

            pair<iterator, bool> insert (const value_type &val) {
                return (insert_value(val));
            }

            iterator insert(iterator pos, const value_type& val) {
				(void)pos;
				return (insert_value(val).first);
			}
            
			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				for (; first != last; ++first) {
					insert(*first);
				}
                print(_root);
            }

            void print(NodePtr n) {
                if (n == _nil)
                    return ;
                print(n->_left);
                std::cout << &n << " " << n->_value.first << " " << n->_value.second << std::endl;
                print(n->_right);
            }
//---------------------------search------------------------------------------
            NodePtr find_node(const value_type& val) {
                NodePtr node = _root;
                while (node != _nil && node->_value != val) {
                    if (_comp(val, node->_value)) {
                        node = node->_left;
                    }
                    else if (_comp(node->_value, val)) {
                        node = node->_right; 
                    }
                }
                if (node->_value == val && node != _nil) {
                    return (node);
                }
                return (_nil);
            }
            iterator find(const value_type& val) const {
                NodePtr node = _root;
                while (node != _nil && node->_value != val) {
                    if (_comp(val, node->_value)) {
                        node = node->_left;
                    }
                    else if (_comp(node->_value, val)) {
                        node = node->_right; 
                    }
                }
                if (node->_value == val && node != _nil) {
                    return (iterator(node, _nil));
                }
                return (iterator(_root, _nil));
            }
            NodePtr rbtree_min(NodePtr node) const {
                if (node == _nil) {
                    return _nil;
                }
                while (node->_left != _nil) {
                    node = node->_left;
                }
                return node;
            }
            NodePtr rbtree_max(NodePtr node) const {
                if (node == _nil) {
                    return _nil;
                }
                while (node->_right != _nil) {
                    node = node->_right;
                }
                return node;
            }
            void clear() {
                delete_tree(_root);
                _root = _nil;
                _size = 0;
            }

//---------------------------erase-------------------------------------------
            void    transplant(NodePtr u, NodePtr v) {
                if (u->_parent == _nil) {
                    _root = v;
                }
                else if (u == u->_parent->_left) {
                    u->_parent->_left = v;
                }
                else {
                    u->_parent->_right = v;
                }
                v->_parent = u->_parent;
            }
            NodePtr tree_minimum(NodePtr cur) {
                NodePtr y;
                y = cur;
                while (y->_left != _nil) {
                    y = y->_left;
                }
                return y;
            }
            size_t delete_value(const value_type& val) {
                NodePtr z = find_node(val);
                if (z == _nil)
                    return (0);
                NodePtr y = z;
                bool    y_origin_color = y->_color;
                NodePtr x;
                
                _size--;
                if (z->_left == _nil) {
                    x = z->_right;
                    transplant(z, z->_right);
                }
                else if (z->_right == _nil) {
                    x = z->_left;
                    transplant(z, z->_left);
                }
                else {
                    y = z->_right;
                    while (y->_left != _nil) {
                        y = y->_left;
                    }
                    y_origin_color = y->_color;
                    x = y->_right;
                    if (y != z->_right) {
                        transplant(y, y->_right);
                        y->_right = z->_right;
                        y->_right->_parent = y;
                    }
                    else
                        x->_parent = y;
                    transplant(z, y);
                    y->_left = z->_left;
                    y->_left->_parent = y;
                    y->_color = z->_color;
                }
                if (y_origin_color == BLACK)
                    delete_fixup(x);
                _node_alloc.destroy(z);
    		    _node_alloc.deallocate(z, 1);
                return (1);
            }
            void    delete_fixup(NodePtr x) {
                while (x != _root && x->_color == BLACK) {
                    if (x == x->_parent->_left) {
                        NodePtr w = x->_parent->_right;
                        if (w->_color == RED) {
                            w->_color = BLACK;
                            x->_parent->_color = RED;
                            left_rotate(x->_parent);
                            w = x->_parent->_right;
                        }
                        if (w->_left->_color == BLACK && w->_right->_color == BLACK) {
                            w->_color = RED;
                            x = x->_parent;
                        }
                        else {
                            if (w->_right->_color == BLACK) {
                                w->_left->_color = BLACK;
                                w->_color = RED;
                                right_rotate(w);
                                w = x->_parent->_right;
                            }
                            w->_color = x->_parent->_color;
                            x->_parent->_color = BLACK;
                            w->_right->_color = BLACK;
                            left_rotate(x->_parent);
                            x = _root;
                        }
                    }
                    else {
                        NodePtr w = x->_parent->_left;
                        if (w->_color == RED) {
                            w->_color = BLACK;
                            x->_parent->_color = RED;
                            right_rotate(x->_parent);
                            w = x->_parent->_left;
                        }
                        if (w->_right->_color == BLACK && w->_left->_color == BLACK) {
                            w->_color = RED;
                            x = x->_parent;
                        }
                        else {
                            if (w->_left->_color == BLACK) {
                                w->_right->_color = BLACK;
                                w->_color = RED;
                                left_rotate(w);
                                w = x->_parent->_left;
                            }
                            w->_color = x->_parent->_color;
                            w->_parent->_color = BLACK;
                            w->_left->_color = BLACK;
                            right_rotate(x->_parent);
                            x = _root;
                        }
                    }
                }
                x->_color = BLACK;
            }
            void erase(const_iterator position){
				delete_value(*position);
			}

			size_type erase(const value_type& val){
				return delete_value(val);
			}

			void erase(const_iterator first, const_iterator last){
				for (const_iterator it = first; it != last; ) {
					erase(it++);
				}
			}
            size_type count(const value_type& v) const {
				iterator tmp = find(v);
				if (tmp == end()) {
					return 0;
				}
				size_type count = 0;
				for (iterator it = tmp; it != end(); ++it) {
					if (!_comp(*it, v) && !_comp(v, *it)) {
						++count;
					}
				}
				return count;
			}
            void swap(RBtree& obj) {
				if (this == &obj) {
					return;
				}
				value_compare	tmp_comp = obj._comp;
				allocator_type	tmp_alloc = obj._alloc;
				node_alloc_type	tmp_node_alloc = obj._node_alloc;
				NodePtr 		tmp_root = obj._root;
                NodePtr        	tmp_nil = obj._nil;
				size_type		tmp_size = obj._size;

				obj._comp = _comp;
				obj._alloc = _alloc;
				obj._node_alloc = _node_alloc;
				obj._root = _root;
				obj._nil = _nil;
				obj._size = _size;

				_comp = tmp_comp;
				_alloc = tmp_alloc;
				_node_alloc = tmp_node_alloc;
				_root = tmp_root;
				_nil = tmp_nil;
				_size = tmp_size;
			}
    };
}

#endif