#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOnCommand : public Command
{
public:
    explicit LivingroomLightOnCommand(const std::shared_ptr<const Light>& light);
    explicit LivingroomLightOnCommand(std::nullptr_t) = delete;
    virtual ~LivingroomLightOnCommand();

    void execute() const;

private:
    std::weak_ptr<const Light> _light {};
};