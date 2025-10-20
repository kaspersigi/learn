#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorDownCommand : public Command
{
public:
    explicit GarageDoorDownCommand(const std::shared_ptr<const GarageDoor>& garageDoor);
    explicit GarageDoorDownCommand(std::nullptr_t) = delete;
    virtual ~GarageDoorDownCommand();

    void execute() const;

private:
    std::weak_ptr<const GarageDoor> _garageDoor {};
};