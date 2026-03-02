#include <fstream>
#include <unordered_map>
#include "serializer.hpp"
#include "../ListNode/ListNode.hpp"
#include "../exceptionsLib/exceptions.hpp"

Serializer::Serializer() {
}

inline std::size_t Serializer::getListSize(ListNode *head) const {
    ListNode *node = head;
    std::size_t size = 0;
    while (node != nullptr) {
        ++size;
        node = node->next;
    }

    return size;
}

void Serializer::serialize(ListNode *head, std::ofstream &ofs) const {
    std::size_t listSize = getListSize(head);
    if (!ofs.write(reinterpret_cast<const char *>(&listSize), sizeof(listSize))) {
        throw InvalidOutputWriteError("Invalud Output Write Error occured: can't write to the file");
    }
    
    ListNode *node = head;
    
    std::unordered_map<ListNode *, std::size_t> indexByNode;
    for (std::size_t i = 0; i < listSize; ++i, node = node->next) {
        indexByNode[node] = i; 
    }

    node = head;
    for (std::size_t _ = 0; _ < listSize; ++_, node = node->next) {
        std::size_t dataSize = node->data.size();
        if (!ofs.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize))) {
            throw InvalidOutputWriteError("Invalid Output Write Error occured: can't write size of data to the file");
        }
        if (!ofs.write(node->data.data(), dataSize)) {
            throw InvalidOutputWriteError("Invalid Output Write Error occured: can't write data to the file");
        }

        int randIndex = -1;
        if (node->rand != nullptr) {
            randIndex = static_cast<int>(indexByNode[node->rand]);
        }
        if (!ofs.write(reinterpret_cast<const char *>(&randIndex), sizeof(randIndex))) {
            throw InvalidOutputWriteError("Invalid Output Write Error occured: can't write randIndex to the file");
        }
    }
}