/* 
 * File:   main.cpp
 * Author: Marc
 *
 * Created on 16 juillet 2016, 11:24
 */
//#include "arduino_fake.h"
#include <cstdlib>

#include <inttypes.h> 
#include <iostream>
using namespace std;

#define HIGH 255
#define LOW 0
#define INPUT 0

// fake arduino
int DR = HIGH; // set digitalRead to HIGH
int digitalRead(int p = 0) { return DR; }
void pinMode(int, int) { }

#include "Bouton.h"


/*
 * 
 */
int main(int argc, char** argv) {

    Bouton* b = new Bouton();
    DR = HIGH;
    /*
    std::cout << "digitalRead[" << (int) digitalRead() << "]" << std::endl;
    Bouton::etatbit_e etat =   b->readState(0b11111);
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState(0b11111);
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState(0b11111);
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState(0b11111);
    //DR = LOW;
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState(0b11111);
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    
    DR = LOW;
    
    etat =   b->readState(0b11111);    
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    int read = b->read();
    std::cout << "read LOW [" << read << "]" << std::endl;
    
    DR = HIGH;
    etat =   b->readState(0b11111);   
    read = b->read();
    std::cout << "read HIGH [" << read << "]" << std::endl;
     * 
     */
    
    std::cout << "digitalRead[" << (int) digitalRead() << "]" << std::endl;
    Bouton::etatbit_e etat =   b->readState2();
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState2();
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState2();
    std::cout << "etat[" << (int) etat << "]" << std::endl;
    etat =   b->readState2();

    
    DR = LOW;
    int read  =   b->read();
    std::cout << "read(3) [" << (int) read << "]" << std::endl;   
    return 0;
}

