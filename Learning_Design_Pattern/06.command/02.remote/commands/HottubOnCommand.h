#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOnCommand : public Command
{
public:
    explicit HottubOnCommand(const std::shared_ptr<const Hottub>& hottub);
    explicit HottubOnCommand(std::nullptr_t) = delete;
    virtual ~HottubOnCommand();

    void execute() const;

private:
    std::weak_ptr<const Hottub> _hottub {};
};