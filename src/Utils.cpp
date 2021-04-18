#include <Arduino.h>

String formatMillis(long millis) {
  unsigned long seconds = millis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  String res = "";
  if (hours < 10) {
    res += "0";
  }
  res += hours;
  res += ":";
  if (minutes < 10) {
    res += "0";
  }
  res += minutes;
  res += ":";
  if (seconds < 10) {
    res += "0";
  }
  res += seconds;

  return res;
}
