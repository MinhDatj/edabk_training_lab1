#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
this program runs only using head instead of both tail and head
*/

typedef struct Person {
	char name[50];
	int id;	//STT trong dsach
	struct Person* next;
}Person;

FILE* fptr;
//const char* file = "D:\\Visual Studio Project\\C++\\LL_PracticeDemo\\Name.txt";
//const char* file = "D:\\C++ projects (devcpp)\\Projects\\LinkList\\userName.txt";
const char* file = "./name.txt";

#define SIZE 50
int i = 0;

Person* newName(const char* name) {
	Person* new_person = (Person*)malloc(sizeof(Person));

	if (new_person == NULL) {
		printf("Out of memory, fail to initialize!");
		return NULL;
	}
	else {
		strncpy(new_person->name, name, sizeof(new_person->name) - 1);
		new_person->name[sizeof(new_person->name) - 1] = '\0';
		new_person->id = ++i;
		new_person->next = NULL;
	}

	return new_person;
}

Person* insertatEnd(Person* head, const char* name) {
	Person* new_person = newName(name);

	if (new_person == NULL) {
		return head;
	}

	if (head == NULL) {
		return new_person;
	}
	else {
		Person* cur = head;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new_person;
	}
	return head;
}

void displayALLNames(Person* head) {
	Person* cur = head;

	if (cur == NULL) {
		printf("No names to display!\n");
	}

	while (cur != NULL) {
		printf("\t%d.  %s\n", cur->id, cur->name);

		cur = cur->next;
	}
}

int howManyNames(Person* head) {
	int length = 0;
	Person* cur = head;

	while (cur != NULL) {
		cur = cur->next;
		length++;
	}

	return length;
}

void findName(Person* head, const char* subname) {
	Person* cur = head;
	int flag = 0;

	while (cur != NULL) {
		const char* idx = strstr(cur->name, subname);

		if (idx != NULL) {
			printf("\t%d.  %s\n", cur->id, cur->name);
			flag = 1;
		}

		cur = cur->next;
	}

	if (!flag) {
		printf("\tThat name doesn't exist\n");
	}
}

Person* deleteName(Person* head, int key) {
	--i;
	if (head == NULL || key < 1 || key > howManyNames(head)) {
		printf("Enter index again (Click 2 to see everyone's index)!\n");
		return head;
	}

	if (key == 1) {
		Person* temp = head;
		head = head->next;
		free(temp);
		Person* cur = head;
		while (cur != NULL) {
			cur->id--;
			cur = cur->next;
		}
		return head;
	}

	Person* cur = head;
	for (int i = 1; i < key - 1 && cur->next != NULL; i++) {
		cur = cur->next;
	}

	if (cur == NULL || cur->next == NULL) {
		return head;
	}

	Person* temp = cur->next;
	cur->next = cur->next->next;
	free(temp);

	cur = cur->next;
	while (cur != NULL) {
		cur->id--;
		cur = cur->next;
	}

	return head;
}

void saveNametoFile(const char* filename, const char* name) {
	fptr = fopen(filename, "a");
	if (fptr == NULL) {
		perror("Error: ");
		return;
	}

	fputs(name, fptr);
	fputs("\n", fptr);
	fclose(fptr);
}

void resaveToFile(Person* head, const char* file_name) {
	fptr = fopen(file_name, "w");
    if (fptr == NULL) {
        perror("Error: ");
        return;
    }

	Person* cur = head;
	while (cur != NULL) {
		fputs(cur->name, fptr);
		fputs("\n", fptr);
		cur = cur->next;
	}
}

int readFromFile(Person** head, const char* filename) {
	char name[SIZE];

	fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("\tFile doesn't exist\n");
        printf("Creating file '%s' now...\n", filename);
        fptr = fopen(filename, "w"); 
        return 0;
    }

	while (fgets(name, SIZE, fptr)) {
		name[strcspn(name, "\n")] = 0;

		*head = insertatEnd(*head, name);
	}

	fclose(fptr);
	return 1;
}

void freeMem(Person* head) {
	Person* cur = head;
	while (cur != NULL) {
		Person* temp = cur;
		cur = cur->next;
		free(temp);
	}
}

int testingDemo1() {
	Person* head = NULL;
	char name[SIZE];
	char subName[SIZE];
	int choice = 1;
	char check;

	if (!readFromFile(&head, file)) {
		fprintf(stdout, "No names loaded to file");
	}

	printf("\n********* Main menu *********");
	printf("\n\tPress 1 to add a Person's name");
	printf("\n\tPress 2 to display all Persons's name");
	printf("\n\tPress 3 to see how many names are there");
	printf("\n\tPress 4 to search a name");
	printf("\n\tPress 5 to delete a name");
	printf("\n\tPress 6 to erase every names");
	printf("\n\tPress 7 to update from file");
	printf("\n\tPress 8 to show file destination");
	printf("\n\tPress any to exit");

	while (1) {
		printf("\nEnter your choice: ");
		if (scanf("%d", &choice) != 1) {
			printf("Please enter again.\n");
			while (getchar() != '\n');
			continue;
		}
		//scanf_s("%d", &choice);
		getchar();

		switch (choice) {
		case 0:
			printf("Exiting program.\n");
			freeMem(head);
			return 0;

		case 1:
			printf("Please enter: ");
			fgets(name, SIZE, stdin);
			name[strcspn(name, "\n")] = 0;

			head = insertatEnd(head, name);

			saveNametoFile(file, name);
			break;

		case 2:
			displayALLNames(head);
			break;

		case 3:
			printf("There are: %d names exist in the file\n", howManyNames(head));
			break;

		case 4:
			printf("Enter a name you want to search: ");
			fgets(subName, SIZE, stdin);
			subName[strcspn(subName, "\n")] = 0;
			findName(head, subName);
			break;

		case 5:
			printf("Enter that person's index: ");
			int idx;
			scanf("%d", &idx);
			head = deleteName(head, idx);
			resaveToFile(head, file);
			break;

		case 6:
			printf("Are you sure about that? (Y/N): ");
			//getchar();
			scanf("%c", &check);
			if (check == 'Y' || check == 'y') {
				fptr = fopen(file, "w");
                if (fptr != NULL) fclose(fptr);
				freeMem(head);
				head = NULL;
				i = 0;
				printf("All names erased!\n");
				break;
			}
			else {
				break;
			}

		case 7:
			freeMem(head);
			head = NULL;
			i = 0;
			readFromFile(&head, file);
			break;

		case 8:
            printf("The file that stores the names is located at: %s\n", file);
            break;

		default:
			printf("Please enter again!\n");
			break;
		}
	}

	freeMem(head);
}

int main() {
	testingDemo1();
	return 0;
}
