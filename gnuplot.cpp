#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void plot_2d(vector<double>  v1, vector<double> v2, vector<vector<vector<double>>> v3, string image_name){

    FILE * gnuplotPipe = _popen ("gnuplot -persistant", "w"); // отваряме виртуална конзола с команда gnuplot и можем да си пишем в нея

    vector<string> commands;
   
    commands.push_back("set terminal gif animate delay 10 size 400, 400");// default размер на изображението (1024, 768)
    commands.push_back("set output '" + image_name + ".gif'"); // може да се промени на .jpeg и други, но трябва преди това set terminal jpeg

    commands.push_back("set xrange [0:1]");
    commands.push_back("set yrange [0:1]");
    commands.push_back("set zrange [-0.1:0.1]");
    commands.push_back("set xyplane at 0");

    //commands.push_back("unset ztics");   
    commands.push_back("set margins 0, 0, 0, 0");
    //commands.push_back("unset border");
    commands.push_back("unset key");

    commands.push_back("set cbrange [-0.1:0.1]");

    commands.push_back("set style data lines");
    commands.push_back("set dgrid3d 10, 10");
    commands.push_back("set pm3d");

    for(int k=0;k<v3.size();k++){
        commands.push_back("$grid << EOD");
        for(int i=0;i<v1.size();i++){
            for(int j=0;j<v2.size();j++){
                commands.push_back(to_string(v1[i]) + "\t"+ to_string(v2[j]) + "\t" + to_string(v3[k][i][j]));
            }
        }
        commands.push_back("EOD");
        commands.push_back("splot '$grid' pal");
    }

    //for(int i=0;i<v1.size();i++){
    //    commands.push_back("plot '-' using 1:2 with linespoints linestyle 1");
    //    for(int j=0;j<v1[0].size();j++){
    //        commands.push_back(to_string(v2[j]) + "\t"+ to_string(v1[i][j]));
    //    }
    //    commands.push_back("e");
    //    
    //    //commands.push_back("set output");
    //    
    //}
    //commands.push_back("set output");
    //commands.push_back("set term pop");
    for(int i =0;i<commands.size();i++){
        fprintf(gnuplotPipe, "%s \n", commands[i].c_str());// много важно конвертиране от c++ string към c string - string.c_str()
    }
}
