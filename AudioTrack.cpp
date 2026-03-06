#include "AudioTrack.h"

AudioTrack::AudioTrack() {
    trackNumber = 0;
    title = "";
}

AudioTrack::AudioTrack(int number, String title) {
    this->trackNumber = number;
    this->title = title;
}

int AudioTrack::getTrackNumber() const {
    return trackNumber;
}

String AudioTrack::getTitle() const {
    return title;
}