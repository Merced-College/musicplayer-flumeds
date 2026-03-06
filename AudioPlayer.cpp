#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(SoftwareSerial* serial) {
    dfSerial = serial;
    currentState = PlayerState::STOPPED;
    currentTrack = -1;
    volumeLevel = 15;
}

void AudioPlayer::begin() {
    dfSerial->begin(9600);

    if (!dfPlayer.begin(*dfSerial)) {
        Serial.println("DFPlayer error!");
        currentState = PlayerState::ERROR;
        printState();
        return;
    }

    dfPlayer.volume(volumeLevel);
    Serial.println("DFPlayer ready.");
}

void AudioPlayer::printState() {
    Serial.print("State changed to: ");

    switch (currentState) {
        case PlayerState::STOPPED: Serial.println("STOPPED"); break;
        case PlayerState::PLAYING: Serial.println("PLAYING"); break;
        case PlayerState::PAUSED:  Serial.println("PAUSED");  break;
        case PlayerState::ERROR:   Serial.println("ERROR");   break;
    }
}

void AudioPlayer::playTrack(int trackNumber) {
    if (trackNumber <= 0) {
        Serial.println("Invalid track number.");
        currentState = PlayerState::ERROR;
        printState();
        return;
    }

    dfPlayer.play(trackNumber);
    currentTrack = trackNumber;
    currentState = PlayerState::PLAYING;
    printState();
}

void AudioPlayer::pause() {
    if (currentState == PlayerState::STOPPED) {
        Serial.println("Cannot pause while stopped.");
        return;
    }

    if (currentState == PlayerState::PLAYING) {
        dfPlayer.pause();
        currentState = PlayerState::PAUSED;
    } else if (currentState == PlayerState::PAUSED) {
        dfPlayer.start();
        currentState = PlayerState::PLAYING;
    }

    printState();
}

void AudioPlayer::stop() {
    dfPlayer.stop();
    currentState = PlayerState::STOPPED;
    printState();
}

void AudioPlayer::nextTrack() {
    if (currentTrack == -1) {
        Serial.println("No track selected.");
        return;
    }

    dfPlayer.next();
    currentState = PlayerState::PLAYING;
    printState();
}

void AudioPlayer::previousTrack() {
    if (currentTrack == -1) {
        Serial.println("No track selected.");
        return;
    }

    dfPlayer.previous();
    currentState = PlayerState::PLAYING;
    printState();
}

void AudioPlayer::setVolume(int level) {
    if (level < 0) level = 0;
    if (level > 30) level = 30;

    volumeLevel = level;
    dfPlayer.volume(volumeLevel);

    Serial.print("Volume set to: ");
    Serial.println(volumeLevel);
}

PlayerState AudioPlayer::getState() const {
    return currentState;
}