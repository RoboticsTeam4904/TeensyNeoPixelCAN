
#include <Adafruit_NeoPixel.h>
#include <TeensyCANBase.h>
#include <avr/power.h>

const int numberPixels = 34;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numberPixels, 6, NEO_GRB + NEO_KHZ800);
TeensyCANBase can(0x600);

const int solidMode = 0;
const int sweepMode = 1;

int mode = 0;
int progress = 0;
int R = 0;
int G = 0;
int B = 0;

void setup() {
  can.begin();
  pixels.begin();
  Serial.begin(9600);
  Serial.println("Begin Teensy Connection");
  mode = 0;
  progress = 0;
  R = 0;
  G = 0;
  B = 0;
}

void loop() {
  if(can.available() > 0){
    uint8_t * data = (uint8_t *) malloc(8);
    if(can.read(data) == 0){
      mode = data[6] + (data[7] << 8);
      progress = data[4] + (data[5] << 8);
      R = data[2];
      G = data[1];
      B = data[0];
      Serial.print(mode);
      Serial.print("\t");
      Serial.print(progress);
      Serial.print("\t");
      Serial.print(R);
      Serial.print("\t");
      Serial.print(G);
      Serial.print("\t");
      Serial.print(B);
      Serial.println();
      can.write(data);
    }
    delete data;
  }

  switch(mode){
    default:
      solid();
  }

  pixels.show();
  delay(10);
}

void solid(){
  for(int i = 0; i < numberPixels; i++){
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
}

