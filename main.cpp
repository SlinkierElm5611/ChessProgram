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
    for(int i=0; i<32; i++){
        pieces[i][pieceid]=i+1;
        pieces[i][dead]=0;
        pieces[i][peicemovecounter]=0;
    }
    for(int i=0; i<8; i++){
        pieces[i+16][x]=i+1;
        pieces[i+16][y]=2;
        pieces[i+16][colour]=1;
        pieces[i+16][piecetype]=6;
        pieces[i+24][x]=i+1;
        pieces[i+24][y]=7;
        pieces[i+24][colour]=0;
        pieces[i+24][piecetype]=6;
        pieces[i][x]=i+1;
        pieces[i][y]=1;
        pieces[i][colour]=1;
        pieces[i+8][x]=i+1;
        pieces[i+8][y]=8;
        pieces[i+8][colour]=0;
    }
    pieces[0][piecetype]=5;
    pieces[8][piecetype]=5;
    pieces[1][piecetype]=4;
    pieces[9][piecetype]=4;
    pieces[2][piecetype]=3;
    pieces[10][piecetype]=3;
    pieces[3][piecetype]=2;
    pieces[11][piecetype]=2;
    pieces[4][piecetype]=1;
    pieces[12][piecetype]=1;
    pieces[5][piecetype]=3;
    pieces[13][piecetype]=3;
    pieces[6][piecetype]=4;
    pieces[14][piecetype]=4;
    pieces[7][piecetype]=5;
    pieces[15][piecetype]=5;
    movecounter=0;
    coloursturn=true;
}
int peiceidentifier(int peicelocation){
    for(int i=0; i<32; i++){
        if(pieces[i][x]==peicelocation/10&&pieces[i][y]==peicelocation%10){
            return pieces[i][pieceid];
        }
    }
    return 0;
}
void peicelocationupdator(int peiceid, int desiredlocation){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            pieces[i][x]=desiredlocation/10;
            pieces[i][y]=desiredlocation%10;
            break;
        }
    }
}
void peicebeingkilled(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            pieces[i][x]=0;
            pieces[i][y]=0;
            pieces[i][dead]=1;
            break;
        }
    }
}
void peicebeingbacktracked(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            pieces[i][dead]=0;
            break;
        }
    }
}
int peicecolouridentifier(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            return pieces[i][colour];
        }
    }
    return 2;
}
int peicefinder(int peiceid){
    for(int i =0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            return pieces[i][x]*10+pieces[i][y];
        }
    }
}
int peicehasbeenmoved(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            return pieces[i][peicemovecounter];
        }
    }
}
void peicemovedupdator(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            pieces[i][peicemovecounter]=1;
            break;
        }
    }
}
int peicetype(int peiceid){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            return pieces[i][piecetype];
        }
    }
}
int getkingid(int colour, int peicetype){
    for(int i=0; i<32; i++){
        if(pieces[i][colour]==colour&&pieces[i][piecetype]==peicetype){
            return pieces[i][pieceid];
        }
    }
}
void peiceprinter(int peicelocation){
    int peiceid=peiceidentifier(peicelocation);
    string outputstring="";
    bool found=false;
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            found=true;
            if(pieces[i][colour]==1){
                outputstring.append("White ");
            }else{
                outputstring.append("Black ");
            }
            if(pieces[i][piecetype]==1){
                outputstring.append("King");
            }else if(pieces[i][piecetype]==2){
                outputstring.append("Queen");
            }else if(pieces[i][piecetype]==3){
                outputstring.append("Bishop");
            }else if(pieces[i][piecetype]==4){
                outputstring.append("Knight");
            }else if(pieces[i][piecetype]==5){
                outputstring.append("Rook");
            }else {
                outputstring.append("Pawn");
            }
        }
    }
    if(found){
        cout<<outputstring<<endl;
    }else{
        cout<<"Empty"<<endl;
    }
}
int returnsspecificvaluerequiredofpeice(int peiceid, int indexwanted){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            return pieces[i][indexwanted];
        }
    }
}
void updatingpositionsafterimport(int peiceid, int index, int inputtednumber){
    for(int i=0; i<32; i++){
        if(pieces[i][pieceid]==peiceid){
            pieces[i][index]=inputtednumber;
            break;
        }
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
    if(peicecolouridentifier(peiceidentifier(desiredlocation))==peicecolouridentifier(peiceid)||(peicetype(peiceidentifier(desiredlocation))!=1)){
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
                int typeofpeice=peicetype(peiceidentifier(peicelocation));
                if(typeofpeice==1){
                    legalmove=king(peicelocation, j*10+z);
                }else if(typeofpeice==2){
                    legalmove=queen(peicelocation, j*10+z);
                }else if(typeofpeice==3){
                    legalmove=bishop(peicelocation, j*10+z);
                }else if(typeofpeice==4){
                    legalmove=knight(peicelocation, j*10+z);
                }else if(typeofpeice==5){
                    legalmove=rook(peicelocation, j*10+z);
                }else if(typeofpeice==6){
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
    int kingpieceid=getkingid(color, 1);
    if(!color){
        if(peicetype(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1))==1) {
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1))==6&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1))==1){
            blackkingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1))==6&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1))==1){
            blackkingcheck=true;
        }
        if(!blackkingcheck) {
            for (int i = kinglocation % 10; i <= 8; i++) {
                if((peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==2||
                    peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==5)&&
                    peicecolouridentifier(peiceidentifier(kinglocation-kinglocation%10+i))==1){
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
                if((peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==2||
                    peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation-kinglocation%10)+i))==1){
                    blackkingcheck = true;
                    break;
                }else if (peiceidentifier((kinglocation-kinglocation%10)+i)!=0&&
                          peiceidentifier((kinglocation-kinglocation%10)+i)!=peiceidentifier(kinglocation)) {
                    break;
                }
            }
        }
        if(!blackkingcheck){
            for(int i=kinglocation/10; i<=8; i++){
                if((peicetype(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==2||
                    peicetype(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==1){
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
                if((peicetype(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==2||
                    peicetype(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==1){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==1){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==1){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==1){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==1){
                    blackkingcheck = true;
                    break;
                } else if (peiceidentifier((i) * 10 + j) != 0 ) {
                    break;
                }
                i--;
                j--;
            }
        }
        if(!blackkingcheck){
            for(int i=-1; i<=1; i++){
                for(int j=-1; j<=1; j++){
                    if(peicetype(peiceidentifier(((kinglocation/10)+i)*10+((kinglocation%10)+j)))==1&&peicecolouridentifier(peiceidentifier(((kinglocation/10)+i)*10+((kinglocation%10)+j)))==1){
                        blackkingcheck=true;
                    }
                }
            }
        }
        return blackkingcheck;
    }else{
        if(peicetype(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+2)*10+kinglocation%10+1))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+2)*10+kinglocation%10-1))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+2))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-2))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+2))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-2))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-2)*10+kinglocation%10+1))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1))==4&&peicecolouridentifier(peiceidentifier((kinglocation/10-2)*10+kinglocation%10-1))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10-1)*10+kinglocation%10+1))==6&&peicecolouridentifier(peiceidentifier((kinglocation/10-1)*10+kinglocation%10-1))==0){
            whitekingcheck=true;
        }else if(peicetype(peiceidentifier((kinglocation/10+1)*10+kinglocation%10+1))==6&&peicecolouridentifier(peiceidentifier((kinglocation/10+1)*10+kinglocation%10-1))==0){
            whitekingcheck=true;
        }
        if(!whitekingcheck){
            for(int i=kinglocation%10; i<=8; i++){
                if((peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==2||
                    peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation-kinglocation%10)+i))==0){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation-kinglocation%10)+i)!=0&&
                         peiceidentifier((kinglocation-kinglocation%10)+i)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!whitekingcheck) {
            for(int i=kinglocation%10; i>=1; i--){
                if((peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==2||
                    peicetype(peiceidentifier((kinglocation-kinglocation%10)+i))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation-kinglocation%10)+i))==0){
                    whitekingcheck=true;
                    break;
                }else if(peiceidentifier((kinglocation-kinglocation%10)+i)!=0&&
                         peiceidentifier((kinglocation-kinglocation%10)+i)!=peiceidentifier(kinglocation)){
                    break;
                }
            }
        }
        if(!whitekingcheck){
            for(int i=kinglocation/10; i<=8; i++){
                if((peicetype(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==2||
                    peicetype(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation/10+i)*10+kinglocation%10))==0){
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
                if((peicetype(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==2||
                    peicetype(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==5)&&
                    peicecolouridentifier(peiceidentifier((kinglocation/10-(kinglocation/10-i))*10+kinglocation%10))==0){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==0){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==0){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)&&
                    peicecolouridentifier(peiceidentifier((i)*10+j))==0){
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
                if((peicetype(peiceidentifier((i)*10+j))==3||
                    peicetype(peiceidentifier((i)*10+j))==2)||
                    peicecolouridentifier(peiceidentifier((i)*10+j))==0){
                    whitekingcheck = true;
                    break;
                } else if (peiceidentifier((i) * 10 + j) != 0) {
                    break;
                }
                i--;
                j--;
            }
        }
        if(!whitekingcheck){
            for(int i=-1; i<=1; i++){
                for(int j=-1; j<=1; j++){
                    if(peicetype(peiceidentifier(((kinglocation/10)+i)*10+((kinglocation%10)+j)))==1&&peicecolouridentifier(peiceidentifier(((kinglocation/10)+i)*10+((kinglocation%10)+j)))==0){
                        whitekingcheck=true;
                    }
                }
            }
        }
        return whitekingcheck;
    }
}
bool checkmate(bool color){
    int kingid=getkingid(color, 1);
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
        for(int j=0; j<7; j++){
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
            for(int j=0; j<7; j++){
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
        if(!actualcharactetest.empty()) {
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
        }else{
            return 7;
        }
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
            }else if(peicelocation==7){
                goto catchcheck;
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
                int typeofpeice=peicetype(peiceid);
                if(typeofpeice==2){
                    allowed=queen(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(typeofpeice==1){
                    allowed=king(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(typeofpeice==3){
                    allowed=bishop(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(typeofpeice==4){
                    allowed=knight(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(typeofpeice==5){
                    allowed=rook(peicelocation, desiredlocation);
                    if(!allowed){
                        inproperinput=MoveNotAllowed();
                    }
                }else if(typeofpeice==6){
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
        bool willbacktrack=check(coloursturn, peicefinder(getkingid(coloursturn, 1)));
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