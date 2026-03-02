#include <string>
#include "exceptions.hpp"

InvalidInputFileError::InvalidInputFileError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}

InvalidInputSemicolonError::InvalidInputSemicolonError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}

InvalidInputRandIndexError::InvalidInputRandIndexError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}

InvalidInputReadError::InvalidInputReadError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}

InvalidOutputFileError::InvalidOutputFileError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}

InvalidOutputWriteError::InvalidOutputWriteError(const std::string &errorMsg) : std::runtime_error(errorMsg) {
}