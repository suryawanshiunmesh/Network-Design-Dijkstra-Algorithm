// -------------------------------------------------------
// Dijkstra Algorithm :
// 1. Finding shortest path from source to all nodes and their cost
// 2. Creating routing and forwarding table
// 3. Show the complete path from source to destination which including nodes and interface
// Name: Unmesh Suryawanshi
// Net id: qd6395
// Course: CS 4590 - Computer Networks
// ----------------------------------------------------------

#include<iostream>
#define inf 99 // 99 for infinity (if there is no direct edge from source to destination
using namespace std;

// class declaration of all variables and functions
class dijks
{
    private:
        int pred[15], distance[15];
        bool mark[15]; //keep track of visited node
        int source, temp, flag, gi; // declaration of temp. variables
        char fpath[15], dest[15], path[15][15], tpath[15];
        int des;
        int aadmat[5][5] = {{0,3,99,99,6},{3,0,1,99,2},{99,1,0,2,99},{99,99,2,0,4},{6,2,99,4,0}}; // cost matrix
        int intmat[5][5] = {{99,1,99,99,0},{0,99,1,99,2},{99,0,99,1,99},{99,99,0,99,1},{0,1,99,2,99}}; // interface matrix
        int nv=5; //no. of nodes
    public: //declaration of all functions in public scope
        void read();
        void initialize();
        int unmark();
        void cald();
        void output();
        void ppath(int);
        void adest();
        void rtable();
        int finterface(int, int);
        int find_cost(int, int);
};

// function for source input
void dijks::read()
{
    cout<<endl<<" Enter the source node ";
    cout<<"(For a=0, b=1, c=2, d=3, e=4): ";
    cin>>source;
    cout<<endl;
    while((source<0) && (source>nv-1)) // for negative input value
    {
        cout<<" Enter the source node again: \n";
        cin>>source;
    }
}

// function for destination output
void dijks::adest()
{
    cout<<" Message: Routing and forwarding table are created. To see the path, ";
    cout<<endl<<endl<<" Enter the Destination node ";
    cout<<"(For a=0, b=1, c=2, d=3, e=4): ";
    cin>>des;
    cout<<endl;
    while((des<0) && (des>nv-1)) // for negative input value
    {
        cout<<" Enter the destination node again: \n";
        cin>>des;
    }
}

// function for initializing default values to variables
void dijks :: initialize()
{
    for(int i=0;i<nv;i++)
    {
        mark[i] = false;
        pred[i] = -1;
        distance[i] = inf;
    }
    distance[source]= 0;
    for(int i=0;i<nv;i++)
    {
        for(int j=0;j<nv;j++)
        {
            path[i][j]='\0';
        }
    }
}

// function for unmark node
int dijks :: unmark()
{
    int minDistance = inf;
    int cunmark;
    for(int i=0;i<nv;i++)
    {
        if((!mark[i]) && ( minDistance >= distance[i]))
        {
            minDistance = distance[i];
            cunmark = i;
        }
    }
    return cunmark;
}

//function for calculating distance
void dijks :: cald()
{
    initialize();
    int minDistance = inf;
    int cunmark;
    int count = 0;
    while(count < nv)
    {
        cunmark = unmark();
        mark[cunmark] = true;
        for(int i=0;i<nv;i++)
        {
            if((!mark[i]) && (aadmat[cunmark][i]>0) )
            {
                if(distance[i] > distance[cunmark]+aadmat[cunmark][i])
                {
                    distance[i] = distance[cunmark]+aadmat[cunmark][i];
                    pred[i] = cunmark;
                }
            }
        }
        count++;
    }
}

//function for finding path
void dijks :: ppath(int node)
{
    if(node == source)
    {
        cout<<(char)(node + 'a')<<"--"; // converting numeric value in character
        flag=1;
        tpath[gi]=(char)(node + 'a');
        gi++;
        //temp++;
    }
    else if(pred[node] == -1)
    {
        cout<<" There is no path "<<endl;
    }
    else
    {
        ppath(pred[node]);
        cout<<(char) (node + 'a')<<"--";
        dest[temp]=(char)(node + 'a');
        tpath[gi]=(char)(node + 'a');
        gi++;
        if(flag==1)
        {
            fpath[temp]=(char) (node + 'a');
            flag=0;
        }
    }
}
// function for display path from source to all nodes
void dijks :: output()
{
    cout<<endl<<" ----------------------------------------------------------------- ";
    cout<<endl<<" Path from source \""<<(char)(source + 'a')<<"\" to all nodes and total cost: "<<endl<<endl;
    int k=0;    temp=0;
    for(int i=0; i<nv; i++)
    {
        for(int j=0; j<nv; j++)
            tpath[j]='\0';
        flag=0; gi=0;
        if(i == source) // display each node in path
        {
            cout<<(char)(source + 'a')<<"--"<<(char)(source + 'a');
            tpath[gi]=(char)(source + 'a');
            fpath[temp]=(char)(source + 'a');
            dest[temp]=(char)(source + 'a');
            temp++;gi++;
        }
        else
        {
            ppath(i);
            temp++;
        }
        cout<<"> "<<distance[i]<<endl; // display distance

        for(int l=0; l<nv; l++)
        {
            path[k][l]=tpath[l];
        }
    k++;
    }
    cout<<endl<<" ----------------------------------------------------------------- ";
    cout<<endl;
}

// display function for routing and forwarding table
void dijks :: rtable()
{
    cout<<endl<<" ----------------------------------------------------------------- ";
    cout<<endl<<" Routing and forwarding table from Source \""<<(char)(source + 'a')<<"\" to destination \""<<(char)(des + 'a')<<"\" : "<<endl;
    cout<<endl<<" \t----------------------------------------- "<<endl;
    cout<<" \t| Source |"<<" Interface |"<<" Next Hope |"<<" Cost |";
    cout<<endl<<" \t----------------------------------------- "<<endl;
    int i=0,j=1, src, dst, lcost=0;

    while(path[des][j]!='\0') // display source node, next hope, outgoing interface and total cost
    {
        src=(int)(path[des][i]-'a');
        dst=(int)(path[des][j]-'a');
        lcost=lcost + find_cost(src, dst);
        cout<<" \t|   "<<path[des][i]<<"    |\t"<<finterface(src,dst)<<"    |     "<<path[des][j]<<"     |   "<<lcost<<"  |"<<endl;

        i++;j++;
    }
    cout<<" \t----------------------------------------- "<<endl;
    i=0;
    j=1;
    lcost=0;

    cout<<endl<<" Shortest Path: "<<(char)(source+ 'a');

    while(path[des][j]!='\0') // display the path and their interface
    {
        cout<<" ";
        src=(int)(path[des][i]-'a');
        dst=(int)(path[des][j]-'a');
        lcost=lcost + find_cost(src, dst);
        cout<<finterface(src,dst)<<" "<<path[des][j];

        i++;j++;
    }
    cout<<endl<<" Total Cost: "<<lcost; // display the total cost of the shortest path
    cout<<endl<<" ----------------------------------------------------------------- "<<endl<<endl;
}

// function for finding interface
int dijks :: finterface (int r, int c)
{
    return intmat[r][c];
}
// function for finding cost
int dijks :: find_cost (int r, int c)
{
    return aadmat[r][c];
}

// main function for calling all user define function
int main()
{
    dijks G;
    G.read();
    G.cald();
    G.output();
    G.adest();
    G.rtable();
    return 0;
}
