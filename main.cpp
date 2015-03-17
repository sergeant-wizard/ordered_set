#include <iostream>
#include <vector>


void print(const std::vector<int> vec) {
    for (const auto& a : vec) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

struct Node {
    std::vector<Node> children;
    int value;
};

std::vector<Node> createNode(std::vector<int> seeds) {
    std::vector<Node> ret;
    if (seeds.size() == 1) {
        std::vector<Node> emptyChildren;
        std::vector<Node> ret = {{emptyChildren, seeds.front()}};
        return ret;
    } else {
        for (const auto& seed : seeds) {
            std::vector<int> childrenSeeds = seeds;
            childrenSeeds.erase(
                std::remove(
                    childrenSeeds.begin(),
                    childrenSeeds.end(),
                    seed),
                childrenSeeds.end());
            ret.push_back({createNode(childrenSeeds), seed});
        }
        return ret;
    }
}

std::vector<std::vector<int>> traverse(const Node& node) {
    if (node.children.empty()) {
        return {{node.value}};
    } else {
        std::vector<std::vector<int>> ret;
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

std::vector<std::vector<int>> getAllSequence(const std::vector<int>& seed)
{
    static const int rootValue = 0;
    Node root = {createNode(seed), rootValue};
    std::vector<std::vector<int>> ret = traverse(root);
    // remove last element which is used only to instantiate root
    for (auto& sequence : ret) {
        sequence.pop_back();
    }
    return ret;
}

int main(void) {
    std::vector<std::vector<int>> result = getAllSequence({1,2,3,4});
    for (const auto& a : result) {
        for (const auto& b : a) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
