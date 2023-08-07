#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const TCHAR AUDIO_ALERT[] = TEXT("./assets/audio/alert.wav");

void audio_play(const TCHAR* path)
{
    WINBOOL res = PlaySound(
        path,
        NULL,
        SND_FILENAME
    );

    if (!res) {
        printf("Error: %d\n", GetLastError());
    }
}
