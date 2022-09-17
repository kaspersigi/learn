#pragma once
#include "../devices/GarageDoor.h"
#include "../interface/Command.h"
#include <memory>

class GarageDoorDownCommand : public Command {
public:
    explicit GarageDoorDownCommand(std::shared_ptr<const GarageDoor> garageDoor);
    explicit GarageDoorDownCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~GarageDoorDownCommand() = default;
    GarageDoorDownCommand(const GarageDoorDownCommand&) = delete;
    GarageDoorDownCommand(GarageDoorDownCommand&&) = delete;
    GarageDoorDownCommand& operator=(const GarageDoorDownCommand&) = delete;
    GarageDoorDownCommand& operator=(GarageDoorDownCommand&&) = delete;

private:
    std::weak_ptr<const GarageDoor> _garageDoor;
};