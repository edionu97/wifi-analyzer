//
// Created by eduard on 11.12.2020.
//

#ifndef RDSOS_STRING_HELPERS_H
#define RDSOS_STRING_HELPERS_H

#include <map>
#include <regex>
#include <sstream>

class string_helpers
{
public:
    /**
     * This function it is used for getting the
     * @param token_identifier: the token identifier (it should be an regex that identifies the searched token)
     * @param group_id: by default it has the value 0 meaning that all the regex is the key of the dictionary
     * @param input_string: the string in which we are searching
     * if it has another value thant then as key we will have the group at that specific index
     * @return a dictionary (the key is the identified and the value is the content before two tokens)
     */
    static std::map<std::string, std::string>
    get_text_between_tokens(const std::regex &token_identifier,
                            const std::string &input_string,
                            const unsigned int group_id = 0);

    /**
     * This function it is used for tokenize a string by a specific separator
     * @param input_string: the string that will be tokenized
     * @param separator: the separator used
     * @return: an array of tokens
     */
    static std::vector<std::string>
    tokenize_string(const std::string &input_string, const char separator);

};


#endif //RDSOS_STRING_HELPERS_H
