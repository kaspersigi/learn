#pragma once
#include "../devices/CeilingFan.h"
#include "../interface/Command.h"
#include <memory>

class CeilingFanOffCommand : public Command {
public:
    explicit CeilingFanOffCommand(const CeilingFan* ceilingFan);
    explicit CeilingFanOffCommand(std::nullptr_t) = delete;
    ~CeilingFanOffCommand() = default;

    void execute() const;

protected:
    CeilingFanOffCommand(const CeilingFanOffCommand&) = delete;
    CeilingFanOffCommand(CeilingFanOffCommand&&) = delete;
    CeilingFanOffCommand& operator=(const CeilingFanOffCommand&) = delete;
    CeilingFanOffCommand& operator=(CeilingFanOffCommand&&) = delete;

private:
    std::shared_ptr<const CeilingFan> _ceilingFan;
};