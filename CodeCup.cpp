#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef unsigned long long ull;
ll colour[9] = {0, 1, 2, 3, 4, 5, 6, 7};
ll board[305][305];
map<string, ll> occur;
//check xem co move dc ko
void PrintBoard()
{
    for (ll i='A'; i<='G'; i++)
    {
        for (ll j='a'; j<='g'; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
// đặt giá trị 1 ô
void Set(string s)
{
    ll point = s[0] - '0';
    char x = s[1], y = s[2];
    board[x][y] = colour[point];
}
// undo giá trị ô đó (dùng để test ở hàm minimax xem nc đi nào tốt nhất?)
void Pre_Set(string s)
{
    char x = s[1], y = s[2];
    board[x][y] = 0;
}
// nước đi của order
void Move(string s)
{
    char x = s[0], y = s[1];
    char x1 = s[2], y1 = s[3];
    swap(board[x][y], board[x1][y1]);
}
void Pre_Move(string s)
{
    char x = s[0], y = s[1];
    char x1 = s[2], y1 = s[3];
    swap(board[x1][y1], board[x][y]);
}
bool CheckPalin_Hang(char x, char a, char b)
{
    if (board[x][a] != board[x][b])
    {
        return false;
    }
    return true;
}
bool CheckPalin_Cot(char x, char a, char b)
{
    if (board[a][x] != board[b][x])
    {
        return false;
    }
    return true;
}
// Đếm điểm
ll Dem_Diem_Hang_Ngang(char x, char a, char b)
{
    ll diem = 0;
    if (a != b)
    {
        while (a >= 'a' && b <= 'g')
        {
            ll length = b - a + 1;
            if (CheckPalin_Hang(x, a, b) == false || board[x][a] == 0 || board[x][b] == 0)
            {
                break;
            }
            if (a < b)
            {
                diem += length;
            }
            a--;
            b++;
        }
    }
    else
    {
        if (a > 'a' && a < 'g')
        {
            ll z = a-1, y = b+1;
            if (board[x][z] == board[x][y] && board[x][z] != 0 && board[x][y] != 0)
            {
                diem = diem + 3;
                a=a-2;
                b=b+2;
            }
        }
        while (a >= 'a' && b <= 'g')
        {
            ll length = b - a + 1;
            if (CheckPalin_Hang(x, a, b) == false || board[x][a] == 0 || board[x][b] == 0)
            {
                break;
            }
            if (a < b)
            {
                diem += length;
            }
            a--;
            b++;
        }
    }
    return diem;
}
ll Dem_Diem_Cot_Doc(char x, char a, char b)
{
    ll diem = 0;
    if (a != b)
    {
        while (a >= 'A' && b <= 'G')
        {
            ll length = b - a + 1;
            if (CheckPalin_Cot(x, a, b) == false || board[a][x] == 0 || board[b][x] == 0)
            {
                break;
            }
            if (a < b)
            {
                diem += length;
            }
            a--;
            b++;
        }
    }
    else
    {
        if (a > 'A' && a < 'G')
        {
            ll z = a-1, y = b+1;
            if (board[z][x] == board[y][x] && board[z][x] != 0 && board[y][x] != 0)
            {
                diem = diem + 3;
                a=a-2;
                b=b+2;
            }
        }
        while (a >= 'A' && b <='G')
        {
            ll length = b - a + 1;
            if (CheckPalin_Cot(x, a, b) == false || board[a][x] == 0 || board[b][x] == 0)
            {
                break;
            }
            if (a < b)
            {
                diem += length;
            }
            a--;
            b++;
        }
    }
    return diem;
}
// Đếm điểm cho Chaos (Nhanh hơn đếm cả bảng)
ll Evaluate_Cross_Pattern(string s)
{
    char x = s[1], y = s[2];
    ll score = 0;
    for (ll i='A'; i<='G'; i++)
    {
        score += Dem_Diem_Cot_Doc(y, i, i+1) + Dem_Diem_Cot_Doc(y, i, i);
    }
    for (ll i='a'; i<='g'; i++)
    {
        score += Dem_Diem_Hang_Ngang(x, i, i+1) + Dem_Diem_Hang_Ngang(x, i, i);
    }
    return score;
}
ll Evaluate_Ca_Bang()
{
    ll evaluated_score = 0;
    for (ll i='A'; i<='G'; i++)
    {
        for (ll j='a'; j<='g'; j++)
        {
            evaluated_score += Dem_Diem_Hang_Ngang(i, j, j+1) + Dem_Diem_Cot_Doc(j, i, i+1) + Dem_Diem_Hang_Ngang(i, j, j) + Dem_Diem_Cot_Doc(j, i, i);
        }
    }
    return evaluated_score;
}
ll Best_Move_Chaos(const string &colour, string &move1)
{
    ll value = INT_MAX;
    ll score_of_Order;
    if (occur[colour] == 1)
    {
        if(board['B']['b'] == 0)
        {
            move1 = colour + "Bb";
        }
        else if(board['B']['f'] == 0)
        {
            move1 = colour + "Bf";
        }
        else if(board['F']['b'] == 0)
        {
            move1 = colour + "Fb";
        }
        else if(board['F']['f'] == 0)
        {
            move1 = colour + "Ff";
        }
        else if(board['C']['c'] == 0)
        {
            move1 = colour + "Cc";
        }
        else if(board['C']['e'] == 0)
        {
            move1 = colour + "Ce";
        }
        else if(board['E']['c'] == 0)
        {
            move1 = colour + "Ec";
        }
        else if(board['E']['e'] == 0)
        {
            move1 = colour + "Ee";
        }
    }
    else if (occur[colour] > 1)
    {
        for (ll i='A'; i<='G'; i++)
        {
            for (ll j='a'; j<='g'; j++)
            {
                if (board[i][j] != 0)
                {
                    continue;
                }
                else
                {
                    string cell = string(1, i) + string(1, j);
                    string set_move = colour;
                    string x;
                    set_move += cell;
                    Set(set_move);
                    score_of_Order = Evaluate_Cross_Pattern(set_move);
                    if (value > score_of_Order)
                    {
                        value = score_of_Order;
                        move1 = set_move;
                    }
                    Pre_Set(set_move);
                }
            }
        }
    }
    return value;
}
string VI_TRI_BEST_MOVE(string colour){
            string move_1;
            Best_Move_Chaos(colour, move_1);
            return move_1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s, turn = "Order";
    while(getline(cin, s))
    {
        if (s == "Start")
        {
            turn = "Chaos";
        }
        else if (s == "Quit")
        {
            break;
        }
        else if (turn == "Chaos")
        {
            // Nếu input của chaos là bước đi của order -> update bảng rồi bỏ qua lượt
            if(s.size() == 4)
            {
                Move(s);
                continue;
            }
            string colour = s;
            occur[s]++;
            string move1;
            move1=VI_TRI_BEST_MOVE(s);
            Set(move1);
            cout << move1[1] << move1[2] << endl;
        }
        else if (turn == "Order")
        {
            Set(s);
            string	Bestmove;
        	int Bestscore=-1;
        	string cell="";
        	vector<string>move;
            for(int i='A';i<='G';i++)
            {
                for(int j='a';j<='g';j++)
                {
                    if(!board[i][j]) continue;
                    cell=string(1,i)+string(1,j);
                    move.push_back(cell + cell);
                    for (ll k = j+1; k<='g'; k++)
                    {
                        if (board[i][k] != 0) break;
                        if (board[i][k] == 0) move.push_back(cell + string(1,i) + string(1,k));
                    }
                    for (ll k=j-1; k>='a'; k--)
                    {
                        if (board[i][k] != 0) break;
                        if(board[i][k] == 0) move.push_back(cell + string(1,i) + string(1,k));
                    }
                    for (ll k = i+1; k <= 'G'; k++)
                    {
                        if (board[k][j] != 0) break;
                        if(board[k][j] == 0) move.push_back(cell + string(1,k) + string(1,j));
                    }
                    for (ll k=i-1; k>='A'; k--)
                    {
                        if (board[k][j] != 0) break;
                        if(board[k][j] == 0) move.push_back(cell + string(1,k) + string(1,j));
                    }
                    for(auto item: move)
                    {
                        Move(item);
                        int diem=-1;
                        for(char i='1';i<='7';i++)
                        {
                            string mau=string(1,i);
                            if(occur[mau]==7) continue;
                            string vitrichaoslucday=VI_TRI_BEST_MOVE(mau);
                            Set(vitrichaoslucday);
                            diem=Evaluate_Ca_Bang();
                            Pre_Set(vitrichaoslucday);
                            if(diem>Bestscore)
                            {
                            Bestscore=diem;
                            Bestmove=item;
                            }
                        }
                        Pre_Move(item);
                    }
                }
            }
            Move(Bestmove);
            cout << Bestmove << endl;
        }
    }
}
