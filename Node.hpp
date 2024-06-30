#ifndef Node_hpp
#define Node_hpp

#include <iostream>

class Node
{
public:
    enum NodeType
    {
        Safe = 0,
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Mine = 9

    };

    NodeType value;
    bool isVisible;

    Node(NodeType inputValue) : value(inputValue){};

    friend NodeType &operator++(NodeType &val)
    {
        val = static_cast<NodeType>(val + 1);
        return val;
    }

    friend NodeType operator++(NodeType &val, int)
    {
        NodeType preVal = val;
        ++val;
        return preVal;
    }

    friend ostream &operator<<(ostream &out, const NodeType &val)
    {
        if (val == Mine)
        {
            out << "*";
        }
        else
        {
            out << to_string(val);
        }
        return out;
    }
};

#endif /* Node_hpp */