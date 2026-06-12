#include "AudioManager.h"

AudioManager::AudioManager(uint8_t pin)
  : buzzerPin(pin), pwmChannel(BUZZER_CHANNEL), volume(80), muted(false) {
}

AudioManager::~AudioManager() {
  stop();
}

void AudioManager::init() {
  Serial.println("  [AudioManager] Initializing buzzer on pin " + String(buzzerPin));
  
  ledcSetup(pwmChannel, 1000, 8);
  ledcAttachPin(buzzerPin, pwmChannel);
  
  Serial.println("  [AudioManager] Buzzer initialized");
}

void AudioManager::playTone(uint16_t frequency, uint16_t duration) {
  if (muted) return;
  
  ledcChangeFrequency(pwmChannel, frequency, 8);
  ledcWrite(pwmChannel, (volume * 255) / 100);
  
  delay(duration);
  
  ledcWrite(pwmChannel, 0);
  delay(50);
}

void AudioManager::playStartupSound() {
  Serial.println("  [AudioManager] Playing startup sound");
  playTone(STARTUP_TONE_FREQ, STARTUP_TONE_DURATION);
}

void AudioManager::playMenuBeep() {
  playTone(MENU_BEEP_FREQ, MENU_BEEP_DURATION);
}

void AudioManager::playSelectSound() {
  playTone(SELECT_SOUND_FREQ, SELECT_SOUND_DURATION);
}

void AudioManager::playBackSound() {
  playTone(BACK_SOUND_FREQ, BACK_SOUND_DURATION);
}

void AudioManager::playErrorTone() {
  playTone(ERROR_TONE_FREQ, ERROR_TONE_DURATION);
}

void AudioManager::playSuccessTone() {
  playTone(SELECT_SOUND_FREQ, SELECT_SOUND_DURATION);
  delay(100);
  playTone(SELECT_SOUND_FREQ * 1.5, SELECT_SOUND_DURATION);
}

void AudioManager::playWarningTone() {
  for (int i = 0; i < 3; i++) {
    playTone(ERROR_TONE_FREQ, 100);
    delay(100);
  }
}

void AudioManager::playCustomTone(uint16_t frequency, uint16_t duration) {
  if (muted) return;
  playTone(frequency, duration);
}

void AudioManager::setVolume(int vol) {
  volume = constrain(vol, 0, 100);
}

void AudioManager::stop() {
  ledcWrite(pwmChannel, 0);
}