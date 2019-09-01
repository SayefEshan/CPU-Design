#include <bits/stdc++.h>
#include <sstream>
#include <string>

using namespace std;






/*
void BinarytoHex(string s,ofstream &out)
{
    int hexadecimalval = 0, i = 1, remainder;

    istringstream buffer(s);
    long long int binaryval;
    buffer >>binaryval;
    while (binaryval != 0)
    {
        remainder = binaryval % 10;
        hexadecimalval = hexadecimalval + remainder * i;
        i = i * 2;
        binaryval = binaryval / 10;
    }


    out<<hex<<uppercase<<hexadecimalval<<endl;


}*/

void BinarytoHex(string binnum,ofstream &out)
{
    char hexa[1000];
    string app="";
    int temp;
    long int i=0,j=0;

    while(binnum[i]){
        binnum[i] = binnum[i] -48;
        ++i;
    }
    --i;
    while(i-2>=0){
        temp =  binnum[i-3] *8 + binnum[i-2] *4 +  binnum[i-1] *2 + binnum[i] ;
        if(temp > 9)
            hexa[j++] = temp + 55;
        else
            hexa[j++] = temp + 48;
        i=i-4;
    }
    if(i ==1)
        hexa[j] = binnum[i-1] *2 + binnum[i] + 48 ;
    else if(i==0)
        hexa[j] =  binnum[i] + 48 ;
    else
        --j;

    while(j>=0){
        app += hexa[j--];
    }
    out<<app<<endl;
}


string  decimalToBinary_two(int n)
{
    std::string binary = std::bitset<2>(n).to_string(); //to binary
    //  std::cout<<binary<<"\n";
    return binary;
}

string  decimalToBinary_three(int n)
{
    std::string binary = std::bitset<3>(n).to_string(); //to binary
    //  std::cout<<binary<<"\n";

    return binary;
}


int main()
{

    string binary,bin;
    ifstream input;
    input.open("input.txt");
    ofstream output;
    output.open("output_binary.txt");
    ofstream output2;
    output2.open("output_hexa.txt");

    string op, rs, rt, rd, j,cons ;
    string instruction,fil;

    string opn, rsn, rtn, rdn ;

    output2<<"v2.0 raw"<<endl;

    string R[2][10];
    int temp=1;

    R[0][0] = "add";
    R[1][0] = "0001";


    R[0][1] = "sub";
    R[1][1] = "0010";


    R[0][2] = "xor";
    R[1][2] = "0011";


    R[0][3] = "nor";
    R[1][3] = "0100";


    R[0][4] = "beq";
    R[1][4] = "0101";


    R[0][5] = "slt";
    R[1][5] = "0110";


    R[0][6] = "lw";
    R[1][6] = "0111";


    R[0][7] = "addi";
    R[1][7] = "0000";

    R[0][8] = "sw";
    R[1][8] = "1000";


    R[0][9] = "j";
    R[1][9] = "1001";

//----------------------------------------------


    string registers[2][4];


    registers[0][0] = "$t0"; //ze = zero
    registers[1][0] = "00";

    registers[0][1] = "$t1";
    registers[1][1] = "01";

    registers[0][2] = "$t2";
    registers[1][2] = "10";

    registers[0][3] = "$t3";
    registers[1][3] = "11";


    int i;


    while(input>>instruction)
    {

        //cout<<instruction;
        for( i=0; i<10; i++)
        {
            if(instruction == R[0][i])
            {

                op = R[1][i];

                break;
            }

        }
        if(i==10)
        {
            cout<<"Instruction not found!"<<endl;

        }


        if(op=="0001"||op=="0010"||op=="0011"||op=="0100"||op=="0110")      //add+sub+and+or+slt
        {
            string rs,rd,rt;


            input>>rd>>rs>>rt;

            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());






            int count = 0;

            for(int i=0; i<4; i++)
            {
                if(count==3)
                {
                    break;
                }
                if(rd==registers[0][i])
                {
                    rdn = registers[1][i];

                    if(rdn=="000")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;

                        break;

                    }
                    count++;
                }
                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    count++;
                }
            }

            if(temp)
            {

                binary=op+rsn+rtn+rdn;
                BinarytoHex(binary,output2);

                output<<op<<rsn<<rtn<<rdn<<endl;

            }
            else
            {
                output<<endl;
            }


            temp=1;
        }
        else if(op=="0000")      //addi
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;



            input>>rt>>rs>>sh;


            if( sh>3)
            {


                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            if( sh<0)
            {


                cout<<"Invalid Address"<<endl;
                temp=0;
            }

            else
            {
                shbin=decimalToBinary_two(sh);

            }
            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());
            int count = 0;

            for(int i=0; i<4; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    if(rdn=="00" && op=="0000")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }

                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    if(rsn=="00" && (op=="0101"))
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }
            }


            j ="000";

            if(temp)
            {

                output<<op<<rsn<<rtn<<shbin<<endl;
                binary=op+rsn+rtn+shbin;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }


        else if(op=="0101")      //beq+bne
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;
            input>>rs>>rt>>sh;
            if( sh<0)
            {


                cout<<"Invalid Address   <0"<<endl;
                temp=0;
            }
            if(sh>3)
            {


                cout<<"Invalid Address     >4"<<endl;
                temp=0;
            }

            else
            {
                shbin=decimalToBinary_two(sh);

            }
            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());

            //   cout<<rt<<" "<<rs<<" "<<sh<<endl;

            int count = 0;

            for(int i=0; i<4; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    if(rdn=="00" && op=="0000")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }

                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    if(rsn=="00" && (op=="0101"))
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }
            }


            j ="000";

            if(temp)
            {

                output<<op<<rsn<<rtn<<shbin<<endl;
                binary=op+rsn+rtn+shbin;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
        else if(op=="1000"||op=="0111")       //lw+sw
        {
            registers[0][0] = "$ze";


            string rdin, rsin;
            string immediate, source;
            input>>rdin>>source;
            for(int i=0; i<source.length(); i++)
            {
                if(source[i]=='$')
                {
                    rsin = rsin+source[i]+source[i+1]+source[i+2];
                    break;
                }
            }
            for(int i=0; i<source.length(); i++)
            {
                if(source[i]=='(')
                    break;
                immediate = immediate+source[i];
            }
            rdin.erase(rdin.begin()+rdin.length()-1, rdin.end());
            int value = atoi(immediate.c_str());

       //     cout<<"  rsin "<<rsin<<endl;





            int count = 0;

            for(int i=0; i<4; i++)
            {
                if(count==3)
                {
                    break;
                }
                if(rdin==registers[0][i])
                {
                    rdn = registers[1][i];
                    if(rdn=="00")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }
                if(rsin==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }

            }

            if(value>=0 && value <3 && value%2==0)
            {
                string shbin=decimalToBinary_two(value);

                immediate =shbin;

                if(temp)
                {
                    output<<op<<rsn<<rdn<<immediate<<endl;
                    binary=op+rsn+rdn+immediate;
                    BinarytoHex(binary,output2);
                }
                else
                {
                    output<<endl;
                }

            }
            else
            {
                cout<<"Invalid Offset!"<<endl;
                output<<endl;
            }




            temp=1;
            registers[0][0] = "$zero";

        }
        else if(op=="1001")       //j
        {
            string shstr;
            stringstream shstrtemp;
            int sh,temp=1;;
            string shbin;


            input>>sh;
            if(sh<0) //63
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            if(sh>3)  //0
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            else
            {
                shbin=decimalToBinary_two(sh);
            }
            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());

            if(temp)
            {
                rs="00";
                rt="00";

                output<<op<<rs<<rt<<shbin<< endl;
                binary=op+rs+rt+cons+shbin;
                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
    }

    cout<<"Successfully converted to binary as well as hexadecimal"<<endl;




    return 0;
}
