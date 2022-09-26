#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

// Проверка корректности файла
int check (FILE *fp){
	int flag = 0, i = 0, j = 0;
	char cm;
	if(fp==NULL){
        printf("Ошибка открытия файла!");
		return(0);
    }
    while ((cm = fgetc(fp)) != EOF){
		if (cm == ' ' || cm == '\n' || cm == '-' || (cm == '0' || cm == '1')){
			if (cm == ' ') j++;
			if (cm == '\n'){
				i++;
				if (i == 1) flag = j;
				if (flag != j){
					printf("Некорректное количество пробелов в файле!");
					return(0);
				}				
				j = 0;
			}
		}
		else{
			printf("Некорректные значения в файле!");
			return(0);
		}
	}
	if (i != j){
		printf("Матрица не квадратная!");
		return(0);
	}
	i++;
    j++;
	printf("Количество строк - %d\nКоличество столбцов - %d\n", i, j);
    fclose(fp);
    return(i);
}

// Проверка рефлексивности
int reflex (bool **m, int b){
	int check = 1, i = 0, j = 0;
	if (m[0][0] == 0) check = 2;
	for (i = 1; i < b; i++)	if (m[i][i] != m[i-1][i-1])	return (3);
	return (check);
}

// Проверка симметричности
int symmetry (bool **m, int b, int reflex){
	int check = 0, flag = 0, a = 0, i, j;
	for (i = 0; i < b; i++){
    	for (j = i+1; j < b; j++){
    		a++;
    		if (m[i][j] == m[j][i]){
    			check++;
    			if (m[i][j] == 1) flag = 1;
    		} 
		} 
	}
	if ((a == check) && (flag == 0) && (reflex != 2)) return (6);
	if ((a == check) && (flag == 0) && (reflex == 2)) return (7);
	if ((a == check) && (flag == 1)) return (2);
	if ((a!=check) && (flag == 0) && (reflex != 2)) return (3);
	if ((a!=check) && (flag == 0) && (reflex == 2)) return (4);
	return (5);
}

// Проверка транзитивности
int transitivy (bool **m, int b){
	int i, j, k;
	for (i = 0; i < b; i++){
		for (j = 0; j < b; j++){
			if (m[i][j] == 1){
				for (k = 0; k < b; k++){
					if ((m[i][k] == 0) && (m[j][k] == 1))	return (0);	
				}
			}
		}	
	}
	return (1);
}

// Проверка порядка
int order (bool **m, int a, int i, int j){
	if (!(((a == 1) || (a == 2)) && ((i == 3) || (i == 6)) && (j != 0))) return (0);
	if (a == 1) return (1);
	return (2);
}

// Проверка линейности
int linear (bool **m, int b){
	int i, j;
	for (i = 0; i < b; i++){
		for (j = 0; j < b; j++){
			if (i!=j){
				if (!(m[i][j]==1 || m[j][i] == 1))	return (0);
			}
		}
	}
	return (1);
}

// Является ли отношение R отношением линейного порядка
int main(){	
	system ("color F0");
	setlocale(LC_ALL,"RUS");
	int  j, i, l, b, flag, a;
	char *fname=(char *)malloc(256); 
do{
	strcpy(fname,"default.txt");
// Стартуем
	printf("Вводить из файла или из клавиатуры? 1/2 - ");
    scanf("%d", &a);
	if (a == 1){
		printf("Ввести имя файла или использовать файл по умолчанию? 1/2 - ");
		scanf("%d", &b);
		if (b == 1){
			printf("Введите имя файла: \n");
    		scanf("%s", fname);
			printf("Содержимое файла %s:\n", fname);
    	}
    	else printf("Содержимое файла default.txt:\n");
		FILE *fp=fopen(fname,"r");
		b = check(fp);
    	if (b == 0) {
			printf("Ошибка проверки файла");
			goto aa;
		}
	}
    else{
		nn:
    	printf("Введите размерность матрицы (матрица должна быть квадратной, не менее 2*2 и не более 20*20!): ");
    	scanf("%d", &b); 
    	if (!(b>=2)){
       		printf("Недопустимый размер!\n");
       		goto nn;
    	}
	}	
// Выдеделение памяти
    bool **m;
	m = malloc (b*sizeof(bool*));
	if (m==NULL) 
	{
		printf("Память не выделена");
		goto aa;
	}
	for (i=0; i<b; i++)
	{
		m[i] = malloc (b*sizeof(bool));
		if (m[i]==NULL) 
		{
			printf("Память не выделена");
			goto aa;
		}
	} 
// Ввод массива с клавиатуры
	if (a == 2){
		printf("Введите элементы массива, только 1 и/или 0:\n");
    	for (i = 0; i<b; i++){
    		for (j = 0; j<b; j++){
        		printf("a[%d][%d] = ", i, j);
        		flag = scanf("%d", &m[i][j]);
        		if ((m[i][j] == 1) && (m[i][j] == 0)){
					printf("Неверные значения ввода!");
					goto aa;
				}
    		}
    	}	
	}
	else{
// Считывание массива с файла	
		FILE *fp=fopen(fname,"r");
		for(i=0;i<b;i++)
        for(j=0;j<b;j++)     
            fscanf(fp,"%d",&m[i][j]);
        fclose(fp);
    }	
// Вывод матрицы	
    printf ("Матрица:\n");
    for (i = 0; i < b; i++){
    	for (j = 0; j < b; j++){
    		printf("%d ", m[i][j]); 
    	}
    	printf("\n");
    } 
// Проверка рефлексивности
	a = reflex (m, b);
	if (a == 1) printf ("Отношение рефлексивно\n");
	else if (a == 2) printf ("Отношение антирефлексивно\n");
	else printf ("Отношение ни рефлексивно, ни антирефлексивно\n");	
// Проверка антисимметричности
	i = symmetry (m, b, a);
	if (i == 2) printf ("Отношение симметрично\n");
	else if (i == 3) printf ("Отношение антисимметрично\n");
	else if (i == 4) printf ("Отношение асимметрично\n");
	else if (i == 6) printf ("Отношение и симметрично, и антисимметрично\n");
	else if (i == 7) printf ("Отношение и симметрично, и асимметрично\n");
	else printf ("Отношение ни симметрично, ни антисимметрично, ни ассиметрично\n");
// Проверка транзитивности
	j = transitivy (m, b);
	if (j == 0) printf ("Отношение не транзитивно\n");
	else printf ("Отношение транзитивно\n");
// Проверка порядка
	flag = order (m, a, i, j);
	if (flag == 0){
		printf ("Отношение не является отношением порядка!\n");
		goto aa;
	}
	if (flag == 1) printf ("Отношение является отношением нестрого порядка\n");
	else printf ("Отношение является отношением строго порядка\n");
// Проверка линейности
	l = linear (m, b);
	if (l == 0){
		printf ("Отношение не является отношением линейного порядка!\n");
		goto aa;
	}
	else printf ("Отношение является отношением линейного порядка\n");
	aa:
	for (i=0; i<b; i++) free(m[i]);
	free(m);
	printf("Закончить программу? 1 - нет / 2 - да : ");
	scanf("%d",&flag);
}while (flag == 1); 
	system("PAUSE");
	getchar(); 
	return 0;
}
	
	
		
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	

