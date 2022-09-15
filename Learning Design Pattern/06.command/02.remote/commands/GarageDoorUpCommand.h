#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorUpCommand : public Command {
public:
    explicit GarageDoorUpCommand(const GarageDoor* garageDoor);
    explicit GarageDoorUpCommand(std::nullptr_t) = delete;
    ~GarageDoorUpCommand() = default;

    void execute() const;

protected:
    GarageDoorUpCommand(const GarageDoorUpCommand&) = delete;
    GarageDoorUpCommand(GarageDoorUpCommand&&) = delete;
    GarageDoorUpCommand& operator=(const GarageDoorUpCommand&) = delete;
    GarageDoorUpCommand& operator=(GarageDoorUpCommand&&) = delete;

private:
    std::shared_ptr<const GarageDoor> _garageDoor;
};