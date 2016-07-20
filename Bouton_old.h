/* 
 * File:   Bouton.h
 * Author: Marc
 *
 * Bouton qui memorise l'etat
 * et qui attende de recevoir x bit à 1 pour donner un etat HIGH
 * ou x but à l'etat 0 pour l'état LOW
 *
 * Reference : digitalRead, pinMode, HIGH
 */
#ifndef BOUTON_H
#define	BOUTON_H

#include <inttypes.h> 
#include <iostream>

typedef uint8_t mask_t; // type du mask

class Bouton {
public:
    /**
     * les états des du bouton
     */
    enum etatbit_e {
        ZERO = 0,
        UN = 0xFF,
        ERR = 0x0F
    };

//private :
    // nombre de bits successifs pour la lecture d'un etat
    mask_t mask; // masque associé pour la lecture
    
    /** 
     * memorise la config
     * 5 bit = n° de pin de 0 - 31
     * 2 bit = etat du bouton old et current
     * 1 bit = memo
     */
    uint8_t config; //0bPPPPPSSM 5bit:  pin 0-16 , 2b : state, 1b memo
    
public:
    // liste des boutons
    enum bouton_e { D0 = 0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, 
            A0, A1, A2, A3, A4, A5 };

    /**
     * Creation du Bouton.
     * @param nbbits : nombre de bits successuf a 1 pour reconnaire un UN
     * @param pin D0,D1...
     */
    Bouton(bouton_e pin, uint8_t nbbits = 5) {
        config = 0;
        //std::cout << "CTOR Bouton(bouton_e pin pin : [" << (int) pin << "]" << std::endl;
        pinMode(pin, INPUT);
        setPin(pin);
        //std::cout << "Bouton(bouton_e pin config : [" << (int) config << "]" << std::endl;
        mask = setMask(nbbits);
    }
    
    
    /**
     * Retourne le n° de pin entre 0 - 31
             xPPPPPxx : octet de config
     >>3 xxxPPPPP : shift
     &   00011111 : masque
     =      PPPPP : n° de pin
    */	
    uint8_t pin() {	return (config >> 3) & 0b00011111;	}

    /**
     * Affecte le n° de pin
     * pin & 0b00011111; // filtre bits pour valeurs 0-31
     * decale de 2, puis applique un ou pour affecter la valeur dans config
     */
    void setPin(bouton_e pin) { 
        //std::cout << "setPin  pin : [" << (int) pin << "]" << std::endl;
        config <<= 5; // 0bxxx;	 preserve SSM
        config >>= 5; // 0b00000xxx;
        config |= ((pin & 0b00011111)<<3) & 0b11111000;	
    }

    /**
     * Lecture avec memorisation des changement d'état
     * retourne l'etat stable 0 ou 1 ou erreur
     * lit un etat fugitif
     */    
    uint8_t update() {
        int count = 0;

        etatbit_e state = ERR;
       // std::cout << "> read() count [" << count << "] state : " << (int) state << "]" << std::endl;
        state = readState2();

        if (state == ERR) return ERR; // fin lecture
        
        // mise a jour de la memorisation : 
        // bit 2 etat actuel
        // bit 1 ancien etat      
        // lecture mise a jour etat actuel : SS
        if ( state == UN ) {
            config  |= ( 1 << 2); // set bit 2  0b00000210
        }
        else{
            config  &= ~(1 << 2 ); // clear bit 2 (3eme))
        }
        
        // memoire sur front descendant :  0bxxxxx01x
        // compare avec config bit 1 et 2
        // bouton relache : ancien etat 1, nouvel etat 0 => xx01x 
	if ((config & 0b00000110) == 0b00000010) {
            if (config & (1<<0) ){ // si Memo up :  clear sinon set
                config &= ~(1<<0); // clear bit 0 : memorise relachement : M
            }
            else {
                config |= (1<<0);  // set bit 0 : memorise appui : M
            }
        }
       
        // mise a jour des etats : bits SS
        // change l'etat old (S1) si different de l'actuel
        if ((config & 4 ) != (config & 2) ) {
             // bit 3 a 1 ?
            if (config & 4) {
               config |= (1 << 1); // set bit 1
            }
            else {
               config &= ~(1 << 1); // clear bit 1
            }
        }       
        return (uint8_t) state;
    }

    // etats  - teste le bit correspondant
    uint8_t memoState() { return (config & 1) ? 0xFF : 0; } // bit 0 (1<<0) = 1
    uint8_t state()     { return (config & (1 << 2)) ? 0xFF : 0; } // bit 2
    uint8_t oldState()  { return (config & (1 << 1)) ? 0xFF : 0; } // bit 1

    
//private:
    /**
     * cree le masque de nbbits
     * exemple pour nbbits = 5 : 
     * cree 0b00010000
     * soustrait 1 : 0b00001111
     * @return 
     */
    mask_t setMask(uint8_t nbbits) {
        mask_t mask = 0;
        mask |= (1 << (++nbbits));
        std::cout << " setMask bits [" << (int)nbbits << "] mask [" << (int)mask << "] " << std::endl;
        return --mask; // retire 1
        //std::cout << "readState2() mask [" << (int)mask << "] " << std::endl;        
    }
    
    /**
     * lecture de l'état réel de la pin et comparaison avec le mask
     * memo : memoire des états successif
     * mask : mask qui correspond à une valeur significative (UN ou ZERO)
     * @return 
     */
    enum etatbit_e readState2(){
        static int count =1;
        //std::cout << "readState2()  count [" << (int)count << "] " << std::endl;
       
        count++;
    	static mask_t memo = 0; // memorise les etats successifs
        memo <<= 1; // passage au bit suivant, le nouveau bit : bit0 est mis à 0
        
        if (digitalRead(this->pin()) == HIGH) {
            memo |= 1 ; // set bit0 a 1
           // std::cout << "readState2()  memo [" << (int)memo << "] " << std::endl;
          //  std::cout << "readState2()  (memo & mask) [" << (int)(memo & mask) << "] " << std::endl;
            
            
            if((memo & mask) == mask) return UN;
        } 
        else { 
            if(((~memo) & mask) == mask) return ZERO;
        }
        return ERR; //erreur
    }    
};

#endif	/* BOUTON_H */

