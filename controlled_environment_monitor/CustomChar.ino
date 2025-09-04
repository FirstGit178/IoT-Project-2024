// void customChar(){
// // customChar truck back cargo on board  (cob)
// byte TruckBcob[8] = {
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B01100,
//   B01100
// };
// // customChar truck front cargo on board   (cob)
// byte TruckFcob[8] = {
//   B11000,
//   B11110,
//   B11010,
//   B11111,
//   B11111,
//   B11111,
//   B01100,
//   B01100
// };
// // customChar truck back no cargo on board   (ncob)
// byte TruckBncob[8] = {
//   B11111,
//   B10000,
//   B10000,
//   B10000,
//   B10000,
//   B11111,
//   B01100,
//   B01100
// };
// // customChar truck front no cargo on board  (ncob)
// byte TruckFncob[8] = {
//   B11000,
//   B01110,
//   B01010,
//   B01111,
//   B01111,
//   B11111,
//   B01100,
//   B01100
// };
// // customChar fuel on reserve   (fuel low)
// byte FuelLow[8] = {
//   B00000,
//   B00000,
//   B00000,
//   B00000,
//   B11111,
//   B11111,
//   B11111,
//   B11111
// };
// // customChar fuel level less than half
// byte Fuelhalf[8] = {
//   B00000,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111
// };
// // customChar dhtRead             !!!!CAN NOT GET THIS CHARACTER TO WORK!!!!
// byte dhtReadchar[8] = {
//   B00000,
//   B00100,
//   B01010,
//   B00100,
//   B00000,
//   B00000,
//   B00000,
//   B00000
// };
// }
void customCharsetup(){
#if 1
  // create character truck back cargo on board
  lcd.createChar(1, TruckBcob);
  // create character truck front cargo on board
  lcd.createChar(2, TruckFcob);
  // create character truck back no cargo on board
  lcd.createChar(3, TruckBncob);
  // create character truck front no cargo on board
  lcd.createChar(4, TruckFncob);
  // create character fuel on reserve 
  lcd.createChar(5, FuelLow);
  // create character fuel level less than half  
  lcd.createChar(6, Fuelhalf);
  // // create character dhtRead                        !!!!CAN NOT GET THIS CHARACTER TO WORK!!!! 
  // lcd.createChar(7, dhtReadchar);                          /*when this part is uncommented it effects character "1, TruckBcob" */    //***I added char TRY AGAIN***
#endif
}