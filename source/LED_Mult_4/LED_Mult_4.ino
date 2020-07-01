int SER = 4;
int CLK = 2;
int LAT = 3;

const int n_scanlines = 8;
const int n_frames = 1;
const int n_fields = 2;

union int_arr{
  uint32_t as_int;
  uint8_t as_array[4];
};

PROGMEM const union int_arr data[n_frames][n_fields][n_scanlines] = {{{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f},{0xdb6924fe,0xdb6924fd,0xdb6924fb,0xdb6924f7,0xdb6924ef,0xdb6924df,0xdb6924bf,0xdb69247f}}};

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
    union int_arr test;
    test.as_int = 0xFF20304;

    int t = millis();

    for (int frame = 0; frame < n_frames; frame++)
    {
        for (int m = 0; m<16; m++)
        {
            for (int field = 0; field < n_fields; field++)
            {
                for (int scan = 0; scan < n_scanlines; scan++)
                {
                  digitalWrite(LAT, LOW);
                  shiftOut(SER, CLK, (byte) pgm_read_byte(&(data[frame][field][scan].as_array[3])));
                  shiftOut(SER, CLK, (byte) pgm_read_byte(&(data[frame][field][scan].as_array[2])));
                  shiftOut(SER, CLK, (byte) pgm_read_byte(&(data[frame][field][scan].as_array[1])));
                  shiftOut(SER, CLK, (byte) pgm_read_byte(&(data[frame][field][scan].as_array[0])));
                  digitalWrite(LAT, HIGH);
                }    
            }
        }
    }

    Serial.println(millis() - t);
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val)
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
