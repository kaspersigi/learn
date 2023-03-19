#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOffCommand : public Command {
public:
    explicit LivingroomLightOffCommand(std::shared_ptr<const Light> light);
    explicit LivingroomLightOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~LivingroomLightOffCommand() = default;
    LivingroomLightOffCommand(const LivingroomLightOffCommand&) = delete;
    LivingroomLightOffCommand(LivingroomLightOffCommand&&) = delete;
    LivingroomLightOffCommand& operator=(const LivingroomLightOffCommand&) = delete;
    LivingroomLightOffCommand& operator=(LivingroomLightOffCommand&&) = delete;

private:
    std::weak_ptr<const Light> _light {};
};