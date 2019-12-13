//author : David Ramirez


#define BLYNK_PRINT stdout
#ifdef RASPBERRY
#include <BlynkApiWiringPi.h>
#else
#include <BlynkApiLinux.h>
#endif
#include <BlynkSocket.h>
#include <BlynkOptionsParser.h>
static BlynkTransportSocket _blynkTransport;
BlynkSocket Blynk(_blynkTransport);
#include <BlynkWidgets.h>

long map(long x, long in_min, long in_max, long out_min, long out_max) 
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void motorControlLeft(int spd1) 
{

    int spd = spd1;
	if(spd < 0) //BACKWARD
	{
		digitalWrite(25, HIGH);
        analogWrite(12, abs(spd));
		digitalWrite(13, HIGH);
	}
	else if(spd > 0) //FORWARD
	{
		digitalWrite(25, LOW);
        analogWrite(12, abs(spd));
		digitalWrite(13, HIGH);
	}
	else //IDLE
	{
		digitalWrite(12, LOW);
		digitalWrite(13, LOW);
	}
}
void motorControlRight(int spd1) //CONTROLS RIGHT
{

    int spd = spd1;
	if (spd < 0) //BACKWARD
	{
        digitalWrite(24, LOW);
        analogWrite(13, abs(spd));
		digitalWrite(12, HIGH);
	}
	else if (spd > 0) //FORWARD
	{
		
        digitalWrite(24, HIGH);
        analogWrite(13, abs(spd));
		digitalWrite(12, HIGH);
	}
	else //IDLE
	{
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
	}
}

BLYNK_WRITE(V0) //LEFT JOYSTICK
{
	digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);
	int x = param[0].asInt();
    printf("Left Value %d\n", x);
	motorControlLeft(x);
}
BLYNK_WRITE(V1) //RIGHT JOYSTICK
{
	
    digitalWrite(22, HIGH);//ENABLE FOR RIGHT
    digitalWrite(23, HIGH);//ENABLE FOR LEFT
	int x = param[0].asInt();
    int y = map(x, -9999, 9999, -255, 255); 
    printf("Right Value %d\n", y);
	motorControlRight(y);
}

void setup()
{
}
void loop()
{
	Blynk.run();
}
int main(int argc, char* argv[])
{

	  
	  //SETS GPIO'S NEEDED TO DRIVE ROBOT AS OUTPUTS
	  pinMode(12, OUTPUT);//DIRECTION FOR RIGHT
	  pinMode(13, OUTPUT);//DIRECTION FOR LEFT
	  pinMode(22, OUTPUT);//ENABLE FOR RIGHT
	  pinMode(23, OUTPUT);//ENABLE FOR LEFT
	  pinMode(24, OUTPUT);//DIRECTION FOR RIGHT
	  pinMode(25, OUTPUT);//DIRECTION FOR LEFT
	  pinMode(5, OUTPUT);
	  pinMode(6, OUTPUT);
	  const char *auth, *serv;
	  uint16_t port;
	  parse_options(argc, argv, auth, serv, port);
	  Blynk.begin(auth, serv, port);
	  setup();
	  while(true) 
	  {
		loop();
	  }
	  return 0;
}
