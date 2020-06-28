int SER = 4;
int CLK = 2;
int LAT = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(SER, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(CLK, OUTPUT);
  //Serial.begin(9600);


}
byte LEDNum = B11111110;

byte colors3[] = {B11011011, B10010010, B10110110, B00100100, B01101101, B01001001};
byte colors2[] = {B01101101, B01001001, B11011011, B10010010, B10110110, B00100100};
byte colors[] = {B10110110, B00100100, B01101101, B01001001, B11011011, B10010010};

int colorNum = 0;
int colorOffset = 0;

void loop() {
  // put your main code here, to run repeatedly:
  for (int j = 0; j<32; j++){
      colorNum = colorOffset;
      for (int i = 0; i<8; i++){
      digitalWrite(LAT, LOW);
      shiftOut(SER, CLK, MSBFIRST, colors3[colorNum]);
      shiftOut(SER, CLK, MSBFIRST, colors2[colorNum]);
      shiftOut(SER, CLK, MSBFIRST, colors[colorNum]);
      shiftOut(SER, CLK, MSBFIRST, LEDNum);
      digitalWrite(LAT, HIGH);
      LEDNum = (LEDNum << 1) + 1;
      colorNum = (colorNum +1)%6;
    }
    LEDNum = LEDNum << 1; 
  }
  colorOffset = (colorOffset +1)%6;
}
