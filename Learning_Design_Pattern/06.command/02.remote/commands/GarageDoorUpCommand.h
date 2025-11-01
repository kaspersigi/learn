#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorUpCommand : public Command {
public:
    explicit GarageDoorUpCommand(const std::shared_ptr<const GarageDoor>& garageDoor);
    explicit GarageDoorUpCommand(std::nullptr_t) = delete;
    virtual ~GarageDoorUpCommand();

    void execute() const;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};