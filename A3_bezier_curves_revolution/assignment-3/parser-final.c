#include <iosfwd>
#include <fstream>
#include <iostream>
using namespace std;
#include <vector>
#include<stdlib.h>
#include<string.h>
#include <cstdio>

std::fstream infile("off1.off",std::ios::in);
char data[100]; //string to read every input from file
class Mesh
{
int numVertices,numFaces,numEdges;
vector< vector<int> >vFaces;
vector< vector<float > >vVertices;
public:
Mesh(int nv,int nf,int ne)
{
	numVertices=nv;
	numFaces=nf;
	numEdges=ne;
}
void fillVertices()
{
	int k,l;	
 	float vertex_coor;
 	for(k=0;k<numVertices;k++){
 		vVertices.push_back( vector <float>());
 		}
 	for(k=0;k<numVertices;k++)
   	{
   		for(l=0;l<3;l++)
   		{
   		infile>>data;
   		vertex_coor=atof(data);
   		vVertices[k].push_back( vertex_coor);
   		}
   	}

}
void fillFaces()
{
	int l,k;
	int vf;
  	infile>>data;	//reading the first input for faces which gives no of vertices per face
   	vf=atoi(data);
   	
   	 for (l = 0; l < numFaces; l++ ) {
		vFaces.push_back ( vector<int>() );
	}
   	vFaces[0].push_back(vf);
   	int i,vf_coor;
   	for(i=1;i<vf+1;i++)
   	{
   		infile>>data;
   		vf_coor=atoi(data);
   		
   		vFaces[0].push_back(vf_coor);
   	}	
   	
   
     	for(k=1;k<numFaces;k++)
   	{
   		for(l=0;l<vf+1;l++)
   		{
   			infile>>data;
   			vf_coor=atoi(data);
   			vFaces[k].push_back(vf_coor);
   			
   		}
   	
  	 }

}

//display functs
void display_vertices()
{
		
int k,l;	
 	float vertex_coor;
 	
 	for(k=0;k<numVertices;k++)
   	{
   		for(l=0;l<3;l++)
   		{
   			cout<<vVertices[k][l]<<" ";
   		}	
   		cout<<"\n";
   	}
   }	
};

int main()
{
	char data[100];
	int vs,f,e,k,l;

   	infile>>data; 
   	if(strcmp(data,"OFF")==0)
   		cout<<"OFF file"<<endl;
 	else{
 		cout<<"Invalid file type"<<endl;
 		return 0;
 	}	
 		
   	infile>>data; 
   	vs=atoi(data);//number of vertices
      	infile>>data;
  	f=atoi(data);//number of faces 
   	infile>>data;
   	e=atoi(data);//number of edges
   	Mesh m1(vs,f,e); //object initialised
  	m1.fillVertices();
  	m1.fillFaces();   
   	cout<<"Read and filled vertices and faces"<<endl;
   	infile.close();
   	m1.display_vertices();
	return 0;
}

