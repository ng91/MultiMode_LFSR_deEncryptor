/*
 ============================================================================
 Name        : lfsr_multi_gen.c
 Author      : ng
 Version     :
 Copyright   : do not use
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LFSR_LENGTH 20
#define T_L 15

uint8_t randomP[LFSR_LENGTH]; //definition of the pseudorandom encryption/decryption table

uint8_t operation8b(uint8_t a);
uint8_t operation16b(uint16_t a);
uint8_t operation24b(uint32_t a);

uint8_t string[T_L]={'M', '1', '7', ' ', 'i', 's', ' ', 't', 'h', 'e', ' ', 'b', 'e', 's', 't'};
uint8_t enc[T_L];

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	//generate8b(0b01000101);
	//generate16b(0b0011010011011010);
	generate24b(0b001101000000101011000010);
	printf(" WYGENEROWANO \n");
	for(int i=0; i<LFSR_LENGTH; i++){
		printf(" %d ,", randomP[i]);
	}
	printf(" CZAS NA KODOWANIE\n");
	for(int i=0; i<T_L; i++){
		enc[i]=string[i]^randomP[i];
		printf("Zamieniono %c na %c kodem %d \n",string[i] , enc[i] , randomP[i]);
		string[i]=0;
	}
	printf(" CZAS NA ODKODOWANIE\n");
	for(int i=0; i<T_L; i++){
		string[i]=enc[i]^randomP[i];
		printf("Zamieniono %c na %c dekodem %d \n",enc[i] , string[i] , randomP[i]);
		enc[i]=0;
	}


	return EXIT_SUCCESS;
}

void generate8b(uint8_t seed){ // generate the lowest security encryption/decryption pseudorandom table
	uint8_t val = seed;
	for(int i=0; i<LFSR_LENGTH; i++){
		for(int q=0; q<8; q++){ // to generate new byte we have to perform shift operation 8 times(in case of 8 bit encryption)
			uint8_t newBit = 0;
			newBit = operation8b(val); // generating a new bit (0 or 1) ...
			val = val<<1; // ... shifting everything by one bit ...
			val = val | newBit; // ... and adding a new bit as LSB
			showBytesPattern8(val); // printing how it looks as ones and zeroes
		}
		showBytesPattern8(val); // printing how new Byte looks like
		printf(" %d ,\n", val); // same
		randomP[i]=val; // saving new Byte in table on the proper place
	}
}

void generate16b(uint16_t seed){ // generate the moderate security encryption/decryption pseudorandom table
	uint16_t val = seed;
	for(int i=0; i<(LFSR_LENGTH/2)+1; i++){
		for(int q=0; q<16; q++){
			uint8_t newBit = 0;
			newBit = operation16b(val);
			val = val<<1;
			val = val | newBit;
			showBytesPattern16(val);
		}
		showBytesPattern16(val);
		printf(" %d ,\n", val);
		if((2*i) <= LFSR_LENGTH){
		randomP[(2*i)]=(uint8_t)((val & 0xFF00) >> 8);
		}
		if(((2*i)+1) <= LFSR_LENGTH){
		randomP[(2*i)+1]=(uint8_t)(val & 0x00FF);
		}
	}
}

void generate24b(uint32_t seed){ // generate the strong security encryption/decryption pseudorandom table
	uint32_t val = seed;
	for(int i=0; i<(LFSR_LENGTH/3)+2; i++){

		for(int q=0; q<24; q++){
			uint8_t newBit = 0;
			newBit = operation24b(val);
			val = val<<1;
			val = val | newBit;
			showBytesPattern24(val);
		}
		showBytesPattern24(val);
		printf(" %d ,\n", val);
		if(3*i <= LFSR_LENGTH){
		randomP[(3*i)]=(uint8_t)((val & 0xFF0000) >> 16);
		}
		if(((3*i)+1) <= LFSR_LENGTH){
		randomP[(3*i)+1]=(uint8_t)((val & 0xFF00) >> 8);
		}
		if(((3*i)+2) <= LFSR_LENGTH){
		randomP[(3*i)+2]=(uint8_t)(val & 0x00FF);
		}
	}
}

void showBytesPattern8(uint8_t val){
	for(int i=0; i<8; i++){
		if(val & 1<<(7-i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}

void showBytesPattern16(uint16_t val){
	for(int i=0; i<16; i++){
		if(val & 1<<(15-i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}

void showBytesPattern24(uint32_t val){
	for(int i=0; i<24; i++){
		if(val & 1<<(23-i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}

uint8_t operation8b(uint8_t a){
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;
	uint8_t out = 0;

	if((a&0b10000000)>0){
		b=1;
	}else{
		b=0;
	}
	if((a&0b00100000)>0){
		c=1;
	}else{
		c=0;
	}
	if((a&0b00010000)>0){
		d=1;
	}else{
		d=0;
	}
	if((a&0b00001000)>0){
		e=1;
	}else{
		e=0;
	}
	out=(((b^c)^d)^e);

	return out;
}

uint8_t operation16b(uint16_t a){
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;
	uint8_t out = 0;

	if((a&0b1000000000000000)>0){
		b=1;
	}else{
		b=0;
	}
	if((a&0b0100000000000000)>0){
		c=1;
	}else{
		c=0;
	}
	if((a&0b0001000000000000)>0){
		d=1;
	}else{
		d=0;
	}
	if((a&0b0000000000001000)>0){
		e=1;
	}else{
		e=0;
	}
	out=(((b^c)^d)^e);

	return out;
}

uint8_t operation24b(uint32_t a){
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;
	uint8_t f = 0;
	uint8_t out = 0;

	if((a&0b100000000000000000000000)>0){
		b=1;
	}else{
		b=0;
	}
	if((a&0b010000000000000000000000)>0){
		c=1;
	}else{
		c=0;
	}
	if((a&0b001000000000000000000000)>0){
		d=1;
	}else{
		d=0;
	}
	if((a&0b000000010000000000000000)>0){
		e=1;
	}else{
		e=0;
	}
	if((a&0b000000000000000000001000)>0){
		f=1;
	}else{
		f=0;
	}
	out=((((b^c)^d)^e)^f);

	return out;
}
