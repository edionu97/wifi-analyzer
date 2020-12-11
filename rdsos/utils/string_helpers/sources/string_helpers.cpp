//
// Created by eduard on 11.12.2020.
//

#include "../headers/string_helpers.h"

std::map<std::string, std::string>
string_helpers::get_text_between_tokens(const std::regex &token_identifier,
                                        const std::string &input_string,
                                        const unsigned int group_id)
{

    //define the oldToken match
    std::smatch token_search_match;

    //if in string we do not find any matcher that return an empty map
    if (!std::regex_search(input_string, token_search_match, token_identifier))
    {
        return {};
    }

    //declare the map
    std::map<std::string, std::string> token_text_association{};

    //get the oldToken
    auto oldToken = token_search_match[group_id];

    //set the next value
    auto next = std::string{token_search_match.suffix()};

    //continue searching
    for (; std::regex_search(next, token_search_match, token_identifier); next = token_search_match.suffix())
    {
        //get the next oldToken
        auto nextToken = token_search_match[group_id];

        //not allow duplicates as key
        if (token_text_association.find(oldToken) != token_text_association.end())
        {
            continue;
        }

        //add the token and the text between tokens
        token_text_association.insert({oldToken, token_search_match.prefix()});

        //get the next token section
        oldToken = nextToken;
    }

    //check if the value is not added in dictionary
    if (token_text_association.find(oldToken) == token_text_association.end())
    {
        token_text_association.insert({oldToken, next});
    }

    return token_text_association;
}

std::vector<std::string> string_helpers::tokenize_string(const std::string &input_string, const char separator)
{
    //the number of tokens
    std::vector<std::string> tokens;

    //create a string stream and use it for reading another token until the separator is encountered
    std::istringstream string_stream{input_string};

    //get tokens
    std::string token{};
    while (std::getline(string_stream, token, separator))
    {
        tokens.push_back(token);
    }

    //get the tokens
    return tokens;
}
