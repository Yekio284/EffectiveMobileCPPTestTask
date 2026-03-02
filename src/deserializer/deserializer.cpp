#include <fstream>
#include <vector>
#include "deserializer.hpp"
#include "../ListNode/ListNode.hpp"
#include "../exceptionsLib/exceptions.hpp"

Deserializer::Deserializer() {
}

inline void Deserializer::abortNodes(std::vector<ListNode *> &nodes) const {
    for (auto node : nodes) {
        delete node;
        node = nullptr;
    }
}

ListNode* Deserializer::deserialize(std::ifstream &ifs) const {
    std::size_t listSize = 0U;
    if (!ifs.read(reinterpret_cast<char *>(&listSize), sizeof(listSize))) {
        throw InvalidInputReadError("Invalid Input Read Error occured: can't read list size");
    }

    if (listSize == 0U) {
        return nullptr;
    }

    std::vector<ListNode *> listNodes(listSize);
    std::vector<int> randIndxs(listSize);

    for (std::size_t i = 0U; i < listSize; ++i) {
        std::size_t dataSize;
        if (!ifs.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize))) {
            abortNodes(listNodes);
            throw InvalidInputReadError("Invalid Input Read Error occured: can't read data size");
        }
        
        std::string data;
        data.resize(dataSize);
        if (!ifs.read(data.data(), dataSize)) {
            abortNodes(listNodes);
            throw InvalidInputReadError("Invalid Input Read Error occured: can't read data");
        }

        int randIndex = -1;
        if (!ifs.read(reinterpret_cast<char *>(&randIndex), sizeof(randIndex))) {
            abortNodes(listNodes);
            throw InvalidInputReadError("Invalid Input Read Error occured: can't read rand index");
        }

        ListNode *node = new ListNode();
        node->data = std::move(data);
        listNodes[i] = node;
        randIndxs[i] = randIndex;
    }    

    for (std::size_t i = 0U; i < listSize; ++i) {
        if (i > 0U) {
            listNodes[i]->prev = listNodes[i - 1U];
        }
        if (i + 1 < listSize) {
            listNodes[i]->next = listNodes[i + 1U];
        }

        if (int randIndex = randIndxs[i]; randIndex == -1) {
            listNodes[i]->rand = nullptr;
        }
        else {
            if (randIndex < -1 || randIndex >= static_cast<int>(listSize)) {
                abortNodes(listNodes);
                throw InvalidInputRandIndexError("Invalid Input Random Index Error occured: value of rand index is out of range");
            }
            listNodes[i]->rand = listNodes[randIndex];
        }
    }

    return listNodes[0U];
}
