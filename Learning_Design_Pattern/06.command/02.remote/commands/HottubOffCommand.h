#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOffCommand : public Command
{
public:
    explicit HottubOffCommand(std::shared_ptr<const Hottub> hottub);
    explicit HottubOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~HottubOffCommand() = default;
    HottubOffCommand(const HottubOffCommand&) = delete;
    HottubOffCommand(HottubOffCommand&&) = delete;
    HottubOffCommand& operator = (const HottubOffCommand&) = delete;
    HottubOffCommand& operator = (HottubOffCommand&&) = delete;

private:
    std::weak_ptr<const Hottub> _hottub {};
};