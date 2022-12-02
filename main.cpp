#include <fstream>
#include <iostream>
#include <string.h>
#include<bits/stdc++.h>
#include<unordered_map>
#include<algorithm>
using namespace std;
string Transition[5][5];
string DFA[5][5];
int sym=0;
int row=0;
char START;
char FINAL;

class Node {
public:
	string str;
	int state;
	Node* next;
	Node(string s)
	{
		str=s;
		state=1;
		next = NULL;
	}
};

class Linkedlist {
	Node* head;
public:
            Linkedlist()
            {
                head = NULL;
            }
            void insertNode(string);
             string processnext();
};
Linkedlist list1;
void Linkedlist::insertNode(string s)
{
    Node *t,*pr;
	for(t=head;t!=NULL;t=t->next)
	{
	    pr=t;
		if(t->str==s)
		return;
	}
	Node* nn = new Node(s);
	if(head==NULL)
    {
        head=nn;
    }
    else
    {
        pr->next=nn;
    }
}

string Linkedlist:: processnext()
{
    Node *curr,*pr;
	for(curr=head;curr!=NULL && curr->state==2 ;pr=curr,curr=curr->next);
	if(curr==NULL)
	return "False";
	curr->state=2;
	return curr->str;
}

int indexof(string s)
{
    int index;
    for(index=0;index<=row;index++)
    {
        if(Transition[index][0]==s)
            return index;
    }
}

int Access_initial_state(string s)
{
    int i;
    for(i=1;i<=row;i++)
        {
            if(Transition[i][0]==s)
                return i;
        }
        return -1;
}

void NFA_TO_DFA()
{
    int i,j,k;
    int rowDFA=0;
    string name;

        char t;
        string in=string(1,START);
        i=Access_initial_state(in);
        for(j=1;j<=sym;j++)
        {
                DFA[0][j]=Transition[0][j];
        }
        DFA[1][0]=in;
        list1.insertNode(in);
        do
        {
            string NEXT=list1.processnext();
            if(NEXT=="False")
                break;
            DFA[++rowDFA][0]=NEXT;

            for(j=1;j<=sym;j++)
            {
			name="";
                for(t=0;NEXT[t]!='\0';t++)
                {
                        k=indexof(string(1,NEXT[t]));
                        name+=Transition[k][j];
                }
                set <char> name_set;
                for (auto i : name)
                name_set.insert(i);
                string res="";
                for (auto const& e : name_set)
                {
                        res += e;
                }
                list1.insertNode(res);
                DFA[rowDFA][j]=res;
            }
        }while(1);
        printf("\n");
        cout<<"Transition Table of DFA"<<endl;
         for(k=0;k<=rowDFA;k++)
                {
                    if(k==1)
                        cout<<"----------------------\n";
                    for(j=0;j<=sym;j++)
                    {
                        if(k==0 && j==0)
                            cout<<"\t";
                        else
                        cout<<"{"<<DFA[k][j]<<"}\t";
                    }
                    cout<<endl;
                }
}

int main()
{
        fstream newfile;
        string tp;
        int i,j;
        newfile.open("T.txt",ios::in);
        if (newfile.is_open())
        {
                        getline(newfile, tp);
                        if(tp=="ALPHABET")
                        {
                                do
                                {
                                    getline(newfile, tp);
                                    if(tp=="STATES")
                                    break;
                                    Transition[0][++sym]=tp;

                                }while(1);
                                 cout<<"INPUT= "<<Transition[0][1]<<" "<<Transition[0][2]<<endl;
                                do
                                {
                                        getline(newfile, tp);
                                        if(tp=="START")
                                            break;
                                        Transition[++row][0]=tp;
                                }while(1);
                                do
                                {
                                        getline(newfile, tp);
                                        if(tp=="FINAL")
                                            break;
                                        START=tp[0];
                                }while(1);
                                cout<<"START = "<<START<<endl;
                                do
                                {
                                    getline(newfile, tp);
                                    if(tp=="TRANSITIONS")
                                        break;
                                    FINAL=tp[0];
                                }while(1);
                                cout<<"FINAL = "<<FINAL<<endl;
                                do
                                {
                                            getline(newfile, tp);
                                            int i=indexof(string(1,tp[0]));
                                            for(j=1;j<=sym;j++)
                                            {
                                                        if(Transition[0][j]==string(1,tp[1]))
                                                        {
                                                                Transition[i][j]=Transition[i][j] + string(1,tp[2]);
                                                                std::sort(Transition[i][j].begin(), Transition[i][j].end());
                                                                break;
                                                        }
                                            }

                                    if(tp=="END")
                                        break;
                                }while(1);
                }
                cout<<"Transition Table of NFA"<<endl;
               for(i=0;i<=row;i++)
                {
                    if(i==1)
                        cout<<"----------------------\n";
                    for(j=0;j<=sym;j++)
                    {
                        if(i==0 && j==0)
                            cout<<"\t";
                        else
                        cout<<"{"<<Transition[i][j]<<"}\t";
                    }
                    cout<<endl;
                }
                newfile.close();
            }
            NFA_TO_DFA();
}