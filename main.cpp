#include <iostream>
#include <vector>

template<class T>
class OrderedSet {
public:
    OrderedSet() = delete;
    OrderedSet(const OrderedSet& other) = delete;
    virtual ~OrderedSet(){}
    OrderedSet(const std::vector<T>& seeds):
        seeds(seeds),
        numOrderedSets(factorial(seeds.size()))
    {
    }
    std::vector<std::vector<T>> getAllOrderedSets() {
        static const T rootValue = 0;
        Node root = {createNode(seeds), rootValue};
        std::vector<std::vector<T>> ret = traverse(root);
        // remove last element which is used only to instantiate root
        for (auto& sequence : ret) {
            sequence.pop_back();
        }
        return ret;
    }
    unsigned getNumOrderedSets() const {
        return numOrderedSets;
    }

private:
    struct Node {
        std::vector<Node> children;
        T value;
    };

    static unsigned factorial(unsigned n) {
        if (n > 1)
            return n * factorial(n-1);
        else
            return 1;
    }

    static std::vector<T> eraseElement(const std::vector<T>& vec, T element) {
        std::vector<T> ret = vec;
        ret.erase(
            std::remove(
                ret.begin(),
                ret.end(),
                element),
            ret.end());
        return ret;
    }

    static std::vector<Node> createNode(const std::vector<T>& seeds) {
        std::vector<Node> ret;
        if (seeds.size() == 1) {
            std::vector<Node> emptyChildren;
            std::vector<Node> ret = {{emptyChildren, seeds.front()}};
            return ret;
        } else {
            for (const auto& seed : seeds) {
                ret.push_back({createNode(eraseElement(seeds, seed)), seed});
            }
            return ret;
        }
    }

    static std::vector<std::vector<T>> traverse(const Node& node) {
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

    const std::vector<T> seeds;
    const unsigned numOrderedSets;
};

int main(void) {
    OrderedSet<int> os({1,2,3,4});
    std::cout << "num:" << os.getNumOrderedSets() << std::endl;
    for (const auto& a : os.getAllOrderedSets()) {
        for (const auto& b : a) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
