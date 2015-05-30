
#define _CRT_SECURE_NO_WARNINGS
// プログラム
#include    <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAXN (100)
#define YES (1)
#define NO (0)

int n;            // 巡回すべき頂点数
int a[MAXN + 1];            // 巡回経路(お試し経路)
int used[MAXN + 1];            // 巡回済か否か
int dist[MAXN + 1][MAXN + 1];    // 隣接行列 dist[a][b] 頂点aから頂点bまでの距離(コスト)
int mina[MAXN + 1];         // 最小コストが得られる巡回経路
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
	//  最初の値はグラフの頂点数
	fscanf(fp, "%d", &n);
	//  範囲外の頂点数の場合は強制終了
	if ((n > MAXN) || (n <= 0)) {
		printf("Out of range: n.\n");
		exit(1);
	}
	//  隣接行列のデータの読みこみ
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp, "%d", &dist[i][j]);
		}
	}
	//  隣接行列のデータの出力
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
	//  始めはどの値も使っていない
	for (i = 0; i < n; i++) {
		used[i] = NO;
	}
	clock_t start, end;
	start = clock();
	perm(0);    //  探索

	end = clock();
	
	// 最短経路(距離合計)の表示
	printf("%d\n", min);
	// 最短経路(訪問順序)の表示
	for (i = 0; i < n; i++) {
		printf("%d", mina[i]);
	}	
	printf("\n");
	//合計経路
	printf("kilyori:%d\n",dist[mina[0]][mina[1]]+ min );
	
	printf("終了時間:%d\n", end);
	printf("処理時間:%d[ms]\n", end - start);
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

