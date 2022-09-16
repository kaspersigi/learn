#pragma once
#include "../devices/CeilingFan.h"
#include "../interface/Command.h"
#include <memory>

class CeilingFanOnCommand : public Command {
public:
    explicit CeilingFanOnCommand(const CeilingFan* ceilingFan);
    explicit CeilingFanOnCommand(std::nullptr_t) = delete;
    ~CeilingFanOnCommand() = default;

    void execute() const;

protected:
    CeilingFanOnCommand(const CeilingFanOnCommand&) = delete;
    CeilingFanOnCommand(CeilingFanOnCommand&&) = delete;
    CeilingFanOnCommand& operator=(const CeilingFanOnCommand&) = delete;
    CeilingFanOnCommand& operator=(CeilingFanOnCommand&&) = delete;

private:
    std::shared_ptr<const CeilingFan> _ceilingFan;
};