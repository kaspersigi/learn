#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(const std::shared_ptr<const Light>& light);
    explicit LightOnCommand(std::nullptr_t) = delete;
    virtual ~LightOnCommand();

    void execute() const;

private:
    std::weak_ptr<const Light> _light {};
};