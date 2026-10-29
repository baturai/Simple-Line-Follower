#define sol_sensor A4
#define orta_sensor A3
#define sag_sensor A2

#define sol_motor_ileri 5
#define sol_motor_geri  6
#define sag_motor_ileri 9
#define sag_motor_geri  10

int sol, orta, sag;

int hiz = 170;  // dusurmeni tavsiye ederim, yarıs ortamına fazla hızlı geldi.
int yavas = 50;

int lastDirection = 0;

void setup() {
  pinMode(sol_motor_ileri, OUTPUT);
  pinMode(sol_motor_geri,  OUTPUT);
  pinMode(sag_motor_ileri, OUTPUT);
  pinMode(sag_motor_geri,  OUTPUT);
}

void loop() {

  sol  = digitalRead(sol_sensor);
  orta = digitalRead(orta_sensor);
  sag  = digitalRead(sag_sensor);

  if (sol==0 && orta==1 && sag==0) {
    motorSur(hiz, hiz);
    lastDirection = 0;
  }

  else if (sol==1 && orta==0 && sag==0) {
    motorSur(hiz, hiz);
    lastDirection = -1;
  }

  else if (sol==1 && orta==1 && sag==0) {
    motorSur(0, hiz); 
    lastDirection = -1;
  }

  else if (sol==0 && orta==0 && sag==1) {
    motorSur(hiz, yavas);
    lastDirection = 1;
  }

  else if (sol==0 && orta==1 && sag==1) {
    motorSur(hiz, 0);
    lastDirection = 1;
  }

  else if (sol==1 && orta==1 && sag==1) {
    motorSur(hiz, hiz);
  }

  else if (sol==0 && orta==0 && sag==0) {
    if (lastDirection == -1) {
      motorSur(0, hiz); 
    }
    else if (lastDirection == 1) {
      motorSur(hiz, 0);
    }
    else {
      motorSur(0, 0);
    }
  }
}

// MOTOR
void motorSur(int solHiz, int sagHiz) {
  analogWrite(sol_motor_ileri, solHiz);
  analogWrite(sol_motor_geri,  0);
  analogWrite(sag_motor_ileri, sagHiz);
  analogWrite(sag_motor_geri,  0);
}
