#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOffCommand : public Command {
public:
    explicit LivingroomLightOffCommand(const Light* light);
    explicit LivingroomLightOffCommand(std::nullptr_t) = delete;
    ~LivingroomLightOffCommand() = default;

    void execute() const;

protected:
    LivingroomLightOffCommand(const LivingroomLightOffCommand&) = delete;
    LivingroomLightOffCommand(LivingroomLightOffCommand&&) = delete;
    LivingroomLightOffCommand& operator=(const LivingroomLightOffCommand&) = delete;
    LivingroomLightOffCommand& operator=(LivingroomLightOffCommand&&) = delete;

private:
    std::shared_ptr<const Light> _light;
};