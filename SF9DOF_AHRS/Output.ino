unsigned int yawDeg=0;
unsigned int pitchDeg=0;
unsigned int rollDeg=0;
unsigned int omegazero=0;
unsigned int omegaone=0;
unsigned int omegatwo=0;


long convert_to_dec(float x)
{
  return x*10000000;
}

void print_analog_ASCII(void){
      Serial.print("!");
      Serial.print(",AN:");
      Serial.print(AN[sensors[0]]);  //(int)read_adc(0)
      Serial.print(",");
      Serial.print(AN[sensors[1]]);
      Serial.print(",");
      Serial.print(AN[sensors[2]]);  
      Serial.print(",");
      Serial.print(ACC[0]);
      Serial.print (",");
      Serial.print(ACC[1]);
      Serial.print (",");
      Serial.print(ACC[2]);
      Serial.print(",");
      Serial.print(magnetom_x);
      Serial.print (",");
      Serial.print(magnetom_y);
      Serial.print (",");
      Serial.print(magnetom_z);
      Serial.println();
}

void print_angles_ASCII(void){
      Serial.print("ANG:");
      Serial.print(ToDeg(roll));
      Serial.print(",");
      Serial.print(ToDeg(pitch));
      Serial.print(",");
      Serial.print(ToDeg(yaw));
}

void Print_Binary_Data(void){
  
  Serial.write(0xFF);  
  yawDeg = (unsigned int)((ToDeg(yaw)*100)+20000);
  pitchDeg = (unsigned int)((ToDeg(pitch)*100)+20000);
  rollDeg = (unsigned int)((ToDeg(roll)*(-1)*100)+20000);
  omegazero = (unsigned int)((ToDeg(Omega[0])*10)+20000);
  omegaone = (unsigned int)((ToDeg(Omega[1])*10)+20000);
  omegatwo = (unsigned int)((ToDeg(Omega[2])*10)+20000);
  
  Serial.write((uint8_t *) &yawDeg ,2);
  Serial.write((uint8_t *) &pitchDeg,2);
  Serial.write((uint8_t *) &rollDeg,2);
   
  Serial.write((uint8_t *) &omegazero,2);
  Serial.write((uint8_t *) &omegaone,2);
  Serial.write((uint8_t *) &omegatwo,2);
  //Serial.write((uint8_t *) &accel_x,2);
  //Serial.write((uint8_t *) &accel_y,2);
  //Serial.write((uint8_t *) &accel_z,2);
  Serial.write(0xF1);
}

void printdata(void)
{   
    print_angles_ASCII();
    print_analog_ASCII();
      
}
