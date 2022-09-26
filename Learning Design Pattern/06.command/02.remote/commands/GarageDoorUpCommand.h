#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorUpCommand : public Command {
public:
    explicit GarageDoorUpCommand(std::shared_ptr<const GarageDoor> garageDoor);
    explicit GarageDoorUpCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~GarageDoorUpCommand() = default;
    GarageDoorUpCommand(const GarageDoorUpCommand&) = delete;
    GarageDoorUpCommand(GarageDoorUpCommand&&) = delete;
    GarageDoorUpCommand& operator=(const GarageDoorUpCommand&) = delete;
    GarageDoorUpCommand& operator=(GarageDoorUpCommand&&) = delete;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};