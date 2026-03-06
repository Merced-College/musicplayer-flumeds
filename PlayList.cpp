#include "Playlist.h"

Playlist::Playlist() {
    trackCount = 0;
}

void Playlist::addTrack(const AudioTrack& track) {
    if (trackCount < MAX_TRACKS) {
        tracks[trackCount++] = track;
    }
}

void Playlist::listTracks() const {
    Serial.println("---- Playlist ----");
    for (int i = 0; i < trackCount; i++) {
        Serial.print(tracks[i].getTrackNumber());
        Serial.print(" - ");
        Serial.println(tracks[i].getTitle());
    }
}

int Playlist::findTrackByKeyword(String keyword) const {
    for (int i = 0; i < trackCount; i++) {
        if (tracks[i].getTitle().indexOf(keyword) >= 0) {
            return tracks[i].getTrackNumber();
        }
    }
    return -1;
}

void Playlist::selectionSortByTitle() {
    for (int i = 0; i < trackCount - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < trackCount; j++) {
            if (tracks[j].getTitle() < tracks[minIndex].getTitle()) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            AudioTrack temp = tracks[i];
            tracks[i] = tracks[minIndex];
            tracks[minIndex] = temp;
        }
    }
}

int Playlist::getTrackCount() const {
    return trackCount;
}

AudioTrack Playlist::getTrack(int index) const {
    if (index >= 0 && index < trackCount) {
        return tracks[index];
    }
    return AudioTrack();
}