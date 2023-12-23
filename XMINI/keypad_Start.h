/**********************************************************
Header File for 4x3 Keypad Interface

V0.1
Niall O'Keeffe
10/1/17

*/

//Keypad Column Pins
#define COL1	0u//IOPORT_CREATE_PIN(PORTB, 0)
#define COL2	1u//IOPORT_CREATE_PIN(PORTB, 1)
#define COL3	2u//IOPORT_CREATE_PIN(PORTB, 2)

//Function Prototypes
void keypadConfigure(void);
unsigned char keyPressed(void);
unsigned char keypadScan(void);