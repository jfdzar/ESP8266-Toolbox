#include <Arduino.h>

#define MOTOR_PIN_1 14 //D5
#define MOTOR_PIN_2 12 //D6
#define MOTOR_PIN_3 13 //D7
#define MOTOR_PIN_4 15 //D8

#define DIRECTION_UP 1
#define DIRECTION_DOWN 0 

bool debug = true;

int step_array[] = {1, 0, 0, 0};
int delay_time = 50;

void print_array( int b[], int sizeOfArray ) {
   // multiply each array element by 2
   for ( int k = 0 ; k < sizeOfArray-1 ; ++k ){
     Serial.print(b[k]);
     Serial.print(",");  
   }
   Serial.println(b[sizeOfArray-1]);
} 

void init_motor(int motor_pin_1, int motor_pin_2,int motor_pin_3,int motor_pin_4){
  //To be done add information about steps per revolution etc
  if(debug){Serial.println("Initializing Motor");}
  pinMode(motor_pin_1,OUTPUT);
  pinMode(motor_pin_2,OUTPUT);
  pinMode(motor_pin_3,OUTPUT);
  pinMode(motor_pin_4,OUTPUT);

}

void set_motor_speed(int motor_speed){
  //To be done add the calculation
  if(debug){Serial.println("Setting Motor Speed");}
  delay_time = motor_speed;
}

void move_step(uint8_t direction){
  
  int aux = 0;

  if(direction == 0){
    //Moving Down
    if(debug){Serial.println("Moving Step Down");}
    aux = step_array[3];    
    step_array[3] = step_array[2];
    step_array[2] = step_array[1];
    step_array[1] = step_array[0];
    step_array[0] = aux;
  }
  else{
    //Moving Up
    if(debug){Serial.println("Moving Step Up");}
    aux = step_array[0];    
    step_array[0] = step_array[1];
    step_array[1] = step_array[2];
    step_array[2] = step_array[3];
    step_array[3] = aux;
  }

}

void move_motor(int steps, uint8_t direction){
    //Move the amount of steps in the given direction
    for(int i=0; i<=steps ;i++){

      digitalWrite(MOTOR_PIN_1, step_array[0]);
      digitalWrite(MOTOR_PIN_2, step_array[1]);
      digitalWrite(MOTOR_PIN_3, step_array[2]);
      digitalWrite(MOTOR_PIN_4, step_array[3]);

      move_step(direction);
      delay(delay_time);
      if(debug){print_array(step_array,4);}
  }
}


void setup() {
  // Initialize the serial port:
  Serial.begin(9600);
  // Init Motor Pins
  init_motor(MOTOR_PIN_1,MOTOR_PIN_2,MOTOR_PIN_3,MOTOR_PIN_4);
}

void loop() {
  

  int i=1;
  debug = false;
  while(1){
    move_motor(1,DIRECTION_UP);
    Serial.println(i);
    i = i + 1;
  }

}

