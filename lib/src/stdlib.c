/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "stdlib.h"
#include "string.h"
#include "mm/mm.h"

char* itoa(int num){
	    char* num_a = (char*) malloc(15); // assuming max 15 digit number.

	    int digits = 0;
	    int temp = num;
	    while(temp > 0){
	        digits++;
	        temp/=10;
	    }

	    for(int i=0;i<digits;i++){
	        num_a[digits-i-1] = '0' + num%10;
	        num/=10;
	    }
		num_a[digits] = '\0';
	    return num_a;
	
}

int stoi(char* str){
	int n = strlen(str);
	int val = 0;
	for(int i=0;i<n;i++){
		val *= 10;
		val += str[i] - '0';
	}

	return val;
}

int pow(int a, int b){
	int ans = 1;

	while(b--) ans *= a;


	return ans;

}

int hex_to_dec(char* num){

	int len = strlen(num);

	int res = 0;
	int exp = 0;

	for(int i=len-1;i>=2;i--){

		int val;

		if(num[i] >= '0' && num[i] <= '9') val = num[i] - '0';
		else{
			val = 10 + num[i] - 'a';
		}

		res += (val) * pow(16, exp);
		exp++;
	}


	return res;

}
