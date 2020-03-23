//
//  main.cpp
//  hw3
//
//  Created by Hasan Furkan Vural on 20.11.2018.
//  Copyright © 2018 H. Furkan Vural. All rights reserved.
//
/**********************************************************************************************************************
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 g++ main.cpp -o output.o -std=c++11
 ./output.o vocab.txt search.txt
 may be needed to use as compiler command.
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 **********************************************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include "HashNode.h"

#define maxsizevocab 13423
#define maxsizesearch 1501
#define m 17863
#define m2 21929
#define p 895
#define hlin 1
#define hdoub 2
#define huniv 3
#define r 3

using namespace std;


int hlinear(int k, int i);
int hdouble(int k, int i);
int h1(int k);
int h2(int k);
int huniversal(int k, int i, int a[]);
void insert(HashNode arr[], HashNode wrd, int opt, int a[], int &i);
int search(HashNode arr[], HashNode wrd, int opt, int a[], int &i);

int hlinear2(int k, int i);
int hdouble2(int k, int i);
int h1_2(int k);
int h2_2(int k);
int huniversal2(int k, int i, int a[]);
void insert2(HashNode arr[], HashNode wrd, int opt, int a[], int &i);
int search2(HashNode arr[], HashNode wrd, int opt, int a[], int &i);


int main(int argc, const char * argv[]) {

    string insertfile, searchfile;
    
    insertfile = string(argv[1]);
    searchfile = string(argv[2]);
    

    int i=0, collusion=0;
    srand(static_cast <unsigned int> (time(0)));
    
    int a[r];
    cout<< "Randomly generated 'a' numbers:";
    for (int j=0; j<r; j++)
    {
        a[j] = rand() %m;
        cout<<"    a"<<j<<": "<<a[j];
    }
    HashNode *linear, *doub, *univers;
    linear = new HashNode[m];
    doub = new HashNode[m];
    univers = new HashNode[m];
    HashNode *linear2, *doub2, *univers2;
    linear2 = new HashNode[m2];
    doub2 = new HashNode[m2];
    univers2 = new HashNode[m2];
    
    HashNode *vocabArr;
    vocabArr = new HashNode[maxsizevocab];
    
    ifstream vocabFile(insertfile);
    if (vocabFile.is_open())
    {
        while (!vocabFile.eof())
        {
            string wrd;
            getline(vocabFile, wrd, '\n');

            vocabArr[i].getnum(i);
            vocabArr[i].getval(wrd);
            i++;
        }
        
        vocabFile.close();
    }
    else
        cout<<"cannot open vocab file";
    
    i=0;
    HashNode *searchArr;
    searchArr = new HashNode[maxsizesearch];
    
    
    ifstream searchFile(searchfile);
    if (searchFile.is_open())
    {
        while (!searchFile.eof())
        {
            string wrd;
            getline(searchFile, wrd, '\n');
            
            searchArr[i].getval(wrd);
            int j=0;
            while(wrd.compare(vocabArr[j].outval()) !=0)
            {
                j++;
            }
            searchArr[i].getnum(vocabArr[j].outnum());
            i++;
        }
        
        searchFile.close();
    }
    else
        cout<<"cannot open search file";
    

    
    cout<<endl<<endl<<"\t\t\t\t\tInsertion"<<endl<<endl<<"\t\t\t Linear\t\t Double\t\t Universal"<<endl<<"m=17863\t\t";
    
    
    
    for (int t=0; t<maxsizevocab; t++) {

        int col = 0;
        insert(linear,vocabArr[t],hlin, a, col);
        collusion+= col;
    }
    cout<<collusion<<"\t\t\t";

    collusion=0;

    for (int t=0; t<maxsizevocab; t++) {

        int col =0;
        insert(doub,vocabArr[t],hdoub, a, col);
        collusion+=col;
    }
    cout<<collusion<<"\t\t\t";

    collusion=0;

    for (int t=0; t<maxsizevocab; t++) {

        int col = 0;
        insert(univers, vocabArr[t], huniv, a, col);
        collusion += col;

    }
    cout<<collusion<<endl<<"m=21929\t\t";
   
    collusion=0;
    
    for (int t=0; t<maxsizevocab; t++) {

        int col = 0;
        insert2(linear2,vocabArr[t],hlin, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizevocab; t++) {

        int col = 0;
        insert2(doub2,vocabArr[t],hdoub, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizevocab; t++) {
        int col = 0;
        insert2(univers2, vocabArr[t], huniv, a, col);
        collusion += col;
        
    }
    cout<<collusion<<endl<<endl;
    
    
    cout<<endl<<"\t\t\t\t\t Search"<<endl<<endl<<"\t\t\t Linear\t\t Double\t\t Universal"<<endl<<"m=17863\t\t";
    
    collusion =0;
    for (int t=0; t<maxsizesearch; t++) {
        int col =0;
        search(linear,searchArr[t],hlin, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizesearch; t++) {

        int col = 0;
        search(doub,searchArr[t],hdoub, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizesearch; t++) {

        int col = 0;
        search(univers, searchArr[t], huniv, a, col);
        collusion += col;
        
    }
    cout<<collusion<<endl<<"m=21929\t\t";

    
    
    
    collusion =0;
    for (int t=0; t<maxsizesearch; t++) {

        int col =0;
        search2(linear2,searchArr[t],hlin, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizesearch; t++) {

        int col = 0;
        search2(doub2,searchArr[t],hdoub, a, col);
        collusion += col;
    }
    cout<<collusion<<"\t\t\t";
    
    collusion=0;
    
    for (int t=0; t<maxsizesearch; t++) {

        int col = 0;
        search2(univers2, searchArr[t], huniv, a, col);
        collusion += col;
        
    }
    cout<<collusion<<endl<<endl;
    
    
    return 0;
}

int hlinear(int k, int i)
{
    return (k+i)%m;
}


int hdouble(int k, int i)
{
    return (h1(k) +(i * h2(k)))%m;
}

int h1(int k)
{
        return k%m;
}

int h2(int k)
{
    return p - (k%p);
}

int huniversal(int k, int i, int a[])
{

    int hval=0;
    for (int j=0; j<r; j++)
    {
        hval += (k%100)* a[j];
        k= k/100;
    }
    hval = hval % m;
    return hval;
}


void insert(HashNode arr[], HashNode wrd, int opt, int a[], int &i)
{
    int hashval = -1;
    if (opt == hlin)
    {
        hashval = hlinear(wrd.outnum(),i);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    else if (opt == hdoub)
    {
        hashval = hdouble(wrd.outnum(),i);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hdouble(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    else if (opt == huniv)
    {
        hashval = huniversal(wrd.outnum(), i, a);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    
}

int search(HashNode arr[], HashNode wrd, int opt, int a[], int &i)
{
    int hashval = -1;
    if (opt == hlin)
    {
        hashval = hlinear(wrd.outnum(),i);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
    }
    else if (opt == hdoub)
    {
        hashval = hdouble(wrd.outnum(),i);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hdouble(wrd.outnum(),i);
        }
    }
    else if (opt == huniv)
    {
        hashval = huniversal(wrd.outnum(), i, a);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
    }
    return hashval;
}

int hlinear2(int k, int i)
{
    return (k+i)%m2;
}


int hdouble2(int k, int i)
{
    return (h1_2(k) +(i * h2_2(k)))%m2;
}

int h1_2(int k)
{
    return k%m2;
}

int h2_2(int k)
{
    return p - (k%p);
}

int huniversal2(int k, int i, int a[])
{
    
    int hval=0;
    for (int j=0; j<r; j++)
    {
        hval += (k%100)* a[j];
        k= k/100;
    }
    hval = hval % m2;
    return hval;
}


void insert2(HashNode arr[], HashNode wrd, int opt, int a[], int &i)
{
    int hashval = -1;
    if (opt == hlin)
    {
        hashval = hlinear2(wrd.outnum(),i);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hlinear2(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    else if (opt == hdoub)
    {
        hashval = hdouble2(wrd.outnum(),i);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hdouble2(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    else if (opt == huniv)
    {
        hashval = huniversal2(wrd.outnum(), i, a);
        while (arr[hashval].outval().empty() != 1)
        {
            i++;
            hashval= hlinear2(wrd.outnum(),i);
        }
        arr[hashval].getval(wrd.outval());
        arr[hashval].getnum(wrd.outnum());
    }
    
}

int search2(HashNode arr[], HashNode wrd, int opt, int a[], int &i)
{

    int hashval = -1;
    if (opt == hlin)
    {
        hashval = hlinear2(wrd.outnum(),i);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
    }
    else if (opt == hdoub)
    {
        hashval = hdouble2(wrd.outnum(),i);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hdouble(wrd.outnum(),i);
        }
    }
    else if (opt == huniv)
    {
        hashval = huniversal2(wrd.outnum(), i, a);
        while (arr[hashval].outval().compare(wrd.outval())  != 0 )
        {
            i++;
            hashval= hlinear(wrd.outnum(),i);
        }
    }
    return hashval;
}


