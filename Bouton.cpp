/* 
 * File:   Bouton.cpp
 * Author: Marc
 * 
 * Created on 16 juillet 2016, 11:25
 */
#include "Bouton.h"



/**
 * Lecture avec memorisation des changement d'état
 * retourne l'etat stable 0 ou 1 ou erreur
 * un 1 ou un 0 est une succession de n bits consecutifs identiques
 * le masque definit nombre de bits au bout desquels l'état est accepté
 * exemple : masknbbitconsec = 0b11111 pour 5 bits
 * @param  masknbbitconsec : masque de validation
 */
int Bouton::readState(uint8_t masknbbitconsec)
//enum Bouton::etatbit_e Bouton::readState(uint8_t masknbbitconsec)
{
	static uint32_t memo = 0; // memorise les etats successifs
	memo <<= 1; // passage au bit suivant, le nouveau bit : bit0 est mis à 0

	if (digitalRead(this->pin()) == HIGH) {
		memo |= 1 ; // set bit0 a 1
		if((memo & masknbbitconsec) == masknbbitconsec) return UN;
	} 
	else { 
		if(((~memo) & masknbbitconsec) == masknbbitconsec) return ZERO;
	}
	return ERR; //erreur
}


