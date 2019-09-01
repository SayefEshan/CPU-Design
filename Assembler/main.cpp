#include <bits/stdc++.h>
#include <sstream>
#include <string>

using namespace std;







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


}




string  decimalToBinary_six(int n)
{
    std::string binary = std::bitset<6>(n).to_string(); //to binary
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

    string op, rs, rt, rd, shamt,j,cons ;
    string instruction,fil;

    string opn, rsn, rtn, rdn, shamtn ;

    output2<<"v2.0 raw"<<endl;

    string R[3][13];
    int temp=1;

    R[0][0] = "add";
    R[1][0] = "0001";


    R[0][1] = "sub";
    R[1][1] = "0010";


    R[0][2] = "and";
    R[1][2] = "0011";


    R[0][3] = "or";
    R[1][3] = "0100";


    R[0][4] = "sll";
    R[1][4] = "0101";


    R[0][5] = "srl";
    R[1][5] = "0110";


    R[0][6] = "slt";
    R[1][6] = "0111";


//--------------------------------------------



    R[0][7] = "addi";
    R[1][7] = "1001";

    R[0][8] = "lw";
    R[1][8] = "1010";


    R[0][9] = "sw";
    R[1][9] = "1011";



    R[0][10] = "beq";
    R[1][10] = "1100";



    R[0][11] = "bne";
    R[1][11] = "1101";


    R[0][12] = "j";
    R[1][12] = "1111";

//----------------------------------------------


    string registers[2][8];


    registers[0][0] = "$zero"; //ze = zero
    registers[1][0] = "000";

    registers[0][1] = "$t0";
    registers[1][1] = "001";

    registers[0][2] = "$t1";
    registers[1][2] = "010";

    registers[0][3] = "$t2";
    registers[1][3] = "011";

    registers[0][4] = "$t3";
    registers[1][4] = "100";

    registers[0][5] = "$s0";
    registers[1][5] = "101";


    registers[0][6] = "$s1";
    registers[1][6] = "110";

    registers[0][7] = "$s2";
    registers[1][7] = "111";



    int i;


    while(input>>instruction)
    {

        //cout<<instruction;
        for( i=0; i<13; i++)
        {
            if(instruction == R[0][i])
            {

                op = R[1][i];

                break;
            }

        }
        if(i==13)
        {
            cout<<"Instruction not found!"<<endl;

        }


        if(op=="0001"||op=="0010"||op=="0011"||op=="0100"||op=="0111")      //add+sub+and+or+slt
        {
            string rs,rd,rt;


            input>>rd>>rs>>rt;

            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());






            int count = 0;

            for(int i=0; i<8; i++)
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
            shamt = "000";
            if(temp)
            {

                binary=op+rsn+rtn+rdn+shamt;
                BinarytoHex(binary,output2);

                output<<op<<" "<<rsn<<" "<<rtn<<" "<<rdn<<" "<<shamt<<endl;

            }
            else
            {
                output<<endl;
            }


            temp=1;
        }

        else if(op=="0101"||op=="0110")      //sll+srl
        {
            string rd,rt,shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;

            input>>rd>>rt>>sh;
            if(sh<=0)
            {
                cout<<"sll can not shift for 0 or negative values!"<<endl;
                temp=0;
            }
            else if(sh>7)
            {
                cout<<"sll can not shift more than 7"<<endl;
                temp=0;
            }
            else
            {
                shbin=decimalToBinary_three(sh);



            }



            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rt.erase(rt.begin()+rt.length()-1, rt.end());






            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
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

                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    count++;
                }
            }
            rs ="000";

            if(temp)
            {

                output<<op<<" "<<rtn<<" "<<rs<<" "<<rdn<<" "<<shbin<<endl;
                binary=op+rtn+rs+rdn+shbin;
                BinarytoHex(binary,output2);


            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
        else if(op=="1001")      //addi
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;



            input>>rt>>rs>>sh;


            if( sh>31)
            {


                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            if( sh<-32)
            {


                cout<<"Invalid Address"<<endl;
                temp=0;
            }

            else
            {
                shbin=decimalToBinary_six(sh);

            }




            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());






            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    if(rdn=="000" && op=="1001")
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
                    if(rsn=="000" && (op=="1100"||op=="1101"))
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

                output<<op<<" "<<rsn<<" "<<rtn<<" "<<shbin<<endl;
                binary=op+rsn+rtn+shbin;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
        else if(op=="1100"||op=="1101")      //beq+bne
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;




            input>>rs>>rt>>sh;


            if( sh<-32)
            {


                cout<<"Invalid Address   <0"<<endl;
                temp=0;
            }
            if(sh>31)
            {


                cout<<"Invalid Address     >63"<<endl;
                temp=0;
            }

            else
            {
                shbin=decimalToBinary_six(sh);



            }




            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());

            //   cout<<rt<<" "<<rs<<" "<<sh<<endl;




            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    if(rdn=="000" && op=="1001")
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
                    if(rsn=="000" && (op=="1100"||op=="1101"))
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

                output<<op<<" "<<rsn<<" "<<rtn<<" "<<shbin<<endl;
                binary=op+rsn+rtn+shbin;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
        else if(op=="1010"||op=="1011")       //lw+sw
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

            for(int i=0; i<8; i++)
            {
                if(count==3)
                {
                    break;
                }
                if(rdin==registers[0][i])
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
                if(rsin==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }

            }








            if(value>=0 && value <64 && value%2==0)
            {
                string shbin=decimalToBinary_six(value);

                immediate =shbin;

                if(temp)
                {
                    output<<op<<" "<<rsn<<" "<<rdn<<" "<<immediate<<endl;
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
        else if(op=="1111")       //j
        {
            string shstr;
            stringstream shstrtemp;
            int sh,temp=1;;
            string shbin;


            input>>sh;
            if(sh<-32) //63
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            if(sh>31)  //0
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            else
            {
                shbin=decimalToBinary_six(sh);



            }




            rt.erase(rt.begin()+rt.length()-1, rt.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());





            if(temp)
            {
                rs="000";
                rt="000";


                output<<op<<" "<<rs<<" "<<rt<<" "<<shbin<< endl;
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
