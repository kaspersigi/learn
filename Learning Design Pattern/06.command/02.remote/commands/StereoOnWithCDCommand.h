#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOnWithCDCommand : public Command {
public:
    explicit StereoOnWithCDCommand(std::shared_ptr<const Stereo> stereo);
    explicit StereoOnWithCDCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    ~StereoOnWithCDCommand() = default;
    StereoOnWithCDCommand(const StereoOnWithCDCommand&) = delete;
    StereoOnWithCDCommand(StereoOnWithCDCommand&&) = delete;
    StereoOnWithCDCommand& operator=(const StereoOnWithCDCommand&) = delete;
    StereoOnWithCDCommand& operator=(StereoOnWithCDCommand&&) = delete;

private:
    std::weak_ptr<const Stereo> _stereo {};
};