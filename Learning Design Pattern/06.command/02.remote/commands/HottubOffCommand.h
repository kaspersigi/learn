#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOffCommand : public Command {
public:
    explicit HottubOffCommand(const Hottub* hottub);
    explicit HottubOffCommand(std::nullptr_t) = delete;
    ~HottubOffCommand() = default;

    void execute() const;

protected:
    HottubOffCommand(const HottubOffCommand&) = delete;
    HottubOffCommand(HottubOffCommand&&) = delete;
    HottubOffCommand& operator=(const HottubOffCommand&) = delete;
    HottubOffCommand& operator=(HottubOffCommand&&) = delete;

private:
    std::shared_ptr<const Hottub> _hottub;
};