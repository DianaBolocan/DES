#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMatrix(FILE* file,int matrix[4][16]){
  for(int i=0;i<4;i++)
	for(int j=0;j<16;j++)
		if(!fscanf(file,"%d",&matrix[i][j]))
			break;
}

int binaryNr(char first,char second){
  if(first == '1'){
	if(second == '1') return 3;
	else return 2;
  }else{
	if(second == '1') return 1;
	else return 0;
  }
}

int binaryColumn(char first,char second,char third,char forth){
  char binary[4];
  binary[0] = first;
  binary[1] = second;
  binary[2] = third;
  binary[3] = forth;

  if( strcmp(binary, "0000") == 0 ) return 0;
  if( strcmp(binary, "0001") == 0 ) return 1;
  if( strcmp(binary, "0010") == 0 ) return 2;
  if( strcmp(binary, "0011") == 0 ) return 3;
  if( strcmp(binary, "0100") == 0 ) return 4;
  if( strcmp(binary, "0101") == 0 ) return 5;
  if( strcmp(binary, "0110") == 0 ) return 6;
  if( strcmp(binary, "0111") == 0 ) return 7;
  if( strcmp(binary, "1000") == 0 ) return 8;
  if( strcmp(binary, "1001") == 0 ) return 9;
  if( strcmp(binary, "1010") == 0 ) return 10;
  if( strcmp(binary, "1011") == 0 ) return 11;
  if( strcmp(binary, "1100") == 0 ) return 12;
  if( strcmp(binary, "1101") == 0 ) return 13;
  if( strcmp(binary, "1110") == 0 ) return 14;
  if( strcmp(binary, "1111") == 0 ) return 15;
}

char* toBinary(char hexa){
  if(hexa == '0') return "0000";
  if(hexa == '1') return "0001";
  if(hexa == '2') return "0010";
  if(hexa == '3') return "0011";
  if(hexa == '4') return "0100";
  if(hexa == '5') return "0101";
  if(hexa == '6') return "0110";
  if(hexa == '7') return "0111";
  if(hexa == '8') return "1000";
  if(hexa == '9') return "1001";
  if(hexa == 'A') return "1010";
  if(hexa == 'B') return "1011";
  if(hexa == 'C') return "1100";
  if(hexa == 'D') return "1101";
  if(hexa == 'E') return "1110";
  if(hexa == 'F') return "1111";   
}

int main(){
  int ip[8][8],e[8][6],s1[4][16],s2[4][16],s3[4][16],s4[4][16],s5[4][16],s6[4][16],s7[4][16],s8[4][16],pc1[8][7],pc2[8][6];
  FILE* text;

  //read all the matrixes that we will use
  text = fopen("IP.txt","r");
  for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
		if(!fscanf(text,"%d",&ip[i][j]))
			break;
  fclose(text);
  text = fopen("E.txt","r");
  for(int i=0;i<8;i++)
	for(int j=0;j<6;j++)
		if(!fscanf(text,"%d",&e[i][j]))
			break;
  fclose(text);
  text = fopen("PC1.txt","r");
  for(int i=0;i<8;i++)
	for(int j=0;j<7;j++)
		if(!fscanf(text,"%d",&pc1[i][j]))
			break;
  fclose(text);
  text = fopen("PC2.txt","r");
  for(int i=0;i<8;i++)
	for(int j=0;j<6;j++)
		if(!fscanf(text,"%d",&pc2[i][j]))
			break;
  fclose(text);
  text = fopen("S1.txt","r");
  getMatrix(text,s1);
  fclose(text);
  text = fopen("S2.txt","r");
  getMatrix(text,s2);
  fclose(text);
  text = fopen("S3.txt","r");
  getMatrix(text,s3);
  fclose(text);
  text = fopen("S4.txt","r");
  getMatrix(text,s4);
  fclose(text);
  text = fopen("S5.txt","r");
  getMatrix(text,s5);
  fclose(text);
  text = fopen("S6.txt","r");
  getMatrix(text,s6);
  fclose(text);
  text = fopen("S7.txt","r");
  getMatrix(text,s7);
  fclose(text);
  text = fopen("S8.txt","r");
  getMatrix(text,s8);
  fclose(text);

  char plainText[16] = "0123456789ABCDEF";
  char key[16] = "133457799BBCDFF1";
  char* binaryText = (char*)malloc(64);
  char* binaryKey = (char*)malloc(64);
  
  //convert from hex to binary
  strcpy(binaryText,toBinary(plainText[0]));
  for(int i=1;i<16;i++)
	strcat(binaryText,toBinary(plainText[i]));

  strcpy(binaryKey,toBinary(key[0]));
  for(int i=1;i<16;i++)
	strcat(binaryKey,toBinary(key[i]));

  //IP shift
  char* IPBinaryText = (char*)malloc(64);
  for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
		IPBinaryText[i*8+j] = binaryText[ip[i][j]-1];
  
  //get L0 and R0
  char* L = (char*)malloc(32);
  char* R = (char*)malloc(32);
  for(int i=0;i<32;i++){
	L[i] = IPBinaryText[i];
	R[i] = IPBinaryText[i+32];
  }

  //get K
  char K[56];
  for(int i=0;i<8;i++)
	for(int j=0;j<7;j++)
		K[i*7+j] = binaryKey[pc1[i][j]-1];

  //compute until L16 and R16 (with Ki, i=[1,16])
  int count=1;
  char* C = (char*)malloc(28);
  char* D = (char*)malloc(28);

  for(int i=0;i<28;i++)
	C[i] = K[i];
  for(int i=28;i<56;i++)
	D[i-28] = K[i];

  while(count <= 1){
	//get Key de count
	  char* newKey = (char*)malloc(48);
	  if( count != 1 && count != 2 && count != 9 && count != 16){
		char firstChar = C[0];
		char secondChar = C[1];
		for(int i=2;i<28;i++)
			C[i-2] = C[i];
		C[26] = firstChar;
		C[27] = secondChar;
		firstChar = D[0];
		secondChar = D[1];
		for(int i=2;i<28;i++)
			D[i-2] = D[i];
		D[26] = firstChar;
		D[27] = secondChar;
	  }else{
		char firstChar = C[0];
		for(int i=1;i<28;i++)
			C[i-1] = C[i];
		C[27] = firstChar;
		firstChar = D[0];
		for(int i=1;i<28;i++)
			D[i-1] = D[i];
		D[27] = firstChar;
	  }
	  char CD[56];
	  for(int i=0;i<28;i++)
		CD[i] = C[i];
	  for(int i=0;i<28;i++)
	  	CD[i+28] = D[i];

	  for(int i=0;i<8;i++)
		for(int j=0;j<6;j++){
			newKey[i*6+j] = CD[pc2[i][j]-1];
	  }	

	//R expandat
	char* RExp = (char*)malloc(48);
	for(int i=0;i<8;i++)
		for(int j=0;j<6;j++)
			RExp[i*6+j] = R[e[i][j]-1];

	//xor cu K de count
	for(int i=0;i<48;i++)	
		if(RExp[i] == newKey[i])
			RExp[i] = '0';
		else
			RExp[i] = '1';

	//get Bi cu i=[1,8]
	char* B1 = (char*)malloc(6);
	char* B2 = (char*)malloc(6);
	char* B3 = (char*)malloc(6);
	char* B4 = (char*)malloc(6);
	char* B5 = (char*)malloc(6);
	char* B6 = (char*)malloc(6);
	char* B7 = (char*)malloc(6);
	char* B8 = (char*)malloc(6);

	for(int i=0;i<6;i++) B1[i] = RExp[i];
	for(int i=6;i<12;i++) B2[i-6] = RExp[i];
	for(int i=12;i<18;i++) B3[i-12] = RExp[i];
	for(int i=18;i<24;i++) B4[i-18] = RExp[i];
	for(int i=24;i<30;i++) B5[i-24] = RExp[i];
	for(int i=30;i<36;i++) B6[i-30] = RExp[i];
	for(int i=36;i<42;i++) B7[i-36] = RExp[i];
	for(int i=42;i<48;i++) B8[i-42] = RExp[i];

	int row,column,C1,C2,C3,C4,C5,C6,C7,C8;

	row = binaryNr(B1[0],B1[5]);
	column = binaryColumn(B1[1],B1[2],B1[3],B1[4]);
	C1 = s1[row][column];

	row = binaryNr(B2[0],B2[5]);
	column = binaryColumn(B2[1],B2[2],B2[3],B2[4]);
	C2 = s2[row][column];

	row = binaryNr(B3[0],B3[5]);
	column = binaryColumn(B3[1],B3[2],B3[3],B3[4]);
	C3 = s3[row][column];

	row = binaryNr(B4[0],B4[5]);
	column = binaryColumn(B4[1],B4[2],B4[3],B4[4]);
	C4 = s4[row][column];

	row = binaryNr(B5[0],B5[5]);
	column = binaryColumn(B5[1],B5[2],B5[3],B5[4]);
	C5 = s5[row][column];

	row = binaryNr(B6[0],B6[5]);
	column = binaryColumn(B6[1],B6[2],B6[3],B6[4]);
	C6 = s6[row][column];

	row = binaryNr(B7[0],B7[5]);
	column = binaryColumn(B7[1],B7[2],B7[3],B7[4]);
	C7 = s7[row][column];

	row = binaryNr(B8[0],B8[5]);
	column = binaryColumn(B8[1],B8[2],B8[3],B8[4]);
	C8 = s8[row][column];

	char* C = (char*)malloc(32);

	count++;
  }

}
