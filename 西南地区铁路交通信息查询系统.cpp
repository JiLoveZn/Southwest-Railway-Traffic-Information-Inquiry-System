/*#include<stdio.h>
#include<stdlib.h>/*exit����Ҳ������*/ 
/*#include<string.h>
#include<ctime>/*��ͷ�ļ����еõ�ϵͳʱ��ĺ���ctime*/
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
	string vex[MAX_VERTEX_NUM];/*��������*/ 
	string info[MAX_VERTEX_NUM];/*������Ϣ����*/ 
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];/*�ڽӾ���*/ 
	int vexnum,arcnum;/*ͼ�ĵ�ǰ�������ͻ���*/ 
	GraphKind DN;/*ͼ�������־*/ 
}MGraph;
/*Ѱ����Ҫ��ѯ�ĳ���*/ 
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
	return 0;/*δ�ҵ�*/ 
}
/*��ȡ�������������*/
void Input_vex(MGraph &G)
{
	FILE *fp;
	int i,j;
	j=0;
	char s[100][100];
	if((fp=fopen("���ϵ������ĳ��к͸õ����������γ���.txt","r"))==NULL)
	{
		printf("Ŀ���ļ���ʧ��\n");
	}
	else
	{
		while(i=fscanf(fp,"%s",s[j])!=EOF)/*δ�ҵ��������ȡ��fscanf�������ڶ�������ļ�*/
		{
			j++;
		}
		fclose(fp);/*�ر��ļ�*/ 
	}
	G.vexnum =j;
	for(j=0;j<G.vexnum;j++)
	{
		G.vex[j]=s[j];
	}
}
/*��ȡȨֵ�ͻ�,���ڹ����ڽӾ���*/
/*int Input_arcs(MGraph &G)
{
	int i,j;
	FILE *fp;
	if((fp=fopen("���ϵ�����·��·.txt","r"))==NULL)
	{
		printf("�ļ���ʧ��\n");
		return 1; 
	}
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			fscanf(fp,"%d",&G.arcs[i][j]);
			if(G.arcs[i][j]!=0)
			{
				G.arcnum++;/*ͳ�ƻ�������*/
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

int Input_arcs(MGraph &G)//��ȡȨֵ�ͻ��� 
{      
	int i,j;
    FILE*fp;
    if((fp=fopen("���ϵ�����·��·.txt","r"))==NULL)
	{
		printf("�ļ���ʧ��\n");
		return 1;
	}
	else
	{
		for(i=0;i<G.vexnum;i++)//��ȡ
		{
        	for(j=0;j<G.vexnum;j++)
        	{
        		fscanf(fp,"%d",&G.arcs[i][j]);
        		if(G.arcs[i][j]!=0)  //g.arcnum++;//ͳ�ƻ��� 
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
		  		G.arcs[i][j]=INFINITY;//��Ȩֵ��ֵ����� 
		  		}
			}
		}
	}

}
/*��ȡ�����������Ϣ*/
void Input_info(MGraph &G)
{
	FILE *fp;
	int i,j;
	j=0;
	char s[200][200];
	if((fp=fopen("���ϵ������ĳ��к͸õ����������γ��е������·��ͨ��Ϣ.txt","r"))==NULL)
	{
		printf("Ŀ���ļ���ʧ��\n");
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
/*�����ڽӾ��󣬹���������*/ 
void Create_DN(MGraph &G)
{
	Input_vex(G);
	Input_arcs(G);
	Input_info(G);
}
typedef int PathMaxtrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];/*���ڴ洢���·���±������*/ 
typedef int ShortPathTable[MAX_VERTEX_NUM];/*���ڴ洢���������·����Ȩֵ��*/ 
void ShortestPath_DIJ(MGraph G,int v0,PathMaxtrix &p,ShortPathTable &D)
{
	int v,w,i,j,min;
	int final[MAX_VERTEX_NUM];/*final[w]=1��ʾ��ö���v0��v(w)�����·��*/ 
	for(v=0;v<G.vexnum;++v)/*��ѭ��������Ϊ��ʼ������*/ 
	{
		final[v]=0;/*ȫ�������ʼ��Ϊδ֪���·��״̬*/ 
		D[v]=G.arcs[v0][v];/*����v0�������ߵĶ������Ȩֵ����ʼֵΪv0��v��ֱ�Ӿ���*/ 
		for(w=0;w<G.vexnum;++w)
		{
			p[v][w]=-1;/*���·��*/ 
		}
		if(D[v]<INFINITY)/*v0��v��ֱ��·��*/ 
		{
			p[v][v0]=v0;
			p[v][v]=v;
		}
	}
	D[v0]=0;/*v0��v0��·��Ϊ0*/ 
	final[v0]=1;/*��ʼ����v0��v0����Ҫ��·��������v0��������S����*/ 
	/*��ʼ��ѭ����ÿ�����v0��v��ĳ��v��������·��������v���뵽S����*/ 
	for(i=1;i<G.vexnum;++i)/*����G.vexnum-1������*/
	{
		min=INFINITY;/*��ǰ��֪��v0�����������룬�ȷ����ֵ������min��СΪINFINITY */ 
		for(w=0;w<G.vexnum;++w)//������еĶ��� 
		{
			if(!final[w])/*w������V-S�ļ�����*/ 
			{
				if(D[w]<min)/*w������v0�������*/ 
				{
					v=w;
					min=D[w];
				}
			}
		}
		final[v]=1;/*��v0���������v����S����*/ 
		for(w=0;w<G.vexnum;++w)/*���µ�ǰ���·���;��� */
		{
			if(!final[w]&&(min+G.arcs[v][w]<D[w])&&min<INFINITY && G.arcs[v][w]<INFINITY)/*w������S������v0->v->w�ľ���<Ŀǰv0->w�ľ��� ��w����V-S����*/ 
			{
				D[w]=min+G.arcs[v][w];//�޸�D[w] 
				for(j=0;j<G.vexnum;j++)/*�޸�p[w]��v0��w�����Ķ������v0��v���������ж����ټ��϶���w*/
					{
						p[w][j]=p[v][j];
						if(p[w][j]==-1)/*��p[w][]��һ������0�ĵط����϶���w*/
							{
								p[w][j]=w;
								break;
							}
					}			
			}
		}
	}
}
/*��ģʽ��T��next����ֵ������next����*/ 
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
/*�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ���������ֵΪ0��T�ǿգ�1<=pos<=StrLength_S */ 
/*int Index_KMP(char S[],char T[],int pos)
{
	int i,j;
	i=pos;/*i��������S��ǰλ���±�ֵ����pos��Ϊ1�����posλ�ÿ�ʼƥ��*/ 
/*	j=1;
	int StrLength_S=0;
	int StrLength_T=0;
	StrLength_S=strlen(S);/*������S�ĳ���*/ 
/*	StrLength_T=strlen(T);/*��ģʽ��T�ĳ���*/ 
/*	int next[255];/*����1��next����*/
/*	get_next(T,next);/*�Դ�T���������õ�next����*/ 
/*	while(i<=StrLength_S && j<=StrLength_T)/*��iС��S�ĳ�����jС��T�ĳ���ʱ��ѭ������*/ 
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
void Display_path(MGraph G,PathMaxtrix p)//��ʾ���·����ά���� 
{   int i,j;
	cout<<"���·������p[i][j]���£�"<<endl;
	for(i=0; i<G.vexnum; i++)
	{
		for(j=0; j<G.vexnum; j++)
			cout<<setw(3)<<p[i][j]<<" ";
		cout<<endl;
	}
}
void Display_ShortestPath_DIJ(MGraph G,PathMaxtrix p,ShortPathTable d,int v0,int v)
{   int i,j;
	//��ʾ���·����·�� 
	for(i=0; i<G.vexnum; i++)
	{  
	   if(i==v)
		{
		  if(d[i]!=INFINITY&&i!=v0)//��·���Ҳ��ǵ����� 
		  {
			cout<<endl<<G.vex[v0]<<"-->"<<G.vex[i]<<"�����·��Ϊ:"<<d[i]<<endl<<endl;
			cout<<"���·��Ϊ��";
			for(j=0; j<G.vexnum; j++)
			{
				if(p[i][j]>-1)  cout<<G.vex[p[i][j]];
					if((p[i][j+1]!=-1)&&(j+1<G.vexnum)) cout<<"-->";//��ӡ��ͷ 
			}
			cout<<endl<<endl;			
		  }
	    
		else if(d[i]==INFINITY)//û��·�� 
			cout<<G.vex[v0]<<"-->"<<G.vex[i]<<":"<<"�޴˽�ͨ·��"<<endl<<endl;
	    
		}
	}
}
/*��ʾ�Ͻ�˹�����㷨�м�¼·��������*/
/*void Display_path(MGraph G,PathMaxtrix P)
{
	int i,j;
	printf("��¼·��������Ϊ��\n");
	for(i=1;i<=G.vexnum;i++)
	{
		for(j=1;j<=G.vexnum;j++)
		{
			printf("%c",P[i][j]);	
		}	
	} 
}
/*��ʾ�Ͻ�˹�����㷨�м�¼��·������̾���*/
/*void Display_ShortestPath_DIJ(MGraph G,PathMaxtrix P,ShortPathTable T,int v,int v0)
{
	int i,j;
	for(i=1;i<=G.vexnum;i++)
	{
		if(i==v)
		{
			if(T[i]!=INFINITY && i!=v0)/*��Ȩֵ���������·������·�����ǵ����Լ������·��*/
/*			{
				printf("%s",G.vex);
				printf("-->% ����̾���Ϊ��",G.vex);
				printf("%d\n",T[i]);
				printf("���·��Ϊ��\n");
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
				printf("����·�߲�����\n"); 
			}	
		}	
	} 
}*/
/*void Display_Information(MGraph G)
{
	printf("�����г�վ��·��ͨ��·��Ϣ���£�\n");
	int i;
	for(i=1;i<=G.vexnum;i++)
	{
		printf("%sվ��\n",G.vex);
		printf("%s",G.info);
	}	
}
void Search_Information(MGraph G)
{
	printf("                              ��վ��·��ͨ��·��Ϣ����\n");
	char S[100][100],T[100][20],Info[20];
	char Ss[100],Tt[20];
	int m,j,i=0,n=0;
	int k,p,l=1;
	FILE *fp;
	if( (fp=fopen("���ϵ������ĳ��к͸õ����������γ��е������·��ͨ��Ϣ.txt","r" ))==NULL  )
	{
		printf("Ŀ���ļ���ʧ��\n");	
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
		printf("��������Ҫ�����ĳ��У�\n");
		scanf("%s",&Info);
		printf("��Ҫ�����ĳ�����·��ͨ��Ϣ���£�\n");
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
			printf("����ʧ�ܣ�ϵͳ��û����Ҫ��ѯ�ĳ��е���·��ͨ��Ϣ\n");
			n=0;	
		}		
	}
}*/
void Search_Route(MGraph G)//�������������е����·��
{  
	int judge=1;
	sleep(1);system("cls"); 
	string s0,s;
	int v0,v,i,j;
   	PathMaxtrix p;
   	ShortPathTable d;
	cout<<"             *********************************************************"<<endl;
	cout<<"             ******************��     ��     ·    ��*****************"<<endl; 
	cout<<"             *********************************************************"<<endl;
	cout<<endl;	
	while(judge==1)
	{
		cout<<"�����������ڳ��У�"<<endl;
		cin>>s0;
		cout<<"��������Ҫǰ���ĳ��У�"<<endl;
		cin>>s;
		v0=Locate(G,s0);//Ѱ��Դ��
		v=Locate(G,s); //Ѱ���յ�	
		if(v0==0||v==0)//���벻�Ϸ���������ݲ����� 
		{
			cout<<endl<<"��Ǹ��С����û���ҵ���������ĳ��С�"<<endl;
			sleep(1);
			cout<<endl; 
			cout<<"             ************************���������밴1********************"<<endl;
			cout<<"             **********************�����ϼ��˵��밴2******************"<<endl; 
			cout<<"             *********************�������������������****************"<<endl;
			cin>>judge;
		//if(judge==2)   operate(g);
			if(judge==1)
			{
				Search_Route(G);
			}   
			else 
			{
				cout<<"             **********************��л����ʹ��!**********************"<<endl;
          		sleep(1);
	      		exit(0); 
        	}
        }
		else
		{
			ShortestPath_DIJ(G,v0,p,d);			
    		Display_ShortestPath_DIJ(G,p,d,v0,v);
			cout<<endl; 
			cout<<"             ************************���²����밴1********************"<<endl;
			cout<<"             **********************�����ϼ��˵��밴2******************"<<endl; 
			cout<<"             *********************�������������������****************"<<endl;
			cin>>judge;
		//if(judge==2)   operate(g);
			if(judge==1)
			{
				Search_Route(G);
			}   
			else 
			{
				cout<<"             **********************��л����ʹ��!**********************"<<endl;
           		sleep(1);
	       		exit(0); 
        	}
    	}
    
    
   } 
}
/*void Search_Route(MGraph G)
{
	printf("                                   ��·����\n");
	int v0,v,i,j,k=1;
	string s0,s;
	PathMaxtrix P;
	ShortPathTable T;
	while(k==1)
	{
		printf("������Ҫ�����ĳ��У�\n");
		scanf("%s",&s0);
		printf("������Ҫ����ĳ��У�\n");
		scanf("%s",&s);
		v0=Locate(G,s0);
		v=Locate(G,s);
		if(v0==-1||v==-1)
		{
			printf("ϵͳ��û������������·��\n");
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
	printf("                         ���ϵ�����·��ͨ��Ϣ��ѯϵͳ\n");
	printf("           ________________________________________________________\n");
	printf("           |                                                      |\n");
	printf("           |                                                      |\n");
	printf("           |         ��ӭ�������ϵ�����·��ͨ��Ϣ��ѯϵͳ         |\n");
	printf("           |        ��ǰϵͳʱ��Ϊ:%s\n",ctime(&t));
	printf("           |         �˲�ѯϵͳ�ɲ�ѯ���ϵ������ĳ���             |\n");
	printf("           |         �͸õ����������γ��е���·��ͨ��Ϣ           |\n"); 
	printf("           |                                                      |\n");
	printf("           |       �ò�ѯϵͳ�е����ϵ���������������������:      |\n");
	printf("           |   �Ĵ�ʡ���ຣʡ������ʡ������ʡ�������С����������� |\n"); 
	printf("           |                                                      |\n");
	printf("           |             ��������ˣ��Ź�1402   �� ��             |\n");
	printf("           |______________________________________________________|\n");
	system("pause\n");/*ʵ�ְ�����������Ĳ���*/ 
	system("cls\n");/*�����Ļ��ʾ������*/	
}
void Menu(MGraph G)
{
	printf("\n");
	printf("                             �ò�ѯϵͳ�Ĳ˵�����\n");
	printf("           ________________________________________________________\n");
	printf("           |                                                      |\n");
	printf("           |                                                      |\n");
	printf("           |�鿴���ϵ������ĳ��к͸õ����������γ���һ�����밴��1 |\n");
	printf("           |          ��ѯ�����г�վ��·��ͨ��·��Ϣ�밴��2       |\n");
	printf("           |                   ��·��ѯ�밴��3                    |\n");
	printf("           |                   �˳�ϵͳ�밴��0                    |\n");
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
