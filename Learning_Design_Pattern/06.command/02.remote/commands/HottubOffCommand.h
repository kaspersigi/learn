#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOffCommand : public Command
{
public:
    explicit HottubOffCommand(const std::shared_ptr<const Hottub>& hottub);
    explicit HottubOffCommand(std::nullptr_t) = delete;
    virtual ~HottubOffCommand();

    void execute() const;

private:
    std::weak_ptr<const Hottub> _hottub {};
};