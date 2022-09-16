#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOnWithCDCommand : public Command {
public:
    explicit StereoOnWithCDCommand(const Stereo* stereo);
    explicit StereoOnWithCDCommand(std::nullptr_t) = delete;
    ~StereoOnWithCDCommand() = default;

    void execute() const;

protected:
    StereoOnWithCDCommand(const StereoOnWithCDCommand&) = delete;
    StereoOnWithCDCommand(StereoOnWithCDCommand&&) = delete;
    StereoOnWithCDCommand& operator=(const StereoOnWithCDCommand&) = delete;
    StereoOnWithCDCommand& operator=(StereoOnWithCDCommand&&) = delete;

private:
    std::shared_ptr<const Stereo> _stereo;
};