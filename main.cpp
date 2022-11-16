/*Proviamo un approccio a backtracking per il problema del calzolaio*/
// Possibili scelte, prendo o non prendo il lavoro...
#include <iostream>
#include <vector>
using namespace std;
struct lavoro{
    int i;
    int time;
    int fine;
};

void load_jobs(vector<lavoro>&);
void print_jobs(vector<lavoro>);
void fill_jobs(vector<lavoro>&);
bool work_choice(vector<lavoro> jobs,vector<vector<int>>& choices,vector<int>& current_choice,vector<bool>& bitVector); // Calcola tutte le possibili permutazioni dell'insieme
vector<int> minFineSequence(vector<lavoro>,vector<vector<int>>); //Seleziona la permutazione che riduce la multa 
int calculateFine(vector<int>,vector<lavoro>);
void printArray(vector<int>);
bool isValid(vector<bool> bitVector,int i);

int main(int argc, const char * argv[]) {
    vector<lavoro> job;
    vector<vector<int>> choices;
    vector<int> current_choice;
    vector<bool> bitVector;
    vector<int> best_choice;
    load_jobs(job);
    print_jobs(job);
    bitVector.resize(job.size());
    for(int i = 0; i<bitVector.size();i++){
        bitVector[i] = false;
    }
    work_choice(job,choices,current_choice,bitVector);
    best_choice = minFineSequence(job,choices);
    cout<<"La sequenza migliore e' "<<endl;
    printArray(best_choice);
    return 0;
}

void fill_jobs(vector<lavoro>& jobs){
    int n_job;
    lavoro valore;
    cout<<"Quanti lavori vuoi inserire ? "<<endl;
    cin>>n_job;
    for(int i = 0; i<n_job;i++){
        cout<<"Inserire il tempo: ";
        cin>>valore.time;
        cout<<"Inserire il tempo di fine: ";
        cin>>valore.fine;
        jobs.push_back(valore);
    }
}

void load_jobs(vector<lavoro>& jobs){
    lavoro job[4] = {{0,3,4},{1,1,1000},{2,2,2},{3,5,5}};
    for(int i = 0; i<4;i++){
        jobs.push_back(job[i]);
    }
}
void print_jobs(vector<lavoro> jobs){
    for(int i = 0; i<jobs.size();i++){
        cout<<jobs[i].i<<" "<<jobs[i].time<<" "<<jobs[i].fine<<" "<<endl;
    }
    cout<<endl;
}

bool work_choice(vector<lavoro> jobs,vector<vector<int>>& choices,vector<int>& current_choice,vector<bool> &bitVector){
    bool res = false;
    if(current_choice.size() == jobs.size()){
        choices.push_back(current_choice);
        return true;
    }
    for(int i = 0; i<jobs.size();i++){
        if(isValid(bitVector, i)){
            current_choice.push_back(i);
            bitVector[i] = true;
            res = work_choice(jobs, choices, current_choice, bitVector)||res;
            current_choice.pop_back();
            bitVector[i] = false;
        }
    }
    return res;
}

bool isValid(vector<bool> bitVector,int i){
    if(bitVector[i]) return false;
    return true;
}
int calculateFine(vector<int> choices,vector<lavoro> jobs){
    int time_sum = 0;
    int t_fine = 0;
    for(int i=0; i<choices.size();i++){
        time_sum += jobs[choices[i]].time;
        if(time_sum > jobs[choices[i]].time){
            t_fine += jobs[choices[i]].fine;
        }
    }
    return t_fine;
}

vector<int> minFineSequence(vector<lavoro> job,vector<vector<int>> choices){
    int min = INT_MAX;
    int curretFine;
    int selectedChoice;
    for(int i = 0; i<choices.size();i++){
        curretFine = calculateFine(choices[i], job);
        if(curretFine < min){
            min = curretFine;
            selectedChoice = i;
        }
    }
    return choices[selectedChoice];
}

void printArray(vector<int> array){
    for(int i = 0; i<array.size();i++){
        cout<<array[i]+1<<" ";
    }
    cout<<endl;
}
