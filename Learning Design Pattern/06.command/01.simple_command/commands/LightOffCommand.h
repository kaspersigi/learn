#pragma once
#include "../devices/Light.h"
#include <memory>

class LightOffCommand {
public:
    explicit LightOffCommand(const Light* light);
    explicit LightOffCommand(std::nullptr_t) = delete;
    ~LightOffCommand() = default;

    void execute() const;

protected:
    LightOffCommand(const LightOffCommand&) = delete;
    LightOffCommand(LightOffCommand&&) = delete;
    LightOffCommand& operator=(const LightOffCommand&) = delete;
    LightOffCommand& operator=(LightOffCommand&&) = delete;

private:
    std::shared_ptr<const Light> _light;
};