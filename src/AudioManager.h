/*
 * Audio Manager - Handles buzzer/speaker tones and sounds
 * Uses PWM for frequency control
 */

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <Arduino.h>
#include "config.h"

class AudioManager {
private:
  uint8_t buzzerPin;
  uint8_t pwmChannel;
  int volume;
  bool muted;
  
  void playTone(uint16_t frequency, uint16_t duration);
  
public:
  AudioManager(uint8_t pin);
  ~AudioManager();
  
  void init();
  
  void playStartupSound();
  void playMenuBeep();
  void playSelectSound();
  void playBackSound();
  void playErrorTone();
  void playSuccessTone();
  void playWarningTone();
  
  void playCustomTone(uint16_t frequency, uint16_t duration);
  
  void setVolume(int vol);
  int getVolume() { return volume; }
  void mute(bool m) { muted = m; }
  bool isMuted() { return muted; }
  
  void stop();
};

#endif