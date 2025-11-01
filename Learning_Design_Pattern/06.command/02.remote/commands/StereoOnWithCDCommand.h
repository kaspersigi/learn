#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOnWithCDCommand : public Command {
public:
    explicit StereoOnWithCDCommand(const std::shared_ptr<const Stereo>& stereo);
    explicit StereoOnWithCDCommand(std::nullptr_t) = delete;
    virtual ~StereoOnWithCDCommand();

    void execute() const;

private:
    std::weak_ptr<const Stereo> _stereo {};
};