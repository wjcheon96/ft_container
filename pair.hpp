#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
    template <class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        T1  first;
        T2  second;

        pair() : first(T1()), second(T2()) {}
        pair(const T1& _first, const T2 _second) : first(_first), second(_second) {}
        
        template <class TP1, class TP2>
        pair(const pair<TP1, TP2>& _p) : first(_p.first), second(_p.second) {}

        pair& operator=(const pair& pr) {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };
    template <class T1, class T2>  
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    };
    template <class T1, class T2>  
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (!(lhs == rhs));
    };
    template <class T1, class T2>  
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return ((lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second));
    };
    template <class T1, class T2>  
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (!(rhs < lhs));
    };
    template <class T1, class T2>  
    bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (rhs < lhs);
    };
    template <class T1, class T2>  
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (!(lhs < rhs));
    };
    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y) {
        return ( pair<T1,T2>(x,y) );
    };
}



#endif