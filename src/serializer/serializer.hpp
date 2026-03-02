#pragma once

#include <fstream>
#include "../ListNode/ListNode.hpp"

class Serializer {
private:
    inline std::size_t getListSize(ListNode *head) const;

public:
    Serializer();

    void serialize(ListNode *head, std::ofstream &ofs) const;
};