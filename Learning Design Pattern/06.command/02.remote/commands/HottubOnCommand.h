#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOnCommand : public Command {
public:
    explicit HottubOnCommand(const Hottub* hottub);
    explicit HottubOnCommand(std::nullptr_t) = delete;
    ~HottubOnCommand() = default;

    void execute() const;

protected:
    HottubOnCommand(const HottubOnCommand&) = delete;
    HottubOnCommand(HottubOnCommand&&) = delete;
    HottubOnCommand& operator=(const HottubOnCommand&) = delete;
    HottubOnCommand& operator=(HottubOnCommand&&) = delete;

private:
    std::shared_ptr<const Hottub> _hottub;
};