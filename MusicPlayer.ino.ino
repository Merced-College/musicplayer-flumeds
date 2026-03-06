#include "AudioTrack.h"
#include "Playlist.h"
#include "AudioPlayer.h"

SoftwareSerial dfSerial(2, 3); // RX, TX
AudioPlayer player(&dfSerial);
Playlist playlist;

void setup() {
    Serial.begin(9600);

    player.begin();

    playlist.addTrack(AudioTrack(1, "Mr Saxobeat"));
    playlist.addTrack(AudioTrack(2, "Moscow"));
    playlist.addTrack(AudioTrack(3, "Solo Me Dejaste"));
    playlist.addTrack(AudioTrack(4, "Dios Por Adalante"));
    playlist.addTrack(AudioTrack(5, "Lady Hear me Tonight"));
    playlist.addTrack(AudioTrack(6, "Es un Secreto"));
    playlist.addTrack(AudioTrack(7, "Kiss Me Thru The Phone"));
    playlist.addTrack(AudioTrack(8, "TBH"));

    Serial.println("System Ready. Type 'help' for commands.");
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command.startsWith("p ")) {
            int num = command.substring(2).toInt();
            player.playTrack(num);
        }
        else if (command == "n") {
            player.nextTrack();
        }
        else if (command == "b") {
            player.previousTrack();
        }
        else if (command == "pause") {
            player.pause();
        }
        else if (command == "s") {
            player.stop();
        }
        else if (command.startsWith("v ")) {
            int vol = command.substring(2).toInt();
            player.setVolume(vol);
        }
        else if (command == "list") {
            playlist.listTracks();
        }
        else if (command.startsWith("find ")) {
            String keyword = command.substring(5);
            int result = playlist.findTrackByKeyword(keyword);
            if (result != -1) {
                Serial.print("Found track number: ");
                Serial.println(result);
            } else {
                Serial.println("Track not found.");
            }
        }
        else if (command == "sort") {
            playlist.selectionSortByTitle();
            Serial.println("Playlist sorted.");
        }
        else if (command == "help") {
            Serial.println("Commands:");
            Serial.println("p <num> - Play track");
            Serial.println("n - Next");
            Serial.println("b - Previous");
            Serial.println("pause - Pause/resume");
            Serial.println("s - Stop");
            Serial.println("v <num> - Set volume (0-30)");
            Serial.println("list - Show playlist");
            Serial.println("find <word> - Search");
            Serial.println("sort - Sort playlist");
        }
        else {
            Serial.println("Invalid command.");
        }
    }
}