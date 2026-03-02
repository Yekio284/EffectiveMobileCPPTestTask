#pragma once

#include <fstream>
#include "../ListNode/ListNode.hpp"

class Deserializer {
private:
    inline void abortNodes(std::vector<ListNode *> &nodes) const;

public:
    Deserializer();

    ListNode* deserialize(std::ifstream &ifs) const;
};