#pragma once
#include "../devices/CeilingFan.h"
#include "../interface/Command.h"
#include <memory>

class CeilingFanOnCommand : public Command
{
public:
    explicit CeilingFanOnCommand(const std::shared_ptr<const CeilingFan>& ceilingFan);
    explicit CeilingFanOnCommand(std::nullptr_t) = delete;
    virtual ~CeilingFanOnCommand();

    void execute() const;

private:
    std::weak_ptr<const CeilingFan> _ceilingFan {};
};