#include <string.h>

//
// Created by Eron on 12/03/2016.
//

void PopularMascara(const char *cNomeProcessamento , int nLinhasMascara, int nColunasMascara, float dMascaraFiltro[nLinhasMascara][nColunasMascara]){


    if (strcmp(cNomeProcessamento, "Sharpen") == 0) {

        dMascaraFiltro[0][0] =  0;  dMascaraFiltro[0][1] = -1; dMascaraFiltro[0][2] =  0;
        dMascaraFiltro[1][0] = -1;  dMascaraFiltro[1][1] =  5; dMascaraFiltro[1][2] = -1;
        dMascaraFiltro[2][0] =  0;  dMascaraFiltro[2][1] = -1; dMascaraFiltro[2][2] =  0;
    }
    if (strcmp(cNomeProcessamento, "Agucar") == 0) {

        dMascaraFiltro[0][0] =  0;  dMascaraFiltro[0][1] = (float) -0.3; dMascaraFiltro[0][2] =  0;
        dMascaraFiltro[1][0] = (float) -0.3;  dMascaraFiltro[1][1] =  2.7; dMascaraFiltro[1][2] = (float) -0.3;
        dMascaraFiltro[2][0] =  0;  dMascaraFiltro[2][1] = (float) -0.3; dMascaraFiltro[2][2] =  0;
    }
    if (strcmp(cNomeProcessamento, "DestacarRelevo") == 0) {
        dMascaraFiltro[0][0] = -2;  dMascaraFiltro[0][1] = -1; dMascaraFiltro[0][2] = 0;
        dMascaraFiltro[1][0] = -1;  dMascaraFiltro[1][1] =  1; dMascaraFiltro[1][2] = 1;
        dMascaraFiltro[2][0] =  0;  dMascaraFiltro[2][1] =  1; dMascaraFiltro[2][2] = 2;

    }
    if (strcmp(cNomeProcessamento, "FreiChenVertical") == 0) {
        dMascaraFiltro[0][0] = -1;           dMascaraFiltro[0][1] = 0; dMascaraFiltro[0][2] = 1;
        dMascaraFiltro[1][0] = -1,41421356;  dMascaraFiltro[1][1] = 0; dMascaraFiltro[1][2] = 1,41421356;
        dMascaraFiltro[2][0] = -1;           dMascaraFiltro[2][1] = 0; dMascaraFiltro[2][2] = 1;
    }
    if (strcmp(cNomeProcessamento, "FreiChenHorizontal") == 0) {
        dMascaraFiltro[0][0] = -1;  dMascaraFiltro[0][1] = -1,41421356;  dMascaraFiltro[0][2] = -1;
        dMascaraFiltro[1][0] =  0;  dMascaraFiltro[1][1] = 0;            dMascaraFiltro[1][2] =  0;
        dMascaraFiltro[2][0] =  1;  dMascaraFiltro[2][1] =  1,41421356;  dMascaraFiltro[2][2] =  1;
    }
    if (strcmp(cNomeProcessamento, "Kirsch") == 0) {
        dMascaraFiltro[0][0] =  5;  dMascaraFiltro[0][1] =  5;  dMascaraFiltro[0][2] =  5;
        dMascaraFiltro[1][0] = -3;  dMascaraFiltro[1][1] =  0;  dMascaraFiltro[1][2] = -3;
        dMascaraFiltro[2][0] = -3;  dMascaraFiltro[2][1] = -3;  dMascaraFiltro[2][2] = -3;
    }
    if (strcmp(cNomeProcessamento, "Laplace") == 0) {

        dMascaraFiltro[0][0] = -1;  dMascaraFiltro[0][1] = -1;  dMascaraFiltro[0][2] = -1;
        dMascaraFiltro[1][0] = -1;  dMascaraFiltro[1][1] = 8 ;  dMascaraFiltro[1][2] = -1;
        dMascaraFiltro[2][0] = -1;  dMascaraFiltro[2][1] = -1;  dMascaraFiltro[2][2] = -1;
    }
    if (strcmp(cNomeProcessamento, "Media") == 0) {
        dMascaraFiltro[0][0] = (float) 0.1111111111; dMascaraFiltro[0][1] = (float) 0.1111111111; dMascaraFiltro[0][2] = (float) 0.1111111111;
        dMascaraFiltro[1][0] = (float) 0.1111111111; dMascaraFiltro[1][1] = (float) 0.1111111111; dMascaraFiltro[1][2] = (float) 0.1111111111;
        dMascaraFiltro[2][0] = (float) 0.1111111111; dMascaraFiltro[2][1] = (float) 0.1111111111; dMascaraFiltro[2][2] = (float) 0.1111111111;
    }
    if (strcmp(cNomeProcessamento, "PrewittVertical") == 0) {

        dMascaraFiltro[0][0] = -1; dMascaraFiltro[0][1] = 0; dMascaraFiltro[0][2] = 1;
        dMascaraFiltro[1][0] = -1; dMascaraFiltro[1][1] = 0; dMascaraFiltro[1][2] = 1;
        dMascaraFiltro[2][0] = -1; dMascaraFiltro[2][1] = 0; dMascaraFiltro[2][2] = 1;
    }
    if (strcmp(cNomeProcessamento, "PrewittHorizontal") == 0) {
        dMascaraFiltro[0][0] = -1;  dMascaraFiltro[0][1] = -1;   dMascaraFiltro[0][2] = -1;
        dMascaraFiltro[1][0] =  0;  dMascaraFiltro[1][1] =  0;   dMascaraFiltro[1][2] =  0;
        dMascaraFiltro[2][0] =  1;  dMascaraFiltro[2][1] =  1;   dMascaraFiltro[2][2] =  1;
    }
    if (strcmp(cNomeProcessamento, "RobertsVertical") == 0) {

        dMascaraFiltro[0][0] = 0; dMascaraFiltro[0][1] =  1; dMascaraFiltro[0][2] = 0;
        dMascaraFiltro[1][0] = 0; dMascaraFiltro[1][1] = -1; dMascaraFiltro[1][2] = 0;
        dMascaraFiltro[2][0] = 0; dMascaraFiltro[2][1] =  0; dMascaraFiltro[2][2] = 0;
    }
    if (strcmp(cNomeProcessamento, "RobertsHorizontal") == 0) {
        dMascaraFiltro[0][0] = 0; dMascaraFiltro[0][1] =  0; dMascaraFiltro[0][2] = 0;
        dMascaraFiltro[1][0] = 0; dMascaraFiltro[1][1] = -1; dMascaraFiltro[1][2] = 0;
        dMascaraFiltro[2][0] = 0; dMascaraFiltro[2][1] =  1; dMascaraFiltro[2][2] = 0;
    }
    if (strcmp(cNomeProcessamento, "SobelVertical") == 0) {
        dMascaraFiltro[0][0] = -1; dMascaraFiltro[0][1] = 0; dMascaraFiltro[0][2] = 1;
        dMascaraFiltro[1][0] = -2; dMascaraFiltro[1][1] = 0; dMascaraFiltro[1][2] = 2;
        dMascaraFiltro[2][0] = -1; dMascaraFiltro[2][1] = 0; dMascaraFiltro[2][2] = 1;
    }
    if (strcmp(cNomeProcessamento, "SobelHorizontal") == 0) {
        dMascaraFiltro[0][0] = -1; dMascaraFiltro[0][1] = -2; dMascaraFiltro[0][2] = -1;
        dMascaraFiltro[1][0] =  0; dMascaraFiltro[1][1] =  0; dMascaraFiltro[1][2] =  0;
        dMascaraFiltro[2][0] =  1; dMascaraFiltro[2][1] =  2; dMascaraFiltro[2][2] =  1;
    }
    if (strcmp(cNomeProcessamento, "Cartoon") == 0) {
        dMascaraFiltro[0][0] = 1; dMascaraFiltro[0][1] = 2; dMascaraFiltro[0][2] = 1;
        dMascaraFiltro[1][0] =  2; dMascaraFiltro[1][1] =  4; dMascaraFiltro[1][2] =  2;
        dMascaraFiltro[2][0] =  1; dMascaraFiltro[2][1] =  2; dMascaraFiltro[2][2] =  1;
    }
    /*
    if (strcmp(cNomeProcessamento, "SobelVertical5x5") == 0) {
        dMascaraFiltro[0][0] = -2; dMascaraFiltro[0][1] = -1; dMascaraFiltro[0][2] = 0;dMascaraFiltro[0][3] = 1;dMascaraFiltro[0][4] = 2;
        dMascaraFiltro[1][0] = -2; dMascaraFiltro[1][1] = -1; dMascaraFiltro[1][2] = 0;dMascaraFiltro[1][3] = 1;dMascaraFiltro[1][4] = 2;
        dMascaraFiltro[2][0] = -4; dMascaraFiltro[2][1] = -2; dMascaraFiltro[2][2] = 0;dMascaraFiltro[2][3] = 2;dMascaraFiltro[2][4] = 4;
        dMascaraFiltro[3][0] = -2; dMascaraFiltro[3][1] = -1; dMascaraFiltro[3][2] = 0;dMascaraFiltro[3][3] = 1;dMascaraFiltro[3][4] = 2;
        dMascaraFiltro[4][0] = -2; dMascaraFiltro[4][1] = -1; dMascaraFiltro[4][2] = 0;dMascaraFiltro[4][3] = 1;dMascaraFiltro[4][4] = 2;

    }

    if (strcmp(cNomeProcessamento, "SobelHorizontal5x5") == 0) {
        dMascaraFiltro[0][0] = 2; dMascaraFiltro[0][1] = 2; dMascaraFiltro[0][2] = 4;dMascaraFiltro[0][3] = 2;dMascaraFiltro[0][4] = 2;
        dMascaraFiltro[1][0] = 1; dMascaraFiltro[1][1] = 1; dMascaraFiltro[1][2] = 2;dMascaraFiltro[1][3] = 1;dMascaraFiltro[1][4] = 1;
        dMascaraFiltro[2][0] = 0; dMascaraFiltro[2][1] = 0; dMascaraFiltro[2][2] = 0;dMascaraFiltro[2][3] = 0;dMascaraFiltro[2][4] = 0;
        dMascaraFiltro[3][0] = -2; dMascaraFiltro[3][1] = -1; dMascaraFiltro[3][2] =-2;dMascaraFiltro[3][3] = -1;dMascaraFiltro[3][4] = -1;
        dMascaraFiltro[4][0] = -1; dMascaraFiltro[4][1] = -2; dMascaraFiltro[4][2] = -4;dMascaraFiltro[4][3] = -2;dMascaraFiltro[4][4] = -2;

    }
    */
    if (strcmp(cNomeProcessamento, "SobelVertical5x5") == 0) {
        dMascaraFiltro[0][0] = 1; dMascaraFiltro[0][1] = 2; dMascaraFiltro[0][2] = 0;dMascaraFiltro[0][3] = -2;dMascaraFiltro[0][4] = -1;
        dMascaraFiltro[1][0] = 4; dMascaraFiltro[1][1] = 8; dMascaraFiltro[1][2] = 0;dMascaraFiltro[1][3] = -8;dMascaraFiltro[1][4] = -4;
        dMascaraFiltro[2][0] = 6; dMascaraFiltro[2][1] = 12; dMascaraFiltro[2][2] = 0;dMascaraFiltro[2][3] = -12;dMascaraFiltro[2][4] = -6;
        dMascaraFiltro[3][0] = 4; dMascaraFiltro[3][1] = 8; dMascaraFiltro[3][2] = 0;dMascaraFiltro[3][3] = -8;dMascaraFiltro[3][4] = -4;
        dMascaraFiltro[4][0] = 1; dMascaraFiltro[4][1] = 2; dMascaraFiltro[4][2] = 0;dMascaraFiltro[4][3] = -2;dMascaraFiltro[4][4] = -1;

    }

    if (strcmp(cNomeProcessamento, "SobelHorizontal5x5") == 0) {
        dMascaraFiltro[0][0] = 1; dMascaraFiltro[0][1] = 4; dMascaraFiltro[0][2] = 6;dMascaraFiltro[0][3] = 4;dMascaraFiltro[0][4] = 1;
        dMascaraFiltro[1][0] = 2; dMascaraFiltro[1][1] = 8; dMascaraFiltro[1][2] = 12;dMascaraFiltro[1][3] = 8;dMascaraFiltro[1][4] = 2;
        dMascaraFiltro[2][0] = 0; dMascaraFiltro[2][1] = 0; dMascaraFiltro[2][2] = 0;dMascaraFiltro[2][3] = 0;dMascaraFiltro[2][4] = 0;
        dMascaraFiltro[3][0] = -2; dMascaraFiltro[3][1] = -8; dMascaraFiltro[3][2] = -12;dMascaraFiltro[3][3] = -8;dMascaraFiltro[3][4] = -2;
        dMascaraFiltro[4][0] = -1; dMascaraFiltro[4][1] = -4; dMascaraFiltro[4][2] = -6;dMascaraFiltro[4][3] = -4;dMascaraFiltro[4][4] = -1;

    }


    if (strcmp(cNomeProcessamento, "Media5x5") == 0) {
        dMascaraFiltro[0][0] = (float) 0.1111111111; dMascaraFiltro[0][1] = (float) 0.1111111111; dMascaraFiltro[0][2] = (float) 0.1111111111;dMascaraFiltro[0][3] = (float) 0.1111111111;dMascaraFiltro[0][4] = (float) 0.1111111111;
        dMascaraFiltro[1][0] = (float) 0.1111111111; dMascaraFiltro[1][1] = (float) 0.1111111111; dMascaraFiltro[1][2] = (float) 0.1111111111;dMascaraFiltro[1][3] = (float) 0.1111111111;dMascaraFiltro[1][4] = (float) 0.1111111111;
        dMascaraFiltro[2][0] = (float) 0.1111111111; dMascaraFiltro[2][1] = (float) 0.1111111111; dMascaraFiltro[2][2] = (float) 0.1111111111;dMascaraFiltro[2][3] = (float) 0.1111111111;dMascaraFiltro[2][4] = (float) 0.1111111111;
        dMascaraFiltro[3][0] = (float) 0.1111111111; dMascaraFiltro[3][1] = (float) 0.1111111111; dMascaraFiltro[3][2] = (float) 0.1111111111;dMascaraFiltro[3][3] = (float) 0.1111111111;dMascaraFiltro[3][4] = (float) 0.1111111111;
        dMascaraFiltro[4][0] = (float) 0.1111111111; dMascaraFiltro[4][1] = (float) 0.1111111111; dMascaraFiltro[4][2] = (float) 0.1111111111;dMascaraFiltro[4][3] = (float) 0.1111111111;dMascaraFiltro[4][4] = (float) 0.1111111111;

    }

    if (strcmp(cNomeProcessamento, "Media7x7") == 0) {
        dMascaraFiltro[0][0] = (float) 0.1111111111; dMascaraFiltro[0][1] = (float) 0.1111111111; dMascaraFiltro[0][2] = (float) 0.1111111111;dMascaraFiltro[0][3] = (float) 0.1111111111;dMascaraFiltro[0][4] = (float) 0.1111111111;dMascaraFiltro[0][5] = (float) 0.1111111111;dMascaraFiltro[0][6] = (float) 0.1111111111;
        dMascaraFiltro[1][0] = (float) 0.1111111111; dMascaraFiltro[1][1] = (float) 0.1111111111; dMascaraFiltro[1][2] = (float) 0.1111111111;dMascaraFiltro[1][3] = (float) 0.1111111111;dMascaraFiltro[1][4] = (float) 0.1111111111;dMascaraFiltro[1][5] = (float) 0.1111111111;dMascaraFiltro[1][6] = (float) 0.1111111111;
        dMascaraFiltro[2][0] = (float) 0.1111111111; dMascaraFiltro[2][1] = (float) 0.1111111111; dMascaraFiltro[2][2] = (float) 0.1111111111;dMascaraFiltro[2][3] = (float) 0.1111111111;dMascaraFiltro[2][4] = (float) 0.1111111111;dMascaraFiltro[2][5] = (float) 0.1111111111;dMascaraFiltro[2][6] = (float) 0.1111111111;
        dMascaraFiltro[3][0] = (float) 0.1111111111; dMascaraFiltro[3][1] = (float) 0.1111111111; dMascaraFiltro[3][2] = (float) 0.1111111111;dMascaraFiltro[3][3] = (float) 0.1111111111;dMascaraFiltro[3][4] = (float) 0.1111111111;dMascaraFiltro[3][5] = (float) 0.1111111111;dMascaraFiltro[3][6] = (float) 0.1111111111;
        dMascaraFiltro[4][0] = (float) 0.1111111111; dMascaraFiltro[4][1] = (float) 0.1111111111; dMascaraFiltro[4][2] = (float) 0.1111111111;dMascaraFiltro[4][3] = (float) 0.1111111111;dMascaraFiltro[4][4] = (float) 0.1111111111;dMascaraFiltro[4][5] = (float) 0.1111111111;dMascaraFiltro[4][6] = (float) 0.1111111111;
        dMascaraFiltro[4][0] = (float) 0.1111111111; dMascaraFiltro[5][1] = (float) 0.1111111111; dMascaraFiltro[5][2] = (float) 0.1111111111;dMascaraFiltro[5][3] = (float) 0.1111111111;dMascaraFiltro[5][4] = (float) 0.1111111111;dMascaraFiltro[5][5] = (float) 0.1111111111;dMascaraFiltro[5][6] = (float) 0.1111111111;
        dMascaraFiltro[4][0] = (float) 0.1111111111; dMascaraFiltro[6][1] = (float) 0.1111111111; dMascaraFiltro[6][2] = (float) 0.1111111111;dMascaraFiltro[6][3] = (float) 0.1111111111;dMascaraFiltro[6][4] = (float) 0.1111111111;dMascaraFiltro[6][5] = (float) 0.1111111111;dMascaraFiltro[6][6] = (float) 0.1111111111;

    }

    if (strcmp(cNomeProcessamento, "Gauss") == 0) {
        dMascaraFiltro[0][0] = (float) 0.0751; dMascaraFiltro[0][1] = (float) 0.1238; dMascaraFiltro[0][2] = (float) 0.0751;
        dMascaraFiltro[1][0] = (float) 0.1238; dMascaraFiltro[1][1] = (float) 0.2042; dMascaraFiltro[1][2] = (float) 0.1238;
        dMascaraFiltro[2][0] = (float) 0.0751; dMascaraFiltro[2][1] = (float) 0.1238; dMascaraFiltro[2][2] = (float) 0.0751;
    }
    /*
    if (strcmp(cNomeProcessamento, "Gauss") == 0) {
        dMascaraFiltro[0][0] = 1; dMascaraFiltro[0][1] = 4; dMascaraFiltro[0][2] = 7;dMascaraFiltro[0][3] = 4;dMascaraFiltro[0][4] = 1;
        dMascaraFiltro[1][0] = 4; dMascaraFiltro[1][1] = 16; dMascaraFiltro[1][2] = 26;dMascaraFiltro[1][3] = 16;dMascaraFiltro[1][4] = 4;
        dMascaraFiltro[2][0] = 7; dMascaraFiltro[2][1] = 26; dMascaraFiltro[2][2] = 41;dMascaraFiltro[2][3] = 26;dMascaraFiltro[2][4] = 7;
        dMascaraFiltro[3][0] = 4; dMascaraFiltro[3][1] = 16; dMascaraFiltro[3][2] =26;dMascaraFiltro[3][3] = 16;dMascaraFiltro[3][4] = 4;
        dMascaraFiltro[4][0] = 1; dMascaraFiltro[4][1] = -4; dMascaraFiltro[4][2] = 7;dMascaraFiltro[4][3] = 4;dMascaraFiltro[4][4] = 1;

    }
     */

}




