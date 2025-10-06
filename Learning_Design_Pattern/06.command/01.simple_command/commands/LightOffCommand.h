#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LightOffCommand : public Command
{
public:
    explicit LightOffCommand(std::shared_ptr<const Light> light);
    explicit LightOffCommand(std::nullptr_t) = delete;
    virtual ~LightOffCommand() = default;

    void execute() const;

private:
    std::weak_ptr<const Light> _light {};
};