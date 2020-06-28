int SER = 4;
int CLK = 2;
int LAT = 3;

const int n_scanlines = 8;
const int n_frames = 2;

uint32_t data[n_frames][n_scanlines] = {{0xDB6DB6FE, 0x924924FD, 0xB6DB6DFB, 0x249249F7, 0x6DB6DBEF, 0x492492DF, 0xDB6DB6BF, 0x9249247F},
                                        {0x924924FE, 0xB6DB6DFD, 0x249249FB, 0x6DB6DBF7, 0x492492EF, 0xDB6DB6DF, 0x924924BF, 0xB6DB6D7F}};

void setup()
{
    // put your setup code here, to run once:
    pinMode(SER, OUTPUT);
    pinMode(LAT, OUTPUT);
    pinMode(CLK, OUTPUT);
    Serial.begin(9600);

}
int t = 0;
void loop()
{
    //t = millis();
    // put your main code here, to run repeatedly:
    for (int d = 0; d<5; d++){
        for (int frame = 0; frame < n_frames; frame++)
        {
            for (int m = 0; m<64; m++)
            {
                for (int scan = 0; scan < n_scanlines; scan++)
                {
                  digitalWrite(LAT, LOW);
                  shiftOut2(SER, CLK, MSBFIRST, (byte) (data[frame][scan] >> 24));
                  shiftOut2(SER, CLK, MSBFIRST, (byte) (data[frame][scan] >> 16));
                  shiftOut2(SER, CLK, MSBFIRST, (byte) (data[frame][scan] >> 8));
                  shiftOut2(SER, CLK, MSBFIRST, (byte) data[frame][scan]);
                  digitalWrite(LAT, HIGH);
                }           
            } 
        }
    }
    //Serial.println(millis()-t);
}

// MSB only
void highShiftOut32(uint8_t dataPin, uint8_t clockPin, uint32_t val)
{
     uint32_t mask = 0x80000000;
     for (uint8_t i = 0; i < 32; i++)
     {
         digitalWrite(dataPin, !!(val & mask));  
         digitalWrite(clockPin, HIGH);
         digitalWrite(clockPin, LOW);
         mask = mask >> 1;        
     }
}

void shiftOut2(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t mask = 0x80;
    for (uint8_t i = 0; i < 8; i++)
    {   
        digitalWrite(dataPin, !!(val & mask));
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
        mask = mask >> 1;        
    }
}
