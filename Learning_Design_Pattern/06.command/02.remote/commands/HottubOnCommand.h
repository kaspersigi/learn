#pragma once
#include "../devices/Hottub.h"
#include "../interface/Command.h"
#include <memory>

class HottubOnCommand : public Command {
public:
    explicit HottubOnCommand(std::shared_ptr<const Hottub> hottub);
    explicit HottubOnCommand(std::nullptr_t) = delete;

    void execute() const;

protected:
    virtual ~HottubOnCommand() = default;
    HottubOnCommand(const HottubOnCommand&) = delete;
    HottubOnCommand(HottubOnCommand&&) = delete;
    HottubOnCommand& operator=(const HottubOnCommand&) = delete;
    HottubOnCommand& operator=(HottubOnCommand&&) = delete;

private:
    std::weak_ptr<const Hottub> _hottub {};
};