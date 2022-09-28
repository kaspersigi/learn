#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(std::shared_ptr<const Light> light);
    explicit LightOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~LightOffCommand() = default;
    LightOffCommand(const LightOffCommand&) = delete;
    LightOffCommand(LightOffCommand&&) = delete;
    LightOffCommand& operator=(const LightOffCommand&) = delete;
    LightOffCommand& operator=(LightOffCommand&&) = delete;

private:
    std::weak_ptr<const Light> _light {};
};