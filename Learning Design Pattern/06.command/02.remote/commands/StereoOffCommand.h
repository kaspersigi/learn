#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOffCommand : public Command {
public:
    explicit StereoOffCommand(std::shared_ptr<const Stereo> stereo);
    explicit StereoOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~StereoOffCommand() = default;
    StereoOffCommand(const StereoOffCommand&) = delete;
    StereoOffCommand(StereoOffCommand&&) = delete;
    StereoOffCommand& operator=(const StereoOffCommand&) = delete;
    StereoOffCommand& operator=(StereoOffCommand&&) = delete;

private:
    std::weak_ptr<const Stereo> _stereo {};
};