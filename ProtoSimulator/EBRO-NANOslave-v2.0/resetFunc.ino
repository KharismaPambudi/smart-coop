void(* resetFunc) (void) = 0;

void RESET(){
  uint8_t SEG_RST[4] = {0x01, 0x01, 0x01, 0x01};
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x02; SEG_RST[1] = 0x02; SEG_RST[2] = 0x02; SEG_RST[3] = 0x02;
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x04; SEG_RST[1] = 0x04; SEG_RST[2] = 0x04; SEG_RST[3] = 0x04;
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x08; SEG_RST[1] = 0x08; SEG_RST[2] = 0x08; SEG_RST[3] = 0x08;
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x0f; SEG_RST[1] = 0x0f; SEG_RST[2] = 0x0f; SEG_RST[3] = 0x0f;
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x20; SEG_RST[1] = 0x20; SEG_RST[2] = 0x20; SEG_RST[3] = 0x20;
  display.setSegments(SEG_RST); delay(125);
  SEG_RST[0] = 0x40; SEG_RST[1] = 0x40; SEG_RST[2] = 0x40; SEG_RST[3] = 0x40;
  display.setSegments(SEG_RST); delay(125);
  display.clear();
  resetFunc();
}
