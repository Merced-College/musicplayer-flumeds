#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H

#include <Arduino.h>

class AudioTrack {
private:
    int trackNumber;
    String title;

public:
    AudioTrack();
    AudioTrack(int number, String title);

    int getTrackNumber() const;
    String getTitle() const;
};

#endif