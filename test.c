#include <webots/robot.h>           // Library untuk fungsi utama robot Webots
#include <webots/motor.h>            // Library untuk kontrol motor pada robot
#include <webots/distance_sensor.h>  // Library untuk kontrol sensor jarak pada robot
#include <stdio.h>                   // Library standar C untuk input-output

#define TIME_STEP 64                 // Mendefinisikan interval waktu dalam milidetik untuk setiap langkah simulasi

int main(int argc, char **argv) {
  wb_robot_init();                   // Inisialisasi fungsi robot dari Webots

  // Mendeklarasikan motor kanan dan kiri
  WbDeviceTag motor_kanan = wb_robot_get_device("right wheel motor"); // Mendapatkan akses ke motor kanan
  WbDeviceTag motor_kiri = wb_robot_get_device("left wheel motor");   // Mendapatkan akses ke motor kiri
ء
  // Mendeklarasikan sensor kanan dan kiri
  WbDeviceTag sensor_kanan = wb_robot_get_device("right_sensor");     // Mendapatkan akses ke sensor kanan
  WbDeviceTag sensor_kiri = wb_robot_get_device("left_sensor");       // Mendapatkan akses ke sensor kiri
  
  // Mengaktifkan sensor jarak dengan interval waktu yang telah ditentukan
  wb_distance_sensor_enable(sensor_kanan, TIME_STEP);                 // Mengaktifkan sensor kanan
  wb_distance_sensor_enable(sensor_kiri, TIME_STEP);                  // Mengaktifkan sensor kiri
  
  // Mengatur posisi motor agar berputar terus-menerus tanpa batas
  wb_motor_set_position(motor_kanan, INFINITY);                       // Motor kanan berputar tanpa batas
  wb_motor_set_position(motor_kiri, INFINITY);                        // Motor kiri berputar tanpa batas
  
  double readIR_kanan, readIR_kiri;                                   // Variabel untuk menyimpan nilai sensor kanan dan kiri
  
  // Loop utama simulasi robot
  while (wb_robot_step(TIME_STEP) != -1) {                            // Menjalankan loop simulasi dengan interval waktu tertentu
    readIR_kanan = wb_distance_sensor_get_value(sensor_kanan);        // Membaca nilai sensor kanan
    readIR_kiri = wb_distance_sensor_get_value(sensor_kiri);          // Membaca nilai sensor kiri
  
    printf("kanan 1 ");                                               // Mencetak label untuk nilai sensor kanan
    printf("%f\n", readIR_kanan);                                     // Mencetak nilai sensor kanan
    printf("kiri 1 ");                                                // Mencetak label untuk nilai sensor kiri
    printf("%f\n", readIR_kiri);                                      // Mencetak nilai sensor kiri
  
    // Kondisi jika sensor kiri mendeteksi objek lebih dekat dibanding sensor kanan
    if (readIR_kiri < readIR_kanan) {
       wb_motor_set_velocity(motor_kanan, 1);                         // Memperlambat motor kanan
       wb_motor_set_velocity(motor_kiri, 2.5);                        // Mempercepat motor kiri untuk berbelok ke kanan
    }
  
    // Kondisi jika sensor kanan mendeteksi objek lebih dekat dibanding sensor kiri
    if (readIR_kiri > readIR_kanan) {
       wb_motor_set_velocity(motor_kanan, 2.5);                       // Mempercepat motor kanan untuk berbelok ke kiri
       wb_motor_set_velocity(motor_kiri, 1);                          // Memperlambat motor kiri
    }
  }
  
  wb_robot_cleanup();                                                 // Membersihkan memori yang digunakan oleh robot

  return 0;                                                           // Mengakhiri program
}
