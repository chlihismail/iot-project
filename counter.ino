#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// WiFi credentials
#define WIFI_SSID "gfsdgdfsgdfsg"
#define WIFI_PASSWORD "gfdgdfsgdfsg"

// Firebase config
#define FIREBASE_HOST "qsdfsdqfsdqfsdqfsdqfsdqfsdqf"
#define FIREBASE_AUTH "sdqfsdqfsdqfsdqfsdqfsdq"

// Firebase setup objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// PIR sensor pins (NodeMCU pins)
const int in_pir = 4;
const int out_pir = 14;

int enter = 0;
int exitCount = 0;
bool last_in = false;
bool last_out = false;

void setup() {
  Serial.begin(9600);

  pinMode(in_pir, INPUT);
  pinMode(out_pir,INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  // Set Firebase credentials
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Firebase.setInt(firebaseData, "/enter", enter);
  Firebase.setInt(firebaseData, "/exit", exitCount);
}

void loop() {
if (Firebase.getInt(firebaseData, "/enter")) {
  enter = firebaseData.intData();
} else {
  Serial.println("Failed to read /enter from Firebase");
}

if (Firebase.getInt(firebaseData, "/exit")) {
  exitCount = firebaseData.intData();
} else {
  Serial.println("Failed to read /exit from Firebase");
}


 bool in = digitalRead(in_pir);
 bool out = digitalRead(out_pir) ; 

  if (in && !last_in) {
    enter++;
    Serial.print("Entry detected: ");
    Serial.println(enter);
    Firebase.setInt(firebaseData, "/enter", enter);
  }

    if (out && !last_out) {
    exitCount++;
    Serial.print("exit detected: ");
    Serial.println(exitCount);
    Firebase.setInt(firebaseData, "/exit", exitCount);
  }


  last_in = in;
  last_out = out ; 

  delay(100);
}
