#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "../exceptionsLib/exceptions.hpp"
#include "../ListNode/ListNode.hpp"
#include "inFileParser.hpp"

InFileParser::InFileParser() {
}

inline bool InFileParser::isStrANumber(const std::string &strNum) const {
    if (strNum.empty() || (strNum.size() == 1U && strNum[0U] == '-')) {
        return false;
    }
    return std::all_of(strNum.begin(), strNum.end(), [](const char sym){ return std::isdigit(sym); }) ||
        (strNum[0U] == '-' && std::all_of(strNum.begin() + 1U, strNum.end(), [](const char sym){ return std::isdigit(sym); }));
}

inline void InFileParser::abortNodes(std::vector<ListNode *> &nodes) const {
    for (auto node : nodes) {
        delete node;
        node = nullptr;
    }
}

ListNode* InFileParser::parseFileToList(std::ifstream &ifs) const {
    std::string line;
    std::vector<ListNode *> listNodes;
    std::vector<int> randIndxs;

    while (std::getline(ifs, line)) {
        std::size_t semicolonPos = line.rfind(';');
        if (semicolonPos == std::string::npos) {
            abortNodes(listNodes);
            throw InvalidInputSemicolonError("Invalid Input Error occured: no semicolon in some row");
        }
        
        std::string data = std::move(line.substr(0U, semicolonPos));
        std::string randIndexStr = std::move(line.substr(semicolonPos + 1U));
        if (!isStrANumber(randIndexStr)) {
            abortNodes(listNodes);
            throw InvalidInputRandIndexError("Invalid Input Random Index Error occured: invalid value of rand index in some row");
        }
        
        ListNode *node = new ListNode();
        node->data = std::move(data);
        listNodes.push_back(node);
        randIndxs.push_back(std::stoi(randIndexStr));
    }

    for (std::size_t i = 0U; i < listNodes.size(); ++i) {
        if (i > 0U) {
            listNodes[i]->prev = listNodes[i - 1U];
        }
        if (i + 1U < listNodes.size()) {
            listNodes[i]->next = listNodes[i + 1U];
        }

        if (int randIndex = randIndxs[i]; randIndex == -1) {
            listNodes[i]->rand = nullptr;
        }
        else {
            if (randIndex < -1 || randIndex >= static_cast<int>(listNodes.size())) {
                abortNodes(listNodes);
                throw InvalidInputRandIndexError("Invalid Input Random Index Error occured: value of rand index is out of range");
            }
            listNodes[i]->rand = listNodes[randIndex];
        }
    }

    return listNodes[0U];
}