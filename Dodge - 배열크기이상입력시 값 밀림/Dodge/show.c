#include "show.h"
//메뉴
//랭킹(입출력)시스템---->>>>@@@@@@@@@@@@@랭킹 기록할지 말지
//사운드(충돌시, 게임시작카운트)
//게임종료시 ■로 END

//@@@@@@@@@@@@@@@@@@위화살표 입력하면 전에 입력했던 값들이 나옴--오류(?)    , 입력버퍼가 남아서 다음 입력이 씹힘->\n을 받아서 버리는 scnaf추가

struct _rank rank[11] = { " ", 0 };		//랭킹구조체 선언, 초기화
int start, timeEnd, bulletTimeEnd;		//시간변수
int temp = 0;		//while문 반복횟수
char num2 = 0;	//개행문자 가져가는변수

void menu() {
	//게임이름 ■로 쓰기
	while (1) {
		int num = 0;		//메뉴선택
		printFrame();
		gotoxy(22, 13); printf("<<메뉴를 선택하세요>>");
		gotoxy(22, 14);  printf("1.  게임시작\n");	 
		gotoxy(22, 15);  printf("2.  랭킹\n");
		gotoxy(22, 16);  printf("3.  종료\n");
		gotoxy(44, 13);  
		
		scanf_s("%d", &num, sizeof(num));
		scanf_s("%c", &num2, sizeof(num2));
		
		printFrame();
		frameMove();
		system("cls");

		switch (num) {
		case 1:
			gameStart();
			frameMove();
			system("cls");
			break;
		case 2:
			printRank();
			system("cls");
			break;
		case 3:
			return;
		default:
			printf("잘못입력하셨습니다.");
			system("pause");
			break;
		}//switch
	}//while
}

void gameStart() {
	struct _bullet* bullet = malloc(sizeof(struct _bullet)*THE_NUMBER_OF_BULLETS);
	struct _bullet bu[THE_NUMBER_OF_BULLETS];
	*bullet = bu[THE_NUMBER_OF_BULLETS];

	printFrame();

	createValue(bullet); // user와 bullet값 초기화
	firstPrintUser();
	gotoxy(15, 10);  printf("<< 시작하려면 아무키나 누르세요 >>");
	system("pause>nul");
	gotoxy(15, 10); printf("                                  ");
	start = clock();		//게임시작시간

	while (1) {
		if (gameOver(bullet) == TRUE) {			//충돌하거나 모두 피하거나
			break;
		}

		bulletTimeEnd = clock();						//지금까지 흐른 시간으로 총알들 출발,이동
		int bulletTime = bulletTimeEnd - start;
		if (bulletTime % UPDATE_SPEED_OF_BULLET == 1) {	//UPDATE_SPEED_OF_BULLET 초마다
			updateBullets(bullet);
			printBullets(bullet);
		}//if

		updateUser();
	}//while
}

void printFrame() {
	for (int i = 2; i < 60; i++) {		//2~58
		gotoxy(i++, 0);
		printf("■");
	}
	for (int i = 1; i < 30; i++) {		//1~29
		gotoxy(0, i);
		printf("■");
	}
	for (int i = 2; i < 60; i++) {
		gotoxy(i++, 30);
		printf("■");
	}
	for (int i = 1; i < 30; i++) {
		gotoxy(60, i);
		printf("■");
	}
}

void firstPrintUser() {
	gotoxy(user.x, user.y); 	printf("★");
}

void printBullets(struct _bullet* bullet) {
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if (bullet[i].isPrint == 1) {
			switch (bullet[i].direction) {			//현재 총알위치로 이동하여 지우고 다시 프린트
			case 1:
				if (bullet[i].x == 2 || bullet[i].y == 29) {				//벽에 닿으면
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;										//총알 소멸
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");		//원래총알지우고
					bullet[i].x -= 2;
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");		//이동해서 프린트
					break;
				}
			case 2:
				if (bullet[i].y == 29) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 3:
				if (bullet[i].x == 58 || bullet[i].y == 29) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					bullet[i].y++;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 4:
				if (bullet[i].x == 2) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x -= 2;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 6:
				if (bullet[i].x == 58) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 7:
				if (bullet[i].x == 2 || bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x -= 2;
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 8:
				if (bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			case 9:
				if (bullet[i].x == 58 || bullet[i].y == 1) {
					gotoxy(bullet[i].x, bullet[i].y);
					printf("  ");
					bullet[i].isPrint = 2;
					break;
				}
				else {
					gotoxy(bullet[i].x, bullet[i].y); printf("  ");
					bullet[i].x += 2;
					bullet[i].y--;
					gotoxy(bullet[i].x, bullet[i].y); printf("●");
					break;
				}
			}//switch
		}//if
	}//for
}

void updateUser() {
	if (_kbhit()) {
		int key = _getch();

		switch (key) {
		case 224:
			key = _getch();
			if (key == 72) {	//상
				if (user.y == 1)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y--;
				}
			}
			else if (key == 80) { //하
				if (user.y == 29)
					user.y;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.y++;
				}
			}
			else if (key == 75) { //좌
				if (user.x == 2)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x -= 2;
				}
			}
			else if (key == 77) { //우
				if (user.x == 58)
					user.x;
				else {
					gotoxy(user.x, user.y); printf("  ");
					user.x += 2;
				}
			}
		}//switch

		gotoxy(user.x, user.y); printf("★");
	}//kbhit
}

void updateBullets(struct _bullet* bullet) {
	if (temp < THE_NUMBER_OF_BULLETS) {		//while문 한번 돌째마다 총알 하나 진행시키고 THE_NUMBER_OF_BULLETS와 temp가 같아지면(총알이 모두 진행하면) 더이상 총알 생성x
		bullet[temp].isPrint = 1;
		temp++;
	}
}

void createValue(struct _bullet* bullet) {
	user.x = 30;
	user.y = 15;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		bullet[i].isPrint = 0;

		bullet[i].startingLocation = rand() % 4; // 상하좌우 중 하나 배정
		switch (bullet[i].startingLocation) {
		case 0: // 상
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 중에서 짝수
			bullet[i].y = 1;
			bullet[i].direction = rand() % 3 + 1; // 방향 1, 2, 3중에 할당
			break;
		case 1: // 하
			bullet[i].x = (rand() % 29) * 2 + 2; // 2 ~ 58 중에서 짝수
			bullet[i].y = 29;
			bullet[i].direction = rand() % 3 + 7; // 방향 7, 8 ,9 중에 할당
			break;
		case 2: // 좌
			bullet[i].x = 2;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3; // 방향 3, 6, 9 중에 할당
			break;
		case 3: // 우
			bullet[i].x = 58;
			bullet[i].y = rand() % 29 + 1; // 1 ~ 29
			bullet[i].direction = (rand() % 3 + 1) * 3 - 2; // 방향 1, 4, 7 중에 할당
			break;
		}//switch
	}//for
}

int checkCrush(struct _bullet* bullet) {
	int count = 0; // x, y 겹치면 각각 +1해서 +2되면 완전 겹침

	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if ((user.x == bullet[i].x) && (bullet[i].isPrint == 1)) {
			count++;
		}
		if (user.y == bullet[i].y && (bullet[i].isPrint == 1)) {
			count++;
		}

		if (count == 2) {
			break;
		}
		else {
			count = 0;
		}
	}//for

	if (count == 2) {
		return 1;
	}
	else {
		return 0;
	}
}

int disappearBullets(struct _bullet* bullet) {
	int count = 0;

	for (int i = 0; i < THE_NUMBER_OF_BULLETS; i++) {
		if (bullet[i].isPrint == 2) {
			count++;
		}
	}

	if (count == THE_NUMBER_OF_BULLETS) {
		return 1;
	}
	else {
		return 0;
	}
}

boolean gameOver(struct _bullet* bullet) {
	if (checkCrush(bullet) == 1 || disappearBullets(bullet) == 1 ) { // user와 bullet들 중 하나라도 부딪히면 break;, bullet들을 모두 피하면 break;
		addRank();
		temp = 0;
		return TRUE;
	}
	return FALSE;
}

void addRank() {
	char save;
	timeEnd = clock();
	rank[10].end = timeEnd - start;
	while(1) {
		system("cls");
		printFrame();
		gotoxy(32, 10);  printf("GAME SET");
		gotoxy(12, 11);  printf("랭킹을 저장하시겠습니까? (Y/N)>>"); 	scanf_s("%c", &save, sizeof(save));
		scanf("%*c");
		if ( save == 'Y' || save=='y' ) {	
			gotoxy(12, 13);  printf("랭킹을 저장할 이니셜을 입력하세요");
			gotoxy(12, 14); printf("영어, 3글자까지 가능) >> ");
			scanf_s("%s", rank[10].name, sizeof(rank[10].name));
			if (strlen(rank[10].name) > 0 && strlen(rank[10].name) < 4) {
				gotoxy(20, 12); printf("랭킹을 저장하였습니다.");
				break;
			}
			else {
				gotoxy(20, 12); printf("3글자까지 가능합니다.");
			}
		}
		else if (save == 'N' || save == 'n') {
			gotoxy(20, 12);  printf("랭킹을 저장하지 않습니다.");
			rank[10].end = 0;
			break;
		}
		else {
			gotoxy(20, 13);  printf("y를 입력하셔야합니다.");		//다른문자 입력하면 다시랭킹저장 물어봄
		}
		delay(500);
	}
	rankSort();			//랭킹정렬
	inputRank();
}

void inputRank() {
	FILE *file_pointer;
	file_pointer = fopen("Ranking.txt", "wt");
	for (int i = 0; i < 10; i++) {
		if (rank[i].end == 0) {
			fprintf(file_pointer, "--- 0 \n");
		}
		else {
			fprintf(file_pointer, " %s % d \n", rank[i].name, rank[i].end);
		}
	}
	fclose(file_pointer);
}

void outputRank() {
	FILE *file_pointer;

	file_pointer = fopen("Ranking.txt", "rt");

	if (file_pointer == NULL) { //오류 or 파일 없을시 새로 생성 
		file_pointer = fopen("Ranking.txt", "a");
		fclose(file_pointer);
		return;
	}
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]); i++) {
		fscanf(file_pointer, "%s %d\n", &rank[i].name, &rank[i].end);
	}
	fclose(file_pointer);
}

void rankSort() {
	struct _rank temp = { NULL, 0 };
	for (int i = 0; i < sizeof(rank)/sizeof(rank[0]); i++) {				//버블소트
		for (int j = 0; j < sizeof(rank)/sizeof(rank[0])-i-1; j++) {
			if (rank[j].end < rank[j + 1].end) {
				temp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = temp;
			}
		}
	}
}


void printRank() {
	outputRank();
	rankSort();	
	gotoxy(2, 3);  printf("--------------------------랭킹----------------------------");
	for (int i = 0; i < sizeof(rank) / sizeof(rank[0]) - 1; i++) {
		if (rank[i].name == NULL)
			break;
		gotoxy(2, i + 4); printf("%2d위 %3s %6d\n", i+1, &rank[i].name, rank[i].end);
	}
	gotoxy(2, 14);  printf("---------------------------------------------------------\n");
	system("pause");
}







void frameMove() {
	int upY = 1;
	int downY = 29;
	int leftX = 2;
	int rightX = 58;
	for (int i = 0; i < 15; i++) {			//그냥 반복		0~62    0~31			가운데 30,15
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//위
			gotoxy(x++, upY);
			printf("■");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//왼쪽
			gotoxy(leftX, y);
			printf("■");
		}
		for (int x = (i * 2) + 4; x < 58 - (i * 2); x++) {		//아래
			gotoxy(x++, downY);
			printf("■");
		}
		for (int y = i + 2; y < 29 - i; y++) {		//오른쪽
			gotoxy(rightX, y);
			printf("■");
		}
		upY++;
		downY--;
		leftX += 2;
		rightX -= 2;
		delay(50);
	}//for
	upY -= 2;
	downY += 2;
	leftX -= 4;
	rightX += 4;
	for (int i = 0; i < 15; i++) {			//그냥 반복		0~62    0~31			가운데 30,15
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//위
			gotoxy(x++, upY);
			printf("   ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//왼쪽
			gotoxy(leftX, y);
			printf(" ");
		}
		for (int x = 30 - (i * 2); x < (i * 2) + 32; x++) {		//아래
			gotoxy(x++, downY);
			printf("  ");
		}
		for (int y = 15 - i; y < 16 + i; y++) {		//오른쪽
			gotoxy(rightX, y);
			printf("  ");
		}
		upY--;
		downY++;
		leftX -= 2;
		rightX += 2;
		delay(50);
	}//for
}

void delay(clock_t n)					//printframe 딜레이
{
	clock_t start = clock();
	while (clock() - start < n);
}

void flushBuffer(void) {
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}