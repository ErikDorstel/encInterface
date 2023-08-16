#define enc0A 4
#define enc0B 18
#define enc1A 19
#define enc1B 21
#define enc2A 22
#define enc2B 23

volatile struct encStruct { uint8_t seqIndex[8]; uint8_t nextCW[8]; uint8_t nextCCW[8]; int32_t value[8]; } enc;
const uint8_t encSequence[6]={1,0,2,3,1,0};

void IRAM_ATTR enc0ISR() {
  uint8_t encIndex=0; uint8_t encInput=0;
  if (digitalRead(enc0A)) { encInput|=2; }
  if (digitalRead(enc0B)) { encInput|=1; }

  if (encInput==enc.nextCW[encIndex]) {
    if (enc.seqIndex[encIndex]<4) { enc.seqIndex[encIndex]+=1; } else { enc.seqIndex[encIndex]=1; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]+=1; } else

  if (encInput==enc.nextCCW[encIndex]) {
    if (enc.seqIndex[encIndex]>1) { enc.seqIndex[encIndex]-=1; } else { enc.seqIndex[encIndex]=4; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]-=1; } }

void IRAM_ATTR enc1ISR() {
  uint8_t encIndex=1; uint8_t encInput=0;
  if (digitalRead(enc1A)) { encInput|=2; }
  if (digitalRead(enc1B)) { encInput|=1; }

  if (encInput==enc.nextCW[encIndex]) {
    if (enc.seqIndex[encIndex]<4) { enc.seqIndex[encIndex]+=1; } else { enc.seqIndex[encIndex]=1; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]+=1; } else

  if (encInput==enc.nextCCW[encIndex]) {
    if (enc.seqIndex[encIndex]>1) { enc.seqIndex[encIndex]-=1; } else { enc.seqIndex[encIndex]=4; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]-=1; } }

void IRAM_ATTR enc2ISR() {
  uint8_t encIndex=2; uint8_t encInput=0;
  if (digitalRead(enc2A)) { encInput|=2; }
  if (digitalRead(enc2B)) { encInput|=1; }

  if (encInput==enc.nextCW[encIndex]) {
    if (enc.seqIndex[encIndex]<4) { enc.seqIndex[encIndex]+=1; } else { enc.seqIndex[encIndex]=1; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]+=1; } else

  if (encInput==enc.nextCCW[encIndex]) {
    if (enc.seqIndex[encIndex]>1) { enc.seqIndex[encIndex]-=1; } else { enc.seqIndex[encIndex]=4; }
    enc.nextCW[encIndex]=encSequence[enc.seqIndex[encIndex]+1];
    enc.nextCCW[encIndex]=encSequence[enc.seqIndex[encIndex]-1];
    enc.value[encIndex]-=1; } }

void setSeqIndex0() {
  uint8_t encIndex=0; uint8_t encInput=0;
  if (digitalRead(enc0A)) { encInput|=2; }
  if (digitalRead(enc0B)) { encInput|=1; }
  for (int i=1;i<=4;i++) { if (encInput==encSequence[i]) { enc.seqIndex[encIndex]=i;
    enc.nextCW[encIndex]=encSequence[i+1]; enc.nextCCW[encIndex]=encSequence[i-1];
    if (debug) { Serial.printf("%i : %i - %i - %i\r\n",encIndex,enc.nextCCW[encIndex],encInput,enc.nextCW[encIndex]); } } } }

void setSeqIndex1() {
  uint8_t encIndex=1; uint8_t encInput=0;
  if (digitalRead(enc1A)) { encInput|=2; }
  if (digitalRead(enc1B)) { encInput|=1; }
  for (int i=1;i<=4;i++) { if (encInput==encSequence[i]) { enc.seqIndex[encIndex]=i;
    enc.nextCW[encIndex]=encSequence[i+1]; enc.nextCCW[encIndex]=encSequence[i-1];
    if (debug) { Serial.printf("%i : %i - %i - %i\r\n",encIndex,enc.nextCCW[encIndex],encInput,enc.nextCW[encIndex]); } } } }

void setSeqIndex2() {
  uint8_t encIndex=2; uint8_t encInput=0;
  if (digitalRead(enc2A)) { encInput|=2; }
  if (digitalRead(enc2B)) { encInput|=1; }
  for (int i=1;i<=4;i++) { if (encInput==encSequence[i]) { enc.seqIndex[encIndex]=i;
    enc.nextCW[encIndex]=encSequence[i+1]; enc.nextCCW[encIndex]=encSequence[i-1];
    if (debug) { Serial.printf("%i : %i - %i - %i\r\n",encIndex,enc.nextCCW[encIndex],encInput,enc.nextCW[encIndex]); } } } }

void initEncoder() {
  pinMode(enc0A,INPUT_PULLUP); pinMode(enc0B,INPUT_PULLUP);
  setSeqIndex0();
  attachInterrupt(enc0A,enc0ISR,CHANGE); attachInterrupt(enc0B,enc0ISR,CHANGE);
  pinMode(enc1A,INPUT_PULLUP); pinMode(enc1B,INPUT_PULLUP);
  setSeqIndex1();
  attachInterrupt(enc1A,enc1ISR,CHANGE); attachInterrupt(enc1B,enc1ISR,CHANGE);
  pinMode(enc2A,INPUT_PULLUP); pinMode(enc2B,INPUT_PULLUP);
  setSeqIndex2();
  attachInterrupt(enc2A,enc2ISR,CHANGE); attachInterrupt(enc2B,enc2ISR,CHANGE); }
