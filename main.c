//
//  main.c
//  MineSweeper
//
//  Created by Zack Sima on 2018/11/18.
//  Copyright © 2018. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int determineDigits (int i) {
    int digits = 0;
    while (i > 0) {
        i /= 10;
        digits++;
    }
    return digits;
}

int main(int argc, const char * argv[]) {
    printf("Minesweeper v1.0 by Zack\n\n");
    while (1) {
        //seed changes rand number
        int seed = 0;
        //difficulty 1 easy 2 normal 3 hard
        int difficulty = 3;
        int fieldSizeX = 10;
        int fieldSizeY = 10;
        
        printf("Please enter difficulty (1 for easy, 2 for medium, 3 for hard)\n");
        scanf("%i", &difficulty);
        if (difficulty > 3) {
            difficulty = 3;
        } else if (difficulty < 1) {
            difficulty = 1;
        }
        printf("\n");
        printf("Please enter seed (0 - 10000)\n");
        scanf("%i", &seed);
        printf("\n");
        if (seed > 10000) {
            seed = 10000;
        } else if (seed < 0) {
            seed = 0;
        }
        
        printf("Please enter map width (5 - 40)\n");
        scanf("%i", &fieldSizeX);
        if (fieldSizeX > 40) {
            fieldSizeX = 40;
        } else if (fieldSizeX < 5) {
            fieldSizeX = 5;
        }
        
    //    printf("Please enter map height (10 - 99)\n");
    //    scanf("%i", &fieldSizeY);
        fieldSizeY = fieldSizeX;
        if (fieldSizeY > 40) {
            fieldSizeY = 40;
        } else if (fieldSizeY < 5) {
            fieldSizeY = 5;
        }
        
        //input coordinates
        int scanCoorX;
        int scanCoorY;
        
        //>= 10 is cleared, < 10 is not cleared (+10 to number after clearing grid)
        int grid[fieldSizeX][fieldSizeY];
        
        //setting up minefield, limit maximum size to 99
        for (int c = 0; c < 2; c++) {
            for (int i = 0; i < fieldSizeX; i++) {
                for (int j = 0; j < fieldSizeY; j++) {
                    if (c == 0) {
                        //create mines
                        if ((rand() + seed) % 100 <= 4 + (difficulty - 1) * 2) {
                            //grid with value of 9 is a mine
                            grid[i][j] = 9;
                        }
                    } else {
                        //create detection numbers  (mines around the grid)
                        int count = 0;
                        if (i - 1 >= 0 && grid[i - 1][j] == 9) {
                            count++;
                        }
                        if (i + 1 < fieldSizeX && grid[i + 1][j] == 9) {
                            count++;
                        }
                        if (j - 1 >= 0 && grid[i][j - 1] == 9) {
                            count++;
                        }
                        if (j + 1 < fieldSizeY && grid[i][j + 1] == 9) {
                            count++;
                        }
                        if (i + 1 < fieldSizeX && j + 1 < fieldSizeY && grid[i + 1][j + 1] == 9) {
                            count++;
                        }
                        if (i + 1 < fieldSizeX && j - 1 >= 0 && grid[i + 1][j - 1] == 9) {
                            count++;
                        }
                        if (i - 1 >= 0 && j + 1 < fieldSizeY && grid[i - 1][j + 1] == 9) {
                            count++;
                        }
                        if (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] == 9) {
                            count++;
                        }
                        if (grid[i][j] != 9) {
                            grid[i][j] = count;
                        }
                    }
                }
            }
        }/*
        //print answer grid (remove)
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < fieldSizeX; j++) {
                if (i == 0) {
                    if (determineDigits(j + 1) == 1) {
                        printf("0");
                    }
                    printf("%i ", j + 1);
                } else {
                    printf("-  ");
                }
            }
            printf("\n");
        }
        for (int j = 0; j < fieldSizeX; j++) {
            for (int i = 0; i < fieldSizeY; i++) {
                printf("%i  ", grid[i][j]);
            }
            printf("| ");
            if (determineDigits(j + 1) == 1) {
                printf("0");
            }
            printf("%i\n", j + 1);
        }
        //remove above in published version
        */
        //print grid
        int winGame = 1;
        for (int h = 0; ; h++) {
            printf("\nMinesweeper Round %i\n\n", h + 1);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < fieldSizeX; j++) {
                    if (i == 0) {
                        if (determineDigits(j + 1) == 1) {
                            printf("0");
                        }
                        printf("%i ", j + 1);
                    } else {
                        printf("-  ");
                    }
                }
                printf("\n");
            }
            //if nothing but mines are remaining player wins
            int loseGame = 0;
            winGame = 1;
            for (int j = 0; j < fieldSizeX; j++) {
                for (int i = 0; i < fieldSizeY; i++) {
                    if (grid[i][j] >= 10) {
                        if (grid[i][j] - 10 != 0) {
                            printf("%i  ", grid[i][j] - 10);
                        } else {
                            printf("   ");
                        }
                        if (grid[i][j] == 19) {
                            loseGame = 1;
                        }
                    } else {
                        printf("*  ");
                        if (grid[i][j] != 9) {
                            winGame = 0;
                        }
                    }
                }
                printf("| ");
                if (determineDigits(j + 1) == 1) {
                    printf("0");
                }
                printf("%i\n", j + 1);
            }
            //stop game here when all mines are cleared
            if (winGame) {
                break;
            }
            if (loseGame) {
                break;
            }
            
            
            //scanned number -1 is grid
            printf("\nPlease enter the X coordinate you want to sweep\n");
            scanf("%i", &scanCoorX);
            printf("\nPlease enter the Y coordinate you want to sweep\n");
            scanf("%i", &scanCoorY);
            scanCoorX--;
            scanCoorY--;
            if (scanCoorX >= fieldSizeX) {
                scanCoorX = fieldSizeX - 1;
            }
            if (scanCoorY >= fieldSizeY) {
                scanCoorY = fieldSizeY - 1;
            }
            if (scanCoorX < 0) {
                scanCoorX = 0;
            }
            if (scanCoorY < 0) {
                scanCoorY = 0;
            }
            if (grid[scanCoorX][scanCoorY] < 10) {
                if (grid[scanCoorX][scanCoorY] == 0) {
                    //clear out all nearby empty fields
                    int clearOutCheck[10000][2];
                    clearOutCheck[0][0] = scanCoorX;
                    clearOutCheck[0][1] = scanCoorY;
                    grid[scanCoorX][scanCoorY] += 10;
                    //first element manually added
                    int clearOutCheckLength = 1;
                    //boolean; when this value remains 0 exits loop
                    int atLeastOneNewCleared = 1;
                    while (atLeastOneNewCleared == 1) {
                        atLeastOneNewCleared = 0;
                        for (int i = 0; i < clearOutCheckLength; i++) {
                            
                            //right
                            if (grid[clearOutCheck[i][0] + 1][clearOutCheck[i][1]] < 9 && clearOutCheck[i][0] + 1 < fieldSizeX) {
                                //reveal grid
                                grid[clearOutCheck[i][0] + 1][clearOutCheck[i][1]] += 10;
                                if (grid[clearOutCheck[i][0] + 1][clearOutCheck[i][1]] - 10 == 0) {
                                    //push array
                                    clearOutCheck[clearOutCheckLength][0] = clearOutCheck[i][0] + 1;
                                    clearOutCheck[clearOutCheckLength][1] = clearOutCheck[i][1];
                                    //printf("[%i, %ir]", clearOutCheck[clearOutCheckLength][0], clearOutCheck[clearOutCheckLength][1]);
                                    clearOutCheckLength++;
                                    atLeastOneNewCleared = 1;
                                    
                                }
                            }
                            //left
                            if (grid[clearOutCheck[i][0] - 1][clearOutCheck[i][1]] < 9 && clearOutCheck[i][0] - 1 >= 0) {
                                //reveal grid
                                grid[clearOutCheck[i][0] - 1][clearOutCheck[i][1]] += 10;
                                if (grid[clearOutCheck[i][0] - 1][clearOutCheck[i][1]] - 10 == 0) {
                                    //push array
                                    clearOutCheck[clearOutCheckLength][0] = clearOutCheck[i][0] - 1;
                                    clearOutCheck[clearOutCheckLength][1] = clearOutCheck[i][1];
                                    //printf("[%i, %il]", clearOutCheck[clearOutCheckLength][0], clearOutCheck[clearOutCheckLength][1]);
                                    clearOutCheckLength++;
                                    atLeastOneNewCleared = 1;
                                }
                            }
                            //up
                            if (grid[clearOutCheck[i][0]][clearOutCheck[i][1] + 1] < 9 && clearOutCheck[i][1] + 1 < fieldSizeY) {
                                //reveal grid
                                grid[clearOutCheck[i][0]][clearOutCheck[i][1] + 1] += 10;
                                if (grid[clearOutCheck[i][0]][clearOutCheck[i][1] + 1] - 10 == 0) {
                                    //push array
                                    clearOutCheck[clearOutCheckLength][0] = clearOutCheck[i][0];
                                    clearOutCheck[clearOutCheckLength][1] = clearOutCheck[i][1] + 1;
                                    //printf("[%i, %iu]", clearOutCheck[clearOutCheckLength][0], clearOutCheck[clearOutCheckLength][1]);
                                    clearOutCheckLength++;
                                    atLeastOneNewCleared = 1;
                                }
                            }
                            //down
                            if (grid[clearOutCheck[i][0]][clearOutCheck[i][1] - 1] < 9 && clearOutCheck[i][1] - 1 >= 0) {
                                //reveal grid
                                grid[clearOutCheck[i][0]][clearOutCheck[i][1] - 1] += 10;
                                if (grid[clearOutCheck[i][0]][clearOutCheck[i][1] - 1] - 10 == 0) {
                                    //push array
                                    clearOutCheck[clearOutCheckLength][0] = clearOutCheck[i][0];
                                    clearOutCheck[clearOutCheckLength][1] = clearOutCheck[i][1] - 1;
                                    //printf("[%i, %id]", clearOutCheck[clearOutCheckLength][0], clearOutCheck[clearOutCheckLength][1]);
                                    clearOutCheckLength++;
                                    atLeastOneNewCleared = 1;
                                }
                            }
                        }
                    }
                    
                } else {
                    grid[scanCoorX][scanCoorY] += 10;
                }
            }
        }
        if (winGame == 1) {
            printf("\nYou Win!\n\n");
        } else {
            printf("\nYou lost by detonating the minefield...\n\n");
        }
        printf("Press 1 to quit and any number to play again\n");
        int num;
        scanf("%d", &num);
        printf("\n");
        if (num == 1) {
            break;
        }
    }
    return 0;
}
