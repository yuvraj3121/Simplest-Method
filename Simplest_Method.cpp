#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    double ans=0;
    cout<<"Number of projects : ";
    cin>>n;
    cout<<n<<endl;
    cout<<"Number of periods : ";
    cin>>m;
    cout<<m<<endl;
    double z[n];
    vector<int> v;
    double arr[m][n],sol[m],st[m][m],far[min(n,m)][min(n,m)],ear[m][n];
    memset(st,0,sizeof(st));
    cout<<"Enter the investment amount of project of each period : "<<endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>arr[i][j];
            ear[i][j]=arr[i][j];
        }
        cin>>sol[i]; 
        st[i][i]=1;
    }
    cout<<"Enter the net present value of each project : "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>z[i];
    }
    int count =0;

    // Simplex method
    while (count < min(n,m))
    {
        double inter[m],min=*max_element(sol, sol+m),max=*max_element(z, z+n);
        int index,id = find(z, z+n, max)-z;
        v.push_back(id+1);
        double mt=z[id];
        // finding the least positive intercept and the pivot row 
        for (int i = 0; i < m; i++)
        {
            inter[i]=sol[i]/arr[i][id];
            if(inter[i]>0 && inter[i]<min){
                min=inter[i];
                index=i;
            }
        }
        // pivot element
        double pit=arr[index][id];
        // dividing the pivot row elements with pivot element
        for (int i = 0; i < n; i++)
        {
            arr[index][i]=arr[index][i]/pit;
        } 
        for (int i = 0; i < m; i++)
        {
            st[index][i]=st[index][i]/pit;
        }
        sol[index]=sol[index]/pit;
        // eliminating the coefficients in the same column above and below the pivot element
        for (int i = 0; i < m; i++)
        {
            if (i==index)
            {
                continue;
            }
            double p=arr[i][id];
            sol[i]=sol[i]-sol[index]*p;
            for (int j = 0; j < n; j++)
            {
                if(arr[count][j]==0){continue;}
                arr[i][j]=arr[i][j]-arr[index][j]*p;
            }   
        }
        ans=ans+z[id]*sol[index];
        for (int i = 0; i < n; i++)
        {
            z[i]=z[i]-mt*arr[index][i];
        }
        count++;
    }
    sort(v.begin(), v.end());
    int a=0;
    for (int i = 0; i < n; i++)
    {
        if(i==(v[a]-1)){
            for (int j = 0; j < m; j++)
            {
                if(arr[j][i]<=1 && arr[j][i]>0.9){
                    for (int k = 0; k < min(n,m); k++)
                    {
                        far[k][a]=ear[k][i]*sol[j];
                    } 
                }
            }
            a++;
        }
    }
    cout<<"Number of projects : "<<n<<endl<<"Number of periods : "<<m<<endl;
    cout<<endl;
    cout<<"Projects in which company should invest to get maximum profit : "<<endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout<<"Project "<<v[i]<<endl;
        cout<<"Investment amount : "<<endl;
        for (int j = 0; j < v.size(); j++)
        {
            cout<<" In Period "<<j+1<<" : "<<far[j][i]<<endl;
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"Net Present Value of the Total Profit at the end of "<<m<<" periods : "<<ans; 
    return 0;
}