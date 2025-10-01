#include "MyWorker.h"

extern "C" {
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
}

void* ChildWorker::child_worker(void*)
{
    char s[256] = { 0 };
    for (size_t i = 0; i < 30; ++i) {
        sleep(1);
        memset(s, 0, 256);
        sprintf(s, "%s: %lu", __PRETTY_FUNCTION__, i);
        printf("%s\n", s);
    }
    return NULL;
}

void* MainWorker::main_worker(void*)
{
    char s[256] = { 0 };
    for (size_t i = 0; i < 60; ++i) {
        sleep(1);
        memset(s, 0, 256);
        sprintf(s, "%s: %lu", __PRETTY_FUNCTION__, i);
        printf("%s\n", s);
    }
    return NULL;
}

void MainWorker::execute()
{
    pthread_t mw_tid = 0;
    pthread_t cw_tid = 0;
    [[maybe_unused]] int mw_ret = pthread_create(&mw_tid, NULL, main_worker, NULL);
    [[maybe_unused]] int cw_ret = pthread_create(&cw_tid, NULL, _cw->child_worker, NULL);
    pthread_join(mw_tid, NULL);
    pthread_join(cw_tid, NULL);
    // https://comp.programming.threads.narkive.com/IS1dxD6T/how-to-pass-class-member-function-to-pthread-create
    // 除了static，没得搞，不要在C++里使用pthread
}