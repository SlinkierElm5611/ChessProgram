/*
 * Made By Stefan Balta
 * If you would like to use this code, please feel free to granted you give the original creator credit where it is needed
 */
#include <iostream>
#include <thread>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
int pieces [32][8];
int const x=0;
int const y=1;
int const colour=2;
int const pieceid=3;
int const dead=4;
int const peicemovecounter=5;
int const piecetype=6;
bool coloursturn;
string actualcharactetest;
string firstcharacter;
string secondcharacter;
bool castle;
int rooklocation;
int newrooklocation;
int movecounter=0;
int blackqueen[7];
int blackking[7];
int blackbishop1[7];
int blackbishop2[7];
int blackknight1[7];
int blackknight2[7];
int blackrook1[7];
int blackrook2[7];
int blackpawn1[7];
int blackpawn2[7];
int blackpawn3[7];
int blackpawn4[7];
int blackpawn5[7];
int blackpawn6[7];
int blackpawn7[7];
int blackpawn8[7];
int whitequeen[7];
int whiteking[7];
int whitebishop1[7];
int whitebishop2[7];
int whiteknight1[7];
int whiteknight2[7];
int whiterook1[7];
int whiterook2[7];
int whitepawn1[7];
int whitepawn2[7];
int whitepawn3[7];
int whitepawn4[7];
int whitepawn5[7];
int whitepawn6[7];
int whitepawn7[7];
int whitepawn8[7];
struct boardinfoforbacktracking{
    int piecethatwasjustmoved;
    int piecethatwaskilled;
    int board[9][9];
    bool turn;
    int turncount;
    int wherepiecemoved;
    int wherepiecethatwasmovedmovedfrom;
};
struct allpossiblemoves{
    int peicelocation;
    int desiredlocation;
};
struct checkmatecheckerdata{
    int pieces[32][7];
};
checkmatecheckerdata currentstate{};
stack <allpossiblemoves> allmovesallowedincurrentstate;
allpossiblemoves usedtosenddatatostack{};
boardinfoforbacktracking backtrackingdata{};
void resetboard(){
    whitequeen[x]=4;
    whitequeen[y]=1;
    whitequeen[colour]=1;
    whitequeen[pieceid]=1;
    whitequeen[dead]=0;
    whitequeen[peicemovecounter]=0;
    blackqueen[x]=4;
    blackqueen[y]=8;
    blackqueen[colour]=0;
    blackqueen[pieceid]=2;
    blackqueen[dead]=0;
    blackqueen[peicemovecounter]=0;
    whiteking[x]=5;
    whiteking[y]=1;
    whiteking[colour]=1;
    whiteking[pieceid]=15;
    whiteking[dead]=0;
    whiteking[peicemovecounter]=0;
    blackking[x]=5;
    blackking[y]=8;
    blackking[colour]=0;
    blackking[pieceid]=16;
    blackking[dead]=0;
    blackking[peicemovecounter]=0;
    whitebishop1[x]=3;
    whitebishop1[y]=1;
    whitebishop1[colour]=1;
    whitebishop1[pieceid]=3;
    whitebishop1[dead]=0;
    whitebishop1[peicemovecounter]=0;
    whitebishop2[x]=6;
    whitebishop2[y]=1;
    whitebishop2[colour]=1;
    whitebishop2[pieceid]=4;
    whitebishop2[dead]=0;
    whitebishop2[peicemovecounter]=0;
    blackbishop1[x]=3;
    blackbishop1[y]=8;
    blackbishop1[colour]=0;
    blackbishop1[pieceid]=5;
    blackbishop1[dead]=0;
    blackbishop1[peicemovecounter]=0;
    blackbishop2[x]=6;
    blackbishop2[y]=8;
    blackbishop2[colour]=0;
    blackbishop2[pieceid]=6;
    blackbishop2[dead]=0;
    blackbishop2[peicemovecounter]=0;
    whiteknight1[x]=2;
    whiteknight1[y]=1;
    whiteknight1[colour]=1;
    whiteknight1[pieceid]=11;
    whiteknight1[dead]=0;
    whiteknight1[peicemovecounter]=0;
    whiteknight2[x]=7;
    whiteknight2[y]=1;
    whiteknight2[colour]=1;
    whiteknight2[pieceid]=12;
    whiteknight2[dead]=0;
    whiteknight2[peicemovecounter]=0;
    blackknight1[x]=2;
    blackknight1[y]=8;
    blackknight1[colour]=0;
    blackknight1[pieceid]=13;
    blackknight1[dead]=0;
    blackknight1[peicemovecounter]=0;
    blackknight2[x]=7;
    blackknight2[y]=8;
    blackknight2[colour]=0;
    blackknight2[pieceid]=14;
    blackknight2[dead]=0;
    blackknight2[peicemovecounter]=0;
    whiterook1[x]=1;
    whiterook1[y]=1;
    whiterook1[colour]=1;
    whiterook1[pieceid]=7;
    whiterook1[dead]=0;
    whiterook1[peicemovecounter]=0;
    whiterook2[x]=8;
    whiterook2[y]=1;
    whiterook2[colour]=1;
    whiterook2[pieceid]=8;
    whiterook2[dead]=0;
    whiterook2[peicemovecounter]=0;
    blackrook1[x]=1;
    blackrook1[y]=8;
    blackrook1[colour]=0;
    blackrook1[pieceid]=9;
    blackrook1[dead]=0;
    blackrook1[peicemovecounter]=0;
    blackrook2[x]=8;
    blackrook2[y]=8;
    blackrook2[colour]=0;
    blackrook2[pieceid]=10;
    blackrook2[dead]=0;
    blackrook2[peicemovecounter]=0;
    whitepawn1[x]=1;
    whitepawn1[y]=2;
    whitepawn1[colour]=1;
    whitepawn1[pieceid]=17;
    whitepawn1[dead]=0;
    whitepawn1[peicemovecounter]=0;
    whitepawn2[x]=2;
    whitepawn2[y]=2;
    whitepawn2[colour]=1;
    whitepawn2[pieceid]=18;
    whitepawn2[dead]=0;
    whitepawn2[peicemovecounter]=0;
    whitepawn3[x]=3;
    whitepawn3[y]=2;
    whitepawn3[colour]=1;
    whitepawn3[pieceid]=19;
    whitepawn3[dead]=0;
    whitepawn3[peicemovecounter]=0;
    whitepawn4[x]=4;
    whitepawn4[y]=2;
    whitepawn4[colour]=1;
    whitepawn4[pieceid]=20;
    whitepawn4[dead]=0;
    whitepawn4[peicemovecounter]=0;
    whitepawn5[x]=5;
    whitepawn5[y]=2;
    whitepawn5[colour]=1;
    whitepawn5[pieceid]=21;
    whitepawn5[dead]=0;
    whitepawn5[peicemovecounter]=0;
    whitepawn6[x]=6;
    whitepawn6[y]=2;
    whitepawn6[colour]=1;
    whitepawn6[pieceid]=22;
    whitepawn6[dead]=0;
    whitepawn6[peicemovecounter]=0;
    whitepawn7[x]=7;
    whitepawn7[y]=2;
    whitepawn7[colour]=1;
    whitepawn7[pieceid]=23;
    whitepawn7[dead]=0;
    whitepawn7[peicemovecounter]=0;
    whitepawn8[x]=8;
    whitepawn8[y]=2;
    whitepawn8[colour]=1;
    whitepawn8[pieceid]=24;
    whitepawn8[dead]=0;
    whitepawn8[peicemovecounter]=0;
    blackpawn1[x]=1;
    blackpawn1[y]=7;
    blackpawn1[colour]=0;
    blackpawn1[pieceid]=25;
    blackpawn1[dead]=0;
    blackpawn1[peicemovecounter]=0;
    blackpawn2[x]=2;
    blackpawn2[y]=7;
    blackpawn2[colour]=0;
    blackpawn2[pieceid]=26;
    blackpawn2[dead]=0;
    blackpawn2[peicemovecounter]=0;
    blackpawn3[x]=3;
    blackpawn3[y]=7;
    blackpawn3[colour]=0;
    blackpawn3[pieceid]=27;
    blackpawn3[dead]=0;
    blackpawn3[peicemovecounter]=0;
    blackpawn4[x]=4;
    blackpawn4[y]=7;
    blackpawn4[colour]=0;
    blackpawn4[pieceid]=28;
    blackpawn4[dead]=0;
    blackpawn4[peicemovecounter]=0;
    blackpawn5[x]=5;
    blackpawn5[y]=7;
    blackpawn5[colour]=0;
    blackpawn5[pieceid]=29;
    blackpawn5[dead]=0;
    blackpawn5[peicemovecounter]=0;
    blackpawn6[x]=6;
    blackpawn6[y]=7;
    blackpawn6[colour]=0;
    blackpawn6[pieceid]=30;
    blackpawn6[dead]=0;
    blackpawn6[peicemovecounter]=0;
    blackpawn7[x]=7;
    blackpawn7[y]=7;
    blackpawn7[colour]=0;
    blackpawn7[pieceid]=31;
    blackpawn7[dead]=0;
    blackpawn7[peicemovecounter]=0;
    blackpawn8[x]=8;
    blackpawn8[y]=7;
    blackpawn8[colour]=0;
    blackpawn8[pieceid]=32;
    blackpawn8[dead]=0;
    blackpawn8[peicemovecounter]=0;
    movecounter=0;
    coloursturn=true;
}
int peiceidentifier(int peicelocation){
    if(whitequeen[x]==peicelocation/10&&whitequeen[y]==peicelocation%10){
        return 1;
    }else if(blackqueen[x]==peicelocation/10&&blackqueen[y]==peicelocation%10){
        return 2;
    }else if(whitebishop1[x]==peicelocation/10&&whitebishop1[y]==peicelocation%10){
        return 3;
    }else if(whitebishop2[x]==peicelocation/10&&whitebishop2[y]==peicelocation%10){
        return 4;
    }else if(blackbishop1[x]==peicelocation/10&&blackbishop1[y]==peicelocation%10){
        return 5;
    }else if(blackbishop2[x]==peicelocation/10&&blackbishop2[y]==peicelocation%10){
        return 6;
    }else if(whiterook1[x]==peicelocation/10&&whiterook1[y]==peicelocation%10){
        return 7;
    }else if(whiterook2[x]==peicelocation/10&&whiterook2[y]==peicelocation%10){
        return 8;
    }else if(blackrook1[x]==peicelocation/10&&blackrook1[y]==peicelocation%10){
        return 9;
    }else if(blackrook2[x]==peicelocation/10&&blackrook2[y]==peicelocation%10){
        return 10;
    }else if(whiteknight1[x]==peicelocation/10&&whiteknight1[y]==peicelocation%10){
        return 11;
    }else if(whiteknight2[x]==peicelocation/10&&whiteknight2[y]==peicelocation%10){
        return 12;
    }else if(blackknight1[x]==peicelocation/10&&blackknight1[y]==peicelocation%10){
        return 13;
    }else if(blackknight2[x]==peicelocation/10&&blackknight2[y]==peicelocation%10){
        return 14;
    }else if(whiteking[x]==peicelocation/10&&whiteking[y]==peicelocation%10){
        return 15;
    }else if(blackking[x]==peicelocation/10&&blackking[y]==peicelocation%10){
        return 16;
    }else if(whitepawn1[x]==peicelocation/10&&whitepawn1[y]==peicelocation%10){
        return 17;
    }else if(whitepawn2[x]==peicelocation/10&&whitepawn2[y]==peicelocation%10){
        return 18;
    }else if(whitepawn3[x]==peicelocation/10&&whitepawn3[y]==peicelocation%10){
        return 19;
    }else if(whitepawn4[x]==peicelocation/10&&whitepawn4[y]==peicelocation%10){
        return 20;
    }else if(whitepawn5[x]==peicelocation/10&&whitepawn5[y]==peicelocation%10){
        return 21;
    }else if(whitepawn6[x]==peicelocation/10&&whitepawn6[y]==peicelocation%10){
        return 22;
    }else if(whitepawn7[x]==peicelocation/10&&whitepawn7[y]==peicelocation%10){
        return 23;
    }else if(whitepawn8[x]==peicelocation/10&&whitepawn8[y]==peicelocation%10){
        return 24;
    }else if(blackpawn1[x]==peicelocation/10&&blackpawn1[y]==peicelocation%10){
        return 25;
    }else if(blackpawn2[x]==peicelocation/10&&blackpawn2[y]==peicelocation%10){
        return 26;
    }else if(blackpawn3[x]==peicelocation/10&&blackpawn3[y]==peicelocation%10){
        return 27;
    }else if(blackpawn4[x]==peicelocation/10&&blackpawn4[y]==peicelocation%10){
        return 28;
    }else if(blackpawn5[x]==peicelocation/10&&blackpawn5[y]==peicelocation%10){
        return 29;
    }else if(blackpawn6[x]==peicelocation/10&&blackpawn6[y]==peicelocation%10){
        return 30;
    }else if(blackpawn7[x]==peicelocation/10&&blackpawn7[y]==peicelocation%10){
        return 31;
    }else if(blackpawn8[x]==peicelocation/10&&blackpawn8[y]==peicelocation%10){
        return 32;
    }else{
        return 0;
    }
}
void peicelocationupdator(int peiceid, int desiredlocation){
    if(whitequeen[pieceid]==peiceid){
        whitequeen[x]=desiredlocation/10;
        whitequeen[y]=desiredlocation%10;
    }else if(blackqueen[pieceid]==peiceid){
        blackqueen[x]=desiredlocation/10;
        blackqueen[y]=desiredlocation%10;
    }else if(whiteking[pieceid]==peiceid){
        whiteking[x]=desiredlocation/10;
        whiteking[y]=desiredlocation%10;
    }else if(blackking[pieceid]==peiceid){
        blackking[x]=desiredlocation/10;
        blackking[y]=desiredlocation%10;
    }else if(whitebishop1[pieceid]==peiceid){
        whitebishop1[x]=desiredlocation/10;
        whitebishop1[y]=desiredlocation%10;
    }else if(whitebishop2[pieceid]==peiceid){
        whitebishop2[x]=desiredlocation/10;
        whitebishop2[y]=desiredlocation%10;
    }else if(blackbishop1[pieceid]==peiceid){
        blackbishop1[x]=desiredlocation/10;
        blackbishop1[y]=desiredlocation%10;
    }else if(blackbishop2[pieceid]==peiceid){
        blackbishop2[x]=desiredlocation/10;
        blackbishop2[y]=desiredlocation%10;
    }else if(whiteknight1[pieceid]==peiceid){
        whiteknight1[x]=desiredlocation/10;
        whiteknight1[y]=desiredlocation%10;
    }else if(whiteknight2[pieceid]==peiceid){
        whiteknight2[x]=desiredlocation/10;
        whiteknight2[y]=desiredlocation%10;
    }else if(blackknight1[pieceid]==peiceid){
        blackknight1[x]=desiredlocation/10;
        blackknight1[y]=desiredlocation%10;
    }else if(blackknight2[pieceid]==peiceid){
        blackknight2[x]=desiredlocation/10;
        blackknight2[y]=desiredlocation%10;
    }else if(whiterook1[pieceid]==peiceid){
        whiterook1[x]=desiredlocation/10;
        whiterook1[y]=desiredlocation%10;
    }else if(whiterook2[pieceid]==peiceid){
        whiterook2[x]=desiredlocation/10;
        whiterook2[y]=desiredlocation%10;
    }else if(blackrook1[pieceid]==peiceid){
        blackrook1[x]=desiredlocation/10;
        blackrook1[y]=desiredlocation%10;
    }else if(blackrook2[pieceid]==peiceid){
        blackrook2[x]=desiredlocation/10;
        blackrook2[y]=desiredlocation%10;
    }else if(whitepawn1[pieceid]==peiceid){
        whitepawn1[x]=desiredlocation/10;
        whitepawn1[y]=desiredlocation%10;
    }else if(whitepawn2[pieceid]==peiceid){
        whitepawn2[x]=desiredlocation/10;
        whitepawn2[y]=desiredlocation%10;
    }else if(whitepawn3[pieceid]==peiceid){
        whitepawn3[x]=desiredlocation/10;
        whitepawn3[y]=desiredlocation%10;
    }else if(whitepawn4[pieceid]==peiceid){
        whitepawn4[x]=desiredlocation/10;
        whitepawn4[y]=desiredlocation%10;
    }else if(whitepawn5[pieceid]==peiceid){
        whitepawn5[x]=desiredlocation/10;
        whitepawn5[y]=desiredlocation%10;
    }else if(whitepawn6[pieceid]==peiceid){
        whitepawn6[x]=desiredlocation/10;
        whitepawn6[y]=desiredlocation%10;
    }else if(whitepawn7[pieceid]==peiceid){
        whitepawn7[x]=desiredlocation/10;
        whitepawn7[y]=desiredlocation%10;
    }else if(whitepawn8[pieceid]==peiceid){
        whitepawn8[x]=desiredlocation/10;
        whitepawn8[y]=desiredlocation%10;
    }else if(blackpawn1[pieceid]==peiceid){
        blackpawn1[x]=desiredlocation/10;
        blackpawn1[y]=desiredlocation%10;
    }else if(blackpawn2[pieceid]==peiceid){
        blackpawn2[x]=desiredlocation/10;
        blackpawn2[y]=desiredlocation%10;
    }else if(blackpawn3[pieceid]==peiceid){
        blackpawn3[x]=desiredlocation/10;
        blackpawn3[y]=desiredlocation%10;
    }else if(blackpawn4[pieceid]==peiceid){
        blackpawn4[x]=desiredlocation/10;
        blackpawn4[y]=desiredlocation%10;
    }else if(blackpawn5[pieceid]==peiceid){
        blackpawn5[x]=desiredlocation/10;
        blackpawn5[y]=desiredlocation%10;
    }else if(blackpawn6[pieceid]==peiceid){
        blackpawn6[x]=desiredlocation/10;
        blackpawn6[y]=desiredlocation%10;
    }else if(blackpawn7[pieceid]==peiceid){
        blackpawn7[x]=desiredlocation/10;
        blackpawn7[y]=desiredlocation%10;
    }else if(blackpawn8[pieceid]==peiceid){
        blackpawn8[x]=desiredlocation/10;
        blackpawn8[y]=desiredlocation%10;
    }
}
void peicebeingkilled(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        whitequeen[x]=0;
        whitequeen[y]=0;
        whitequeen[dead]=1;
    }else if(blackqueen[pieceid]==peiceid){
        blackqueen[x]=0;
        blackqueen[y]=0;
        blackqueen[dead]=1;
    }else if(whiteking[pieceid]==peiceid){
        whiteking[x]=0;
        whiteking[y]=0;
    }else if(blackking[pieceid]==peiceid){
        blackking[x]=0;
        blackking[y]=0;
    }else if(whitebishop1[pieceid]==peiceid){
        whitebishop1[x]=0;
        whitebishop1[y]=0;
        whitebishop1[dead]=1;
    }else if(whitebishop2[pieceid]==peiceid){
        whitebishop2[x]=0;
        whitebishop2[y]=0;
        whitebishop2[dead]=1;
    }else if(blackbishop1[pieceid]==peiceid){
        blackbishop1[x]=0;
        blackbishop1[y]=0;
        blackbishop1[dead]=1;
    }else if(blackbishop2[pieceid]==peiceid){
        blackbishop2[x]=0;
        blackbishop2[y]=0;
        blackbishop2[dead]=1;
    }else if(whiteknight1[pieceid]==peiceid){
        whiteknight1[x]=0;
        whiteknight1[y]=0;
        whiteknight1[dead]=1;
    }else if(whiteknight2[pieceid]==peiceid){
        whiteknight2[x]=0;
        whiteknight2[y]=0;
        whiteknight2[dead]=1;
    }else if(blackknight1[pieceid]==peiceid){
        blackknight1[x]=0;
        blackknight1[y]=0;
        blackknight1[dead]=1;
    }else if(blackknight2[pieceid]==peiceid){
        blackknight2[x]=0;
        blackknight2[y]=0;
        blackknight2[dead]=1;
    }else if(whiterook1[pieceid]==peiceid){
        whiterook1[x]=0;
        whiterook1[y]=0;
        whiterook1[dead]=1;
    }else if(whiterook2[pieceid]==peiceid){
        whiterook2[x]=0;
        whiterook2[y]=0;
        whiterook2[dead]=1;
    }else if(blackrook1[pieceid]==peiceid){
        blackrook1[x]=0;
        blackrook1[y]=0;
        blackrook1[dead]=1;
    }else if(blackrook2[pieceid]==peiceid){
        blackrook2[x]=0;
        blackrook2[y]=0;
        blackrook2[dead]=1;
    }else if(whitepawn1[pieceid]==peiceid){
        whitepawn1[x]=0;
        whitepawn1[y]=0;
        whitepawn1[dead]=1;
    }else if(whitepawn2[pieceid]==peiceid){
        whitepawn2[x]=0;
        whitepawn2[y]=0;
        whitepawn2[dead]=1;
    }else if(whitepawn3[pieceid]==peiceid){
        whitepawn3[x]=0;
        whitepawn3[y]=0;
        whitepawn3[dead]=1;
    }else if(whitepawn4[pieceid]==peiceid){
        whitepawn4[x]=0;
        whitepawn4[y]=0;
        whitepawn4[dead]=1;
    }else if(whitepawn5[pieceid]==peiceid){
        whitepawn5[x]=0;
        whitepawn5[y]=0;
        whitepawn5[dead]=1;
    }else if(whitepawn6[pieceid]==peiceid){
        whitepawn6[x]=0;
        whitepawn6[y]=0;
        whitepawn6[dead]=1;
    }else if(whitepawn7[pieceid]==peiceid){
        whitepawn7[x]=0;
        whitepawn7[y]=0;
        whitepawn7[dead]=1;
    }else if(whitepawn8[pieceid]==peiceid){
        whitepawn8[x]=0;
        whitepawn8[y]=0;
        whitepawn8[dead]=1;
    }else if(blackpawn1[pieceid]==peiceid){
        blackpawn1[x]=0;
        blackpawn1[y]=0;
        blackpawn1[dead]=1;
    }else if(blackpawn2[pieceid]==peiceid){
        blackpawn2[x]=0;
        blackpawn2[y]=0;
        blackpawn2[dead]=1;
    }else if(blackpawn3[pieceid]==peiceid){
        blackpawn3[x]=0;
        blackpawn3[y]=0;
        blackpawn3[dead]=1;
    }else if(blackpawn4[pieceid]==peiceid){
        blackpawn4[x]=0;
        blackpawn4[y]=0;
        blackpawn4[dead]=1;
    }else if(blackpawn5[pieceid]==peiceid){
        blackpawn5[x]=0;
        blackpawn5[y]=0;
        blackpawn5[dead]=1;
    }else if(blackpawn6[pieceid]==peiceid){
        blackpawn6[x]=0;
        blackpawn6[y]=0;
        blackpawn6[dead]=1;
    }else if(blackpawn7[pieceid]==peiceid){
        blackpawn7[x]=0;
        blackpawn7[y]=0;
        blackpawn7[dead]=1;
    }else if(blackpawn8[pieceid]==peiceid){
        blackpawn8[x]=0;
        blackpawn8[y]=0;
        blackpawn8[dead]=1;
    }
}
void peicebeingbacktracked(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        whitequeen[dead]=0;
    }else if(blackqueen[pieceid]==peiceid){
        blackqueen[dead]=0;
    }else if(whitebishop1[pieceid]==peiceid){
        whitebishop1[dead]=0;
    }else if(whitebishop2[pieceid]==peiceid){
        whitebishop2[dead]=0;
    }else if(blackbishop1[pieceid]==peiceid){
        blackbishop1[dead]=0;
    }else if(blackbishop2[pieceid]==peiceid){
        blackbishop2[dead]=0;
    }else if(whiteknight1[pieceid]==peiceid){
        whiteknight1[dead]=0;
    }else if(whiteknight2[pieceid]==peiceid){
        whiteknight2[dead]=0;
    }else if(blackknight1[pieceid]==peiceid){
        blackknight1[dead]=0;
    }else if(blackknight2[pieceid]==peiceid){
        blackknight2[dead]=0;
    }else if(whiterook1[pieceid]==peiceid){
        whiterook1[dead]=0;
    }else if(whiterook2[pieceid]==peiceid){
        whiterook2[dead]=0;
    }else if(blackrook1[pieceid]==peiceid){
        blackrook1[dead]=0;
    }else if(blackrook2[pieceid]==peiceid){
        blackrook2[dead]=0;
    }else if(whitepawn1[pieceid]==peiceid){
        whitepawn1[dead]=0;
    }else if(whitepawn2[pieceid]==peiceid){
        whitepawn2[dead]=0;
    }else if(whitepawn3[pieceid]==peiceid){
        whitepawn3[dead]=0;
    }else if(whitepawn4[pieceid]==peiceid){
        whitepawn4[dead]=0;
    }else if(whitepawn5[pieceid]==peiceid){
        whitepawn5[dead]=0;
    }else if(whitepawn6[pieceid]==peiceid){
        whitepawn6[dead]=0;
    }else if(whitepawn7[pieceid]==peiceid){
        whitepawn7[dead]=0;
    }else if(whitepawn8[pieceid]==peiceid){
        whitepawn8[dead]=0;
    }else if(blackpawn1[pieceid]==peiceid){
        blackpawn1[dead]=0;
    }else if(blackpawn2[pieceid]==peiceid){
        blackpawn2[dead]=0;
    }else if(blackpawn3[pieceid]==peiceid){
        blackpawn3[dead]=0;
    }else if(blackpawn4[pieceid]==peiceid){
        blackpawn4[dead]=0;
    }else if(blackpawn5[pieceid]==peiceid){
        blackpawn5[dead]=0;
    }else if(blackpawn6[pieceid]==peiceid){
        blackpawn6[dead]=0;
    }else if(blackpawn7[pieceid]==peiceid){
        blackpawn7[dead]=0;
    }else if(blackpawn8[pieceid]==peiceid){
        blackpawn8[dead]=0;
    }
}
int peicecolouridentifier(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        return whitequeen[colour];
    }else if(blackqueen[pieceid]==peiceid){
        return blackqueen[colour];
    }else if(whiteking[pieceid]==peiceid){
        return whiteking[colour];
    }else if(blackking[pieceid]==peiceid){
        return blackking[colour];
    }else if(whitebishop1[pieceid]==peiceid){
        return whitebishop1[colour];
    }else if(whitebishop2[pieceid]==peiceid){
        return whitebishop2[colour];
    }else if(blackbishop1[pieceid]==peiceid){
        return blackbishop1[colour];
    }else if(blackbishop2[pieceid]==peiceid){
        return blackbishop2[colour];
    }else if(whiteknight1[pieceid]==peiceid){
        return whiteknight1[colour];
    }else if(whiteknight2[pieceid]==peiceid){
        return whiteknight2[colour];
    }else if(blackknight1[pieceid]==peiceid){
        return blackknight1[colour];
    }else if(blackknight2[pieceid]==peiceid){
        return blackknight2[colour];
    }else if(whiterook1[pieceid]==peiceid){
        return whiterook1[colour];
    }else if(whiterook2[pieceid]==peiceid){
        return whiterook2[colour];
    }else if(blackrook1[pieceid]==peiceid){
        return blackrook1[colour];
    }else if(blackrook2[pieceid]==peiceid){
        return blackrook2[colour];
    }else if(whitepawn1[pieceid]==peiceid){
        return whitepawn1[colour];
    }else if(whitepawn2[pieceid]==peiceid){
        return whitepawn2[colour];
    }else if(whitepawn3[pieceid]==peiceid){
        return whitepawn3[colour];
    }else if(whitepawn4[pieceid]==peiceid){
        return whitepawn4[colour];
    }else if(whitepawn5[pieceid]==peiceid){
        return whitepawn5[colour];
    }else if(whitepawn6[pieceid]==peiceid){
        return whitepawn6[colour];
    }else if(whitepawn7[pieceid]==peiceid){
        return whitepawn7[colour];
    }else if(whitepawn8[pieceid]==peiceid){
        return whitepawn8[colour];
    }else if(blackpawn1[pieceid]==peiceid){
        return blackpawn1[colour];
    }else if(blackpawn2[pieceid]==peiceid){
        return blackpawn2[colour];
    }else if(blackpawn3[pieceid]==peiceid){
        return blackpawn3[colour];
    }else if(blackpawn4[pieceid]==peiceid){
        return blackpawn4[colour];
    }else if(blackpawn5[pieceid]==peiceid){
        return blackpawn5[colour];
    }else if(blackpawn6[pieceid]==peiceid){
        return blackpawn6[colour];
    }else if(blackpawn7[pieceid]==peiceid){
        return blackpawn7[colour];
    }else if(blackpawn8[pieceid]==peiceid){
        return blackpawn8[colour];
    }else{
        return 2;
    }
}
int peicefinder(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        return whitequeen[x]*10+whitequeen[y];
    }else if(blackqueen[pieceid]==peiceid){
        return blackqueen[x]*10+blackqueen[y];
    }else if(whiteking[pieceid]==peiceid){
        return whiteking[x]*10+whiteking[y];
    }else if(blackking[pieceid]==peiceid){
        return blackking[x]*10+blackking[y];
    }else if(whitebishop1[pieceid]==peiceid){
        return whitebishop1[x]*10+whitebishop1[y];
    }else if(whitebishop2[pieceid]==peiceid){
        return whitebishop2[x]*10+whitebishop2[y];
    }else if(blackbishop1[pieceid]==peiceid){
        return blackbishop1[x]*10+blackbishop1[y];
    }else if(blackbishop2[pieceid]==peiceid){
        return blackbishop2[x]*10+blackbishop2[y];
    }else if(whiteknight1[pieceid]==peiceid){
        return whiteknight1[x]*10+whiteknight1[y];
    }else if(whiteknight2[pieceid]==peiceid){
        return whiteknight2[x]*10+whiteknight2[y];
    }else if(blackknight1[pieceid]==peiceid){
        return blackknight1[x]*10+blackknight1[y];
    }else if(blackknight2[pieceid]==peiceid){
        return blackknight2[x]*10+blackknight2[y];
    }else if(whiterook1[pieceid]==peiceid){
        return whiterook1[x]*10+whiterook1[y];
    }else if(whiterook2[pieceid]==peiceid){
        return whiterook2[x]*10+whiterook2[y];
    }else if(blackrook1[pieceid]==peiceid){
        return blackrook1[x]*10+blackrook1[y];
    }else if(blackrook2[pieceid]==peiceid){
        return blackrook2[x]*10+blackrook2[y];
    }else if(whitepawn1[pieceid]==peiceid){
        return whitepawn1[x]*10+whitepawn1[y];
    }else if(whitepawn2[pieceid]==peiceid){
        return whitepawn2[x]*10+whitepawn2[y];
    }else if(whitepawn3[pieceid]==peiceid){
        return whitepawn3[x]*10+whitepawn3[y];
    }else if(whitepawn4[pieceid]==peiceid){
        return whitepawn4[x]*10+whitepawn4[y];
    }else if(whitepawn5[pieceid]==peiceid){
        return whitepawn5[x]*10+whitepawn5[y];
    }else if(whitepawn6[pieceid]==peiceid){
        return whitepawn6[x]*10+whitepawn6[y];
    }else if(whitepawn7[pieceid]==peiceid){
        return whitepawn7[x]*10+whitepawn7[y];
    }else if(whitepawn8[pieceid]==peiceid){
        return whitepawn8[x]*10+whitepawn8[y];
    }else if(blackpawn1[pieceid]==peiceid){
        return blackpawn1[x]*10+blackpawn1[y];
    }else if(blackpawn2[pieceid]==peiceid){
        return blackpawn2[x]*10+blackpawn2[y];
    }else if(blackpawn3[pieceid]==peiceid){
        return blackpawn3[x]*10+blackpawn3[y];
    }else if(blackpawn4[pieceid]==peiceid){
        return blackpawn4[x]*10+blackpawn4[y];
    }else if(blackpawn5[pieceid]==peiceid){
        return blackpawn5[x]*10+blackpawn5[y];
    }else if(blackpawn6[pieceid]==peiceid){
        return blackpawn6[x]*10+blackpawn6[y];
    }else if(blackpawn7[pieceid]==peiceid){
        return blackpawn7[x]*10+blackpawn7[y];
    }else if(blackpawn8[pieceid]==peiceid){
        return blackpawn8[x]*10+blackpawn8[y];
    }
}
int peicehasbeenmoved(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        return whitequeen[peicemovecounter];
    }else if(blackqueen[pieceid]==peiceid){
        return blackqueen[peicemovecounter];
    }else if(whiteking[pieceid]==peiceid){
        return whiteking[peicemovecounter];
    }else if(blackking[pieceid]==peiceid){
        return blackking[peicemovecounter];
    }else if(whitebishop1[pieceid]==peiceid){
        return whitebishop1[peicemovecounter];
    }else if(whitebishop2[pieceid]==peiceid){
        return whitebishop2[peicemovecounter];
    }else if(blackbishop1[pieceid]==peiceid){
        return blackbishop1[peicemovecounter];
    }else if(blackbishop2[pieceid]==peiceid){
        return blackbishop2[peicemovecounter];
    }else if(whiteknight1[pieceid]==peiceid){
        return whiteknight1[peicemovecounter];
    }else if(whiteknight2[pieceid]==peiceid){
        return whiteknight2[peicemovecounter];
    }else if(blackknight1[pieceid]==peiceid){
        return blackknight1[peicemovecounter];
    }else if(blackknight2[pieceid]==peiceid){
        return blackknight2[peicemovecounter];
    }else if(whiterook1[pieceid]==peiceid){
        return whiterook1[peicemovecounter];
    }else if(whiterook2[pieceid]==peiceid){
        return whiterook2[peicemovecounter];
    }else if(blackrook1[pieceid]==peiceid){
        return blackrook1[peicemovecounter];
    }else if(blackrook2[pieceid]==peiceid){
        return blackrook2[peicemovecounter];
    }else if(whitepawn1[pieceid]==peiceid){
        return whitepawn1[peicemovecounter];
    }else if(whitepawn2[pieceid]==peiceid){
        return whitepawn2[peicemovecounter];
    }else if(whitepawn3[pieceid]==peiceid){
        return whitepawn3[peicemovecounter];
    }else if(whitepawn4[pieceid]==peiceid){
        return whitepawn4[peicemovecounter];
    }else if(whitepawn5[pieceid]==peiceid){
        return whitepawn5[peicemovecounter];
    }else if(whitepawn6[pieceid]==peiceid){
        return whitepawn6[peicemovecounter];
    }else if(whitepawn7[pieceid]==peiceid){
        return whitepawn7[peicemovecounter];
    }else if(whitepawn8[pieceid]==peiceid){
        return whitepawn8[peicemovecounter];
    }else if(blackpawn1[pieceid]==peiceid){
        return blackpawn1[peicemovecounter];
    }else if(blackpawn2[pieceid]==peiceid){
        return blackpawn2[peicemovecounter];
    }else if(blackpawn3[pieceid]==peiceid){
        return blackpawn3[peicemovecounter];
    }else if(blackpawn4[pieceid]==peiceid){
        return blackpawn4[peicemovecounter];
    }else if(blackpawn5[pieceid]==peiceid){
        return blackpawn5[peicemovecounter];
    }else if(blackpawn6[pieceid]==peiceid){
        return blackpawn6[peicemovecounter];
    }else if(blackpawn7[pieceid]==peiceid){
        return blackpawn7[peicemovecounter];
    }else if(blackpawn8[pieceid]==peiceid){
        return blackpawn8[peicemovecounter];
    }
}
void peicemovedupdator(int peiceid){
    if(whitequeen[pieceid]==peiceid){
        whitequeen[peicemovecounter]=1;
    }else if(blackqueen[pieceid]==peiceid){
        blackqueen[peicemovecounter]=1;
    }else if(whiteking[pieceid]==peiceid){
        whiteking[peicemovecounter]=1;
    }else if(blackking[pieceid]==peiceid){
        blackking[peicemovecounter]=1;
    }else if(whitebishop1[pieceid]==peiceid){
        whitebishop1[peicemovecounter]=1;
    }else if(whitebishop2[pieceid]==peiceid){
        whitebishop2[peicemovecounter]=1;
    }else if(blackbishop1[pieceid]==peiceid){
        blackbishop1[peicemovecounter]=1;
    }else if(blackbishop2[pieceid]==peiceid){
        blackbishop2[peicemovecounter]=1;
    }else if(whiteknight1[pieceid]==peiceid){
        whiteknight1[peicemovecounter]=1;
    }else if(whiteknight2[pieceid]==peiceid){
        whiteknight2[peicemovecounter]=1;
    }else if(blackknight1[pieceid]==peiceid){
        blackknight1[peicemovecounter]=1;
    }else if(blackknight2[pieceid]==peiceid){
        blackknight2[peicemovecounter]=1;
    }else if(whiterook1[pieceid]==peiceid){
        whiterook1[peicemovecounter]=1;
    }else if(whiterook2[pieceid]==peiceid){
        whiterook2[peicemovecounter]=1;
    }else if(blackrook1[pieceid]==peiceid){
        blackrook1[peicemovecounter]=1;
    }else if(blackrook2[pieceid]==peiceid){
        blackrook2[peicemovecounter]=1;
    }else if(whitepawn1[pieceid]==peiceid){
        whitepawn1[peicemovecounter]=1;
    }else if(whitepawn2[pieceid]==peiceid){
        whitepawn2[peicemovecounter]=1;
    }else if(whitepawn3[pieceid]==peiceid){
        whitepawn3[peicemovecounter]=1;
    }else if(whitepawn4[pieceid]==peiceid){
        whitepawn4[peicemovecounter]=1;
    }else if(whitepawn5[pieceid]==peiceid){
        whitepawn5[peicemovecounter]=1;
    }else if(whitepawn6[pieceid]==peiceid){
        whitepawn6[peicemovecounter]=1;
    }else if(whitepawn7[pieceid]==peiceid){
        whitepawn7[peicemovecounter]=1;
    }else if(whitepawn8[pieceid]==peiceid){
        whitepawn8[peicemovecounter]=1;
    }else if(blackpawn1[pieceid]==peiceid){
        blackpawn1[peicemovecounter]=1;
    }else if(blackpawn2[pieceid]==peiceid){
        blackpawn2[peicemovecounter]=1;
    }else if(blackpawn3[pieceid]==peiceid){
        blackpawn3[peicemovecounter]=1;
    }else if(blackpawn4[pieceid]==peiceid){
        blackpawn4[peicemovecounter]=1;
    }else if(blackpawn5[pieceid]==peiceid){
        blackpawn5[peicemovecounter]=1;
    }else if(blackpawn6[pieceid]==peiceid){
        blackpawn6[peicemovecounter]=1;
    }else if(blackpawn7[pieceid]==peiceid){
        blackpawn7[peicemovecounter]=1;
    }else if(blackpawn8[pieceid]==peiceid){
        blackpawn8[peicemovecounter]=1;
    }
}
void peiceprinter(int peicelocation){
    int peiceid=peiceidentifier(peicelocation);
    if(whitequeen[pieceid]==peiceid){
        cout<<"White Queen"<<endl;
    }else if(blackqueen[pieceid]==peiceid){
        cout<<"Black Queen"<<endl;
    }else if(whiteking[pieceid]==peiceid){
        cout<<"White King"<<endl;
    }else if(blackking[pieceid]==peiceid){
        cout<<"Black King"<<endl;
    }else if(whitebishop1[pieceid]==peiceid){
        cout<<"White Bishop"<<endl;
    }else if(whitebishop2[pieceid]==peiceid){
        cout<<"White Bishop"<<endl;
    }else if(blackbishop1[pieceid]==peiceid){
        cout<<"Black Bishop"<<endl;
    }else if(blackbishop2[pieceid]==peiceid){
        cout<<"Black Bishop"<<endl;
    }else if(whiteknight1[pieceid]==peiceid){
        cout<<"White Knight"<<endl;
    }else if(whiteknight2[pieceid]==peiceid){
        cout<<"White Knight"<<endl;
    }else if(blackknight1[pieceid]==peiceid){
        cout<<"Black Knight"<<endl;
    }else if(blackknight2[pieceid]==peiceid){
        cout<<"Black Knight"<<endl;
    }else if(whiterook1[pieceid]==peiceid){
        cout<<"White Rook"<<endl;
    }else if(whiterook2[pieceid]==peiceid){
        cout<<"White Rook"<<endl;
    }else if(blackrook1[pieceid]==peiceid){
        cout<<"Black Rook"<<endl;
    }else if(blackrook2[pieceid]==peiceid){
        cout<<"Black Rook"<<endl;
    }else if(whitepawn1[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn2[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn3[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn4[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn5[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn6[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn7[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(whitepawn8[pieceid]==peiceid){
        cout<<"White Pawn"<<endl;
    }else if(blackpawn1[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn2[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn3[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn4[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn5[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn6[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn7[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    }else if(blackpawn8[pieceid]==peiceid){
        cout<<"Black Pawn"<<endl;
    } else{
        cout<<"Empty"<<endl;
    }
}
int returnsspecificvaluerequiredofpeice(int peiceid, int indexwanted){
    if(whitequeen[pieceid]==peiceid){
        return whitequeen[indexwanted];
    }else if(blackqueen[pieceid]==peiceid){
        return blackqueen[indexwanted];
    }else if(whiteking[pieceid]==peiceid){
        return whiteking[indexwanted];
    }else if(blackking[pieceid]==peiceid){
        return blackking[indexwanted];
    }else if(whitebishop1[pieceid]==peiceid){
        return whitebishop1[indexwanted];
    }else if(whitebishop2[pieceid]==peiceid){
        return whitebishop2[indexwanted];
    }else if(blackbishop1[pieceid]==peiceid){
        return blackbishop1[indexwanted];
    }else if(blackbishop2[pieceid]==peiceid){
        return blackbishop2[indexwanted];
    }else if(whiteknight1[pieceid]==peiceid){
        return whiteknight1[indexwanted];
    }else if(whiteknight2[pieceid]==peiceid){
        return whiteknight2[indexwanted];
    }else if(blackknight1[pieceid]==peiceid){
        return blackknight1[indexwanted];
    }else if(blackknight2[pieceid]==peiceid){
        return blackknight2[indexwanted];
    }else if(whiterook1[pieceid]==peiceid){
        return whiterook1[indexwanted];
    }else if(whiterook2[pieceid]==peiceid){
        return whiterook2[indexwanted];
    }else if(blackrook1[pieceid]==peiceid){
        return blackrook1[indexwanted];
    }else if(blackrook2[pieceid]==peiceid){
        return blackrook2[indexwanted];
    }else if(whitepawn1[pieceid]==peiceid){
        return whitepawn1[indexwanted];
    }else if(whitepawn2[pieceid]==peiceid){
        return whitepawn2[indexwanted];
    }else if(whitepawn3[pieceid]==peiceid){
        return whitepawn3[indexwanted];
    }else if(whitepawn4[pieceid]==peiceid){
        return whitepawn4[indexwanted];
    }else if(whitepawn5[pieceid]==peiceid){
        return whitepawn5[indexwanted];
    }else if(whitepawn6[pieceid]==peiceid){
        return whitepawn6[indexwanted];
    }else if(whitepawn7[pieceid]==peiceid){
        return whitepawn7[indexwanted];
    }else if(whitepawn8[pieceid]==peiceid){
        return whitepawn8[indexwanted];
    }else if(blackpawn1[pieceid]==peiceid){
        return blackpawn1[indexwanted];
    }else if(blackpawn2[pieceid]==peiceid){
        return blackpawn2[indexwanted];
    }else if(blackpawn3[pieceid]==peiceid){
        return blackpawn3[indexwanted];
    }else if(blackpawn4[pieceid]==peiceid){
        return blackpawn4[indexwanted];
    }else if(blackpawn5[pieceid]==peiceid){
        return blackpawn5[indexwanted];
    }else if(blackpawn6[pieceid]==peiceid){
        return blackpawn6[indexwanted];
    }else if(blackpawn7[pieceid]==peiceid){
        return blackpawn7[indexwanted];
    }else if(blackpawn8[pieceid]==peiceid){
        return blackpawn8[indexwanted];
    }
}
void updatingpositionsafterimport(int peiceid, int index, int inputtednumber){
    if(whitequeen[pieceid]==peiceid){
        whitequeen[index]=inputtednumber;
    }else if(blackqueen[pieceid]==peiceid){
        blackqueen[index]=inputtednumber;
    }else if(whiteking[pieceid]==peiceid){
        whiteking[index]=inputtednumber;
    }else if(blackking[pieceid]==peiceid){
        blackking[index]=inputtednumber;
    }else if(whitebishop1[pieceid]==peiceid){
        whitebishop1[index]=inputtednumber;
    }else if(whitebishop2[pieceid]==peiceid){
        whitebishop2[index]=inputtednumber;
    }else if(blackbishop1[pieceid]==peiceid){
        blackbishop1[index]=inputtednumber;
    }else if(blackbishop2[pieceid]==peiceid){
        blackbishop2[index]=inputtednumber;
    }else if(whiteknight1[pieceid]==peiceid){
        whiteknight1[index]=inputtednumber;
    }else if(whiteknight2[pieceid]==peiceid){
        whiteknight2[index]=inputtednumber;
    }else if(blackknight1[pieceid]==peiceid){
        blackknight1[index]=inputtednumber;
    }else if(blackknight2[pieceid]==peiceid){
        blackknight2[index]=inputtednumber;
    }else if(whiterook1[pieceid]==peiceid){
        whiterook1[index]=inputtednumber;
    }else if(whiterook2[pieceid]==peiceid){
        whiterook2[index]=inputtednumber;
    }else if(blackrook1[pieceid]==peiceid){
        blackrook1[index]=inputtednumber;
    }else if(blackrook2[pieceid]==peiceid){
        blackrook2[index]=inputtednumber;
    }else if(whitepawn1[pieceid]==peiceid){
        whitepawn1[index]=inputtednumber;
    }else if(whitepawn2[pieceid]==peiceid){
        whitepawn2[index]=inputtednumber;
    }else if(whitepawn3[pieceid]==peiceid){
        whitepawn3[index]=inputtednumber;
    }else if(whitepawn4[pieceid]==peiceid){
        whitepawn4[index]=inputtednumber;
    }else if(whitepawn5[pieceid]==peiceid){
        whitepawn5[index]=inputtednumber;
    }else if(whitepawn6[pieceid]==peiceid){
        whitepawn6[index]=inputtednumber;
    }else if(whitepawn7[pieceid]==peiceid){
        whitepawn7[index]=inputtednumber;
    }else if(whitepawn8[pieceid]==peiceid){
        whitepawn8[index]=inputtednumber;
    }else if(blackpawn1[pieceid]==peiceid){
        blackpawn1[index]=inputtednumber;
    }else if(blackpawn2[pieceid]==peiceid){
        blackpawn2[index]=inputtednumber;
    }else if(blackpawn3[pieceid]==peiceid){
        blackpawn3[index]=inputtednumber;
    }else if(blackpawn4[pieceid]==peiceid){
        blackpawn4[index]=inputtednumber;
    }else if(blackpawn5[pieceid]==peiceid){
        blackpawn5[index]=inputtednumber;
    }else if(blackpawn6[pieceid]==peiceid){
        blackpawn6[index]=inputtednumber;
    }else if(blackpawn7[pieceid]==peiceid){
        blackpawn7[index]=inputtednumber;
    }else if(blackpawn8[pieceid]==peiceid){
        blackpawn8[index]=inputtednumber;
    }
}
bool king(int peicelocation, int desiredlocation){
    int peiceid=peiceidentifier(peicelocation);
    bool moveallowed=false;
    castle=false;
    if(peicelocation/10-desiredlocation/10==2&&peicelocation%10==desiredlocation%10){
        moveallowed= true;
        castle=true;
        rooklocation=(peicelocation/10+3)*10+peicelocation%10;
        newrooklocation=(peicelocation/10+1)*10+peicelocation%10;
        if(peicehasbeenmoved(peiceid)==0&&peicehasbeenmoved(peiceidentifier(((peicelocation/10+3)*10+peicelocation%10)))==0){
            for(int i=desiredlocation/10; i<peicelocation/10; i++){
                if(peiceidentifier((i*10)+peicelocation%10)!=0){
                    castle=false;
                    moveallowed=false;
                    return moveallowed;
                }
            }
        }else{
            castle=false;
            moveallowed=false;
            return moveallowed;
        }
    }else if(desiredlocation/10-peicelocation/10==2&&peicelocation%10==desiredlocation%10){
        moveallowed=true;
        castle=true;
        rooklocation=(peicelocation/10+3)*10+peicelocation%10;
        newrooklocation=(peicelocation/10+1)*10+peicelocation%10;
        if(peicehasbeenmoved(peiceid)==0&&peicehasbeenmoved(peiceidentifier(((peicelocation/10-4)*10+peicelocation%10)))==0){
            for(int i=peicelocation/10+1; i<=desiredlocation/10; i++){
                if(peiceidentifier((i*10)+peicelocation%10)!=0){
                    castle=false;
                    moveallowed=false;
                    return moveallowed;
                }
            }
        }else{
            castle=false;
            moveallowed=false;
            return moveallowed;
        }
    }else if(peicelocation/10-1==desiredlocation/10){
        if(peicelocation%10==desiredlocation%10){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }else if(peicelocation%10==desiredlocation%10+1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }else if(peicelocation%10==desiredlocation%10-1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }
    }else if(peicelocation/10==desiredlocation/10){
        castle=false;
        if(peicelocation==desiredlocation+1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }else if(peicelocation==desiredlocation-1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }
    }else if(peicelocation/10+1==desiredlocation/10){
        if(peicelocation%10==desiredlocation%10){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }else if(peicelocation%10==desiredlocation%10+1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }else if(peicelocation%10==desiredlocation%10-1){
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceid)!=peicecolouridentifier(peiceidentifier(desiredlocation))){
                moveallowed=true;
            }
        }
    }
    return moveallowed;
}
bool queen(int peicelocation, int desiredlocation){
    int peiceid=peiceidentifier(peicelocation);
    bool moveallowed=false;
    bool willkillapiece=false;
    if(abs(((peicelocation/10)-(desiredlocation/10)))==abs(((peicelocation%10)-(desiredlocation%10)))){
        moveallowed=true;
        if(((peicelocation/10)-(desiredlocation/10))>0&&((peicelocation%10)-(desiredlocation%10))>0){//down and to the left
            for(int i=1; i<peicelocation/10-desiredlocation/10; i++){
                if(peiceidentifier((peicelocation/10-i)*10+(peicelocation%10-i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)<0&&(peicelocation%10)-(desiredlocation%10)>0){//down and to the right
            for(int i=1; i<desiredlocation/10-peicelocation/10; i++){
                if(peiceidentifier((peicelocation/10+i)*10+(peicelocation%10-i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)>0&&(peicelocation%10)-(desiredlocation%10)<0){//up and to the left
            for(int i=1; i<peicelocation/10-desiredlocation/10; i++){
                if(peiceidentifier((peicelocation/10-i)*10+(peicelocation%10+i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)<0&&(peicelocation%10)-(desiredlocation%10)<0){// up and to the right
            for(int i=1; i<desiredlocation/10-peicelocation/10; i++){
                if(peiceidentifier((peicelocation/10+i)*10+(peicelocation%10+i))!=0){
                    moveallowed=false;
                }
            }
        }
    } else if(peicelocation%10==desiredlocation%10||peicelocation/10==desiredlocation/10){
        moveallowed=true;
        if (peicelocation % 10 == desiredlocation % 10 && peicelocation / 10 != desiredlocation / 10) {
            if (peicelocation / 10 - desiredlocation / 10 < 0) {//right
                for (int i = 1; i < desiredlocation / 10 - peicelocation / 10; i++) {
                    if (peiceidentifier((peicelocation / 10 + i) * 10 + peicelocation % 10)!=0) {
                        moveallowed = false;
                    }
                }
            } else if (peicelocation / 10 - desiredlocation / 10 > 0) {//left
                for (int i = 1; i < peicelocation / 10 - desiredlocation / 10; i++) {
                    if (peiceidentifier((peicelocation / 10 - i) * 10 + peicelocation % 10)!=0) {
                        moveallowed = false;
                    }
                }
            }
        } else if (peicelocation / 10 == desiredlocation / 10 && peicelocation % 10 != desiredlocation % 10) {
            if (peicelocation % 10 - desiredlocation % 10 < 0) {//down
                for (int i = 1; i < desiredlocation % 10 - peicelocation % 10; i++) {
                    if (peiceidentifier((peicelocation + i))!=0) {
                        moveallowed = false;
                    }
                }
            } else if (peicelocation % 10 - desiredlocation % 10 > 0) {//up
                for (int i = 1; i < peicelocation - desiredlocation; i++) {
                    if (peiceidentifier(peicelocation - i)!=0) {
                        moveallowed = false;
                    }
                }
            }
        }
    }
    if(peicecolouridentifier(peiceidentifier(desiredlocation))==peicecolouridentifier(peiceid)||(peiceidentifier(desiredlocation)==blackking[pieceid]||peiceidentifier(desiredlocation)==whiteking[pieceid])){
        moveallowed=false;
    }
    return moveallowed;
}
bool knight(int peicelocation, int desiredlocation){
    int peiceid=peiceidentifier(peicelocation);
    bool moveallowed=false;
    if(peicelocation%10-desiredlocation%10==2){//down by two
        if(peicelocation/10-desiredlocation/10==1){//left by one
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }else if(peicelocation/10-desiredlocation/10==-1){//right by one
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }
    }else if(peicelocation%10-desiredlocation%10==1){//down by one
        if(peicelocation/10-desiredlocation/10==2){//left by two
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }else if(peicelocation/10-desiredlocation/10==-2){//right by two
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }
    }else if(peicelocation%10-desiredlocation%10==-1){//up by one
        if(peicelocation/10-desiredlocation/10==2){//left by two
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }else if(peicelocation/10-desiredlocation/10==-2){//right by two
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }
    }else if(peicelocation%10-desiredlocation%10==-2){//up by two
        if(peicelocation/10-desiredlocation/10==1){//left by one
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }else if(peicelocation/10-desiredlocation/10==-1){//right by one
            if(peiceidentifier(desiredlocation)==0||peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
                moveallowed=true;
            }
        }
    }
    return moveallowed;
}
bool rook(int peicelocation, int desiredlocation){
    if(peicelocation%10==desiredlocation%10||peicelocation/10==desiredlocation/10) {
        bool moveallowed = true;
        int peiceid = peiceidentifier(peicelocation);
        if (peicelocation % 10 == desiredlocation % 10 && peicelocation / 10 != desiredlocation / 10) {
            if (peicelocation / 10 - desiredlocation / 10 < 0) {//right
                for (int i = 1; i < desiredlocation / 10 - peicelocation / 10; i++) {
                    if (peiceidentifier((peicelocation / 10 + i) * 10 + peicelocation % 10)!=0) {
                        moveallowed = false;
                        break;
                    }
                }
            } else if (peicelocation / 10 - desiredlocation / 10 > 0) {//left
                for (int i = 1; i < peicelocation / 10 - desiredlocation / 10; i++) {
                    if (peiceidentifier((peicelocation / 10 - i) * 10 + peicelocation % 10)!=0) {
                        moveallowed = false;
                        break;
                    }
                }
            }
        } else if (peicelocation / 10 == desiredlocation / 10 && peicelocation % 10 != desiredlocation % 10) {
            if (peicelocation % 10 - desiredlocation % 10 < 0) {//down
                for (int i = 1; i <= desiredlocation % 10 - peicelocation % 10; i++) {
                    if (peiceidentifier((peicelocation + i))!=0) {
                        moveallowed = false;
                        break;
                    }
                }
            } else if (peicelocation % 10 - desiredlocation % 10 > 0) {//up
                for (int i = 1; i <= peicelocation - desiredlocation; i++) {
                    if (peiceidentifier(peicelocation - i)!=0) {
                        moveallowed = false;
                        break;
                    }
                }
            }
        }
        if (peicecolouridentifier(peiceidentifier(desiredlocation)) == peicecolouridentifier(peiceid)) {
            moveallowed = false;
        }
        return moveallowed;
    }
    return false;
}
bool bishop(int peicelocation, int desiredlocation){
    bool moveallowed=false;
    if(abs(((peicelocation/10)-(desiredlocation/10)))==abs(((peicelocation%10)-(desiredlocation%10)))){
        if(((peicelocation/10)-(desiredlocation/10))>0&&((peicelocation%10)-(desiredlocation%10))>0){//down and to the left
            moveallowed=true;
            for(int i=1; i<peicelocation/10-desiredlocation/10; i++){
                if(peiceidentifier((peicelocation/10-i)*10+(peicelocation%10-i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)<0&&(peicelocation%10)-(desiredlocation%10)>0){//down and to the right
            moveallowed=true;
            for(int i=1; i<desiredlocation/10-peicelocation/10; i++){
                if(peiceidentifier((peicelocation/10+i)*10+(peicelocation%10-i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)>0&&(peicelocation%10)-(desiredlocation%10)<0){//up and to the left
            moveallowed=true;
            for(int i=1; i<peicelocation/10-desiredlocation/10; i++){
                if(peiceidentifier((peicelocation/10-i)*10+(peicelocation%10+i))!=0){
                    moveallowed=false;
                }
            }
        }else if((peicelocation/10)-(desiredlocation/10)<0&&(peicelocation%10)-(desiredlocation%10)<0){// up and to the right
            moveallowed=true;
            for(int i=1; i<desiredlocation/10-peicelocation/10; i++){
                if(peiceidentifier((peicelocation/10+i)*10+(peicelocation%10+i))!=0){
                    moveallowed=false;
                }
            }
        }
    }
    return moveallowed;
}
bool pawns(int peicelocation, int desiredlocation){
    int peiceid=peiceidentifier(peicelocation);
    bool moveallowed=false;
    if(peicecolouridentifier(peiceid)==1){//white
        if(peicehasbeenmoved(peiceid)==0){
            if(peicelocation%10+2==desiredlocation%10&&peicelocation/10==desiredlocation/10&&peiceidentifier(desiredlocation)==0&&peiceidentifier(peicelocation+1)==0){
                moveallowed = true;
            }
        }
        if((peicelocation/10-1)*10+peicelocation%10+1==desiredlocation&&peiceidentifier(desiredlocation)!=0&&peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
            moveallowed=true;
        }
        if(peicelocation+1==desiredlocation&&peiceidentifier(desiredlocation)==0){
            moveallowed=true;
        }
        if((peicelocation/10+1)*10+peicelocation%10+1==desiredlocation&&peiceidentifier(desiredlocation)!=0&&peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
            moveallowed=true;
        }
    }else if(peicecolouridentifier(peiceid)==0){//black
        if(peicehasbeenmoved(peiceid)==0){
            if(peicelocation%10-2==desiredlocation%10&&peicelocation/10==desiredlocation/10&&peiceidentifier(desiredlocation)==0&&peiceidentifier(peicelocation-1)==0) {
                moveallowed = true;
            }
        }
        if((peicelocation/10-1)*10+peicelocation%10-1==desiredlocation&&peiceidentifier(desiredlocation)!=0&&peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
            moveallowed=true;
        }
        if(peicelocation-1==desiredlocation&&peiceidentifier(desiredlocation)==0){
            moveallowed=true;
        }
        if((peicelocation/10+1)*10+peicelocation%10-1==desiredlocation&&peiceidentifier(desiredlocation)!=0&&peicecolouridentifier(peiceidentifier(desiredlocation))!=peicecolouridentifier(peiceid)){
            moveallowed=true;
        }
    }
    return moveallowed;
}
void generatealllegalmoves(int color){
    bool legalmove;
    for(int i=1; i<=32; i++){
        int peicelocation=peicefinder(i);
        for(int j=1; j<9; j++){
            for(int z=1; z<9; z++){
                if(i==1||i==2){
                    legalmove=queen(peicelocation, j*10+z);
                }else if(i==15||i==16){
                    legalmove=king(peicelocation, j*10+z);
                }else if(i<=6&&i>=3){
                    legalmove=bishop(peicelocation, j*10+z);
                }else if(i>=11&&i<=14){
                    legalmove=knight(peicelocation, j*10+z);
                }else if(i<=10&&i>=7){
                    legalmove=rook(peicelocation, j*10+z);
                }else if(i<=32&&i>=17){
                    legalmove=pawns(peicelocation, j*10+z);
                }
                if(legalmove){
                    if(peicecolouridentifier(i)==color) {
                        usedtosenddatatostack.peicelocation = peicelocation;
                        usedtosenddatatostack.desiredlocation = j * 10 + z;
                        allmovesallowedincurrentstate.push(usedtosenddatatostack);
                    }
                }
            }
        }
    }
}
bool MoveNotAllowed(){
    cout<<"Move Not Allowed"<<endl;
    return true;
}
bool check(bool color, int kinglocation){
    bool blackkingcheck=false;
    bool whitekingcheck=false;
    if(!color){
        if(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1)==whiteknight2[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1)==whiteknight1[pieceid]||peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1)==whiteknight2[pieceid]) {
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1)>=whitepawn1[pieceid]&&peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1)<=whitepawn8[pieceid]){
            blackkingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1)>=whitepawn1[pieceid]&&peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1)<=whitepawn8[pieceid]){
            blackkingcheck=true;
        }
        if(!blackkingcheck) {
            for (int i = kinglocation % 10; i <= 8; i++) {
                if (peiceidentifier((kinglocation - kinglocation % 10) + i) == whiterook1[pieceid] ||
                peiceidentifier((kinglocation - kinglocation % 10) + i) == whiterook2[pieceid] ||
                peiceidentifier((kinglocation - kinglocation % 10) + i) == whitequeen[pieceid]) {
                    blackkingcheck = true;
                    break;
                }else if (peiceidentifier((kinglocation - kinglocation % 10) + i) != 0 &&
                           peiceidentifier((kinglocation - kinglocation % 10) + i) != peiceidentifier(kinglocation)) {
                    break;
                }
            }
        }
        if(!blackkingcheck) {
            for(int i=kinglocation%10; i>=1; i--){
                if (peiceidentifier((kinglocation - kinglocation % 10) + i) == whiterook1[pieceid] ||
                peiceidentifier((kinglocation - kinglocation % 10) + i) == whiterook2[pieceid] ||
                peiceidentifier((kinglocation - kinglocation % 10) + i) == whitequeen[pieceid]) {
                    blackkingcheck = true;
                    break;
                }else if (peiceidentifier((kinglocation - kinglocation % 10) + i) != 0 &&
                          peiceidentifier((kinglocation - kinglocation % 10) + i) != peiceidentifier(kinglocation)) {
                    break;
                }
            }
        }
        if(!blackkingcheck){
            for(int i=kinglocation/10; i<=8; i++){
                if(peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==whiterook1[pieceid]||
                peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==whiterook2[pieceid]||
                peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==whitequeen[pieceid]){
                    blackkingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation/10+i)*10+kinglocation%10)!=0&&
                         peiceidentifier((kinglocation/10+i)*10+kinglocation%10)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!blackkingcheck){
            for(int i=kinglocation/10; i>=1; i--){
                if(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==whiterook1[pieceid]||
                peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==whiterook2[pieceid]||
                peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==whitequeen[pieceid]){
                    blackkingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)!=0&&
                         peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!blackkingcheck){
            int i=kinglocation/10+1;
            int j=kinglocation%10+1;
            while(i<=8&&j<=8){
                if(peiceidentifier((i)*10+j)==whitebishop1[pieceid]||
                   peiceidentifier((i)*10+j)==whitebishop2[pieceid]||
                   peiceidentifier((i)*10+j)==whitequeen[pieceid]){
                    blackkingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i++;
                j++;
            }
        }
        if(!blackkingcheck){
            int i=kinglocation/10-1;
            int j=kinglocation%10+1;
            while(i>=1&&j<=8){
                if(peiceidentifier((i)*10+j)==whitebishop1[pieceid]||
                   peiceidentifier((i)*10+j)==whitebishop2[pieceid]||
                   peiceidentifier((i)*10+j)==whitequeen[pieceid]){
                    blackkingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i--;
                j++;
            }
        }
        if(!blackkingcheck){
            int i=kinglocation/10+1;
            int j=kinglocation%10-1;
            while(i<=8&&j>=1){
                if(peiceidentifier((i)*10+j)==whitebishop1[pieceid]||
                   peiceidentifier((i)*10+j)==whitebishop2[pieceid]||
                   peiceidentifier((i)*10+j)==whitequeen[pieceid]){
                    blackkingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i++;
                j--;
            }
        }
        if(!blackkingcheck){
            int i=kinglocation/10-1;
            int j=kinglocation%10-1;
            while(i>=1&&j>=1){
                if (peiceidentifier((i) * 10 + j) == whitebishop1[pieceid] ||
                    peiceidentifier((i) * 10 + j) == whitebishop2[pieceid] ||
                    peiceidentifier((i) * 10 + j) == whitequeen[pieceid]) {
                    blackkingcheck = true;
                    break;
                } else if (peiceidentifier((i) * 10 + j) != 0 ) {
                    break;
                }
                i--;
                j--;
            }
        }
        return blackkingcheck;
    }else{
        if(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1)==blackknight1[pieceid]||peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1)==blackknight1[pieceid]||peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2)==blackknight1[pieceid]||peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2)==blackknight1[pieceid]||peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2)==blackknight1[pieceid]||peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2)==blackknight1[pieceid]||peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1)==blackknight1[pieceid]||peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1)==blackknight2[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1)==blackknight1[pieceid]||peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1)==blackknight2[pieceid]) {
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+1)>=blackpawn1[pieceid]&&peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1)<=blackpawn8[pieceid]){
            whitekingcheck=true;
        }else if(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+1)>=blackpawn1[pieceid]&&peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1)<=blackpawn8[pieceid]){
            whitekingcheck=true;
        }
        if(!whitekingcheck) {
            for (int i = kinglocation % 10; i <= 8; i++) {
                if (peiceidentifier((kinglocation - kinglocation % 10) + i) == blackrook1[pieceid] ||
                    peiceidentifier((kinglocation - kinglocation % 10) + i) == blackrook2[pieceid] ||
                    peiceidentifier((kinglocation - kinglocation % 10) + i) == blackqueen[pieceid]) {
                    whitekingcheck = true;
                    break;
                }else if (peiceidentifier((kinglocation - kinglocation % 10) + i) != 0 &&
                          peiceidentifier((kinglocation - kinglocation % 10) + i) != peiceidentifier(kinglocation)) {
                    break;
                }
            }
        }
        if(!whitekingcheck) {
            for(int i=kinglocation%10; i>=1; i--){
                if (peiceidentifier((kinglocation - kinglocation % 10) + i) == blackrook1[pieceid] ||
                    peiceidentifier((kinglocation - kinglocation % 10) + i) == blackrook2[pieceid] ||
                    peiceidentifier((kinglocation - kinglocation % 10) + i) == blackqueen[pieceid]) {
                    whitekingcheck = true;
                    break;
                }else if (peiceidentifier((kinglocation - kinglocation % 10) + i) != 0 &&
                          peiceidentifier((kinglocation - kinglocation % 10) + i) != peiceidentifier(kinglocation)) {
                    break;
                }
            }
        }
        if(!whitekingcheck){
            for(int i=kinglocation/10; i<=8; i++){
                if(peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==blackrook1[pieceid]||
                   peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==blackrook2[pieceid]||
                   peiceidentifier((kinglocation/10+i)*10+kinglocation%10)==blackqueen[pieceid]){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation/10+i)*10+kinglocation%10)!=0&&
                         peiceidentifier((kinglocation/10+i)*10+kinglocation%10)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!whitekingcheck){
            for(int i=kinglocation/10; i>=1; i--){
                if(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==blackrook1[pieceid]||
                   peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==blackrook2[pieceid]||
                   peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)==blackqueen[pieceid]){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)!=0&&
                         peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!whitekingcheck){
            int i=kinglocation/10+1;
            int j=kinglocation%10+1;
            while(i<=8&&j<=8){
                if(peiceidentifier((i)*10+j)==blackbishop1[pieceid]||
                   peiceidentifier((i)*10+j)==blackbishop2[pieceid]||
                   peiceidentifier((i)*10+j)==blackqueen[pieceid]){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i++;
                j++;
            }
        }
        if(!whitekingcheck){
            int i=kinglocation/10-1;
            int j=kinglocation%10+1;
            while(i>=1&&j<=8){
                if(peiceidentifier((i)*10+j)==blackbishop1[pieceid]||
                   peiceidentifier((i)*10+j)==blackbishop2[pieceid]||
                   peiceidentifier((i)*10+j)==blackqueen[pieceid]){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i--;
                j++;
            }
        }
        if(!whitekingcheck){
            int i=kinglocation/10+1;
            int j=kinglocation%10-1;
            while(i<=8&&j>=1){
                if(peiceidentifier((i)*10+j)==blackbishop1[pieceid]||
                   peiceidentifier((i)*10+j)==blackbishop2[pieceid]||
                   peiceidentifier((i)*10+j)==blackqueen[pieceid]){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((i)*10+j)!=0){
                    break;
                }
                i++;
                j--;
            }
        }
        if(!whitekingcheck){
            int i=kinglocation/10-1;
            int j=kinglocation%10-1;
            while(i>=1&&j>=1){
                if (peiceidentifier((i) * 10 + j) == blackbishop1[pieceid] ||
                    peiceidentifier((i) * 10 + j) == blackbishop2[pieceid] ||
                    peiceidentifier((i) * 10 + j) == blackqueen[pieceid]) {
                    whitekingcheck = true;
                    break;
                } else if (peiceidentifier((i) * 10 + j) != 0) {
                    break;
                }
                i--;
                j--;
            }
        }
        return whitekingcheck;
    }
}
bool checkmate(bool color){
    int kingid;
    if(color){
        kingid=15;
    }else{
        kingid=16;
    }
    if(!check(color, peicefinder(kingid))){
        return false;
    }
    for(int i=0; i<32; i++){
        for(int j=0; j<6; j++){
            currentstate.pieces[i][j]=returnsspecificvaluerequiredofpeice(i+1, j);
        }
    }
    while(!allmovesallowedincurrentstate.empty()){
        allmovesallowedincurrentstate.pop();
    }
    generatealllegalmoves(color);
    for(int i=0; i<allmovesallowedincurrentstate.size(); i++){
        peicebeingkilled(peiceidentifier(allmovesallowedincurrentstate.top().desiredlocation));
        peicelocationupdator(allmovesallowedincurrentstate.top().peicelocation, allmovesallowedincurrentstate.top().desiredlocation);
        allmovesallowedincurrentstate.pop();
        if(!check(coloursturn, kingid)){
            return false;
        }
        for(int j=0; j<32; j++){
            for(int z=0; z<6; z++){
                updatingpositionsafterimport(currentstate.pieces[j][3], z, currentstate.pieces[j][z]);
            }
        }
    }
    return true;
}
void fromimportedstringtoactualdata(const string& importdata){
    vector<int> workinginformation;
    stringstream data(importdata);
    for(int i; data>>i;){
        workinginformation.push_back(i);
        if(data.peek()==','){
            data.ignore();
        }
    }
    for(int i=0; i<32; i++){
        for(int j=0; j<6; j++){
            updatingpositionsafterimport(workinginformation[i*6+3], j, workinginformation[i*6+j]);
        }
    }int size=workinginformation.size();
    movecounter=workinginformation[size-1];
    coloursturn=workinginformation[size-2];
}
void importdatafromfile(){
    string importdatafromfiletoworkwith;
    ifstream importingfile;
    importingfile.open("Saves.dat");
    if(importingfile.is_open()){
        cout<<"Importing Data"<<endl;
        getline(importingfile, importdatafromfiletoworkwith);
        fromimportedstringtoactualdata(importdatafromfiletoworkwith);
        cout<<"Data Imported Successfully"<<endl;
    }
    importingfile.close();
}
void savedatatofile(){
    ofstream savingfile;
    savingfile.open("Saves.dat");
    if(savingfile.is_open()){
        cout<<"Saving Data"<<endl;
        for(int i=1; i<=32; i++){
            for(int j=0; j<6; j++){
                savingfile<<returnsspecificvaluerequiredofpeice(i, j)<<",";
            }
        }
        savingfile<<coloursturn<<",";
        savingfile<<movecounter;
        cout<<"Data Saved Successfully"<<endl;
        savingfile.close();
    }else{
        cout<<"Error Opening File"<<endl;
    }
}
void printboard(){
    int peiceid;
    int numberofspaces;
    for(int i=8; i>=1; i--){
        for(int j=1; j<=8; j++){
            peiceid=peiceidentifier((j*10)+i);
            if(peiceid<10){
                numberofspaces=1;
            }else{
                numberofspaces=0;
            }
            cout<<"| "<<peiceid;
            if(numberofspaces==1){
                cout<<" ";
            }
            cout<<" |";
        }
        cout<<endl;
    }
}
int maininputthing(){
    getline(cin, actualcharactetest);
    transform(actualcharactetest.begin(), actualcharactetest.end(),actualcharactetest.begin(), ::toupper);
    if(actualcharactetest=="IMPORT"){
        return 0;
    }else if(actualcharactetest=="SAVE"){
        return 1;
    }else if(actualcharactetest=="RESET"){
        cout<<"Resetting board"<<endl;
        return 2;
    }else if(actualcharactetest=="EXIT"){
        cout<<"Exiting";
        return 3;
    }else if(actualcharactetest=="PRINT"){
        return 4;
    }else if(actualcharactetest=="CHECK LOCATION"){
        return 5;
    }else if(actualcharactetest=="CHECK LEGAL"){
        return 6;
    }else {
        firstcharacter = toupper(actualcharactetest[0]);
        int horizontalvalue = 0;
        string a = "A";
        string b = "B";
        string c = "C";
        string d = "D";
        string e = "E";
        string f = "F";
        string g = "G";
        string h = "H";
        if (!firstcharacter.compare(a)) {
            horizontalvalue = 1;
        } else if (!firstcharacter.compare(b)) {
            horizontalvalue = 2;
        } else if (!firstcharacter.compare(c)) {
            horizontalvalue = 3;
        } else if (!firstcharacter.compare(d)) {
            horizontalvalue = 4;
        } else if (!firstcharacter.compare(e)) {
            horizontalvalue = 5;
        } else if (!firstcharacter.compare(f)) {
            horizontalvalue = 6;
        } else if (!firstcharacter.compare(g)) {
            horizontalvalue = 7;
        } else if (!firstcharacter.compare(h)) {
            horizontalvalue = 8;
        } else {
            horizontalvalue = 9;
        }
        secondcharacter = actualcharactetest[1];
        stringstream stringstream1(secondcharacter);
        int verticalvalue = 0;
        stringstream1 >> verticalvalue;
        return (horizontalvalue * 10) + verticalvalue;
    }
}
void returnstostatebeforemove(){
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++ ){
            peicelocationupdator(backtrackingdata.board[i][j], i*10+j);
        }
    }
    peicelocationupdator(backtrackingdata.piecethatwasjustmoved, backtrackingdata.wherepiecethatwasmovedmovedfrom);
    if(backtrackingdata.piecethatwaskilled!=0){
        peicelocationupdator(backtrackingdata.piecethatwaskilled, backtrackingdata.wherepiecemoved);
        peicebeingbacktracked(backtrackingdata.piecethatwaskilled);
    }
}
int main(){
    resetboard();
    int peicelocation;
    int desiredlocation;
    int peiceid;
    bool inproperinput=true;
    dataimported:
    while(!checkmate(coloursturn)){
        printboard();
        castle=false;
        movecounter++;
        for(int i=1; i<9; i++){
            for(int j=1; j<8; j++){
                backtrackingdata.board[i][j]=peiceidentifier(i*10+j);
            }
        }
        while(inproperinput) {
            catchcheck:
            cout << "enter piece you would like to move" << endl;
            peicelocation=maininputthing();
            if(peicelocation==0){
                importdatafromfile();
                goto dataimported;
            }else if(peicelocation==1){
                savedatatofile();
                goto dataimported;
            }else if(peicelocation==2){
                resetboard();
                goto dataimported;
            }else if(peicelocation==3){
                return 0;
            }else if(peicelocation==4){
                cout<<"Printing board"<<endl;
                goto dataimported;
            }else if(peicelocation==5){
                cout<<"enter piece location"<<endl;
                peiceprinter(maininputthing());
                goto dataimported;
            }else if(peicelocation==6){
                generatealllegalmoves(coloursturn);
                while(!allmovesallowedincurrentstate.empty()){
                    cout<<allmovesallowedincurrentstate.top().peicelocation<<endl;
                    cout<<allmovesallowedincurrentstate.top().desiredlocation<<endl;
                    allmovesallowedincurrentstate.pop();
                }
                goto dataimported;
            }
            backtrackingdata.wherepiecethatwasmovedmovedfrom=peicelocation;
            cout << "enter location you would like to move to" << endl;
            desiredlocation=maininputthing();
            if(desiredlocation==0){
                importdatafromfile();
                goto dataimported;
            }else if(desiredlocation==1){
                savedatatofile();
                goto dataimported;
            }else if(desiredlocation==2){
                resetboard();
                goto dataimported;
            }else if(desiredlocation==3){
                return 0;
            }else if(desiredlocation==4){
                cout<<"Printing board"<<endl;
                printboard();
                goto dataimported;
            }else if(desiredlocation==5){
                cout<<"enter piece location"<<endl;
                peiceprinter(maininputthing());
                goto dataimported;
            }else if(desiredlocation==6){
                generatealllegalmoves(coloursturn);
                goto dataimported;
            }
            if(peicelocation/10>=1&&peicelocation/10<=8&&peicelocation%10<=8&&peicelocation%10>=1&&desiredlocation/10>=1&&desiredlocation/10<=8&&desiredlocation%10<=8&&desiredlocation%10>=1){
                if((peicecolouridentifier(peiceidentifier(peicelocation))==1&&coloursturn)||(peicecolouridentifier(peiceidentifier(peicelocation))==0&&!coloursturn)){
                    inproperinput=false;
                }else if(peicecolouridentifier(peiceidentifier(peicelocation))==2){
                    cout<<"There is no piece there you retard"<<endl;
                }else{
                    cout<<"Wrong Colour!!!"<<endl;
                    inproperinput=true;
                }
            }else{
                inproperinput=true;
                cout<<"Please input proper information"<<endl;
            }
            if(!inproperinput){
                bool allowed;
                peiceid=peiceidentifier(peicelocation);
                if(peiceid==1||peiceid==2){
                    allowed=queen(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(peiceid==15||peiceid==16){
                    allowed=king(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(peiceid<=6&&peiceid>=3){
                    allowed=bishop(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(peiceid>=11&&peiceid<=14){
                    allowed=knight(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(peiceid<=10&&peiceid>=7){
                    allowed=rook(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(peiceid<=32&&peiceid>=17){
                    allowed=pawns(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }
                if(allowed){
                    if(castle){
                        thread thread1(peicelocationupdator, peiceid, desiredlocation);
                        thread thread2(peicelocationupdator, peiceidentifier(rooklocation), newrooklocation);
                        thread1.join();
                        thread2.join();
                        peicemovedupdator(peiceidentifier(newrooklocation));
                        peicemovedupdator(peiceid);

                    }else {
                        if(peiceidentifier(desiredlocation)!=0&&peicecolouridentifier(peiceidentifier(desiredlocation))==!coloursturn){
                            backtrackingdata.piecethatwaskilled=peiceidentifier(desiredlocation);
                        }
                        peicebeingkilled(peiceidentifier(desiredlocation));
                        thread thread1(peicelocationupdator, peiceid, desiredlocation);
                        thread thread2(peicemovedupdator, peiceid);
                        thread1.join();
                        thread2.join();
                    }
                }
            }
        }
        backtrackingdata.piecethatwasjustmoved=peiceid;
        backtrackingdata.turn=coloursturn;
        backtrackingdata.turncount=movecounter;
        backtrackingdata.wherepiecemoved=desiredlocation;
        bool willbacktrack;
        if(coloursturn){
            willbacktrack=check(coloursturn, peicefinder(15));
        }else{
            willbacktrack=check(coloursturn, peicefinder(16));
        }
        if(willbacktrack){
            movecounter=backtrackingdata.turncount;
            returnstostatebeforemove();
            cout<<"You Are In Check"<<endl;
            goto catchcheck;
        }
        coloursturn = !coloursturn;
        if(checkmate(coloursturn)){
            break;
        }
        inproperinput=true;
        if(movecounter/2==0){
            cout<<movecounter<<endl;
        }else {
            cout << movecounter / 2 << endl;
        }
    }
    if(!coloursturn){
        cout<<"White Wins";
    }else{
        cout<<"Black Wins";
    }
    return 5611;
}