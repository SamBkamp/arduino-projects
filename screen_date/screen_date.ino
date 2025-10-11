#include "/home/sam/arduino_projects/screen_io.c"
#include <TimeLib.h>

char buff[64];

char *dow[] = {"Sunday",
	      "Monday",
	      "Tuesday",
	      "Wednesday",
	      "Thursday",
	      "Friday",
	      "Saturday"
};

void setup() {
  pin_init();
  function_set();
  display_init(1, 0, 0);
  entry_mode(1, 0);

  time_t t = 1760176772;
  setTime(t);

}

void loop() {
  clear_display();
  time_t t = now();
  sprintf(buff, "%s %d:%02d", dow[weekday(t)-1], hour(t), minute(t));
  screen_put_string(buff);
  set_cursor(0, 1);
  sprintf(buff, "%02d.%02d.%02d", day(t), month(t), year(t));
  screen_put_string(buff);
  delay(30000); //wait half a minute
}
