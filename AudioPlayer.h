#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

enum class PlayerState { STOPPED, PLAYING, PAUSED, ERROR };

class AudioPlayer {
private:
    SoftwareSerial* dfSerial;
    DFRobotDFPlayerMini dfPlayer;

    PlayerState currentState;
    int currentTrack;
    int volumeLevel;

    void printState();

public:
    AudioPlayer(SoftwareSerial* serial);

    void begin();

    void playTrack(int trackNumber);
    void pause();
    void stop();
    void nextTrack();
    void previousTrack();
    void setVolume(int level);

    PlayerState getState() const;
};

#endif