#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

namespace ft {
    enum color { RED, BLACK };
    template <typename T>
    struct RBtree_node {
        T               _value;
        color           _color;
        RBtree_node*    _left;
        RBtree_node*    _right;
        RBtree_node*    _parent;

        RBtree_node() : _value(), _color(RED), _left(NULL), _right(NULL), _parent(NULL) {}
        RBtree_node(const T& value, color color = RED, RBtree_node* left = NULL, RBtree_node* right = NULL, RBtree_node* parent = NULL ) : _value(value), _color(color), _left(left), _right(right), _parent(parent) {}
        RBtree_node(const RBtree_node& obj) : _value(obj._value), _color(obj._color), _left(obj._left), _right(obj._right), _parent(obj._parent) {}
        ~RBtree_node() {}

        RBtree_node &operator=(const RBtree_node& obj) {
            _value = obj._value;
            _color = obj._color;
            _left = obj._left;
            _right = obj._right;
            _parent = obj._parent;
            return (*this);
        }
        bool operator==(const RedBlackTreeNode &other) const {
			return value == other.value;
		}
		bool operator!=(const RedBlackTreeNode &other) const {
			return value != other.value;
		}
    };
	template <class T1, class T2>
	bool operator==(const RBtree_node<T1> &lhs, const RBtree_node<T2> &rhs) {
		return lhs == rhs;
	}
	template <class T1, class T2>
	bool operator!=(const RBtree_node<T1> &lhs, const RBtree_node<T2> &rhs) {
		return lhs != rhs;
	}
};

#endif