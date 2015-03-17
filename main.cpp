#include <iostream>
#include <vector>

template<class T>
struct Node {
    std::vector<Node> children;
    T value;
};

template<class T>
std::vector<T> eraseElement(const std::vector<T>& vec, T element) {
    std::vector<T> ret = vec;
    ret.erase(
        std::remove(
            ret.begin(),
            ret.end(),
            element),
        ret.end());
    return ret;
}

template<class T>
std::vector<Node<T>> createNode(std::vector<T> seeds) {
    std::vector<Node<T>> ret;
    if (seeds.size() == 1) {
        std::vector<Node<T>> emptyChildren;
        std::vector<Node<T>> ret = {{emptyChildren, seeds.front()}};
        return ret;
    } else {
        for (const auto& seed : seeds) {
            ret.push_back({createNode(eraseElement(seeds, seed)), seed});
        }
        return ret;
    }
}

template<class T>
std::vector<std::vector<T>> traverse(const Node<T>& node) {
    if (node.children.empty()) {
        return {{node.value}};
    } else {
        std::vector<std::vector<T>> ret;
        for (const auto& child : node.children) {
            for (const auto& childSequence : traverse(child)) {
                ret.push_back(childSequence);
            }
        }
        for (auto& sequence : ret) {
            sequence.push_back(node.value);
        }
        return ret;
    }
}

template<class T>
std::vector<std::vector<T>> getAllSequence(const std::vector<T>& seed)
{
    static const T rootValue = 0;
    Node<T> root = {createNode(seed), rootValue};
    std::vector<std::vector<T>> ret = traverse(root);
    // remove last element which is used only to instantiate root
    for (auto& sequence : ret) {
        sequence.pop_back();
    }
    return ret;
}

int main(void) {
    std::vector<std::vector<int>> result = getAllSequence<int>({1,2,3,4});
    for (const auto& a : result) {
        for (const auto& b : a) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
