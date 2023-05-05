#include "../../BinTree/Huffman.h"
#include <fstream>
int main()
{
    // 读取文件内容到str
    string filename = "I Have a Dream.txt";
    ifstream infile(filename);
    string str;
    string line;
    while (getline(infile, line))
    {
        str += line + "\n";
    }
    infile.close();
    HuffmanNode *root = buildHuffTree(str);
    unordered_map<char, string> codeMap;
    generateCodes(root, "", codeMap);
    string Code1 = codeMap['D'] + codeMap['r'] + codeMap['e'] + codeMap['a'] + codeMap['m'];
    cout << "Dream的Huffman编码为:" << Code1 << endl;
    string Code2 = codeMap['a'] + codeMap['b'] + codeMap['a'] + codeMap['n'] + codeMap['d'] + codeMap['o'] + codeMap['n'];
    cout << "abandon的Huffman编码为:" << Code2 << endl;

    return 0;
}