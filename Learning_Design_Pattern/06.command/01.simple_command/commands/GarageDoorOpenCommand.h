#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorOpenCommand : public Command
{
public:
    explicit GarageDoorOpenCommand(std::shared_ptr<const GarageDoor> garageDoor);
    explicit GarageDoorOpenCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~GarageDoorOpenCommand() = default;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};