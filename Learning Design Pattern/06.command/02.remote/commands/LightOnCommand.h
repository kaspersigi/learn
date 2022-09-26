#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(std::shared_ptr<const Light> light);
    explicit LightOnCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~LightOnCommand() = default;
    LightOnCommand(const LightOnCommand&) = delete;
    LightOnCommand(LightOnCommand&&) = delete;
    LightOnCommand& operator=(const LightOnCommand&) = delete;
    LightOnCommand& operator=(LightOnCommand&&) = delete;

private:
    std::weak_ptr<const Light> _light {};
};