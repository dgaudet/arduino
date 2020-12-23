#include "Arduino.h"

class Fade {
  public:
    Fade() {};
  
    Fade(
      uint8_t start,
      uint8_t end,
      unsigned long interval,
      bool showLog
    )
    {
      _start = start;
      _end = end;
      _interval = interval;
      _currentNum = start;
      _showLog = showLog;
    };

    uint8_t startFader(int fadeAmount);
  private:
    uint8_t _start;
    uint8_t _end;
    unsigned long _interval;
    
    uint8_t _currentNum;
    unsigned long _previousMillis = 0;
    bool _showLog;
};

uint8_t Fade::startFader(int fadeAmount) {
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _interval) {
    _previousMillis = currentMillis;

    _currentNum = _currentNum + fadeAmount;
    if (_currentNum > _end) {
      _currentNum = _end;
    } 
    if (_currentNum < _start) {
      _currentNum = _start;
    }

    if (_showLog){
      Serial.print("--start fader called-- ");
      Serial.print(" - ");
      Serial.print(_currentNum);
      Serial.print("\n");  
    }
  }
  
  return _currentNum;
}
