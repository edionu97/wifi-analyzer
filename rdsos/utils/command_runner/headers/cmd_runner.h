#pragma  once

#include <string>
#include <array>
#include <memory>

class cmd_runner
{
public:

    /**
     * This function it is used for executing a command
     * @param command: the command string that will be executed
     * @return the result obtained by command execution
     */
    static std::string execute_command(const std::string &command);
};
