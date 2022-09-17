#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOnCommand : public Command {
public:
    explicit LivingroomLightOnCommand(std::shared_ptr<const Light> light);
    explicit LivingroomLightOnCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~LivingroomLightOnCommand() = default;
    LivingroomLightOnCommand(const LivingroomLightOnCommand&) = delete;
    LivingroomLightOnCommand(LivingroomLightOnCommand&&) = delete;
    LivingroomLightOnCommand& operator=(const LivingroomLightOnCommand&) = delete;
    LivingroomLightOnCommand& operator=(LivingroomLightOnCommand&&) = delete;

private:
    std::weak_ptr<const Light> _light;
};