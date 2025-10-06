#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOnCommand : public Command
{
public:
    explicit LivingroomLightOnCommand(std::shared_ptr<const Light> light);
    explicit LivingroomLightOnCommand(std::nullptr_t) = delete;
    virtual ~LivingroomLightOnCommand() = default;

    void execute() const;

private:
    std::weak_ptr<const Light> _light {};
};