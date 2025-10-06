#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOffCommand : public Command
{
public:
    explicit StereoOffCommand(std::shared_ptr<const Stereo> stereo);
    explicit StereoOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~StereoOffCommand() = default;

private:
    std::weak_ptr<const Stereo> _stereo {};
};