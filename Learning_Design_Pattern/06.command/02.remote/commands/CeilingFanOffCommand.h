#pragma once
#include "../devices/CeilingFan.h"
#include "../interface/Command.h"
#include <memory>

class CeilingFanOffCommand : public Command
{
public:
    explicit CeilingFanOffCommand(const std::shared_ptr<const CeilingFan>& ceilingFan);
    explicit CeilingFanOffCommand(std::nullptr_t) = delete;
    virtual ~CeilingFanOffCommand();

    void execute() const;

private:
    std::weak_ptr<const CeilingFan> _ceilingFan {};
};