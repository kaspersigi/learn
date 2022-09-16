#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOffCommand : public Command {
public:
    explicit StereoOffCommand(const Stereo* stereo);
    explicit StereoOffCommand(std::nullptr_t) = delete;
    ~StereoOffCommand() = default;

    void execute() const;

protected:
    StereoOffCommand(const StereoOffCommand&) = delete;
    StereoOffCommand(StereoOffCommand&&) = delete;
    StereoOffCommand& operator=(const StereoOffCommand&) = delete;
    StereoOffCommand& operator=(StereoOffCommand&&) = delete;

private:
    std::shared_ptr<const Stereo> _stereo;
};