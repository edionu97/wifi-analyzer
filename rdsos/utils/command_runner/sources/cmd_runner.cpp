//
// Created by eduard on 11.12.2020.
//

#include "../headers/cmd_runner.h"


std::string cmd_runner::execute_command(const std::string &command)
{
    //declare the pipe
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    //in case that the creation of the pipe fails
    if (pipe == nullptr)
    {
        throw std::runtime_error("Error, popen failed");
    }

    //read the result (chunk by chunk)
    std::string result;
    std::array<char, 128> buffer{};
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result.append(buffer.data());
    }

    //get back the result
    return result;
}