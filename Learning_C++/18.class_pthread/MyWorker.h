#pragma once

#include <memory>

class ChildWorker {
public:
    ChildWorker() = default;
    ~ChildWorker() = default;

    static void* child_worker(void*);

protected:
    ChildWorker(const ChildWorker&)
        = delete;
    ChildWorker(ChildWorker&&) = delete;
    ChildWorker& operator=(const ChildWorker&) = delete;
    ChildWorker& operator=(ChildWorker&&) = delete;
};

class MainWorker {
public:
    MainWorker() = default;
    ~MainWorker() = default;

    void execute();

protected:
    MainWorker(const MainWorker&) = delete;
    MainWorker(MainWorker&&) = delete;
    MainWorker& operator=(const MainWorker&) = delete;
    MainWorker& operator=(MainWorker&&) = delete;

private:
    static void* main_worker(void*);
    std::shared_ptr<ChildWorker> _cw {};
};