#include "shell.h"

void rsi(char *filename, int periods, double top, double bottom ){

    const char *delim = ",";
    FILE* dataset = fopen(filename, "r");
    char buffer[1024];
    char* tok = NULL;
    double rsi=0.0, avggain=0.0, avgloss=0.0, prevavggain=0.0, prevavgloss=0.0, price=0.0, lastprice=0.0;
    int period=0;

    if(periods <= 1){
        printf("Default RSI period as per Wilder's book is 14.\n In this case we'll accept anything above 1. Have fun!\n");
        return;
    }

    if(dataset==NULL){
        perror("Input file wasn't accepted, somehow.\n");
    }
    fgets( buffer, 1024, dataset );
    while( fgets( buffer, 1024, dataset ) != NULL ){
        printf("%s\n", buffer);
        tok = strtok(buffer, delim);
        tok = strtok(NULL, delim);
        while(tok!=NULL){
            printf("%s\n", tok);
            sscanf(tok, "%lf", &price);
            
            if( period >= periods ){
                if( price > lastprice ){
                    avggain = ( ( ( prevavggain * ( periods - 1 ) ) + ( price - lastprice ) ) / periods );
                }else if( price < lastprice ){
                    avgloss = ( ( ( prevavgloss * ( periods - 1 ) ) + ( abs(price - lastprice ) ) ) / periods);
                } 


            }else{
                if( price > lastprice ){
                    avggain += price - lastprice;
                }else if( price < lastprice ){
                    avgloss += abs(price - lastprice);
                }
                if( period == periods){
                    prevavggain = avggain / periods;
                    prevavgloss = avgloss / periods;
                    avggain = prevavggain;
                    avgloss = prevavgloss;
                }

            }
            
            tok = strtok(NULL, delim);
        }
        lastprice = price;
        printf("%lf\n%lf\n",avggain, avgloss );
        if(period >= periods){
            rsi = 100 - ( 100 / 1 + ( avggain / avgloss ) );

            if( rsi >= top ){
                printf("RSI (%d) :  %lf  : OVERBOUGHT!\n", periods, rsi);
            }else if( rsi <= bottom ) printf("RSI (%d) :  %lf  : OVERSOLD!\n", periods, rsi);
        }
        period++;
    }

}