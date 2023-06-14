void SwitchDisplayUpdate(){
  bool Read_SW[] = {digitalRead(saklar0), digitalRead(saklar1), digitalRead(saklar2), digitalRead(saklar3)};
  if (Read_SW != Slave_SW){
    for (int i = 0; i <= 3; i++) {
      Slave_SW[i] = Read_SW[i];
    }
  }
  if (Slave_SW[0]){
    segment4[0] = 0x00; segment4[1] = 0x77; segment4[2] = 0x40;
    segment4[3] = display.encodeDigit(Slave_SW[1]*4 + Slave_SW[2]*2 + Slave_SW[3]*1 + 1);
    Slave_TYPE = "AM";
    Slave_ID = Slave_SW[1]*4 + Slave_SW[2]*2 + Slave_SW[3]*1 + 1;
  } else {
    segment4[0] = 0x74; segment4[1] = 0x78; segment4[2] = 0x40;
    segment4[3] = display.encodeDigit(Slave_SW[1]*4 + Slave_SW[2]*2 + Slave_SW[3]*1 + 1);
    Slave_TYPE = "HT";
    Slave_ID = Slave_SW[1]*4 + Slave_SW[2]*2 + Slave_SW[3]*1 + 1;
  }
  unsigned long displaymillis = millis();
  if (Slave_TYPE=="HT"){
    if (displaymillis%6000<3000){
      display.setSegments(segment4);
    } else if (displaymillis%6000>=3000 && displaymillis%6000<4500 ){
      segment4[0] = 0x78; segment4[1] = 0x00;
      segment4[2] = display.encodeDigit(int(floor(t_sekarang/10)));
      segment4[3] = display.encodeDigit(int(floor(t_sekarang))%10);
      display.setSegments(segment4);
    } else if (displaymillis%6000>=4500){
      segment4[0] = 0x74; segment4[1] = 0x00;
      segment4[2] = display.encodeDigit(int(floor(h_sekarang/10)));
      segment4[3] = display.encodeDigit(int(floor(h_sekarang))%10);
      display.setSegments(segment4);
    }
  }
  if (Slave_TYPE=="AM"){
    if (displaymillis%4000<=2000){
      display.setSegments(segment4);
    } else {
      segment4[0] = 0x77;
      if (floor(a_sekarang)<100){
        segment4[1] = 0x00;
        segment4[2] = display.encodeDigit(int(floor(a_sekarang/10)));
        segment4[3] = display.encodeDigit(int(floor(a_sekarang))%10);
        display.setSegments(segment4);
      } else {
        segment4[1] = display.encodeDigit(int(floor(a_sekarang))/100);
        segment4[2] = display.encodeDigit((int(floor(a_sekarang))%100)/10);
        segment4[3] = display.encodeDigit(int(floor(a_sekarang))%10);
        display.setSegments(segment4);
      }
      
    }
  }
}
