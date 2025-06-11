#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

const int in_pir = 4;   // D2 on NodeMCU
const int out_pir = 14; // D5 on NodeMCU

#define FIREBASE_HOST "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "your_firebase_database_secret"
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

int enter = 0;
int exit = 0;
bool last_in = false;
bool last_out = false;

void setFirebaseValues(int entry, int exit) {
  Firebase.setInt("enter", entry);
  if (Firebase.failed()) {
    Serial.print("Firebase set failed: ");
    Serial.println(Firebase.error());
  }

  Firebase.setInt("exit", exit);
  if (Firebase.failed()) {
    Serial.print("Firebase set failed: ");
    Serial.println(Firebase.error());
  }
}

void setup() {
  pinMode(in_pir, INPUT);
  pinMode(out_pir, INPUT);

  Serial.begin(9600);
  delay(500);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  setFirebaseValues(enter, exit);
}

void loop() {
  bool in = digitalRead(in_pir);
  bool out = digitalRead(out_pir);

  if (in && !last_in) {
    enter++;
    Serial.print("Entry detected: ");
    Serial.println(enter);
    setFirebaseValues(enter, exit);
  }

  if (out && !last_out) {
    exit++;
    Serial.print("Exit detected: ");
    Serial.println(exit);
    setFirebaseValues(enter, exit);
  }

  last_in = in;
  last_out = out;

  delay(100);
}
