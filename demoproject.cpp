#include<stdio.h>
struct customerRecords{
	char name[100];
	int id;
	char order[100];
	int qty;
	char date[100];
	int status;
}e1[100];

FILE *fp;

int createId();
void inputOrder(int);
void viewDetails();
void moreOptions();
void viewPendingOrders();
void viewCanceledOrders();

void front()
{	
	printf("--------------BAKERY MANAGEMENT SYSTEM--------------\n\n");
	
	label:
	printf("1. Create an ID\n");
	printf("2. Have an ID ; Place an order\n");
	printf("3. View order details\n");
	printf("4. More options\n");
	printf("5. Exit\n");
	
	int ch;
	printf("Enter your choice: ");
	scanf("%d",&ch);
	
	if(ch==1){
		printf("Your details will be assigned with ID number %d.\n\n",createId());
		goto label;
	}
	else if(ch==2){
		inputOrder(createId());
		goto label;
	}
	else if(ch==3){
		viewDetails();
		goto label;
	}
	else if(ch==4){
		moreOptions();
		goto label;
	}else if(ch==5){
		return;
	}
	else{
		printf("\nInvalid choice.\n\n");
		goto label;
	}
}

int createId()
{
	int i=0;
	int large=0;
	fp=fopen("order.txt","r");
	if(fp == NULL){
 		large=-1;
	}else{
		//reading data from the file
		while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
			if(large<e1[i].id){
				large=e1[i].id;
			}
			i++;
		}
	}
	fclose(fp);
	return large+1;
}

void inputOrder(int idx)
{
	fp=fopen("order.txt","a");
	
	printf("Enter your id: ");
	scanf("%d",&e1[idx].id);
	printf("Enter your name (name_surname): ");
	scanf("%s",e1[idx].name);
	printf("Enter your order (order_name): ");
	scanf("%s",e1[idx].order);
	printf("Enter the quantity of your order: ");
	scanf("%d",&e1[idx].qty);
	printf("Enter the date of order (DD/MM/YY): ");
	scanf("%s",e1[idx].date);
	
	printf("\n1. Continue\n2. Cancel Order\n");
	int ch;
	label:
	printf("Enter your choice: ");
	scanf("%d",&ch);
	
	switch(ch){
		case 1:
			e1[idx].status=1; // 1 for pending order
			break;
		case 2:
			e1[idx].status=0; // 0 for canceled order
			break;
		default:
			printf("\nInvalid choice.\n");			
			goto label;
	}
	
	//writing data into the file
	fprintf(fp,"%d\t%s\t\t%s\t\t%d\t\t%s\t%d\n",e1[idx].id,e1[idx].name,e1[idx].order,e1[idx].qty,e1[idx].date,e1[idx].status);
	if(e1[idx].status==0){
		printf("\nYour order has been canceled.\n\n");
	}else{
		printf("\nYour order has been placed.\n\n");	
	}
	
	fclose(fp);
	return;
}

void viewDetails()
{
	int ID;
	printf("Enter your ID: ");
	scanf("%d",&ID);
	
	fp=fopen("order.txt","r");
	if(fp==NULL){
		printf("\nNo Such ID exists.\n\n");
		fclose(fp);
		return;
	}
	int i=0;
	int large=0;
	while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
		if(large<e1[i].id){
				large=e1[i].id;
		}
		i++;
	}
	fclose(fp);
	
	if(ID>large||ID<0){
		printf("\nNo such ID exists.\n");
	}else{
		fp=fopen("order.txt","r");
		int i=0;
		printf("\nID\tName\t\t\tOrder\t\t\tQuantity\tDate\t\tStatus\n\n");
		
		//reading data from the file
		while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
			if(e1[i].id==ID){
				if(e1[i].status==1){
					printf("%d\t%s\t\t%s\t\t%d\t\t%s\tPending\n",e1[i].id,e1[i].name,e1[i].order,e1[i].qty,e1[i].date);	
				}else{
					printf("%d\t%s\t\t%s\t\t%d\t\t%s\tCanceled\n",e1[i].id,e1[i].name,e1[i].order,e1[i].qty,e1[i].date);
				}
			}
			i++;
		}
		
		fclose(fp);
	}
	
	printf("\n");
	return;
}

void viewPendingOrders()
{
	fp=fopen("order.txt","r");
	
	if(fp==NULL){
		printf("\nNo record exists.\n\n");
		fclose(fp);
		return;
	}
	
	int i=0,count=0;
	while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
		if(e1[i].status==1){
			count++;
		}
		i++;	
	}
	fclose(fp);
	
	if(count==0){
		printf("\nNo record exists.\n\n");
		return;
	}
	
	fp=fopen("order.txt","r");
	printf("\nID\tName\t\t\tOrder\t\t\tQuantity\tDate\n\n");
	
	i=0;
	while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
		if(e1[i].status==1){
			printf("%d\t%s\t\t%s\t\t%d\t\t%s\n",e1[i].id,e1[i].name,e1[i].order,e1[i].qty,e1[i].date);
		}
		i++;	
	}
	printf("\n");
	fclose(fp);
	return;
}

void viewCanceledOrders()
{
	fp=fopen("order.txt","r");
	
	if(fp==NULL){
		printf("\nNo record exists.\n\n");
		fclose(fp);
		return;
	}
	
	int i=0,count=0;
	while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
		if(e1[i].status==0){
			count++;
		}
		i++;	
	}
	fclose(fp);
	
	if(count==0){
		printf("\nNo record exists.\n\n");
		return;
	}
	
	fp=fopen("order.txt","r");
	printf("\nID\tName\t\t\tOrder\t\t\tQuantity\tDate\n\n");
	
	i=0;
	while(fscanf(fp,"%d%s%s%d%s%d",&e1[i].id,e1[i].name,e1[i].order,&e1[i].qty,e1[i].date,&e1[i].status)!=EOF){
		if(e1[i].status==0){
			printf("%d\t%s\t\t%s\t\t%d\t\t%s\n",e1[i].id,e1[i].name,e1[i].order,e1[i].qty,e1[i].date);
		}
		i++;	
	}
	printf("\n");
	fclose(fp);
	return;
}

void moreOptions()
{
	printf("\n1. View pending orders");
	printf("\n2. View canceled orders\n\n");
	
	int ch;
	label:
	printf("Enter your choice: ");
	scanf("%d",&ch);
	
	switch(ch){
		case 1:
			viewPendingOrders(); // 1 for pending orders
			break;
		case 2:
			viewCanceledOrders(); // 2 for canceled orders
			break;
		default:
			printf("\nInvalid choice.\n");
			goto label;
	}
	return;
}

int main()
{
	front();
	return 0;
}
