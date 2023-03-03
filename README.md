# Scrabble-game-using-C-language

Pas 0 :
	Am declarat tabela de joc tabla_joc ca o matrice de tip caracter
cu dimensiunea 15 x 15 si am populat-o cu caracterul '.' . 
	Am definit un vector, scor[26], care memoreaza punctajele 
pentru litere pentru calcularea scorului jucatorilor.
	Pentru dialogul cu utilizatorul, citirea numarului task-ului 
am facut-o cu functiile fgtes si strtol. 
	Executia optiunii utilizatorului am facut-o utlizand comanda switch case.
	
	
Pas 1 :
	Citirea inputului, numarul de linii N s-a facut in variabila n.
	Coordonatele liniilor Y, X si directia D precum si cuvantul primit s-au memorat in variabilele y, x, d si
cuvant, intr-o bucla for.
	La sfarsit utilizand functia printboard s-a afisat tabla de joc.
	
 Pas 2 :
	Pentru pasul 2 s-au calculat punctajele celor 2 jucatori,
utilizandu-se pentru fiecare litera punctajele din vectorul scor[].
	Utilizand conventia, liniile cu numarul de ordine impar apartin jucatorului 1 
si par jucatorului 2.

Pas 3 :
	S-a utilizat algoritmul de la pasul 2.
	In plus, s-au citit substringurile XX si YY in variabilele xx si yy
pentru casutele marcate cu 1 si respectiv 2 din tabela de bonusuri data.
	Cele n linii s-au citit printr-o bucla for, in cadrul buclei pentru fiecare cuvant utilizand
functia strncpy() si strcmp() s-a memorat in variabila bonus_y = 1, daca cuvantul se termina cu
substringul yy si respectiv prin fuctia strstr() s-a memorat in variabila bonus_x = 1,
daca substringul xx se gaseste in interiorul cuvantului.
	In functie de valoarea directiei d ( 0 sau 1 ) s-au calculat in variabila bonus, 
bonusul acordat - bonus_x = 1, se dubleaza valoarea cuvantului si 
bonus_y = 1, se tripleaza valoarea cuvantului.
	S-a calculat scorul pentru jucatori dupa regula linie impara jucator 1,
linie para jucator 2.
	La sfarsit, punctajul final s-a multiplicat cu bonusul.
	
Pas 4 :
	S-a utilizat algoritmul de la pas 3, pentru citirea substringurilor de 
bonus si a liniilor primite. 
	Cuvintele primite (existente pe tabla) s-au memorat utilizand functia strcpy()
in matricea de tip char words_puse de dimensiunea 100 x 100. 
	Prin intermediul unei bucle for cu index k < NUM_WORDS am parcurs vectorul words[]
(din fisierul header scrabble.h ) si m-am oprit la prima nepotrivire a cuvantului
cu cel din matricea words_puse.
	Cuvantul selectat din words l-am memorat intr-o copie cu numele word_2 cu lungimea len_2.
	Apoi, am parcurs tabla de joc incepand cu linia 0 si coloana 0 
si am cautat litera egala cu prima litera a cuvantului gasit si am verificat daca cuvantul se poate scrie
(are loc) pe orizontala, apoi pe verticala si in caz afirmativ,
l-am scris in tabla de joc.

Pas 5 :
	S-a utilizat acelasi algoritm de la pas 4, in plus am definit o functie punctaj() care primind 
pointerii catre substringurile de bonus YY1, XX1, coordonatale y, x, directia d, vectorul de scor 
si cuvantul intoarce punctajul cuvantului.
	Dupa citirea elementelor de joc, am scris in tabela de joc cuvintele primite si 
le-am calculat punctajele celor 2 jucatori. 
	Dupa care, printr-o bucla for de index k < NUM_WORDS, am cautat primul cuvant din vectorul words[] care
nu se gaseste pe tabla.
	In cazul in care am gasit cuvantul potrivit si are loc pe tabla, am memorat
coordonatele y, x, d, punctaj, intr-un vector optim[4] si cuvantul in vectorul word_opt, daca punctajul total al jucatorul 2 
(variabila Player2) e mai mare ca valoare punctajului jucatorului 1 (variabila Player 1).
	Cautare cuvintelor din vectorul words[] nu se opreste la fel ca la pasul 4, la prima potrivire,
ci continua pana la parcurgerea celor 100 de cuvinte, la sfarsit.
	De fiecare data, la identificarea unui cuvant potrivit s-au memorat coordonatele, directia si punctajul precum si cuvantul 
vectorii optim[4] si word_opt, marcandu-se cu flag-ul op = 1.
	Cuvantul optim este memorat daca indeplineste cerintele date.
        La sfarsit in fuctie de valoare flag-ului op, se scrie in tabela de joc, cuvantul din word_opt, daca op = 1 si
se afiseaza mesajul Fail, daca op = 0.
