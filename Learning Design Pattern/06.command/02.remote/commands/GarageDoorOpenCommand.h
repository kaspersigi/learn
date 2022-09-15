#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorOpenCommand : public Command {
public:
    explicit GarageDoorOpenCommand(const GarageDoor* garageDoor);
    explicit GarageDoorOpenCommand(std::nullptr_t) = delete;
    ~GarageDoorOpenCommand() = default;

    void execute() const;

protected:
    GarageDoorOpenCommand(const GarageDoorOpenCommand&) = delete;
    GarageDoorOpenCommand(GarageDoorOpenCommand&&) = delete;
    GarageDoorOpenCommand& operator=(const GarageDoorOpenCommand&) = delete;
    GarageDoorOpenCommand& operator=(GarageDoorOpenCommand&&) = delete;

private:
    std::shared_ptr<const GarageDoor> _garageDoor;
};