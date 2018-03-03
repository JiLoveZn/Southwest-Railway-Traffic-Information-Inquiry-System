/*#include<stdio.h>
#include<stdlib.h>/*exit函数也在其中*/ 
/*#include<string.h>
#include<ctime>/*此头文件内有得到系统时间的函数ctime*/
/*#include<iomanip>*/
#include<iostream>
#include<windows.h>
#include<conio.h>//getch
#include<string.h>
#include<stdio.h>
#include<ctime>
#include<iomanip>
#include<stdlib.h>
#include <unistd.h>//sleep
#define INFINITY    INT_MAX
#define MAX_VERTEX_NUM 50
using namespace std;
typedef enum
{DG,DN,UDG,UDN}GraphKind;
typedef struct
{
	string vex[MAX_VERTEX_NUM];/*顶点向量*/ 
	string info[MAX_VERTEX_NUM];/*顶点信息向量*/ 
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];/*邻接矩阵*/ 
	int vexnum,arcnum;/*图的当前顶点数和弧数*/ 
	GraphKind DN;/*图的种类标志*/ 
}MGraph;
/*寻找需要查询的城市*/ 
int Locate(MGraph G,string s)
{
	int i;
	for(i=0;i<G.vexnum;++i)
	{
		if(G.vex[i]==s)
		{
			return i;
		}
	}
	return 0;/*未找到*/ 
}
/*读取顶点个数和名称*/
void Input_vex(MGraph &G)
{
	FILE *fp;
	int i,j;
	j=0;
	char s[100][100];
	if((fp=fopen("西南地区中心城市和该地区热门旅游城市.txt","r"))==NULL)
	{
		printf("目标文件打开失败\n");
	}
	else
	{
		while(i=fscanf(fp,"%s",s[j])!=EOF)/*未找到则继续读取，fscanf函数用于读入磁盘文件*/
		{
			j++;
		}
		fclose(fp);/*关闭文件*/ 
	}
	G.vexnum =j;
	for(j=0;j<G.vexnum;j++)
	{
		G.vex[j]=s[j];
	}
}
/*读取权值和弧,用于构建邻接矩阵*/
/*int Input_arcs(MGraph &G)
{
	int i,j;
	FILE *fp;
	if((fp=fopen("西南地区铁路线路.txt","r"))==NULL)
	{
		printf("文件打开失败\n");
		return 1; 
	}
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			fscanf(fp,"%d",&G.arcs[i][j]);
			if(G.arcs[i][j]!=0)
			{
				G.arcnum++;/*统计弧的数量*/
/*			}
		}
	}
	fclose(fp);
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;i<G.vexnum;j++)
		{
			if(G.arcs[i][j]=0)
			{
				G.arcs[i][j]=INFINITY;
			}
		}
	}
		 
}*/

int Input_arcs(MGraph &G)//读取权值和弧数 
{      
	int i,j;
    FILE*fp;
    if((fp=fopen("西南地区铁路线路.txt","r"))==NULL)
	{
		printf("文件打开失败\n");
		return 1;
	}
	else
	{
		for(i=0;i<G.vexnum;i++)//读取
		{
        	for(j=0;j<G.vexnum;j++)
        	{
        		fscanf(fp,"%d",&G.arcs[i][j]);
        		if(G.arcs[i][j]!=0)  //g.arcnum++;//统计弧数 
        		{
        			G.arcnum++;
				}
            }
        }
       
		fclose(fp);
		for(i=0;i<G.vexnum;++i)
		{
			for(j=0;j<G.vexnum;++j)
			{
				if(G.arcs[i][j]==0)
				{
		  		G.arcs[i][j]=INFINITY;//无权值赋值无穷大 
		  		}
			}
		}
	}

}
/*读取顶点的其他信息*/
void Input_info(MGraph &G)
{
	FILE *fp;
	int i,j;
	j=0;
	char s[200][200];
	if((fp=fopen("西南地区中心城市和该地区热门旅游城市的相关铁路交通信息.txt","r"))==NULL)
	{
		printf("目标文件打开失败\n");
	}
	else
	{
		while((i=fscanf(fp,"%s", s[j])!= EOF))
		{
			j++;	
		}  
       
		fclose(fp);
    } 
   
	for(j=0;i<G.vexnum;++i)
	{
		G.info[j]=s[j];	
	}	
}
/*采用邻接矩阵，构造有向网*/ 
void Create_DN(MGraph &G)
{
	Input_vex(G);
	Input_arcs(G);
	Input_info(G);
}
typedef int PathMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];/*用于存储最短路径下标的数组*/ 
typedef int ShortPathTable[MAX_VERTEX_NUM];/*用于存储到各点最短路径的权值和*/ 
void ShortestPath_DIJ(MGraph G,int v0,PathMaxtrix &p,ShortPathTable &D)
{
	int v,w,i,j,min;
	int final[MAX_VERTEX_NUM];/*final[w]=1表示求得顶点v0到v(w)的最短路径*/ 
	for(v=0;v<G.vexnum;++v)/*此循环的作用为初始化数据*/ 
	{
		final[v]=0;/*全部顶点初始化为未知最短路径状态*/ 
		D[v]=G.arcs[v0][v];/*将与v0点有连线的顶点加上权值，初始值为v0到v的直接距离*/ 
		for(w=0;w<G.vexnum;++w)
		{
			p[v][w]=-1;/*设空路径*/ 
		}
		if(D[v]<INFINITY)/*v0到v有直接路径*/ 
		{
			p[v][v0]=v0;
			p[v][v]=v;
		}
	}
	D[v0]=0;/*v0到v0的路径为0*/ 
	final[v0]=1;/*初始化，v0到v0不需要求路径，所以v0顶点属于S集合*/ 
	/*开始主循环，每次求得v0到v的某个v顶点的最短路径，并将v加入到S集合*/ 
	for(i=1;i<G.vexnum;++i)/*其余G.vexnum-1个顶点*/
	{
		min=INFINITY;/*当前所知离v0顶点的最近距离，先放最大值，假设min最小为INFINITY */ 
		for(w=0;w<G.vexnum;++w)//检查所有的顶点 
		{
			if(!final[w])/*w顶点在V-S的集合中*/ 
			{
				if(D[w]<min)/*w顶点离v0顶点更近*/ 
				{
					v=w;
					min=D[w];
				}
			}
		}
		final[v]=1;/*离v0顶点最近的v加入S集合*/ 
		for(w=0;w<G.vexnum;++w)/*更新当前最短路径和距离 */
		{
			if(!final[w]&&(min+G.arcs[v][w]<D[w])&&min<INFINITY && G.arcs[v][w]<INFINITY)/*w不属于S集合且v0->v->w的距离<目前v0->w的距离 ，w属于V-S集合*/ 
			{
				D[w]=min+G.arcs[v][w];//修改D[w] 
				for(j=0;j<G.vexnum;j++)/*修改p[w]，v0到w经过的顶点包括v0到v经过的所有顶点再加上顶点w*/
					{
						p[w][j]=p[v][j];
						if(p[w][j]==-1)/*在p[w][]第一个等于0的地方加上顶点w*/
							{
								p[w][j]=w;
								break;
							}
					}			
			}
		}
	}
}
/*求模式串T的next函数值并存入next数组*/ 
/*void get_next(char T[],int next[])
{
	int i=1,j;
	next[1]=0;
	j=0;
	int StrLength_T=0;
	StrLength_T=strlen(T);
	while(i<StrLength_T)
	{
		if(j==0 || T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
		{
			j=next[j];
		}
	}
}*/
/*返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0。T非空，1<=pos<=StrLength_S */ 
/*int Index_KMP(char S[],char T[],int pos)
{
	int i,j;
	i=pos;/*i用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配*/ 
/*	j=1;
	int StrLength_S=0;
	int StrLength_T=0;
	StrLength_S=strlen(S);/*求主串S的长度*/ 
/*	StrLength_T=strlen(T);/*求模式串T的长度*/ 
/*	int next[255];/*定义1个next数组*/
/*	get_next(T,next);/*对串T做分析，得到next数组*/ 
/*	while(i<=StrLength_S && j<=StrLength_T)/*若i小于S的长度且j小于T的长度时，循环继续*/ 
/*	{
		if(j==0 || S[i]==T[j])
		{
			++i;
			++j;
		}
		else
		{
			j=next[j];
		}
	}
	if(j>StrLength_T)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}*/
void Display_path(MGraph G,PathMaxtrix p)//显示最短路径二维数组 
{   int i,j;
	cout<<"最短路径数组p[i][j]如下："<<endl;
	for(i=0; i<G.vexnum; i++)
	{
		for(j=0; j<G.vexnum; j++)
			cout<<setw(3)<<p[i][j]<<" ";
		cout<<endl;
	}
}
void Display_ShortestPath_DIJ(MGraph G,PathMaxtrix p,ShortPathTable d,int v0,int v)
{   int i,j;
	//显示最短路径和路程 
	for(i=0; i<G.vexnum; i++)
	{  
	   if(i==v)
		{
		  if(d[i]!=INFINITY&&i!=v0)//有路线且不是到本身 
		  {
			cout<<endl<<G.vex[v0]<<"-->"<<G.vex[i]<<"的最短路程为:"<<d[i]<<endl<<endl;
			cout<<"最短路线为：";
			for(j=0; j<G.vexnum; j++)
			{
				if(p[i][j]>-1)  cout<<G.vex[p[i][j]];
					if((p[i][j+1]!=-1)&&(j+1<G.vexnum)) cout<<"-->";//打印箭头 
			}
			cout<<endl<<endl;			
		  }
	    
		else if(d[i]==INFINITY)//没有路线 
			cout<<G.vex[v0]<<"-->"<<G.vex[i]<<":"<<"无此交通路线"<<endl<<endl;
	    
		}
	}
}
/*显示迪杰斯特拉算法中记录路径的数组*/
/*void Display_path(MGraph G,PathMaxtrix P)
{
	int i,j;
	printf("记录路经的数组为：\n");
	for(i=1;i<=G.vexnum;i++)
	{
		for(j=1;j<=G.vexnum;j++)
		{
			printf("%c",P[i][j]);	
		}	
	} 
}
/*显示迪杰斯特拉算法中记录的路径和最短距离*/
/*void Display_ShortestPath_DIJ(MGraph G,PathMaxtrix P,ShortPathTable T,int v,int v0)
{
	int i,j;
	for(i=1;i<=G.vexnum;i++)
	{
		if(i==v)
		{
			if(T[i]!=INFINITY && i!=v0)/*有权值不是无穷的路径并且路径不是到达自己本身的路经*/
/*			{
				printf("%s",G.vex);
				printf("-->% 的最短距离为：",G.vex);
				printf("%d\n",T[i]);
				printf("最短路径为：\n");
				for(j=1;j<=G.vexnum;j++)
				{
					if(P[i][j]>-1)
					{
						printf("%s",G.vex/*[P[i][j]]*///);
/*						if((P[i][j+1]!=-1)&&(j+1<G.vexnum))
						{
							printf("--->");	
						}	
					}	
				}	
			}
		}
		else
		{
			if(T[i]==INFINITY)
			{
				printf("%s-->%s",G.vex,G.vex);
				printf("这条路线不存在\n"); 
			}	
		}	
	} 
}*/
/*void Display_Information(MGraph G)
{
	printf("各城市车站铁路交通线路信息如下：\n");
	int i;
	for(i=1;i<=G.vexnum;i++)
	{
		printf("%s站：\n",G.vex);
		printf("%s",G.info);
	}	
}
void Search_Information(MGraph G)
{
	printf("                              车站铁路交通线路信息搜索\n");
	char S[100][100],T[100][20],Info[20];
	char Ss[100],Tt[20];
	int m,j,i=0,n=0;
	int k,p,l=1;
	FILE *fp;
	if( (fp=fopen("西南地区中心城市和该地区热门旅游城市的相关铁路交通信息.txt","r" ))==NULL  )
	{
		printf("目标文件打开失败\n");	
	}
	else
	{
		while((m=fscanf(fp,"%s", S[i])!= EOF));
		{
			i++;
		}
		fclose(fp);
	}
	while(l=1)
	{
		printf("请输入你要搜索的城市：\n");
		scanf("%s",&Info);
		printf("您要搜索的城市铁路交通信息如下：\n");
		for(j=1;j<=i;j++)
		{
			strcpy(T[j],Info);	
		}
		for(j=1;j<=i;j++)
		{
			strcpy(Ss,S[j]);
			strcpy(Tt,T[j]);
		}
		k=Index_KMP(Ss,Tt,p);
		if(k==1)
		{
			n++;
			printf("%s",G.vex);
			printf("%s",S[j]);
		}
		if(n==0)
		{
			printf("搜索失败，系统中没有您要查询的城市的铁路交通信息\n");
			n=0;	
		}		
	}
}*/
void Search_Route(MGraph G)//查任意两座城市的最短路线
{  
	int judge=1;
	sleep(1);system("cls"); 
	string s0,s;
	int v0,v,i,j;
   	PathMaxtrix p;
   	ShortPathTable d;
	cout<<"             *********************************************************"<<endl;
	cout<<"             ******************查     找     路    线*****************"<<endl; 
	cout<<"             *********************************************************"<<endl;
	cout<<endl;	
	while(judge==1)
	{
		cout<<"请输入您所在城市："<<endl;
		cin>>s0;
		cout<<"请输入您要前往的城市："<<endl;
		cin>>s;
		v0=Locate(G,s0);//寻找源点
		v=Locate(G,s); //寻找终点	
		if(v0==0||v==0)//输入不合法或城市数据不存在 
		{
			cout<<endl<<"抱歉，小助手没有找到您所输入的城市。"<<endl;
			sleep(1);
			cout<<endl; 
			cout<<"             ************************重新输入请按1********************"<<endl;
			cout<<"             **********************返回上级菜单请按2******************"<<endl; 
			cout<<"             *********************按其它任意键结束程序****************"<<endl;
			cin>>judge;
		//if(judge==2)   operate(g);
			if(judge==1)
			{
				Search_Route(G);
			}   
			else 
			{
				cout<<"             **********************感谢您的使用!**********************"<<endl;
          		sleep(1);
	      		exit(0); 
        	}
        }
		else
		{
			ShortestPath_DIJ(G,v0,p,d);			
    		Display_ShortestPath_DIJ(G,p,d,v0,v);
			cout<<endl; 
			cout<<"             ************************重新查找请按1********************"<<endl;
			cout<<"             **********************返回上级菜单请按2******************"<<endl; 
			cout<<"             *********************按其它任意键结束程序****************"<<endl;
			cin>>judge;
		//if(judge==2)   operate(g);
			if(judge==1)
			{
				Search_Route(G);
			}   
			else 
			{
				cout<<"             **********************感谢您的使用!**********************"<<endl;
           		sleep(1);
	       		exit(0); 
        	}
    	}
    
    
   } 
}
/*void Search_Route(MGraph G)
{
	printf("                                   线路查找\n");
	int v0,v,i,j,k=1;
	string s0,s;
	PathMaxtrix P;
	ShortPathTable T;
	while(k==1)
	{
		printf("请输入要出发的城市：\n");
		scanf("%s",&s0);
		printf("请输入要到达的城市：\n");
		scanf("%s",&s);
		v0=Locate(G,s0);
		v=Locate(G,s);
		if(v0==-1||v==-1)
		{
			printf("系统中没有您所搜索的路线\n");
		}
		else
		{
			ShortestPath_DIJ(G,v0,P,T);
			Display_ShortestPath_DIJ(G,P,T,v,v0);
		}
	}		
} */
void Welcome()
{
	int a;
	char s;
	time_t t;
	time(&t);
	system("color 4B");
	printf("\n");
	printf("                         西南地区铁路交通信息查询系统\n");
	printf("           ________________________________________________________\n");
	printf("           |                                                      |\n");
	printf("           |                                                      |\n");
	printf("           |         欢迎进入西南地区铁路交通信息查询系统         |\n");
	printf("           |        当前系统时间为:%s\n",ctime(&t));
	printf("           |         此查询系统可查询西南地区中心城市             |\n");
	printf("           |         和该地区热门旅游城市的铁路交通信息           |\n"); 
	printf("           |                                                      |\n");
	printf("           |       该查询系统中的西南地区包括了以下行政区域:      |\n");
	printf("           |   四川省、青海省、云南省、贵州省、重庆市、西藏自治区 |\n"); 
	printf("           |                                                      |\n");
	printf("           |             设计制作人：信管1402   陈 吉             |\n");
	printf("           |______________________________________________________|\n");
	system("pause\n");/*实现按任意键继续的操作*/ 
	system("cls\n");/*清空屏幕显示的内容*/	
}
void Menu(MGraph G)
{
	printf("\n");
	printf("                             该查询系统的菜单如下\n");
	printf("           ________________________________________________________\n");
	printf("           |                                                      |\n");
	printf("           |                                                      |\n");
	printf("           |查看西南地区中心城市和该地区热门旅游城市一览表请按：1 |\n");
	printf("           |          查询各城市车站铁路交通线路信息请按：2       |\n");
	printf("           |                   线路查询请按：3                    |\n");
	printf("           |                   退出系统请按：0                    |\n");
	printf("           |______________________________________________________|\n");
	int i,b;
	scanf("%d",&b); 
	if(b==1)
	{
		//Display_Information(G);	
	}
	if(b==2)
	{
		//Search_Information(G);	
	}
	if(b==3)
	{
		Search_Route(G);
	}
	if(b==0)
	{
		exit(0);
	}
			
} 
main()
{
	MGraph G;
	Welcome();
	Create_DN(G);
	Menu(G);	
}
