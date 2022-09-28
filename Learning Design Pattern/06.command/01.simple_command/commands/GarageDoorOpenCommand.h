#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorOpenCommand : public Command {
public:
    explicit GarageDoorOpenCommand(std::shared_ptr<const GarageDoor> garageDoor);
    explicit GarageDoorOpenCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~GarageDoorOpenCommand() = default;
    GarageDoorOpenCommand(const GarageDoorOpenCommand&) = delete;
    GarageDoorOpenCommand(GarageDoorOpenCommand&&) = delete;
    GarageDoorOpenCommand& operator=(const GarageDoorOpenCommand&) = delete;
    GarageDoorOpenCommand& operator=(GarageDoorOpenCommand&&) = delete;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};