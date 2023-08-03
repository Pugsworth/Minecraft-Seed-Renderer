#pragma once

/**
 * @file interrupt.h
 * @author your name (you@domain.com)
 * @brief Small interrupt handling library.
 * @version 0.1
 * @date 2023-08-02
 *
 * @copyright Copyright (c) 2023
 */

#ifdef _WIN32

#include <windows.h>
#include <stdio.h>

static FUNCTION handler = NULL;

typedef void (*FUNCTION)();

BOOL WINAPI consoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        printf("\nCtrl-C handled\n");
        if (handler != NULL) {
            handler();
        }
        exit(0);
    }

    return FALSE;
}

void setInterruptHandler(FUNCTION _handler)
{
    handler = _handler;
    SetConsoleCtrlHandler(consoleHandler, TRUE);
}

#endif