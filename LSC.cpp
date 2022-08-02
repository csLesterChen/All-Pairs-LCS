#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <ctime> 
#include <fstream>
#include <utility>

using namespace std;


struct InputPair{
    string str1;
    string str2;
};
struct Sequence
{
    int len;
    //string direction;
    set<string> sub_seq;// store all subsequences
};

InputPair read_file(string file_path)
{
    ifstream fin(file_path.c_str());  // default mode ios::in
    if (!fin) {
        cerr << "error: open file for input failed!" << endl;
        abort();
    }
    InputPair input;
    fin >> input.str1;
    fin >> input.str2;

    return input;
}


void print_result(vector<vector<Sequence>> table)
{
    string filename = "Result.txt";
    ofstream fout(filename.c_str());

    if (!fout) {
      cerr << "error: open file for output failed!" << endl;
      abort();  // in <cstdlib> header
    }

    fout << table[table.size() - 1][table[0].size() - 1].len << endl;
    fout << table[table.size() - 1][table[0].size() - 1].sub_seq.size() << endl;
    for (auto result : table[table.size() - 1][table[0].size() - 1].sub_seq)
    {
        fout << result << endl;
    }

    fout.close();
    

}

int main(void)
{
    // Read from file
    string file_path = "./testcases/basic1.txt";
    string str1;
    string str2;
    InputPair input = read_file(file_path);
    str1 = input.str1;
    str2 = input.str2;

    // Initial DP table
    vector<vector<Sequence>> table(str1.size() + 1);

    for (int i = 0; i < table.size(); i++)
    {
        table[i].resize(str2.size() + 1);

        for (int j = 0; j < table[i].size(); j++)
        {
            table[i][j].len = 0;
            //table[i][j].direction = "↑";
        }
    }

    
    clock_t start, end; // variables for storing time
    start = clock(); // start time

    for (int i = 1; i < table.size(); i++)
    {
        for (int j = 1; j < table[i].size(); j++)
        {
            //cout << i << " "<< j << endl;
            if (str1[i - 1] != str2[j - 1])
            {
                if (table[i - 1][j].len > table[i][j - 1].len)
                {
                    table[i][j].len = table[i - 1][j].len;
                    //table[i][j].direction = "←";

                    if (table[i - 1][j].len != 0)
                    {
                        for (auto temp : table[i - 1][j].sub_seq)
                        {
                            table[i][j].sub_seq.insert(temp);
                        }
                        //table[i - 1][j].sub_seq.clear();
                    }
                }
                else if (table[i - 1][j].len == table[i][j - 1].len)
                {
                    table[i][j].len = table[i][j - 1].len;
                    //table[i][j].direction = "←↑";

                    if (table[i - 1][j].len != 0 && table[i][j - 1].len != 0)
                    {
                        for (auto temp : table[i - 1][j].sub_seq)
                        {
                            table[i][j].sub_seq.insert(temp);
                        }
                        for (auto temp : table[i][j - 1].sub_seq)
                        {
                            table[i][j].sub_seq.insert(temp);
                        }
                        //table[i - 1][j].sub_seq.clear();
                        //table[i][j-1].sub_seq.clear();
                    }
                }
                else 
                {
                    table[i][j].len = table[i][j - 1].len;
                    //table[i][j].direction = "↑";

                    if (table[i][j - 1].len != 0)
                    {
                        for (auto temp : table[i][j - 1].sub_seq)
                        {
                            table[i][j].sub_seq.insert(temp);
                        }
                        //table[i][j-1].sub_seq.clear();
                    }
                }
            }
            else //str1[i - 1] == str2[j - 1]
            {
                table[i][j].len = table[i - 1][j - 1].len + 1;
                //table[i][j].direction = "↖";
                string s;
                s.push_back(str1[i - 1]);
                
                if (table[i - 1][j - 1].len == 0)
                {
                    table[i][j].sub_seq.insert(s);
                }
                else
                {
                    for (auto temp : table[i - 1][j - 1].sub_seq)
                    {
                        temp = temp + s;
                        table[i][j].sub_seq.insert(temp);
                        //cout << temp << endl;
                    }
                    
                }
            }

            table[i-1][j-1].sub_seq.clear();// clear up-left sequences
        }
    }

    end = clock(); // end time
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // calculate actual cost time
    cout <<"Time used: " <<cpu_time_used << endl;
    print_result(table);

    return 0;
}