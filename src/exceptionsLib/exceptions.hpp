#pragma once

#include <stdexcept>
#include <string>

class InvalidInputFileError : public std::runtime_error {
public:
    explicit InvalidInputFileError(const std::string &errorMsg);
};

class InvalidInputSemicolonError : public std::runtime_error {
public:
    explicit InvalidInputSemicolonError(const std::string &errorMsg);
};

class InvalidInputRandIndexError : public std::runtime_error {
public:
    explicit InvalidInputRandIndexError(const std::string &errorMsg);
};

class InvalidInputReadError : public std::runtime_error {
public:
    explicit InvalidInputReadError(const std::string &errorMsg);
};

class InvalidOutputFileError : public std::runtime_error {
public:
    explicit InvalidOutputFileError(const std::string &errorMsg);
};

class InvalidOutputWriteError : public std::runtime_error {
public:
    explicit InvalidOutputWriteError(const std::string &errorMsg);
};