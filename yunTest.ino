#include <Bridge.h>
#include <HttpClient.h>
#include <string.h>
#include <Time.h>
#include <TimeAlarms.h>

String url = "http://uvcrawler.parseapp.com/data";
char data[7];
char* split1 = ":";
char* split2 = "\n";
char* saveptr;
int i = 0;
const int minutes = 30; 
const int hrs = 0;
const int seconds = 0;
//boolean getData = false;

void setup() {
  //pinMode(13, OUTPUT);
  //digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial);
  setTime(11, 43, 0, 8, 6, 14);
  Alarm.timerRepeat(hrs, minutes, seconds, httpRequest);
}

void loop() {
  digitalClockDisplay();
  //Alarm.delay(5000);
  //delay(5000);
}

void cleanData(int len){
  for(int i = 0;i < len;i++){
    data[i] = '\0';
  }
}

void changeColor(char* value){
  int val = atoi(value);
  Serial.println(val);
  //val -> color 
}

void httpRequest(){
 HttpClient client;
 client.get(url);
  while (client.available()) {
    char c = client.read();
    if(c != '\n' && c != '\0'){
      //Serial.print(c);
      data[i++] = c; 
    }else{
      //Serial.println("else");
      data[i] = '\n';
      char* token = strtok_r(data, split1, &saveptr);
      if(token){
        if(strcmp(token, "val") == 0){
            //Serial.print('v');
            token = strtok_r(NULL, split2, &saveptr);
            //change the color of leds
            changeColor(token);
        }else if(strcmp(token, "num") == 0){
            token = strtok_r(NULL, split2, &saveptr);
            if(strcmp(token, "0") != 0){
              //immediately send get request
            }
        }
      }
      cleanData(i);
      i = 0;
    }
    //Serial.print(c);
  }
  Serial.flush();
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}
void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
