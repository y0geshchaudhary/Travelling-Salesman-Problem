#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int minHamCycleCost;

void swapValues(vector<int> &arr, int i, int j) {
    int temp;
    temp = arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

void findCycles(int s, int vertexs, vector<int> &arr , vector<vector<int> > &adjacencyMatrix) {
    if(s==vertexs){
        int currentCycleCost = 0, i;
        for (i = 1; i <vertexs ; ++i) {
            currentCycleCost += adjacencyMatrix[arr[i-1]][arr[i]];
        }
        currentCycleCost += adjacencyMatrix[arr[i-1]][arr[0]];
        
        if(currentCycleCost<minHamCycleCost)
            minHamCycleCost = currentCycleCost;
        return;
    }
    else{
        for (int i = s; i <vertexs ; ++i) {
            swapValues(arr,s,i);
            findCycles(s+1,vertexs,arr,adjacencyMatrix);
            swapValues(arr,s,i);
        }
    }
}

void findMinHamiltonianCycleCost(vector<vector<int> > &adjacencyMatrix, int numOfVertexs){

    vector<int> arr(numOfVertexs);
    for (int i = 0; i < numOfVertexs; ++i) {
        arr[i]=i;
    }
    findCycles(1,numOfVertexs,arr,adjacencyMatrix);
    return;
}

int main(int argc, char *argv[]) {

    ifstream input(argv[1]);
    if (!input) {
        cout << "Unable to read input.txt file." << endl;
        return -1;
    }
    ofstream output(argv[2]);
    if (!output) {
        cout << "Unable to write to output.txt file." << endl;
        return -1;
    }

    int dataset,x,y,weight;
    input>>dataset;
    for (int i = 0; i < dataset; ++i) {
        int numOfVertex, numOfEdges;
        input>>numOfVertex>>numOfEdges;
        vector<vector<int> > adjacencyMatrix(numOfVertex);
        for (int j = 0; j < numOfVertex; ++j) {
            adjacencyMatrix[j].resize(numOfVertex);
        }
        for (int k = 0; k < numOfEdges; ++k) {
            input>>x>>y>>weight;
            adjacencyMatrix[x][y]= weight;
            adjacencyMatrix[y][x]= weight;
        }
        minHamCycleCost = INT_MAX;
        findMinHamiltonianCycleCost(adjacencyMatrix,numOfVertex);
        output<<minHamCycleCost<<endl;
    }
    return 0;
}