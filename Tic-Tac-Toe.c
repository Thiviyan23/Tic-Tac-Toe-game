#include<stdio.h>
     
char arr[10]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
 
void creatingboard() {

    printf("\n\nTic-Tac-Toe\n\n");
    printf("player 1 (X) -- player 2 (O)\n");

    printf("     |     |     \n");
    printf(" %c   | %c   | %c \n", arr[1],arr[2],arr[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf(" %c   | %c   | %c \n", arr[4],arr[5],arr[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf(" %c   | %c   | %c \n", arr[7],arr[8],arr[9]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
}
void marking(int choice, char mark) {

 if(choice==1 && arr[1]=='1')       //choosing the boxes
      arr[1] = mark;
    else if(choice==2 && arr[2]=='2')
    arr[2] = mark;
else if(choice==3 && arr[3]=='3')
    arr[3] = mark;
else if(choice==4 && arr[4]=='4')
    arr[4] = mark;
else if(choice==5 && arr[5]=='5')
    arr[5] = mark;
else if(choice==6 && arr[6]=='6')
    arr[6] = mark;
else if(choice==7 && arr[7]=='7')
    arr[7] = mark;
else if(choice==8 && arr[8]=='8')
    arr[8] = mark;
else if(choice==9 && arr[9]=='9')
    arr[9] = mark;
else
    printf("invalid choice\n");

}


int checkwin() {

//horizontal matching
if(arr[1]==arr[2] && arr[2]==arr[3])
return 1;
else if(arr[4]==arr[5] && arr[5]==arr[6])
return 1;
else if(arr[7]==arr[8] && arr[8]==arr[9])
return 1;
//
//vertical matching
else if(arr[1]==arr[4] && arr[4]==arr[7])
return 1;
else if(arr[2]==arr[5] && arr[5]==arr[8])
return 1;
else if(arr[3]==arr[6] && arr[6]==arr[9])
return 1;
//
//diagonal matching
else if(arr[1]==arr[5] && arr[5]==arr[9])
return 1;
else if(arr[3]==arr[5] && arr[5]==arr[9])
return 1;
//
//draw condition
else if(arr[1]!='1' && arr[2]!='2' && arr[2]!='2'&& arr[3]!='3'&& arr[4]!='4'&& arr[5]!='5'&& arr[6]!='6'&& arr[7]!='7'&& arr[8]!='8'&& arr[9]!='9')
return 0;

return -1;
}

int main(){
 int choice, player=1,i;
    char mark;
    do{
        creatingboard();
        player = (player %2)? 1: 2;
        
        printf("player %d: Select a number between 1 to 9: ",player);
        scanf("%d", &choice);

        mark = (player==1)? 'X': 'O';
        marking(choice, mark);

        i =checkwin();
        player++;


    }
     while(i==-1);

     creatingboard();
     if(i==1)
        printf("Player %d won the game",--player);
     else
        printf("<=======Draw=======>");
    return 0;
}




