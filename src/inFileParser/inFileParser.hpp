#pragma once

#include <fstream>
#include <vector>
#include "../ListNode/ListNode.hpp"

class InFileParser {
private:
    inline bool isStrANumber(const std::string &strNum) const;
    inline void abortNodes(std::vector<ListNode *> &nodes) const;

public:
    InFileParser();

    ListNode* parseFileToList(std::ifstream &ifs) const;
};