#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LightOnCommand : public Command
{
public:
    virtual ~LightOnCommand() = default;
    explicit LightOnCommand(std::shared_ptr<const Light> light);
    explicit LightOnCommand(std::nullptr_t) = delete;

    void execute() const;
    void undo() const;

private:
    std::weak_ptr<const Light> _light {};
};