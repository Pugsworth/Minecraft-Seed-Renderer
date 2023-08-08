#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


const TCHAR AUDIO_ALERT[] = TEXT("./assets/audio/alert.wav");
void audio_play(const TCHAR* path)
{
    // Must use int here instead of WINBOOL. Doesn't compile with WINBOOL.
    int res = PlaySound(
        path,
        NULL,
        SND_FILENAME | SND_NODEFAULT
    );

    if (!res) {
        printf("Error: %d\n", GetLastError());
    }
}