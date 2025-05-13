#include<stdio.h>
#include<stdlib.h>//malloc��ͷ�ļ�
#include<string.h> 
#define FILENAME "finance.txt" 
typedef struct faminfor{
	int year;//��
	int month;//�� 
	int day;//��
	float amount;//���
	char name[20];//ʹ����   
	int type;//״̬ 
	char comment[100];//���� 
	struct faminfor *next;//ָ����һ����ָ�� 
}family;
family *head=NULL;//ͷָ��

void save();//�������� 
void print_record();

//��ӭҳ
void welcome()
{
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t\t��ͥ�������ϵͳ\n");
	sleep(1);
} 

//ϵͳ���˵�
int menu()
{
	int n;
	system("cls");//����
	printf("\n\n\n\n\n");
	printf("\t\t====================================��ͥ�������ϵͳ====================================");
	printf("\n");
	printf("\t\t========================================================================================");
	printf("\t\t\n\t\t||                                        �˵�                                        ||\n");
	printf("\t\t||                                     1.������¼                                     ||\n");
	printf("\t\t||                                     2.��ʾ��¼                                     ||\n");
	printf("\t\t||                                     3.��ѯ��¼                                     ||\n");
	printf("\t\t||                                     4.ɾ����¼                                     ||\n");
	printf("\t\t||                                     5.�޸ļ�¼                                     ||\n");
	printf("\t\t||                                     0.�˳�ϵͳ                                     ||\n");
	printf("\t\t========================================================================================");
	printf("                                                                ��ѡ������Ҫ�Ĺ��� (0-5) :\n                            ");
	scanf("%d",&n);
	return n;
}

//�ļ���ȡ 
void  read()
{
	FILE *fp;
	family *p;
	//����a+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp=fopen(FILENAME,"a+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	fseek(fp,0,SEEK_END);//�ļ�ָ���ƶ���ĩβ 
	int size=ftell(fp);//�ƶ���ƫ���� 
	fseek(fp,0,SEEK_SET);//�ƶ���ͷ 
	//�����ǰ�ļ�ָ��fpƫ����С����ƫ��������ѭ�� 
	while(ftell(fp)<size)
	{
		p=(family *)malloc(sizeof(struct faminfor));//��̬�����ڴ�ռ�
		fread(p,sizeof(struct faminfor),1,fp);
		p->next=head;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
		head=p;//�½��Ϊͷ��� 
	}
}

//��ʾ
void show()
{
    family *p=head;
    if(!head)
    {
    	printf("��ǰû����Ϣ��\n");
    	return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
	printf("|======================================================================================================================|\n");
    while (p!=NULL)
	{
        printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
        p=p->next;//ָ���ƶ�����һ���ڵ� 
    }
    system("pause");//��ͣ 
} 

//¼��
void add()
{
	system("cls");//����
	family *p=NULL;
	p=(family *)malloc(sizeof(struct faminfor));//��̬�����ڴ�ռ�
	//��ʼ���·�����ڴ�ռ䣬���⡰�ࡱ����
	memset(p,0,sizeof(struct faminfor));
	printf("��������ݣ�"); 
	scanf("%d",&p->year);
	printf("�������·ݣ�"); 
	scanf("%d",&p->month);
	printf("���������ڣ�"); 
	scanf("%d",&p->day);
	printf("�������"); 
	scanf("%f",&p->amount);
	printf("������������"); 
	scanf("%s",p->name);
	printf("����������(����Ϊ1��֧��Ϊ0)��"); 
	scanf("%d",&p->type);
	printf("���������"); 
	scanf("%s",p->comment);
	p->next=head;//��һ��ʱheadΪ�գ��ڶ��ο�ʼΪ��һ��ͷ���ĵ�ַ 
	head=p;//�½��Ϊͷ��� 
	save();//���� 
}

//�����ļ�
void save()
{
	FILE *fp;
	family *p=NULL;
	//����wb+���ɶ�����д����׷�ӣ�����ļ��������򴴽�
	if((fp=fopen(FILENAME,"wb+"))==NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		system("pause");//��ͣ 
		return;
	}
	for(p=head;p!=NULL;p=p->next)
	{
		if(fwrite(p,sizeof(struct faminfor),1,fp)!=1)
		{
			printf("д��ʧ�ܣ�\n");
			return;
		}
	}
	printf("д��ɹ���\n");		
	system("pause");//��ͣ 
	fclose(fp);
} 
 
//����
void search()
{
	system("cls");//����
	family *p=NULL;
	int choice,type;
	char name[20];
	printf("1.��������2.�����ͣ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",name);
		for(p=head;p!=NULL;p=p->next)
		{
			//�ڶ��������Ƿ�Ϊ��һ�����Ӽ���ʵ��ģ������Ч�� 
			if(strstr(p->name,name)!=NULL)
			{
				printf("|======================================================================================================================|\n");
				printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			} 
		}
	system("pause");//��ͣ 
	return; 
	}
	if(choice==2)
	{
		printf("����������(����Ϊ1��֧��Ϊ0)��");
		scanf("%d",&type); 
		for(p=head;p!=NULL;p=p->next)
		{
			if(p->type==type)
			{
				printf("|======================================================================================================================|\n");
 				printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
				printf("|======================================================================================================================|\n");
				printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			}
		}
	system("pause");//��ͣ 
	return; 
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
	 
} 

//����
void search1()
{
	system("cls");//����
	family *p=NULL;
	int choice,type;
	char faminfor[20];
	printf("1.��������2.�����ͣ�"); 
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("������������");
		scanf("%s",faminfor);
		print_record(choice,faminfor);
		system("pause");//��ͣ 
		return;
	}
	if(choice==2)
	{
		printf("����������(����Ϊ1��֧��Ϊ0)��");
		scanf("%d",&type);
		//��������type��תΪ���飨�ɵڶ�������ȷ��������������Ϊ��ת���Ľ��� 
		itoa(type,faminfor,10);
		print_record(choice,faminfor);
		system("pause");//��ͣ 
		return;
	}
	else
	{
		printf("�������\n");
		system("pause");//��ͣ 
		return;
	} 
	 
}

//�����Ϣ�����ң��������У�����choiceΪ1��faminfor����������choiceΪ2��faminfor������
void print_record(int choice,char faminfor[20])
{
	family *p=head;
	float income=0.0;
	float outgoing=0.0;
	float balance=0.0;
    if(!head)
    { 
    	printf("��ǰû����Ϣ��\n");
		return;
	}
	system("cls");//����
	printf("|======================================================================================================================|\n");
	printf("|\t��\t|\t��\t|\t��\t|\t���\t  |\tʹ����\t   |   \t  ״̬\t   |\t   ����\t       |\n");
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
	printf("������: %.1f\n", income);
    printf("��֧��: %.1f\n", outgoing);
    printf("������(����-֧��): %.1f\n", income-outgoing);
	system("pause");//��ͣ 
}

//ɾ��
void del()
{
	family *p=head;
	family *prev=head;
	char name[20];//ʹ����
	int choice;
	float amount;//���
	system("cls");//���� 
	
	printf("������������");
	scanf("%s",name);
	printf("�������");
	scanf("%f",&amount);
	
	for(;p!=NULL;prev=p,p=p->next)
	{
		if(strcmp(p->name,name)==0 && p->amount==amount)
		{
			printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t  %s\t\t   %d\t\t   %s\t\t\n",p->year,p->month,p->day,p->amount,p->name,p->type,p->comment);
			printf("���Ƿ�Ҫɾ��(1ɾ����0��ɾ��)��");
			scanf("%d", &choice);
			if(choice==1)
			{
				if(p==head)
				{
					head=p->next;
					free(p);
					printf("ɾ���ɹ���\n");
					break;
				} 
				else
				{
					prev->next=p->next;
					free(p);
					printf("ɾ���ɹ���\n");
					save();
					break;	
				}
			}
			else
			{
				printf("��ɾ����\n");
				system("pause");
				return;
			}
		}
	}
	if(p==NULL)
	{
		printf("δ�ҵ���\n");
		system("pause");
		return;
	}
 } 

//�޸�
void edit()
{
    family *p = head;
    int choice; 
    char name[20]; // ʹ����
    float amount;  // ���
    system("cls"); // ���� 

    printf("������������");
    scanf("%s", name);
    printf("�������");
    scanf("%f", &amount);

    for (; p != NULL; p = p->next)
    {
        if (strcmp(p->name,name) == 0 && p->amount == amount)
        {
            // ��ʾ��ǰ��Ϣ
            printf("\t%d \t\t%d \t\t%d\t\t%.1f\t\t%s\t\t%d\t\t%s\n",p->year, p->month, p->day, p->amount, p->name, p->type, p->comment);
            printf("��ȷ���Ƿ��޸Ĵ�����¼(1 ȷ�ϣ�0 ȡ��)��");
            scanf("%d", &choice);
            if (choice == 1)
            {
                // ��ȡ����Ϣ
                printf("��������ݣ���ǰ��%d����", p->year);
                scanf("%d", &p->year);
                printf("�������·ݣ���ǰ��%d����", p->month);
                scanf("%d", &p->month);
                printf("���������ڣ���ǰ��%d����", p->day);
                scanf("%d", &p->day);
                printf("���������ǰ��%.1f����", p->amount);
                scanf("%f", &p->amount);
                printf("��������������ǰ��%s����", p->name);
                scanf("%s", p->name);
                printf("����������(����Ϊ1��֧��Ϊ0)����ǰ��%d����", p->type);
                scanf("%d", &p->type);
                printf("�����������ǰ��%s����", p->comment);
                scanf(" %s", p->comment);

                // �������
                save();
                printf("�޸ĳɹ���\n");
                return;
            }
            else
            {
                printf("ȡ���޸ġ�\n");
                return;
            }
        }
    }

    printf("δ�ҵ�ƥ���¼��\n");
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
