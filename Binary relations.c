#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

// �������� ������������ �����
int check (FILE *fp){
	int flag = 0, i = 0, j = 0;
	char cm;
	if(fp==NULL){
        printf("������ �������� �����!");
		return(0);
    }
    while ((cm = fgetc(fp)) != EOF){
		if (cm == ' ' || cm == '\n' || cm == '-' || (cm == '0' || cm == '1')){
			if (cm == ' ') j++;
			if (cm == '\n'){
				i++;
				if (i == 1) flag = j;
				if (flag != j){
					printf("������������ ���������� �������� � �����!");
					return(0);
				}				
				j = 0;
			}
		}
		else{
			printf("������������ �������� � �����!");
			return(0);
		}
	}
	if (i != j){
		printf("������� �� ����������!");
		return(0);
	}
	i++;
    j++;
	printf("���������� ����� - %d\n���������� �������� - %d\n", i, j);
    fclose(fp);
    return(i);
}

// �������� ��������������
int reflex (bool **m, int b){
	int check = 1, i = 0, j = 0;
	if (m[0][0] == 0) check = 2;
	for (i = 1; i < b; i++)	if (m[i][i] != m[i-1][i-1])	return (3);
	return (check);
}

// �������� ��������������
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

// �������� ��������������
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

// �������� �������
int order (bool **m, int a, int i, int j){
	if (!(((a == 1) || (a == 2)) && ((i == 3) || (i == 6)) && (j != 0))) return (0);
	if (a == 1) return (1);
	return (2);
}

// �������� ����������
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

// �������� �� ��������� R ���������� ��������� �������
int main(){	
	system ("color F0");
	setlocale(LC_ALL,"RUS");
	int  j, i, l, b, flag, a;
	char *fname=(char *)malloc(256); 
do{
	strcpy(fname,"default.txt");
// ��������
	printf("������� �� ����� ��� �� ����������? 1/2 - ");
    scanf("%d", &a);
	if (a == 1){
		printf("������ ��� ����� ��� ������������ ���� �� ���������? 1/2 - ");
		scanf("%d", &b);
		if (b == 1){
			printf("������� ��� �����: \n");
    		scanf("%s", fname);
			printf("���������� ����� %s:\n", fname);
    	}
    	else printf("���������� ����� default.txt:\n");
		FILE *fp=fopen(fname,"r");
		b = check(fp);
    	if (b == 0) {
			printf("������ �������� �����");
			goto aa;
		}
	}
    else{
		nn:
    	printf("������� ����������� ������� (������� ������ ���� ����������, �� ����� 2*2 � �� ����� 20*20!): ");
    	scanf("%d", &b); 
    	if (!(b>=2)){
       		printf("������������ ������!\n");
       		goto nn;
    	}
	}	
// ����������� ������
    bool **m;
	m = malloc (b*sizeof(bool*));
	if (m==NULL) 
	{
		printf("������ �� ��������");
		goto aa;
	}
	for (i=0; i<b; i++)
	{
		m[i] = malloc (b*sizeof(bool));
		if (m[i]==NULL) 
		{
			printf("������ �� ��������");
			goto aa;
		}
	} 
// ���� ������� � ����������
	if (a == 2){
		printf("������� �������� �������, ������ 1 �/��� 0:\n");
    	for (i = 0; i<b; i++){
    		for (j = 0; j<b; j++){
        		printf("a[%d][%d] = ", i, j);
        		flag = scanf("%d", &m[i][j]);
        		if ((m[i][j] == 1) && (m[i][j] == 0)){
					printf("�������� �������� �����!");
					goto aa;
				}
    		}
    	}	
	}
	else{
// ���������� ������� � �����	
		FILE *fp=fopen(fname,"r");
		for(i=0;i<b;i++)
        for(j=0;j<b;j++)     
            fscanf(fp,"%d",&m[i][j]);
        fclose(fp);
    }	
// ����� �������	
    printf ("�������:\n");
    for (i = 0; i < b; i++){
    	for (j = 0; j < b; j++){
    		printf("%d ", m[i][j]); 
    	}
    	printf("\n");
    } 
// �������� ��������������
	a = reflex (m, b);
	if (a == 1) printf ("��������� �����������\n");
	else if (a == 2) printf ("��������� ���������������\n");
	else printf ("��������� �� �����������, �� ���������������\n");	
// �������� ������������������
	i = symmetry (m, b, a);
	if (i == 2) printf ("��������� �����������\n");
	else if (i == 3) printf ("��������� ���������������\n");
	else if (i == 4) printf ("��������� ������������\n");
	else if (i == 6) printf ("��������� � �����������, � ���������������\n");
	else if (i == 7) printf ("��������� � �����������, � ������������\n");
	else printf ("��������� �� �����������, �� ���������������, �� ������������\n");
// �������� ��������������
	j = transitivy (m, b);
	if (j == 0) printf ("��������� �� �����������\n");
	else printf ("��������� �����������\n");
// �������� �������
	flag = order (m, a, i, j);
	if (flag == 0){
		printf ("��������� �� �������� ���������� �������!\n");
		goto aa;
	}
	if (flag == 1) printf ("��������� �������� ���������� �������� �������\n");
	else printf ("��������� �������� ���������� ������ �������\n");
// �������� ����������
	l = linear (m, b);
	if (l == 0){
		printf ("��������� �� �������� ���������� ��������� �������!\n");
		goto aa;
	}
	else printf ("��������� �������� ���������� ��������� �������\n");
	aa:
	for (i=0; i<b; i++) free(m[i]);
	free(m);
	printf("��������� ���������? 1 - ��� / 2 - �� : ");
	scanf("%d",&flag);
}while (flag == 1); 
	system("PAUSE");
	getchar(); 
	return 0;
}
	
	
		
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	

