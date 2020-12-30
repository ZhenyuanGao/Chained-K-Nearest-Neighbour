#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include<string.h>
#include<chrono>
#include<random>

using namespace std;

struct point
{
    
    string point_name;
    int y;
    int x;
};

struct edge
{
   
    double distance;
    point A;
    point B;
};
vector<vector<point>> clusters;
vector<edge> edges;
vector<edge> edges_copy;

string input;
string filename="hw6_sample_input.txt";
int number_of_points;
vector <point> real_points;
vector <int> runtimes;

double get_EU_distance(point a, point b){

    double distance  = sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));

    return distance;

}


void get_input(){
    // hold all the points.
    vector<string> points;
    // amount of times to run
    vector<string>amount;
    ifstream myfile;

    myfile.open(filename);
   

    if(myfile.is_open()){
      

        //"using getline() to read the whole file"
       while (getline(myfile, input))
        {
           
            // remove empty lines
            if(input=="\r")
                continue;
            // if  space detected, then it is a point with x,y
            if(input.find_first_of(" ")!=input.npos){
                 points.push_back(input);
            }
            // if no space detected, then, it is the k value we are putting.
             if(input.find_first_of(" ")==input.npos){
                 amount.push_back(input);
            }
        }



};
  // get the number of points.
    stringstream ss(amount[0]);
    int i;
    ss >> number_of_points;
    
// use a runtime, this global vector, to hold all of the run times from amount, local variable to global.
    for(int i=1;i<amount.size();i++){
         stringstream ss(amount[i]);
         int number;
        ss >> number;

       runtimes.push_back(number);
   }
    
     for(int i=0;i<runtimes.size();i++){
   }
   // initialize a point
    point mypoint = {"A",0,0};
   for (int i = 0;i<number_of_points;i++){
       real_points.push_back(mypoint);

   }
   string delimiter = " ";
    // seperate the x and y coordinate from a string.
      for(int i=0;i<points.size();i++){
        string a = points[i];
        real_points[i].point_name= string(a.c_str(), a.c_str() + a.find(" "));
        a=a.substr(a.find(delimiter)+1,a.size());
        stringstream ss(string( a.c_str(), a.c_str() + a.find(" ")));
         int number;
         ss >> number;
        real_points[i].y =number;
        a=a.substr(a.find(delimiter)+1,a.size());
        stringstream ss1(string( a.c_str() + a.find(" ")+1, a.c_str()+ a.size()));
         int number2;
         ss1 >> number2;
        real_points[i].x =number2;

        
     
   }
  
}
// in case the user want to input k values 
void get_user_valueK(){
    string userK;
   
    int number;
    while (userK!="0"){
        cout<<"We have already read through the file, is there additional input one would like to provide? Press 0 to quit:";

         getline(cin,userK);
          stringstream ss(userK);
          ss>>number;
          if(number>number_of_points){
              cout<<"the K values you inputed is too big, over the number of points, can not achieve.\n ";
              exit(3);
          }
        runtimes.push_back(number);

    }
   runtimes.pop_back();

   // for(int i=0;i<runtimes.size();i++){
   //     cout<<runtimes[i]<<endl;
   // }

}

//now I have a vector that holds all of the points and we need to construct the edge.
void constructEdge(){
    // this is designed to construct a edge vector.
    // get all edges between any two points.
    for(int i=0;i<real_points.size()-1;i++){
        for (int j =i+1;j<real_points.size();j++){
            edges.push_back({get_EU_distance(real_points[i],real_points[j]), real_points[i],real_points[j]});

        }
    }

 

}
// make the clusters vector, where it's size equals to the number of points, each element holds a vector.
void initlizeCluster(){
    // vector hold each point as a element
    clusters.clear();
    vector <point> appender;
    for (int i=0;i<real_points.size();i++){
        appender.push_back(real_points[i]);
        clusters.push_back(appender);
        appender.pop_back();
    }
    
}

// get the MST .
void getMST(){
    double temp = edges[0].distance;
    int index=0;
    for(int i=1;i<edges.size();i++){

        if(edges[i].distance<temp){
            temp = edges[i].distance;
            index = i;

        }



    }

}
// partition for quick sort.
int partition(int low, int high){
    double pivot = edges[high].distance;
    int i = low;
    for (int j=low; j<=high;j++){
        // get the first character of the title. for sorting, change all of them into lower case.
        if(edges[j].distance>pivot){
            swap(edges[i],edges[j]);
            i=i+1;
        }
    }
    swap(edges[i],edges[high]);
    return i;
}
// quick sort to sort all of the Euclidean distance.
void quick_sort(int low, int high){
    //when current_number_of_songs is greater than 1
    if(low<high){
         int p = partition(low, high);
         quick_sort(low,p-1);
         quick_sort(p+1,high);

    }

}
// use quicksort on the array and get the output
void call_quicksort(){
    quick_sort(0,edges.size()-1);
  
  
}
void make_comprison(int a, int b){
    // first case
    if(a!=b){
        // add all elements of b to a
        for(int i =0;i<clusters[b].size();i++){
            clusters[a].push_back(clusters[b][i]);

        }
      
        clusters.erase(clusters.begin()+b);
    }




}
void makeMST(){
    int first_index;
    int second_index;
// we currently have this cluster that holding the point number of elements.
    int size_edge = edges_copy.size();
    for(int i =0;i<clusters.size();i++){
        for(int j =0;j<clusters[i].size();j++){
         
            if(clusters[i][j].point_name==edges_copy[size_edge-1].A.point_name){
                first_index =i;
            }
    }

        for(int j =0;j<clusters[i].size();j++){
      
            if(clusters[i][j].point_name==edges_copy[size_edge-1].B.point_name){
                second_index =i;
        }
    }




    }
    make_comprison(first_index, second_index);
    edges_copy.pop_back();


 




}

void getcluster(int k){
   for(int i =0;i<edges.size();i++){
       edges_copy.push_back(edges[i]);


   }
    while(clusters.size()>k){
        makeMST();

    }



}
void print_the_result_one_iteration(){

 for(int i =0;i<clusters.size();i++){
    cout<<"    Cluster "<<i+1<<":\n";
    cout<<"    ";
     for(int j=0;j<clusters[i].size();j++){
         cout<<clusters[i][j].point_name<<" ";
         
     }
           cout<<"\n";
   

        }


}

void get_final_result(){

    for(int i=0;i<runtimes.size();i++){
        getcluster(runtimes[i]);
        cout<<"K = "<<runtimes[i]<<"\n";
        print_the_result_one_iteration();
        initlizeCluster();

       

    }




}









int main(){
    get_input();
    get_user_valueK();
    constructEdge();
    initlizeCluster();
    getMST();
    call_quicksort();
    get_final_result();
    

    return 0;
}