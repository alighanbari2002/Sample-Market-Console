#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Good
{
	char name[20];
	int price;
	int count;
	struct Good* next;
};
struct User
{
	char username[20];
	int password;
	int money;
	int prize;
	struct User* next;
};
struct sabad
{
	char esm[20];
	char goodname[20];
	int goodprice;
	int goodcount;
	struct sabad* next;
};
typedef struct Good good;
typedef struct User user;
typedef struct sabad cart;

good* creat_goods_linkedlist(FILE* Goods, good* head);
char* command(void);
user* adduser(user* head, char user_name[], int pass_word, int prize);
user* creat_users_linkedlist(FILE* Users, user* head);
user* user_search(user* head, char data[]);
good* good_search(good* head, char data[]);
int searchleastprice(good* head);
cart* kala_search(cart* head, char data[], char name[]);
cart* addkala(cart* head, char name[], char kala[], int price, int count);
good* remove_good(good* head, char data[]);
void savegoods(FILE* NewGoods, good* head);
void saveusers(FILE* NewUsers, user* head);
int checkcart(cart* head, char data[]);
void display_cart(cart* head, char data[]);
void display_linkedlist(good* head);
void printerror(void);

int main()
{
	FILE* Goods = fopen("goods_db.txt", "r");
	FILE* NewGoods = fopen("new_goods.txt", "w");
	FILE* Users = fopen("users.txt", "r");
	FILE* NewUsers = fopen("newusers.txt", "w");
	system("color 0A");
	if (Goods == NULL)
	{
		printf("goods's file doesn't exist.\n");
	}
	if (Users == NULL)
	{
		printf("user's file doesn't exist.\n");
	}
	good* HEADgoods = NULL;
	user* HEADusers = NULL;
	cart* HEADcart = NULL;
	HEADgoods = creat_goods_linkedlist(Goods, HEADgoods);
	HEADusers = creat_users_linkedlist(Users, HEADusers);
	while (1)
	{
		int password = 0, money = 0, count = 0, i = 0, l = 0, flag = 0, least = 0, nesab = 0, temporary = 0;
		char* username, * name, * temp, * tmp, * one, * two;
		good* whom;//for goods
		user* who;// for users
		one = command();
		if ((strlen(one) == 0) || (strcmp(one, "exit") == 0))
		{
			if (strlen(one) == 0)
				printf("805\n");
			else
				printf("800\n");
			free(one);
			break;
		}
		else if ((strcmp(one, "buy") == 0) || (strcmp(one, "deposit") == 0))
		{
			while (getchar() != '\n');
			printf("801\n");
		}
		else if (strcmp(one, "show_goods") == 0)
		{
			display_linkedlist(HEADgoods);
		}
		else if (strcmp(one, "help") == 0)
		{
			printerror();
		}
		else if (strcmp(one, "save") == 0)
		{
			savegoods(NewGoods, HEADgoods);
			saveusers(NewUsers, HEADusers);
			printf("800\n");
		}
		else if (strcmp(one, "signup") == 0)
		{
			password = 0;
			username = command();
			temp = command();
			l = strlen(temp);
			for (i = 0; i < l; i++)
			{
				temporary = (int)temp[i];
				if ((temporary >= 48) && (temporary <= 57))
					password = password * 10 + temporary - 48;
				else
				{
					printf("804\n");
					password = 0;
					break;
				}
			}
			if (password == 0)
				continue;
			if (user_search(HEADusers, username) != NULL)//az ghabl sabt nam karde bashe
			{
				printf("802\n");
				continue;
			}
			HEADusers = adduser(HEADusers, username, password, 0);
			printf("800\n");
		}
		else if (strcmp(one, "login") == 0)///log in
		{
			username = command();
			temp = command();
			l = strlen(temp);
			for (i = 0; i < l; i++)
				password = password * 10 + (int)temp[i] - 48;
			if (user_search(HEADusers, username) == NULL)
			{

				printf("803\n");
				continue;
			}
			else
			{
				who = user_search(HEADusers, username);
				if (who->password != password)
				{
					printf("804\n");
					continue;
				}
			}
			printf("800\n");
			while (1)
			{
				money = 0;
				one = command();
				if ((strlen(one) == 0) || (strcmp(one, "exit") == 0))
				{
					if (strlen(one) == 0)
						printf("805\n");
					else
						printf("800\n");
					flag = 2;
					break;
				}
				else if (strcmp(one, "save") == 0)
				{
					savegoods(NewGoods, HEADgoods);
					saveusers(NewUsers, HEADusers);
					printf("800\n");
				}
				else if (strcmp(one, "logout") == 0)
				{
					printf("800\n");
					flag = 1;
					break;
				}
				else if (strcmp(one, "help") == 0)
				{
					printerror();
				}
				else if (strcmp(one, "my_bonus") == 0)
				{
					if (who->prize == 0)
					{
						printf("812\n");
					}
					else
					{
						printf("%d\n", who->prize);
					}
				}
				else if (strcmp(one, "convert_bonus") == 0)
				{
					least = searchleastprice(HEADgoods);
					if (least <= who->prize)
					{
						who->money += who->prize;
						who->prize = 0;
						printf("814\n");
					}
					else
						printf("813\n");
				}
				else if (strcmp(one, "show_cart") == 0)
				{
					nesab = checkcart(HEADcart, who->username);
					if (nesab == 0)
						printf("811\n");
					else
						display_cart(HEADcart, who->username);
				}
				else if (strcmp(one, "deposit") == 0)
				{
					two = command();
					l = strlen(two);
					for (i = 0; i < l; i++)
					{
						temporary = (int)two[i];
						if ((temporary >= 48) && (temporary <= 57))
							money = money * 10 + temporary - 48;
						else
						{
							printf("801\n");
							money = 0;
							break;
						}
					}
					if (money == 0)
						continue;
					if (money < 0)
					{
						printf("806\n");
						continue;
					}
					who->money += money;
					printf("800\n");
				}
				else if (strcmp(one, "credit") == 0)
				{
					printf("%d\n", who->money);
				}
				else if (strcmp(one, "show_goods") == 0)
				{
					display_linkedlist(HEADgoods);
				}
				else if (strcmp(one, "buy") == 0)
				{
					count = 0;
					tmp = command();
					temp = command();
					l = strlen(temp);
					for (i = 0; i < l; i++)
						count = count * 10 + (int)temp[i] - 48;
					l = strlen(tmp);
					name = (char*)malloc((l + 1) * sizeof(char));
					strcpy(name, tmp);
					strcat(name, ",");
					if (count < 1)
					{
						printf("806\n");
						continue;
					}
					else if (good_search(HEADgoods, name) == NULL)
					{
						printf("807\n");
						continue;
					}
					whom = good_search(HEADgoods, name);
					if (whom->count < count)
					{
						printf("808\n");
						continue;
					}
					else if ((count * whom->price) > who->money)
					{
						printf("809\n");
						continue;
					}
					else
					{
						who->prize = who->prize + (count * whom->price / 10);
						whom->count -= count;
						who->money = who->money - (count * whom->price);
						HEADcart = addkala(HEADcart, who->username, whom->name, whom->price, count);
						if (whom->count == 0)
							HEADgoods = remove_good(HEADgoods, name);
						printf("810\n");
					}
				}
				else if ((strcmp(one, "signup") == 0) || (strcmp(one, "login") == 0))
				{
					while (getchar() != '\n');
					printf("801\n");
				}
				else
				{
					printf("801\n");
					continue;
				}
			}
			if (flag == 2)
				break;
			else if (flag == 1)
				continue;
		}
		else
		{
			printf("801\n");
		}
	}
	fclose(Goods);
	fclose(NewGoods);
	fclose(Users);
	fclose(NewUsers);
	return 0;
}

good* creat_goods_linkedlist(FILE* Goods, good* head)
{
	int i = 0;
	good* temp = NULL;
	good* p = NULL;
	while (!feof(Goods))
	{
		temp = (good*)malloc(sizeof(good));
		fscanf(Goods, "%s %d, %d", temp->name, &(temp->price), &(temp->count));
		fgetc(Goods);
		temp->next = NULL;

		if (head == NULL)
			head = temp;
		else
		{
			p = head;
			while (p->next != NULL)
				p = p->next;
			p->next = temp;
		}
	}
	return head;
}


char* command(void)
{
	char* input = (char*)malloc(sizeof(char));
	int n = 0;
	while (1)
	{
		char* tmp;
		char c;
		int flag = 0;
		while (1)
		{
			c = getchar();
			if ((c == ' ') || (c == '\n'))
			{
				flag = 1;
				break;
			}
			input[n] = c;
			if (input != NULL)
			{
				tmp = (char*)realloc(input, (n + 2));
				if (tmp != NULL)
				{
					input = tmp;
				}
			}
			n++;
		}
		input[n] = '\0';
		if (flag == 1)
			break;
	}
	return input;
}

user* adduser(user* head, char user_name[], int pass_word, int prize)
{
	user* new_user = (user*)malloc(sizeof(user));
	user* last_user = head;
	strcpy(new_user->username, user_name);
	new_user->password = pass_word;
	new_user->money = 0;
	new_user->prize = prize;
	new_user->next = NULL;
	if (last_user == NULL)
	{
		head = new_user;
		return head;
	}
	while (last_user->next != NULL)
	{
		last_user = last_user->next;
	}
	last_user->next = new_user;
	return head;
}

user* creat_users_linkedlist(FILE* Users, user* head)
{
	while (!feof(Users))
	{
		int password = 0, prize = 0, l = 0;
		char tmp[20];
		fscanf(Users, "%s %d, %d", tmp, &(password), &(prize));
		fgetc(Users);
		l = strlen(tmp);
		char* temp = (char*)malloc(l * sizeof(char));
		strncpy(temp, tmp, (l - 1));
		temp[l - 1] = '\0';
		head = adduser(head, temp, password, prize);
		free(temp);
	}
	return head;
}

user* user_search(user* head, char data[])
{
	user* current = head;
	if (head == NULL)
		return NULL;
	if (current == NULL)
		return NULL;
	while ((strcmp(current->username, data)) != 0)
	{
		if ((current->next) == NULL)
			return NULL;
		else
			current = current->next;
	}
	return current;
}

good* good_search(good* head, char data[])
{
	good* current = head;
	if (head == NULL)
		return NULL;
	if (current == NULL)
		return NULL;
	while ((strcmp(current->name, data)) != 0)
	{
		if ((current->next) == NULL)
			return NULL;
		else
			current = current->next;
	}
	return current;
}

int searchleastprice(good* head)
{
	int check;
	good* current = head;
	check = head->price;
	while (current != NULL)
	{
		if ((current->price) < check)
			check = current->price;
		current = current->next;
	}
	return check;
}

cart* kala_search(cart* head, char data[], char name[])
{
	cart* current = head;
	if (head == NULL)
		return NULL;
	if (current == NULL)
		return NULL;
	while (((strcmp(current->goodname, data)) != 0) || ((strcmp(current->esm, name)) != 0))
	{
		if ((current->next) == NULL)
			return NULL;
		else
			current = current->next;
	}
	return current;
}

cart* addkala(cart* head, char name[], char kala[], int price, int count)
{
	cart* x = kala_search(head, kala, name);
	if (x != NULL)
	{
		x->goodcount += count;
		return head;
	}
	free(x);
	cart* new_kala = (cart*)malloc(sizeof(cart));
	cart* last_kala = head;
	strcpy(new_kala->esm, name);
	strcpy(new_kala->goodname, kala);
	new_kala->goodprice = price;
	new_kala->goodcount = count;
	new_kala->next = NULL;
	if (last_kala == NULL)
	{
		head = new_kala;
		return head;
	}
	while (last_kala->next != NULL)
	{
		last_kala = last_kala->next;
	}
	last_kala->next = new_kala;
	return head;
}

good* remove_good(good* head, char data[])
{
	if (strcmp(head->name, data) == 0)
	{
		if (head->next != NULL)
		{
			head = head->next;
			return head;
		}
		else
		{
			head = NULL;
			return head;
		}
	}
	else if ((strcmp(head->name, data) != 0) && (head->next == NULL))
		return head;

	good* current = head;
	good* prev = current;

	while ((current->next != NULL) && (strcmp(current->name, data) != 0))
	{
		prev = current;
		current = current->next;
	}
	if (strcmp(current->name, data) == 0)
	{
		if (current->next == NULL)
			prev->next = NULL;
		else
			prev->next = prev->next->next;
		free(current);
	}
	return head;
}

void savegoods(FILE* NewGoods, good* head)
{
	good* p = head;
	while (p != NULL)
	{
		fprintf(NewGoods, "%s %d, %d", p->name, p->price, p->count);
		if (p->next != NULL)
			fprintf(NewGoods, "\n");
		p = p->next;
	}
}

void saveusers(FILE* NewUsers, user* head)
{
	user* p = head;
	while (p != NULL)
	{
		fprintf(NewUsers, "%s %d, %d", p->username, p->password, p->prize);
		if (p->next != NULL)
			fprintf(NewUsers, "\n");
		p = p->next;
	}
}

int checkcart(cart* head, char data[])
{
	int i = 0;
	cart* p = head;
	while (p != NULL)
	{
		if (strcmp(p->esm, data) == 0)
			i++;
		p = p->next;
	}
	return i;
}

void display_cart(cart* head, char name[])
{
	cart* p = head;
	while (p != NULL)
	{
		if (strcmp(p->esm, name) == 0)
			printf("%s %d, %d\n", p->goodname, p->goodprice, p->goodcount);
		p = p->next;
	}
}

void display_linkedlist(good* head)
{
	good* p = head;
	while (p != NULL)
	{
		printf("%s %d, %d\n", p->name, p->price, p->count);
		p = p->next;
	}
}

void printerror(void)
{
	printf("800 -> Successful\n");
	printf("801 -> Command Not found OR Invalid Command\n");
	printf("802 -> Username already Exists\n");
	printf("803 -> User not found\n");
	printf("804 -> Wrong password\n");
	printf("805 -> Unexpected Error\n");
	printf("806 -> Invalid input\n");
	printf("807 -> Good not found\n");
	printf("808 -> Not enough good\n");
	printf("809 -> You cannot afford this good\n");
	printf("810 -> Bought successful\n");
	printf("811 -> Cart is Empty\n");
	printf("812 -> Bonus is zero\n");
	printf("813 -> Convert Unsuccessful\n");
	printf("814 -> Convert Successful\n");
}