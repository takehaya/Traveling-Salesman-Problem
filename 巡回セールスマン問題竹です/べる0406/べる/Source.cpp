#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<vector>
#include<stack>
#include<queue>
#include<sstream>
#include<string>
#include<deque>
#include<list>
#include<set>
#include<iostream>
#include<winsock2.h>
#include<algorithm>
#include<utility>


using namespace std;

////////////////定義index///////////////////////////////////
#define Empty	0//土地
#define Target	1//取ると１００点まぁitemの進化版
#define block	2//ブロックぶつかるというか刺さると-200点
#define item	3//おなじみのあいつ；10点
#define out_get -1//場外
#define	warpR	20//→右ワープ取ると右へ１０マスぶっとぶ
#define warpL	21//←左ワープ取ると左へ１０マスぶっとぶ
#define warpU	22//↑上ワープ取ると上に１０マスぶっとぶ
#define warpD	23//↓下ワープ取ると右へ１０マスぶっとぶ
typedef pair<int, int> P;//構造体の代わり
typedef vector<int> p;
vector<p> costmap;//costmap[][]と同じ
const int getlook = 10;//いくつとるかのインデックス
const int INF = 100;//初期

/////////////////////グローバル変数///////////////////////////////////////////
//map基本(今回の場合書き換えてもＯＫなmapがほしいのでこれを使う)
int map[20][20];
	//数値書き込むmap
	int target_map[20][20];
	//道かきこむ
	int tac_map[20][20];
	//複数のまっぷ
int mmap[20][20];
//スタート位置
int y = 10, x = 10;
//8方向を表すために用いる配列(x用)
int cx[12] = { 1, 1, -1, -1 ,- 1, 1, 0, 0, -1, -1, 1, 1 };
//8方向を表すために用いる配列(y用)
int cy[12] = { 2, -2, 2, -2,0, 0, -1, 1, -1, 1, -1, 1 };
int k_x = 0, k_y = 0;

int target_va=0;//いくつアイテム見たか

int start_costs[getlook];
int loadcost[getlook][getlook];
///******************入力データ******************//
int at = 0;
 const int	mapdata[20][20] = {					//マップ
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//1
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//2
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//3
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//4
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//5
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//6
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//7
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, -1, -1,//8
	-1, -1, -1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//9
	-1, -1, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//10
	-1, -1, -1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//11
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//12
	-1, -1, -1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//13
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, -1, -1, -1,//14
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, -1, -1,//15
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,//16
	-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, -1, -1,//17
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//18
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//19
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//20
};

/////////////////////////////////////////////////////////////////////////////


//////////////////////プロトタイプ宣言//////////////////////////////////////

void que();
void cnt_target_io();
void que_io();
void view();
////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	bool gameflag = true;
	costmap.resize(20);
	for (int i = 0; i<20; i++){
		costmap[i].resize(20);
	}
	//初期化したいときのやつ
	for (int a = 0; a<20; a++){
		for (int b = 0; b<20; b++){
			map[a][b] = mapdata[a][b];
			target_map[a][b] = INF; 
		}
	}
/*	while (gameflag)
	{
		
	
	}*/
	 view();
	 clock_t start, end;
	 start = clock();
	
	 que();
	 printf("tar_va%d\nstartcosts",target_va);//target数
	 for (int i = 0; i < getlook; i++)
	 {
		 printf("%d", start_costs[i]);
	 }
	 puts("");
	for (int a = 0; a<getlook; a++){
		for (int b = 0; b<getlook; b++){
			printf("%d ", loadcost[a][b]);
		}
		puts("");
	}

	printf("%d\n",at);
	end = clock();
	printf("終了時間:%d\n", end);
	printf("処理時間:%d[ms]\n", end - start);
	return 0;
}

//8方向を表すために用いる配列(x用)
//int cx[12] = { -1, 1, 0, 0, -1, -1, 1, 1, 1, 1, -1, -1 };
//8方向を表すために用いる配列(y用)
//int cy[12] = { 0, 0, -1, 1, -1, 1, -1, 1, 2, -2, 2, -2 };

//手あたり次第に歩数振る->costmapに全座標のコストを振る
void que()
{
	//無限ループバグ防ぐために
	//if (map[y][x] == out_get || map[y][x] == block)return;	

	vector<P> pr_pointer;//一番初めに座標を入れておく入れ物
	vector<P> pr＿mapiniter;//消したあとにいれてそれに基づいてmapのtarget消す

		//queueの宣言
		queue<P> q;
		//基点となる座標一回目のとき
		q.push(make_pair(y, x));
		target_map[y][x] = 0; // targetからの座標で始めるとき2（始めの座標にゼロとしてる
		for (int f = 0; f < getlook;f++)//my,a,b,c.d....t縦列
		{
			//始め以外（２週目以降)クリアにするflag
			if (f != 0)
			{
				while (!q.empty()){ q.pop(); }//queueの中身を空にする
				//座標を入れておく入れ物が空なら終わり。
				//if (pr_pointer.empty()){ 
				//	pr＿mapiniter.clear();//使用したtarget位置を格納の中身に残らないように
				//	break;
				//}
				/*リスタート*/
				q.push(make_pair(pr_pointer.front().first, pr_pointer.front().second));//targetからの座標で始めるとき
				 pr＿mapiniter.push_back(make_pair(pr_pointer.front().first,pr_pointer.front().second));//使用したtarget位置を格納

				 if (f==1)
				 {
					 target_va = pr_pointer.size();//target数いくつ見たか格納
				 }

				//初期化したいときのやつ
				for (int a = 0; a<20; a++)	
				{
					for (int b = 0; b<20; b++)
					{
						map[a][b] = mapdata[a][b];//始めのマップになる。
						target_map[a][b] = INF;//幅優先で値振ったのを消す
					}
				}
				//今まで使用したところを埋める。(autoってvarと同じらしいよ。ただしコンパイラ時に型決めるらしい動的じゃないらしい。)
				for each (auto x in pr＿mapiniter)
				{
					map[x.first][x.second] = 0;
				}
				target_map[pr_pointer.front().first][pr_pointer.front().second] = 0;//targetからの座標で始めるとき2（始めの座標に足していくので始めの座標にゼロとしてる）
				vector<P>::iterator it = pr_pointer.erase(pr_pointer.begin());//先頭要素のイテレータを入れる//先頭要素のイテレータを返すための入れ物((つまるところポインタ
			}
			int g= f;//カウント
			//queue無くなるまで
				while (!q.empty())
				{
					//queueのｘとｙの要素先頭要素にアクセス
					int yy = q.front().first, xx = q.front().second;
					//後がつっかえるのでqueueの先頭要素の消す。
					q.pop();
					//12方向のループ
					for (int i = 0; i < 12; i++)
					{
						int ax = xx + cx[i], ay = yy + cy[i];
						if (ax >= 0 && ax < 20 && ay >= 0 && ay < 20)
						{
							//未訪問でかつ壁以外((今回はワープも除外コースにいれてる
							if (target_map[ay][ax]==INF&&mapdata[ay][ax] != block && mapdata[ay][ax] != out_get&&mapdata[ay][ax] != warpR&&mapdata[ay][ax] != warpL&&mapdata[ay][ax] != warpU &&mapdata[ay][ax] != warpD)
							{
								//前のとこから歩数入れる
								target_map[ay][ax] = target_map[yy][xx] + 1;//道の制御でTargetmapつかう
								//item発見！！
								if (map[ay][ax] == Target)//アイテム数の制御でmapつかう
								{
									printf("target\n");
									k_y = ay;
									k_x = ax;
									map[ay][ax] = 0;//一つ見たのターゲット一つを消す
									if (f == g){ at += target_map[ay][ax]; }
									costmap[f][g++] = target_map[ay][ax];//costをメモ入れる

									if (f == 0){ pr_pointer.push_back(make_pair(ay, ax)); }//自分の座標以外からやるときのための座標メモ
									if (!(g<getlook))
									{
										goto next;//getlook回行ったら逃げる。
									}
								}
								//歩数入れたということできゅーの末尾に入れてやる
								q.push(make_pair(ay, ax));
							}
						}
					}
				}
			next:;//getlook回行ったら逃げる。
		}
		for each (auto x in pr＿mapiniter)
		{
			printf("%d：：%d\n",x.first,x.second);
		}

		//隣接行列に変えてグラフ化
		for (int i = 0; i < getlook; i++)
		{
			start_costs[i] = 0;
			for (int g = 0; g < getlook; g++)
			{
				loadcost[i][g] = 0;
			}
			
		}
		for (int i = 0, o = 1; i < getlook; i++, o++)
		{
			start_costs[i] = costmap[0][i];
			for (int g = 0; g < getlook; g++)
			{
				loadcost[g][i] = costmap[o][g];
			}
		}
		for (int i = 0, o = 1; i < getlook; i++, o++)
		{
			for (int g = 0; g < getlook; g++)
			{
				if (0 != costmap[o][g])
				{
					loadcost[i][g] = costmap[o][g];
				}
			}
		}
		
}

//そこからの距離を求めるつまり道を振る
	void cnt_target_io(){

		//もしも場外除外してんのに場外出てたりブロックに入ったりしてバグらないために
		if (map[y][x] == out_get || map[y][x] == 2)return;
		//i今の場所をゼロとする。
		tac_map[y][x] = 0;
		//終了時座標入れる箱
		int  i_yi = 0, i_xi=0;
		//まわせー！！
		while (true)
		{
			//値が入ったらwhileを偽に
			//if (i_yi == y&&i_xi == x)i_y = 0;
			//幅優先の逆のパターンでまわせば帰れる
			for (int i = 0; i<12; i++)
			{
				int ay = k_y - cy[i], ax = k_x - cx[i];

				if (target_map[ay][ax] == target_map[k_y][k_x] - 1 && map[ay][ax] != out_get&& map[ay][ax] != 2)
				{
					//値マイナスしてく
					tac_map[ay][ax] = target_map[k_y][k_x] - 1;
					if (tac_map[ay][ax] == 0)
					{
						//自分のとこにたどり着いたらreturn
						printf("io_target\n");
						i_yi = ay;
						i_xi = ax;
						return;
					}
					//代入してけばいいやん
					k_y = ay;
					k_x = ax;
				}
			}
			if (i_yi)break;
		}
	}


	
	void view()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int g = 0; g < 20;g++)
			{
				if(i==y&&g==x){
					printf("x");
				}
				else if (mapdata[i][g] == out_get)
				{
					printf("@");
				}
				else if (mapdata[i][g] == block)
				{
					printf("#");
				}
				else if (mapdata[i][g]==Target)
				{
					printf("&");
				}
				else if (mapdata[i][g] == Empty)
				{
					printf(" ");
				}
			}
			puts("");
		}
	}