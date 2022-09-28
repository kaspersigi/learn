#pragma once
#include "../devices/CeilingFan.h"
#include "../interface/Command.h"
#include <memory>

class CeilingFanOffCommand : public Command {
public:
    explicit CeilingFanOffCommand(std::shared_ptr<const CeilingFan> ceilingFan);
    explicit CeilingFanOffCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~CeilingFanOffCommand() = default;
    CeilingFanOffCommand(const CeilingFanOffCommand&) = delete;
    CeilingFanOffCommand(CeilingFanOffCommand&&) = delete;
    CeilingFanOffCommand& operator=(const CeilingFanOffCommand&) = delete;
    CeilingFanOffCommand& operator=(CeilingFanOffCommand&&) = delete;

private:
    std::weak_ptr<const CeilingFan> _ceilingFan {};
};