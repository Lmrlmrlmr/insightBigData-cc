#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <bits/stl_set.h>
#include <unordered_map>
#include <queue>

using namespace std;



typedef std::map<std::string, int> word_map;

/*
 * Constant and global variable declarations
 * */
const std::string file_name_in = "tweets_input/tweets.txt"; //used for first feature.
const std::string in_file_name = "tweets_input/tweets.txt"; //used for second feauture
const std::string file_name_out_list = "tweets_output//ft1.txt"; //output for first feautre
const std::string out_file_name = "tweets_output//ft2.txt"; //output for the second feature.
const int space_btwn = 20;              //The amount of space between words
// and number of times appeared
/*
 * Function Declarations
 * */
void countTheWords(word_map& word_sort);
void outputTheWords(word_map & word_print);
void countTheWordsUnique();
/*
 * Main
 * */
int main(){
    word_map word_map_current;
    countTheWords(word_map_current);      //calls function to count words and create word map
    outputTheWords(word_map_current);     //calls function to print out results.
    countTheWordsUnique(); //calls function to get median
    return 0;
}
/*
 * countTheWords
 * return type: void
 * parameters: It receives the map of words from the main function
 * Description: This function will open the file stated under file_name_in it will stop the program it if is not able to
 * open the input file. If it opens successfully it will retrieve each word and place it in word_sort.
 * */
void countTheWords(word_map& word_sort){
    ifstream input;                //Opening file for input

    input.open(file_name_in.c_str(),ios::in);
    if(!input){exit(EXIT_FAILURE);}    //In case of failure
    std::string x;
    while(input>>x)
    {
        ++word_sort[x];
    }
    input.close();                     //close files before exiting.
}
/*
 * outputTheWords
 * return type: void
 * parameters: It receives the map of words from the main function
 * Description: This function will open the file stated under file_name_output it will stop the program it if is not
 * able to open the output file. If it opens successfully it will place it on the document. after it finishes it returns
 * to main.
 * */
void outputTheWords(word_map & word_print)
{
    std::ofstream output;               //opening file for input
    output.open(file_name_out_list.c_str(),ios::out);
    if(!output){exit(EXIT_FAILURE);}    //In case of failure
    for (word_map::iterator x = word_print.begin();x != word_print.end();++x){
        output << std::setw(space_btwn) << std::left
        << x->first << "\t" << x->second << "\n";
    }
    output.close();                     //close files before exiting.
}
/*
 * countTheWordsUnique
 * return type: void
 * parameters: It receives the map of words from the main function
 * Description: This function will open the file stated under file_name_in it will stop the program it if is not able to
 * open the input file. If it opens successfully it will retrieve each word and place it in a map after that it will
 * out put the median
 * */
void countTheWordsUnique(){
    ifstream input(in_file_name.c_str());
    unordered_map<std::string, bool> word_map_unique;              //creating an unsorted map.
    string current_tweet;                                        //variable to get line from document
    std::queue<int> median_list;                                //keeps track of median list.
    while (getline(input, current_tweet)) {
        int start = 0;
        for (unsigned int current = 0; current < current_tweet.size(); current++) {
            if (current_tweet[current] == ' ') {
                word_map_unique.emplace(string(current_tweet.c_str()+start,current - start), true);//make sure tweet
                //isn't already there.
                start = current + 1;//update
            }
        }
        median_list.push(word_map_unique.size() + 1);   //Save the word.
        word_map_unique.clear();                        //clear map to start again in next iteration of while loop.
    }
    input.close()                  ;                     //close file after use.
    int array[median_list.size()] = {0};
    unsigned int x = median_list.size();
    for(int current = 0;current < x;current++)
    {
        array[current] = median_list.front();
        median_list.pop();
    }
    double sum = 0.0;
    std::queue<int> totalMedianList;
    ofstream output(out_file_name.c_str());
    for(int current = 0;current < x;current++) {
        sum = sum + array[current];
        if(current>0){totalMedianList.push(sum);output << "\n" << sum/(current+1);}
        else{totalMedianList.push(sum);output << sum;}
    }
    output.close();                                     //close files after opening it.
}