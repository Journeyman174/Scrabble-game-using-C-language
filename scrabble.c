#include <stdio.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#include <stdlib.h>
#include <string.h>
#define N 15

//===============
//functia punctaj
int punctaj(char *yy1,char *xx1,int y1,int x1,int d1,int *scor1, char *cuvint1)
{
int bonus_x = 0, bonus_y = 0, bonus = 1, puncte = 0, s;
char YY1[2];

strncpy(YY1,cuvint1+(int)strlen(cuvint1)-2,2);

if (strcmp(yy1,YY1) == 0)
	bonus_y = 1;			
//===========================================================================================================				
if (strstr(cuvint1, xx1) != NULL) // bonus x
	bonus_x = 1;
		
if(d1== 0) // verific daca cuvintul are bonusuri in tabela bonus_board pe orizontala sau pe verticala
	for(int i = 0; i < (int)strlen(cuvint1); i++)
		{
			if ((bonus_board[y1][x1+i] == 1) && (bonus_x == 1))
				bonus=bonus*2;
			if ((bonus_board[y1][x1+i] == 2) && (bonus_y == 1))
				bonus=bonus*3;
		}
else
	if(d1 == 1)
		for(int i = 0; i < (int)strlen(cuvint1); i++)
			{
				if ((bonus_board[y1+i][x1] == 1) && (bonus_x == 1))
					bonus=bonus*2;
				if ((bonus_board[y1+i][x1] == 2) && (bonus_y == 1))
					bonus=bonus*3;
			}
//calculez scorul pt jucatori						
for(int i = 0; i < (int)strlen(cuvint1); i++)
	{
		s = (int)(*(cuvint1 + i))-65;
		puncte = puncte+scor1[s];
	}
 return puncte*bonus;
 }
//sfarsit functie punctaj


int  main ()
{
	
	int  i, j, n, k, s, x, y, d, q, r, nr_task, scor[26], Player1=0, Player2=0, jucator=1, bonus, bonus_x, bonus_y, puncte1=0, puncte2=0, puncte=0, len_2, este_loc, gasit=0, gata=0, optim[4], op=0, len_opt=0;
	char tabla_joc[N][N],linie[100],litera,xx[10], yy[10],YY[10], words_puse[100][100], word_2[100], word_opt[100];
	char *element, *cuvint;
//vectorul scor memoreaza punctajele pentru litere pt calcularea scorului	
	char unu[]="A, E, I, L, N, O, R, S, T, U" ;
	char doi[]= "D, G";
	char trei[]= "B, C, M, P";
	char patru[]= "F, H, V, W, Y";
	char cinci[]=" K ";
	char opt[]= "J, X";
	char zece[]= "Q, Z";

	for (i = 0; i < 26; i++)
		{
		litera = (char)(i+65);
		if (strchr(unu,litera) != NULL)
			scor[i] = 1;
		if (strchr(doi,litera) != NULL)
			scor[i] = 2;
		if (strchr(trei,litera) != NULL)
			scor[i] = 3;
		if (strchr(patru,litera) != NULL)
			scor[i] = 4;
		if (strchr(cinci,litera) != NULL)
			scor[i] = 5; 
		if (strchr(opt,litera) != NULL)
			scor[i] = 8;
		if (strchr(zece,litera) != NULL)
			scor[i] = 10;
		}
//
/*se initializeaza matricea tabla_joc cu puncte*/
	for(i = 0;  i < N; i++)
		for(j = 0; j < N; j++)
        		tabla_joc[i][j] = '.';

	fgets(linie, 100, stdin);
	nr_task = strtol(linie, NULL, 0);

	switch  (nr_task)
	{
		case 0:
			print_board(tabla_joc);
			break;
		case 1:
			fgets(linie, 100, stdin);
			n = strtol(linie, NULL, 0); //citesc numarul N de linii care urmeaza
			for (k = 0; k < n; k++)
			{
				fgets(linie,100,stdin); //citesc liniile  ce contin coordonatele,directia si cuvintul
				element = strtok(linie, " ");
				y = strtol(element, NULL, 0);
		
				element = strtok(NULL," ");
				x = strtol(element, NULL, 0);

				element = strtok(NULL," ");
				d = strtol(element, NULL, 0);
		
				element = strtok(NULL," ");
				cuvint = element;
		
				if(d == 0)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						tabla_joc[y][x+i] = *(cuvint + i);
				else
					if(d == 1)
						for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
							tabla_joc[y+i][x] = *(cuvint + i);
			}
			print_board(tabla_joc);
			break;
//*****************************************************************************************************
		case 2:
			{
			fgets(linie, 100, stdin);
			n = strtol(linie, NULL, 0);
			for (k = 0; k < n; k++)
				{
				fgets(linie, 100, stdin);

				element = strtok(linie, " ");
				y = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				x = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				d = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				cuvint = element;

				if(jucator % 2 == 1)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s = (int)(*(cuvint + i)) - 65;
						Player1 = Player1 + scor[s];
					}

				else 
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s = (int)(*(cuvint + i)) - 65;
						Player2 = Player2 + scor[s];
					}

				jucator++;
				}
			printf("Player 1: %d Points\n", Player1);
			printf("Player 2: %d Points\n", Player2);
			break;
			}
//*********************************************************************************************************************
		case 3:
		{
			fgets(xx, 100, stdin); // citesc literele pentru bonus *2
			if (xx[strlen(xx) - 1] == '\n')
				xx[strlen(xx) - 1] = '\0';
			fgets(yy, 100, stdin); //citesc literele pt bonus *3
			if (yy[strlen(yy) - 1] == '\n')
				yy[strlen(yy) - 1] = '\0';
			fgets(linie, 100, stdin); //nr de linii
			n = strtol(linie, NULL, 0);
			
			for (k = 0; k < n; k ++) //citesc liniile
			{
				bonus_x = 0;
				bonus_y = 0;
				bonus = 1;
				puncte1 = 0;
				puncte2 = 0;
				fgets(linie, 100, stdin); // linia

				element = strtok(linie, " ");
				y = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				x = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				d = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				cuvint = element;
//=============================================================================================================				
//verific daca in cuvint sunt yy bonus y

				strncpy(YY, cuvint+(int)strlen(cuvint) - 3, 2);
				if (strcmp(yy, YY) == 0)
						bonus_y = 1;			
//===========================================================================================================				
				if (strstr(cuvint,xx) != NULL) // bonus x
					bonus_x = 1;
		
				if(d == 0) // verific daca cuvintul are bonusuri in tabela bonus_board pe orizontala sau pe verticala
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						{
							if ((bonus_board[y][x+i] == 1) && (bonus_x == 1))
								bonus=bonus*2;
							if ((bonus_board[y][x+i] == 2) && (bonus_y == 1))
								bonus=bonus*3;
						}
				else
					if(d == 1)
						for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						{
							if ((bonus_board[y+i][x] == 1) && (bonus_x == 1))
								bonus = bonus*2;
							if ((bonus_board[y+i][x] == 2) && (bonus_y == 1))
								bonus = bonus*3;
						}
//calculez scorul pt jucatori						
				if(jucator % 2 == 1)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s=(int)(*(cuvint + i))-65;
						puncte1 = puncte1+scor[s];
//						Player1 = Player1 + scor[s];
					}

				else 
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s = (int)(*(cuvint + i)) - 65;
						puncte2 = puncte2+scor[s];
//						Player2 = Player2 + scor[s];
					}
				Player1 = Player1 + puncte1*bonus;
				Player2 = Player2 + puncte2*bonus;
				jucator++;
			}
			printf("Player 1: %d Points\n", Player1);
			printf("Player 2: %d Points\n", Player2);
			break;
		}		
//=====================================================================================================================
//task 4
//=====================================================================================================================
		case 4:
		{
		//5
			fgets(xx, 100, stdin); // citesc literele pentru bonus *2
			if (xx[strlen(xx) - 1] =='\n')
				xx[strlen(xx) - 1]= '\0';
			fgets(yy, 100, stdin); //citesc literele pt bonus *3
			if (yy[strlen(yy) - 1] =='\n')
				yy[strlen(yy) - 1] = '\0';
			fgets(linie, 100, stdin); //nr de linii
			n = strtol(linie, NULL, 0);
			
			for (k=0; k<n; k++) //citesc liniile si le memorez in tabela_joc
				{
				fgets(linie, 100, stdin); // linia

				element = strtok(linie, " ");
				y = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				x = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				d = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				cuvint = element;
//scriu pe tabla de joc cuvintele celor 2 jucatori
				if(d == 0)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						tabla_joc[y][x+i] = *(cuvint + i);
				else
					if(d == 1)
						for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
							tabla_joc[y+i][x] = *(cuvint + i);
//memorez cuvintul in tabla words_puse
				strcpy(words_puse[k], cuvint);
				}
//am terminat de citit si memorat input-ul si incep sa caut cuvintul pentru Player 2
//caut in vectorul words primul cuvint care nu e in tabla words_puse
//BUCLA 0
			for(k = 0; k < NUM_WORDS; k++)	
				{
				//4
				gasit=0;
				gata=0;
				for ( r = 0; r < n; r++) //caut in words_puse
					{
					if (strstr(words_puse[r],words[k]) == NULL)
						gasit = 1;
					else
						{
						gasit = 0;
						break;
						}
					}
				if (gasit == 1)
					{		//40	corp 1 gasit cuvintul
//					break;
//am gasit in words cuvintul
					strcpy(word_2, words[k]);	//word_2 este cuv din words
					len_2 = strlen(word_2);	//lungimea lui word_2
					este_loc = 0;
					gata = 0;
					for(i = 0;  i < N; i++) //verific daca prima litera este in tabla_joc
						{	//40000		bucla 2
							for(j = 0; j < N; j++)
//incep cautarea
				        			if (words[k][0]==tabla_joc[i][j]) // am gasit prima litera pe tabla
									{
									//44000  corp 3
							        		q = 1;
	      									if (j+len_2 <= 15) //mai e loc ca lungime pe orizontala
	        									{
	        									//400 corp4
	        										este_loc = 0;
	      											for (int l = j+1; l < j+len_2; l++)	//verific daca am loc liber pe orizontala
		        									{
		        										if (tabla_joc[i][l] == '.')
		        											este_loc = 1;
													else
														{
															este_loc = 0;
															break;
														}
												}
												if (este_loc == 1)
												{
													for (int m = j+1; m < j+len_2; m++)
														{
															tabla_joc[i][m] = *(word_2+q);
															q++;
														}
													gata = 1;
												}
								        			else
													gata = 0;
											}
											//400 corp 4
									
//										else
										if(gata==0)
//nu este loc pe orizontala verific pe verticala este_loc=0
											{
						        				if (i+len_2 <= 15) //mai e loc pe verticala
						        					{//4000 corp 5
							        					este_loc = 0;
							        					for (int l=i+1; l < i+len_2; l++)	//verific daca am loc pe verticala
						        						{
						        							if (tabla_joc[l][j] == '.')
															este_loc = 1;
														else
															{
															este_loc = 0;
															break;
															}
													}
													if (este_loc == 1)
														{
														for (int m = i+1; m < i+len_2; m++)
															{
																tabla_joc[m][j] = *(word_2+q);
																q++;
															}
														gata = 1;
														}
									        			else
														gata = 0;
												}//4000 corp 5
											}
									}//44000 corp 3
								if (gata == 1)
									break;
						}//40000 bucla 2
						if (gata == 1)
							break;
					}//40 corp 1

				if(gata == 1)
					break;
				}//4 bucla 0
			print_board(tabla_joc);
			break;
		}//5
//=====================================================================================================================
//task 5
//=====================================================================================================================
		case 5:
		{
//*****************************************************************************************************
			fgets(xx, 100, stdin); // citesc literele pentru bonus *2
			if (xx[strlen(xx) - 1] =='\n')
				xx[strlen(xx) - 1] = '\0';
			fgets(yy, 100, stdin); //citesc literele pt bonus *3
			if (yy[strlen(yy) - 1] =='\n')
				yy[strlen(yy) - 1] = '\0';
			fgets(linie, 100, stdin); //nr de linii
			n = strtol(linie, NULL, 0);
			
			for (k = 0; k < n; k++) //citesc liniile
			{
				bonus_x = 0;
				bonus_y = 0;
				bonus = 1;
				puncte1 = 0;
				puncte2 = 0;
				fgets(linie, 100, stdin); // linia

				element = strtok(linie, " ");
				y = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				x = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				d = strtol(element, NULL, 0);

				element = strtok(NULL, " ");
				cuvint = element;


//scriu pe tabla de joc cuvintele celor 2 jucatori
				if(d == 0)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						tabla_joc[y][x+i] = *(cuvint + i);
				else
					if(d == 1)
						for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
							tabla_joc[y+i][x] = *(cuvint + i);
//memorez cuvintul in tabla words_puse
				strcpy(words_puse[k], cuvint);
//=============================================================================================================				
//verific daca in cuvint sunt yy bonus y

				strncpy(YY, cuvint + (int)strlen(cuvint)-3, 2);
				if (strcmp(yy, YY) == 0)
						bonus_y = 1;			
//===========================================================================================================				
				if (strstr(cuvint, xx) != NULL) // bonus x
					bonus_x = 1;
		
				if(d == 0) // verific daca cuvintul are bonusuri in tabela bonus_board pe orizontala sau pe verticala
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						{
							if ((bonus_board[y][x+i] == 1) && (bonus_x == 1))
								bonus = bonus*2;
							if ((bonus_board[y][x+i] == 2) && (bonus_y == 1))
								bonus = bonus*3;
						}
				else
					if(d == 1)
						for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
						{
							if ((bonus_board[y+i][x] == 1) && (bonus_x == 1))
								bonus = bonus*2;
							if ((bonus_board[y+i][x] == 2) && (bonus_y == 1))
								bonus = bonus*3;
						}
//calculez scorul pt jucatori						
				if(jucator % 2 == 1)
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s = (int)(*(cuvint + i)) - 65;
						puncte1 = puncte1 + scor[s];

					}

				else 
					for(int i = 0; i < (int)strlen(cuvint) - 1; i++)
					{
						s = (int)(*(cuvint + i)) - 65;
						puncte2 = puncte2 + scor[s];

					}
				Player1 = Player1 + puncte1*bonus;
				Player2 = Player2 + puncte2*bonus;
				jucator++;
			}

			
//am calculat punctajele pentru cei 2 jucatori	
//caut in vectorul words primul cuvint care nu e in tabla words_puse
//BUCLA 0
	for(k = 0;k < NUM_WORDS; k++)	
		{
		//4
			gasit = 0;
			gata = 0;
			for ( r = 0; r < n; r++) //caut in words_puse
				{
					if (strstr(words_puse[r],words[k]) == NULL)
						gasit = 1;
					else
						{
						gasit = 0;
						break;
						}
					}
				if (gasit == 1)
					{		//40	corp 1 gasit cuvintul

//am gasit in words cuvintul
					strcpy(word_2, words[k]);	//word_2 este cuv din words
					len_2 = strlen(word_2);	//lungimea lui word_2
					este_loc = 0;
					gata = 0;
					for(i = 0;  i < N; i++) //verific daca prima litera este in tabla_joc
						{	//40000		bucla 2
							for(j = 0; j < N; j++)
//incep cautarea
								{
				        			if (words[k][0] == tabla_joc[i][j]) // am gasit prima litera pe tabla
									{
									//44000  corp 3
							        		q = 1;
	      									if (j + len_2 <= 15) //mai e loc ca lungime pe orizontala
	        									{
	        									//400 corp4
	        										este_loc = 0;
	      											for (int l = j+1; l < j+len_2; l++)	//verific daca am loc liber pe orizontala
		        									{
		        										if (tabla_joc[i][l]=='.')
		        											este_loc = 1;
													else
														{
															este_loc = 0;
															break;
														}
												}
												if (este_loc == 1)
												{
													d = 0;
													puncte = punctaj(yy, xx, i, j, d, scor, word_2);
													if (Player2+puncte >= Player1)
														{
														if (Player2+puncte >= optim[3])
															{
											
															if (strcmp(word_2, word_opt) != 0)
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
															else
																{
																if ( (optim[2] == 1) && (i < optim[0]) )
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
																
																else
																	if (Player2 + puncte > optim[3])
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
																}	
															}
														gata = 1;

														}
													else
														{
														gata = 0;
														}
												}
								        			else
													gata = 0;
											}
											//400 corp 4
									
//										else
										if(gata == 0)
//nu este loc pe orizontala verific pe verticala este_loc=0
											{
						        				if (i+len_2 <= 15) //mai e loc pe verticala
						        					{//4000 corp 5
							        					este_loc = 0;
							        					for (int l = i+1; l < i+len_2; l++)	//verific daca am loc pe verticala
						        						{
						        							if (tabla_joc[l][j] == '.')
															este_loc = 1;
														else
															{
															este_loc = 0;
															break;
															}
													}
													if (este_loc == 1)
														{
															d = 1;
															puncte = punctaj(yy, xx, i, j, d, scor, word_2);
															if (Player2 + puncte >= Player1)
																{
																	if (Player2 + puncte >= optim[3])
																		{
																			
															if (strcmp(word_2, word_opt) != 0)
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
															else
																{
																if ((optim[2] == 1) && (i < optim[0]))
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
																
																else
																	if (Player2 + puncte > optim[3])
																{
																	optim[0] = i;
																	optim[1] = j;
																	optim[2] = d;
																	optim[3] = Player2 + puncte;
																	strcpy(word_opt, word_2);	//word_optim
																	op = 1;
																}
																}	
																		}
																	gata = 1;

																}
															else
																{
																	gata = 0;

																}
														}
									        			else
														gata = 0;
												}//4000 corp 5
											}
									}//44000 corp 3
								}
						}//40000 bucla 2
					}//40 corp 1
				}//4 bucla 0
		
//********************************************************************************************************************		

			if (op == 1)
				{
					q = 1;
					len_opt = strlen(word_opt);

					if (optim[2] == 0)
						{
							for (int m = optim[1] + 1; m < optim[1] + len_opt; m++)
								{
									tabla_joc[optim[0]][m] = *(word_opt+q);
									q++;
								}
						}
					else
						{
							for (int m = optim[0] + 1; m < optim[0] + len_opt; m++)
								{
									tabla_joc[m][optim[1]] = *(word_opt+q);
									q++;
								}
						}
				
					print_board(tabla_joc);
				}
			else
				printf("Fail!\n");
			break;
		}// sfarsit case 5

			
//*********************************************************************************************************************
//end switch
	}
	return 0;
}

