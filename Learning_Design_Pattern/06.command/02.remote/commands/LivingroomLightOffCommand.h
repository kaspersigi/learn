#pragma once
#include "../devices/Light.h"
#include "../interface/Command.h"
#include <memory>

class LivingroomLightOffCommand : public Command {
public:
    explicit LivingroomLightOffCommand(const std::shared_ptr<const Light>& light);
    explicit LivingroomLightOffCommand(std::nullptr_t) = delete;
    virtual ~LivingroomLightOffCommand();

    void execute() const;

private:
    std::weak_ptr<const Light> _light {};
};