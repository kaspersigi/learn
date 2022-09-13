#pragma once
#include "../devices/Light.h"
#include <memory>

class LightOnCommand {
public:
    explicit LightOnCommand(const Light* light);
    explicit LightOnCommand(std::nullptr_t) = delete;
    ~LightOnCommand() = default;

    void execute() const;

protected:
    LightOnCommand(const LightOnCommand&) = delete;
    LightOnCommand(LightOnCommand&&) = delete;
    LightOnCommand& operator=(const LightOnCommand&) = delete;
    LightOnCommand& operator=(LightOnCommand&&) = delete;

private:
    std::shared_ptr<const Light> _light;
};