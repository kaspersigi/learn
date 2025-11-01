#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorOpenCommand : public Command {
public:
    explicit GarageDoorOpenCommand(const std::shared_ptr<const GarageDoor>& garageDoor);
    explicit GarageDoorOpenCommand(std::nullptr_t) = delete;
    virtual ~GarageDoorOpenCommand();

    void execute() const;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};