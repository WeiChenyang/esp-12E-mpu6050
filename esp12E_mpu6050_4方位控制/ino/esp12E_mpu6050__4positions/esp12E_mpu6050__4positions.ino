// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const uint8_t scl = D6;
const uint8_t sda = D7;

Adafruit_MPU6050 mpu;

float i;//计算偏移量时的循环次数
float ax_offset = 0, ay_offset = 0; //x,y轴的加速度偏移量
float gx_offset = 0, gy_offset = 0; //x,y轴的角速度偏移量
float rad2deg = 57.29578;
float roll, pitch; //储存角度
float count =0;//计数

void setup(void) {
  Serial.begin(115200);
  Wire.begin(sda, scl);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  count++;
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int pitch = (atan2(a.acceleration.x, sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z))*180.0)/M_PI;
  int roll = (atan2(a.acceleration.y, a.acceleration.z)*180.0)/M_PI;
  int cross = (atan2(a.acceleration.z, a.acceleration.y)*180.0)/M_PI;
  Serial.print("俯仰x轴变 pitch: ");
  Serial.print(pitch);
  Serial.print(",横滚y轴变 roll: ");
  Serial.print(roll);
  Serial.print(",斜滚xy交叉轴变 cross: ");
  Serial.print(cross);
  Serial.print("  ");
  if(pitch<-5&&roll<2){
      Serial.println("前进");
  }else if( pitch>5&&roll>0){
      Serial.println("后退"); 
  }else if(pitch<5&&roll<-5){
      Serial.println("向左"); 
  }else if(pitch>-5&&roll>5){
      Serial.println("向右"); 
  }else{
      Serial.println("停止"); 
  }

  /* Print out the values */
  Serial.print("加速度 X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("角速度 X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  /*Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");*/
  Serial.print("》》》》》第");
  Serial.print(count);
  Serial.println("次 结束《《《《《");
  delay(500);
}
