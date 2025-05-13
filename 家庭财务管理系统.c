#include<stdio.h>
#include<stdlib.h>//malloc的头文件
#include<string.h> 
#define FILENAME "finance.txt" 
typedef struct faminfor{
	int year;//年
	int month;//月 
	int day;//日
	float amount;//金额
	char name[20];//使用人   
	int type;//状态 
	char comment[100];//事项 
	struct faminfor *next;//指向下一结点的指针 
}family;
family *head=NULL;//头指针

void save();//申明函数 
void print_record();

//欢迎页
void welcome()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t\t家庭财务管理系统\n");
	sleep(1);
} 

//系统主菜单
int menu()
{
	int n;
	system("cls");//清屏
	printf("\n\n\n\n\n");
	printf("\t\t====================================家庭财务管理系统====================================");
	printf("\n");
	printf("\t\t========================================================================================");
	printf("\t\t\n\t\t||                                        菜单                                        ||\n");
	printf("\t\t||                                     1.新增记录                                     ||\n");
	printf("\t\t||                                     2.显示记录                                     ||\n");
	printf("\t\t||                                     3.查询记录                                     ||\n");
	printf("\t\t||                                     4.删除记录                                     ||\n");
	printf("\t\t||                                     5.修改记录                                     ||\n");
	printf("\t\t||                                     0.退出系统                                     ||\n");
	printf("\t\t========================================================================================");
	printf("                                                                请选择您想要的功能 (0-5) :\n                            ");
	scanf("%d",&n);
	return n;
}

//文件读取 
void  read()
{
	FILE *fp;
	family *p;
	//参数a+，可读，可写，可追加，如果文件不存在则创建
	if((fp=fopen(FILENAME,"a+"))==NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	fseek(fp,0,SEEK_END);//文件指针移动到末尾 
	int size=ftell(fp);//移动的偏移量 
	fseek(fp,0,SEEK_SET);//移动到头 
	//如果当前文件指针fp偏移量小于总偏移量，则循环 
	while(ftell(fp)<size)
	{
		p=(family *)malloc(sizeof(struct faminfor));//动态分配内存空间
		fread(p,sizeof(struct faminfor),1,fp);
		p->next=head;//第一次时head为空，第二次开始为上一个头结点的地址 
		head=p;//新结点为头结点 
	}
}

//显示
void show()
{
    family *p=head;
    if(!head)
    {
    	printf("当前没有信息！\n");
    	return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
	printf("|======================================================================================================================|\n");
    while (p!=NULL)
	{
        printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
        p=p->next;//指针移动到下一个节点 
    }
    system("pause");//暂停 
} 

//录入
void add()
{
	system("cls");//清屏
	family *p=NULL;
	p=(family *)malloc(sizeof(struct faminfor));//动态分配内存空间
	//初始化新分配的内存空间，避免“脏”数据
	memset(p,0,sizeof(struct faminfor));
	printf("请输入年份："); 
	scanf("%d",&p->year);
	printf("请输入月份："); 
	scanf("%d",&p->month);
	printf("请输入日期："); 
	scanf("%d",&p->day);
	printf("请输入金额："); 
	scanf("%f",&p->amount);
	printf("请输入姓名："); 
	scanf("%s",p->name);
	printf("请输入类型(收入为1，支出为0)："); 
	scanf("%d",&p->type);
	printf("请输入事项："); 
	scanf("%s",p->comment);
	p->next=head;//第一次时head为空，第二次开始为上一个头结点的地址 
	head=p;//新结点为头结点 
	save();//保存 
}

//保存文件
void save()
{
	FILE *fp;
	family *p=NULL;
	//参数wb+，可读，可写，可追加，如果文件不存在则创建
	if((fp=fopen(FILENAME,"wb+"))==NULL)
	{
		printf("文件打开失败！\n");
		system("pause");//暂停 
		return;
	}
	for(p=head;p!=NULL;p=p->next)
	{
		if(fwrite(p,sizeof(struct faminfor),1,fp)!=1)
		{
			printf("写入失败！\n");
			return;
		}
	}
	printf("写入成功！\n");		
	system("pause");//暂停 
	fclose(fp);
} 
 
//查找
void search()
{
	system("cls");//清屏
	family *p=NULL;
	int choice,type;
	char name[20];
	printf("1.按姓名；2.按类型："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",name);
		for(p=head;p!=NULL;p=p->next)
		{
			//第二个参数是否为第一个的子集，实现模糊查找效果 
			if(strstr(p->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			} 
		}
	system("pause");//暂停 
	return; 
	}
	if(choice==2)
	{
		printf("请输入类型(收入为1，支出为0)：");
		scanf("%d",&type); 
		for(p=head;p!=NULL;p=p->next)
		{
			if(p->type==type)
			{
				printf("|======================================================================================================================|\n");
 				printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			}
		}
	system("pause");//暂停 
	return; 
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
	 
} 

//查找
void search1()
{
	system("cls");//清屏
	family *p=NULL;
	int choice,type;
	char faminfor[20];
	printf("1.按姓名；2.按类型："); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("请输入姓名：");
		scanf("%s",faminfor);
		print_record(choice,faminfor);
		system("pause");//暂停 
		return;
	}
	if(choice==2)
	{
		printf("请输入类型(收入为1，支出为0)：");
		scanf("%d",&type);
		//将整数（type）转为数组（由第二个参数确定），第三个数为待转数的进制 
		itoa(type,faminfor,10);
		print_record(choice,faminfor);
		system("pause");//暂停 
		return;
	}
	else
	{
		printf("输入错误！\n");
		system("pause");//暂停 
		return;
	} 
	 
}

//输出信息（查找，或者所有），当choice为1则faminfor是姓名，当choice为2则faminfor是类型
void print_record(int choice,char faminfor[20])
{
	family *p=head;
	float income=0.0;
	float outgoing=0.0;
	float balance=0.0;
    if(!head)
    { 
    	printf("当前没有信息！\n");
		return;
	}
	system("cls");//清屏
	printf("|======================================================================================================================|\n");
	printf("|\t年\t|\t月\t|\t日\t|\t金额\t  |\t使用人\t   |   \t  状态\t   |\t   事项\t       |\n");
	printf("|======================================================================================================================|\n");
	for(p=head;p!=NULL;p=p->next)
	{
		switch(choice)
		{
			case 1:
				if(strstr(p->name,faminfor)!=NULL)
				{
					goto printinfor;
				}
				break;
			case 2:
				if(p->type==atoi(faminfor))
				{
					goto printinfor;
				}
				break;
			case 99:
				if(p->type==1)
				{
					income+=p->amount;
				}
				else
				{
					outgoing+=p->amount;
				}
				goto printinfor;
				
			printinfor:
			printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			
		}
	}
	printf("总收入: %.1f\n", income);
    printf("总支出: %.1f\n", outgoing);
    printf("净收入(收入-支出): %.1f\n", income-outgoing);
	system("pause");//暂停 
}

//删除
void del()
{
	family *p=head;
	family *prev=head;
	char name[20];//使用人
	int choice;
	float amount;//金额
	system("cls");//清屏 
	
	printf("请输入姓名：");
	scanf("%s",name);
	printf("请输入金额：");
	scanf("%f",&amount);
	
	for(;p!=NULL;prev=p,p=p->next)
	{
		if(strcmp(p->name,name)==0 && p->amount==amount)
		{
			printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			printf("你是否要删除(1删除，0不删除)：");
			scanf("%d", &choice);
			if(choice==1)
			{
				if(p==head)
				{
					head=p->next;
					free(p);
					printf("删除成功！\n");
					break;
				} 
				else
				{
					prev->next=p->next;
					free(p);
					printf("删除成功！\n");
					save();
					break;	
				}
			}
			else
			{
				printf("不删除！\n");
				system("pause");
				return;
			}
		}
	}
	if(p==NULL)
	{
		printf("未找到！\n");
		system("pause");
		return;
	}
 } 

//修改
void edit()
{
    family *p = head;
    int choice; 
    char name[20]; // 使用人
    float amount;  // 金额
    system("cls"); // 清屏 

    printf("请输入姓名：");
    scanf("%s", name);
    printf("请输入金额：");
    scanf("%f", &amount);

    for (; p != NULL; p = p->next)
    {
        if (strcmp(p->name,name) == 0 && p->amount == amount)
        {
            // 显示当前信息
            printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t%d\t\t%s\n",p->year, p->month, p->day, p->amount, p->name, p->type, p->comment);
            printf("请确认是否修改此条记录(1 确认，0 取消)：");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // 获取新信息
                printf("请输入年份（当前：%d）：", p->year);
                scanf("%d", &p->year);
                printf("请输入月份（当前：%d）：", p->month);
                scanf("%d", &p->month);
                printf("请输入日期（当前：%d）：", p->day);
                scanf("%d", &p->day);
                printf("请输入金额（当前：%.1f）：", p->amount);
                scanf("%f", &p->amount);
                printf("请输入姓名（当前：%s）：", p->name);
                scanf("%s", p->name);
                printf("请输入类型(收入为1，支出为0)（当前：%d）：", p->type);
                scanf("%d", &p->type);
                printf("请输入事项（当前：%s）：", p->comment);
                scanf(" %s", p->comment);

                // 保存更改
                save();
                printf("修改成功！\n");
                return;
            }
            else
            {
                printf("取消修改。\n");
                return;
            }
        }
    }

    printf("未找到匹配记录。\n");
} 

int main()
{
	int n;
	welcome();
	read();
	do{
		n=menu();
		switch(n)
		{
			case 1:
				add();
				break;
			case 2:
				print_record(99,NULL);
				break;
			case 3:
				//search();
				search1();
				break;
			case 4:
				del();
				break;
			case 5:
				edit();
				break;
		}
	}while(n);
	return 0;
}
