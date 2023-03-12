#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "RBtree_iterator_traits.hpp"
#include "RBtree_node.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
    template<typename T, typename Compare, typename Alloc = std::allocator<T> > 
    class RBTree {
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
            RBTree(value_compare const& comp, allocator_type const& alloc, node_alloc_type const& node_alloc = node_alloc_type())
            : _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _root(NULL), _nil(NULL), _size(0) {
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, node_type());
                _root = _nil;
				_nil->color = BLACK;
            }
            RBTree(const RBTree& x) : _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(NULL), _size(0) {
                _nil = _node_alloc.allocate(1);
				_node_alloc.construct(_nil, node_type());
                _root = _nil;
				_nil->color = BLACK;
			}
			iterator				begin() { return iterator(rbtree_min(_root)); }
			const_iterator			begin() const { return const_iterator(rbtree_min(_root)); }
			iterator				end() { return iterator(_nil); }
			const_iterator			end() const { return const_iterator(_nil); }
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
        private:
            void    right_rotate(NodePtr node) {
                NodePtr left_child = node->left;

                node->left = left_child->right;
                if (left_child != _nil) {
                    left_child->right->parent = node;
                }
                left_child->parent = node->parent;
                if (node->parent == _nil) {
                    _root = left_child;
                }
                else if (node == node->parent->left) {
                    node->parent->left = left_child;
                }
                else {
                    node->parent->right = left_child;
                }
                left_child->right = node;
                node->parent = left_child;
            }
            void    left_rotate(NodePtr node) {
                NodePtr right_child = node->right;
                node->right = right_child->left;

                if (right_child != _nil) {
                    right_child->left->parent = node;
                }
                right_child->parent = node->parent;
                if (node->parent == _nil) {
                    _root = right_child;
                }
                else if (node == node->parent->left) {
                    node->parent->left = right_child;
                }
                else {
                    node->parent->right = right_child;
                }
            }
            void    delete_tree(NodePtr node) {
                if (node != _nil) {
                    delete_tree(node->left);
                    delete_tree(node->right);
                    _node_alloc.destroy(node);
				    _node_alloc.deallocate(node, 1);
                }
            }
        public:
            bool empty() const {
				return (_size == 0);
			}

			size_type size() const {
				return _size;
			}

			size_type max_size() const {
				return (_node_alloc.max_size());
			}
//---------------------------------insert--------------------------------------
            pair<iterator, bool> insert_value(const value_type& val) {
                NodePtr node = _node_alloc.allocate(1);
				_node_alloc.construct(node, node_type(val));

                NodePtr y = _nil;
                NodePtr x = _root;
                while (x != _nil) {
                    y = x;
                    if (_comp(node->value, x->value)) {
                        x = x->left;
                    }
                    else if (_comp(x->value, node->value)) {
                        x = x->right;
                    }
                    else {
                        _node_alloc.destroy(node);
    					_node_alloc.deallocate(node, 1);
                        return (ft::make_pair(iterator(x), false));
                    }
                }
                _size++;
                node->parent = y;
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
                node->color = RED;
                bool ret = insert_fixup(node);
                return (ft::make_pair(iterator(node), ret));
            }

            bool    insert_fixup(NodePtr z) {
                while (node->parent->color == RED) {
                    if (node->parent == node->parent->parent->left) {
                        NodePtr y = z->parent->parent->right;
                        if (y->color = RED) {
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        }
                        else {
                            if (z == z->parent->right) {
                                z = z->parent;
                                left_rotate(z);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED:
                            right_rotate(z->parent->parent);
                        }
                    }
                    else {
                        NodePtr y = z->parent->parent->left;
                        if (y->color = RED) {
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        }
                        else {
                            if (z == z->parent->left) {
                                z = z->parent;
                                right_rotate(z);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED;
                            left_rotate(z->parent->parent);
                        }
                    }
                }
                t->root->color = BLACK;
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
				for (InputIterator it = first; it != last; ++it) {
					insert(*it);
				}
			}
//---------------------------search------------------------------------------
            NodePtr find_node(const value_type& val) {
                NodePtr node = _root;
                while (node != _nil && node->_val != val) {
                    if (_comp(node->val, val)) {
                        node = node->right; 
                    }
                    else (_comp(node->val, val)) {
                        node = node->left;
                    }
                }
                if (node->val == val && node != _nil) {
                    return (node);
                }
                return (NULL);
            }
            iterator find(const value_type& val) {
                NodePtr node = _root;
                while (node != _nil && node->_val != val) {
                    if (_comp(node->val, val)) {
                        node = node->right; 
                    }
                    else (_comp(node->val, val)) {
                        node = node->left;
                    }
                }
                if (node->val == val && node != _nil) {
                    return (iterator(node));
                }
                return (iterator(_root));
            }
            NodePtr rbtree_min() {
                NodePtr cur = _root;
                while (cur->left != _nil) {
                    cur = cur->left;
                }
                return cur;
            }
            NodePtr rbtree_max() {
                NodePtr cur = _root;
                while (cur -> right != _nil) {
                    cur = cur->right;
                }
                return cur;
            }
            void clear() {
                delete_tree(_root);
                _root = NULL;
                _size = 0;
            }

//---------------------------erase-------------------------------------------
            void    transplate(NodePtr u, NodePtr v) {
                if (u->parent == _nil) {
                    _root = v;
                }
                else if (u == u->parent->left) {
                    u->parent->left = v;
                }
                else {
                    u->parent->right = v;
                }
                v->parent = u->parent;
            }
            NodePtr tree_minimum(NodePtr cur) {
                NodePtr y;
                y = cur;
                while (y->left != _nil) {
                    y = y->left;
                }
                return y;
            }
            size_t delete_value(const value_type& val) {
                NodePtr z = find_node(val);
                if (z == NULL)
                    return (0);
                NodePtr y = z;
                NodePtr x;                
                bool    y_origin_color = y->color;
                
                _size--;
                if (z->left == _nil) {
                    x = z->right;
                    transplant(z, z->right)
                }
                else if (z->right == _nil) {
                    x= z->left;
                    transplant(z, z->left);
                }
                else {
                    y = tree_minimum(z->right);
                    y_origin_color = y->color;
                    x = y->right;
                    if (y->parent == z) {
                        x->parent = y;
                    }
                    else {
                        transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    rb_transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }
                if (y_origin_color == BLACK) {
                    delete_fixup(x);
                }
                _node_alloc.destroy(x);
                _node_alloc.deallocate(x, 1);
                return (1);
            }
            void    delete_fixup(NodePtr x) {
                while (x != _root && x->color = BLACK) {
                    if (x == x->parent->left) {
                        NodePtr w = x->parent->right;
                        if (w->color = RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            left_rotate(x->parent);
                            w = x->parent->right;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        }
                        else {
                            if (w->right->color == BLACK) {
                                w->left->color = BLACK;
                                w->color = RED;
                                right_rotate(w);
                                w = x->parent->right;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->right->color = BLACK;
                            left_rotate(x->parent);
                            x = _root;
                        }
                    }
                    else {
                        NodePtr w = x->parent->left;
                        if (w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            right_rotate(x->parent);
                            w = x->parent->left;
                        }
                        if (w->right->color == BLACk && w->left->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        }
                        else {
                            if (w->left->color = BLACK) {
                                w->right->color = BLACK;
                                w->color = RED;
                                left_rotate(w);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            w->parent->color = BLACK;
                            w->left->color = BLACK;
                            right_rotate(x->parent);
                            x = _root;
                        }
                    }
                }
                x->color = BLACK;
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
            void swap(red_black_tree& obj) {
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
				_root = _root;
				_nil = _nil;
				_size = tmp_size;
			}
    };
}

#endif