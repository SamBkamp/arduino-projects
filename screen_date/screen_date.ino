#include "/home/sam/arduino_projects/screen_io.c"
#include "/home/sam/arduino_projects/screen_date/WifiCredentials.h"
#include <TimeLib.h>
#include <WiFi.h>
WiFiClient client; //yucky OOP
int port = 8080;

char buff[64];
char qqq[30];
char *dow[] = {"Sunday",
	      "Monday",
	      "Tuesday",
	      "Wednesday",
	      "Thursday",
	      "Friday",
	      "Saturday"
};


void make_req(char* endpoint){
  IPAddress base(192,168,50,196);
  int res; //connection result
  res = client.connect(base, port);
  clear_display();
  if(res){
    screen_put_string("success!");
    client.println(endpoint);
    clear_display();
    while(!client.available()){ //check if ready to recieve bytes TODO: create an auto stop
      delay(20);
    }
    sprintf(buff,"%d bytes to read", client.available());
    screen_put_string(buff);
    int index = 0;
    char construction[13];
    while(client.available()){
      construction[index++] = client.read();
    }
    client.flush();
    client.stop();
    construction[index] = 0;
    if(strcmp(endpoint, "HIII")==0){
      setTime(strtoul(construction, NULL, 10));
    }else{
      strcpy(qqq, construction);
    }
    clear_display();
  }else{
    screen_put_string("failed!");
  }
}


void setup() {
  pin_init();
  function_set();
  display_init(1, 0, 0);
  entry_mode(1, 0);

  setTime(0);
  clear_display();
  screen_put_string("Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED){
    delay(700);
  }
  clear_display();
  screen_put_string("Connected!");
  delay(500);
  make_req("HIII");
  delay(500);
  make_req("qqq");
  delay(500);
  WiFi.disconnect();
}

void loop() {
  clear_display();
  time_t t = now();
  sprintf(buff, "%s %d:%02d", dow[weekday(t)-1], hour(t), minute(t));
  screen_put_string(buff);
  set_cursor(0, 1);
  sprintf(buff, "%02d.%02d.%02d", day(t), month(t), year(t));
  screen_put_string(buff);

  delay(10000);

  clear_display();
  sprintf(buff, "QQQ:  %s", qqq);
  screen_put_string(buff);
  delay(10000);
}
