#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <filesystem>
#include "../exceptionsLib/exceptions.hpp"
#include "../inFileParser/inFileParser.hpp"
#include "../ListNode/ListNode.hpp"
#include "../serializer/serializer.hpp"
#include "../deserializer/deserializer.hpp"

char readAnswer() {
    std::string ans;
    std::getline(std::cin, ans);
    if (ans.size() != 1) {
        return '?';
    }
    ans[0] = std::tolower(ans[0]);

    return ans[0];
}

char getAnswer() {
    char ans = readAnswer();
    while (ans != 'y' && ans != 'n') {
        std::cout << "Wrong input.\nAnswer(y/n): ";
        ans = readAnswer();
    }

    return ans;
}

void printList(const ListNode *const head) {
    const ListNode *node = head;
    std::size_t n = 0;
    
    while (node != nullptr) {
        std::cout << "\nNode " << n++ << ":\n"
            << "  Data: \"" << node->data << "\"\n  PrevData: " << (node->prev ? std::string("\"" + node->prev->data + "\"") : "nullptr")
            << "\n  NextData: " << (node->next ? std::string("\"" + node->next->data + "\"") : "nullptr") 
            << "\n  RandData: " << (node->rand ? std::string("\"" + node->rand->data + "\"") : "nullptr")
            << "\n\n----------------------------------------\n";
        node = node->next;
    }
    std::cout << std::endl;
}

void deleteList(ListNode *head) {
    ListNode *node;
    while (head != nullptr) {
        node = head;
        head = head->next;
        delete node;
        node = nullptr;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3U) {
        std::cerr << "Usage: ./app <inputFile> <outputFile>" << std::endl;
        return 1;
    }

    ListNode *head = nullptr;
    try {
        std::ifstream inputFile;
        std::string filename = argv[1U];
        if (std::filesystem::exists(filename)) {
            inputFile.open(filename);
            if (!inputFile.is_open()) {
                throw InvalidInputFileError("Invalid Input File Error occured: can't open file \"" + filename + '\"');
            }
        }
        else {
            throw InvalidInputFileError("Invalid Input File Error occured: file \"" + filename + "\" doesn't exist");
        }

        if (!std::filesystem::is_empty(filename)) {
            InFileParser parser;
            head = parser.parseFileToList(inputFile);
        
            std::cout << "Would you like to print your List?\nAnswer(y/n): ";
            char ans = getAnswer();
            if (ans == 'y') {
                printList(head);
            }
        }

        filename = argv[2U];
        std::ofstream outputFile(filename, std::ios::binary);
        if (!outputFile.is_open()) {
            throw InvalidOutputFileError("Invalid Output File Error occured: can't open file \"" + filename + '\"');
        }

        Serializer serializer;
        serializer.serialize(head, outputFile);

        std::cout << "Output file saved as " << filename << '\n';
        inputFile.close();
        outputFile.flush();
        outputFile.close();
        
        std::cout << "\nWould you like to deserialize " << filename << " back into List?\nAnswer(y/n): ";
        char ans = getAnswer();
        if (ans == 'y') {
            inputFile.open(filename, std::ios::binary);
            if (!inputFile.is_open()) {
                throw InvalidInputFileError("Invalid Input File Error occured: can't open file \"" + filename + '\"');
            }

            ListNode *deserlzd = nullptr;
            Deserializer deserializer;
            deserlzd = deserializer.deserialize(inputFile);
            
            std::cout << "Would you like to print your deserialized List?\nAnswer(y/n): ";
            ans = getAnswer();
            if (ans == 'y') {
                printList(deserlzd);
            }

            deleteList(deserlzd);
        }
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << "\n";
    }
    catch (...) {
        std::cerr << "Caught an unknown exception\n";
    }

    deleteList(head);

    return 0;
}