
#define _CRT_SECURE_NO_WARNINGS
// �v���O����
#include    <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAXN (100)
#define YES (1)
#define NO (0)

int n;            // ���񂷂ׂ����_��
int a[MAXN + 1];            // ����o�H(�������o�H)
int used[MAXN + 1];            // ����ς��ۂ�
int dist[MAXN + 1][MAXN + 1];    // �אڍs�� dist[a][b] ���_a���璸�_b�܂ł̋���(�R�X�g)
int mina[MAXN + 1];         // �ŏ��R�X�g�������鏄��o�H
int min = 10000;

void perm(int d);

int main(int argc, char **argv)
{
	int  i, j;
	FILE*   fp;
	fp = fopen("C:\\Users\\take\\Documents\\Visual Studio 2013\\Projects\\Project2\\Debug\\io.txt", "r");
	if (fp == NULL) {
		printf("File not found.\n");
		exit(1);
	}
	//  �ŏ��̒l�̓O���t�̒��_��
	fscanf(fp, "%d", &n);
	//  �͈͊O�̒��_���̏ꍇ�͋����I��
	if ((n > MAXN) || (n <= 0)) {
		printf("Out of range: n.\n");
		exit(1);
	}
	//  �אڍs��̃f�[�^�̓ǂ݂���
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp, "%d", &dist[i][j]);
		}
	}
	//  �אڍs��̃f�[�^�̏o��
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
	//  �n�߂͂ǂ̒l���g���Ă��Ȃ�
	for (i = 0; i < n; i++) {
		used[i] = NO;
	}
	clock_t start, end;
	start = clock();
	perm(0);    //  �T��

	end = clock();
	
	// �ŒZ�o�H(�������v)�̕\��
	printf("%d\n", min);
	// �ŒZ�o�H(�K�⏇��)�̕\��
	for (i = 0; i < n; i++) {
		printf("%d", mina[i]);
	}	
	printf("\n");
	//���v�o�H
	printf("kilyori:%d\n",dist[mina[0]][mina[1]]+ min );
	
	printf("�I������:%d\n", end);
	printf("��������:%d[ms]\n", end - start);
}

void perm(int d)
{
	int i;
	int length = 0;
	if (d == n) {
		for (i = 0; i < n - 1; i++) {
			length += dist[a[i]][a[i + 1]];
		}
		if (length < min) {
			min = length;
			for (i = 0; i < n; i++) {
				mina[i] = a[i];
			}
		}
	}
	else {
		for (i = 0; i < n; i++) {
			if (used[i] == NO) {
				a[d] = i;
				used[i] = YES;
				perm(d + 1);
				used[i] = NO;
			}
		}
	}
}

