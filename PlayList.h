#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "AudioTrack.h"

const int MAX_TRACKS = 10;

class Playlist {
private:
    AudioTrack tracks[MAX_TRACKS];
    int trackCount;

public:
    Playlist();

    void addTrack(const AudioTrack& track);
    void listTracks() const;
    int findTrackByKeyword(String keyword) const;
    void selectionSortByTitle();

    int getTrackCount() const;
    AudioTrack getTrack(int index) const;
};

#endif