#include <vector>

using namespace std;

class MinStack {
private:
    vector<pair<int,int>> _minstack;
public:
    /** initialize your data structure here. */
    MinStack() {
        _minstack.clear();
    }
    
    void push(int x) {
        if(_minstack.empty())_minstack.push_back(make_pair(x,x));
        else _minstack.push_back(
            make_pair(x,
                x<_minstack.back().second?x:_minstack.back().second));
    }
    
    void pop() {
        if(!_minstack.empty())_minstack.pop_back();
    }
    
    int top() {
        if(!_minstack.empty())return _minstack.back().first;
        else return INT_MAX;
    }
    
    int getMin() {
        if(!_minstack.empty())return _minstack.back().second;
        else return INT_MAX;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */