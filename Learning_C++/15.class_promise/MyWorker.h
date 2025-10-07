#pragma once

#include <future>
#include <memory>
#include <string>

class ChildWorker
{
public:
    ChildWorker() = default;
    ~ChildWorker() = default;

    int child_worker(int value, const std::string& str, std::promise<int>& p);

protected:
    ChildWorker(const ChildWorker&) = delete;
    ChildWorker(ChildWorker&&) = delete;
    ChildWorker& operator = (const ChildWorker&) = delete;
    ChildWorker& operator = (ChildWorker&&) = delete;
};

class MainWorker
{
public:
    MainWorker() = default;
    ~MainWorker() = default;

    void execute(int value, const std::string& str);

protected:
    MainWorker(const MainWorker&) = delete;
    MainWorker(MainWorker&&) = delete;
    MainWorker& operator = (const MainWorker&) = delete;
    MainWorker& operator = (MainWorker&&) = delete;

private:
    int main_worker();
    std::shared_ptr<ChildWorker> _cw {};
};